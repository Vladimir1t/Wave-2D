// Запуск сгенерированного IR логического модуля в ExecutionEngine.
//
//   ./app_ir_gen                 интерпретатор LLVM (EngineKind::Interpreter)
//   ./app_ir_gen --jit           MCJIT (EngineKind::JIT), реальная скорость
//   ./app_ir_gen --emit app.ll   дополнительно сохранить построенный IR
//
// Графические функции sim.h (simPutPixel, simFlush, simRand) не входят
// в модуль: они объявлены в нём как внешние и пробрасываются в
// ExecutionEngine на нативные реализации из sim.c.

extern "C" {
#include "../sim.h"
}
#include "app_ir_gen.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

#include <cstring>
#include <string>

using namespace llvm;

// Нативные реализации внешних функций модуля.
static void *simFunction(StringRef Name) {
  if (Name == "simPutPixel")
    return reinterpret_cast<void *>(simPutPixel);
  if (Name == "simFlush")
    return reinterpret_cast<void *>(simFlush);
  if (Name == "simRand")
    return reinterpret_cast<void *>(simRand);
  return nullptr;
}

// Интерпретатор LLVM не умеет исполнять llvm.umin/umax/smin/smax
// (IntrinsicLowering их не знает), поэтому для него они заменяются на
// эквивалентную пару icmp + select. Для JIT модуль не меняется.
static unsigned lowerMinMaxIntrinsics(Module &M) {
  SmallVector<MinMaxIntrinsic *, 16> Calls;
  for (Function &F : M)
    for (Instruction &I : instructions(F))
      if (auto *MM = dyn_cast<MinMaxIntrinsic>(&I))
        Calls.push_back(MM);
  for (MinMaxIntrinsic *MM : Calls) {
    IRBuilder<> B(MM);
    Value *Cmp = B.CreateICmp(MM->getPredicate(), MM->getLHS(), MM->getRHS());
    MM->replaceAllUsesWith(B.CreateSelect(Cmp, MM->getLHS(), MM->getRHS()));
    MM->eraseFromParent();
  }
  return Calls.size();
}

int main(int argc, char **argv) {
  bool UseJIT = false;
  const char *EmitPath = nullptr;
  for (int I = 1; I < argc; I++) {
    if (!strcmp(argv[I], "--jit"))
      UseJIT = true;
    else if (!strcmp(argv[I], "--interp"))
      UseJIT = false;
    else if (!strcmp(argv[I], "--emit") && I + 1 < argc)
      EmitPath = argv[++I];
    else {
      errs() << "usage: " << argv[0] << " [--interp | --jit] [--emit file.ll]\n";
      return 1;
    }
  }

  LLVMContext Ctx;
  auto M = std::make_unique<Module>("app.c", Ctx);
  Function *AppFunc = generateApp(*M);

  bool Broken = verifyModule(*M, &errs());
  outs() << "[VERIFICATION] " << (Broken ? "FAIL" : "OK") << '\n';
  if (Broken)
    return 1;
  if (EmitPath) {
    std::error_code EC;
    raw_fd_ostream File(EmitPath, EC, sys::fs::OF_Text);
    if (EC) {
      errs() << EmitPath << ": " << EC.message() << '\n';
      return 1;
    }
    M->print(File, nullptr);
    outs() << "[IR] written to " << EmitPath << '\n';
  }

  if (!UseJIT)
    outs() << "[Interpreter] lowered " << lowerMinMaxIntrinsics(*M)
           << " min/max intrinsics\n";

  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();

  // Внешние функции модуля до передачи владения в ExecutionEngine.
  SmallVector<std::pair<Function *, void *>, 4> Mappings;
  for (Function &F : *M)
    if (F.isDeclaration() && !F.isIntrinsic())
      if (void *Ptr = simFunction(F.getName()))
        Mappings.push_back({&F, Ptr});

  std::string Err;
  ExecutionEngine *EE =
      EngineBuilder(std::move(M))
          .setEngineKind(UseJIT ? EngineKind::JIT : EngineKind::Interpreter)
          .setErrorStr(&Err)
          .create();
  if (!EE) {
    errs() << "[EE] cannot create ExecutionEngine: " << Err << '\n';
    return 1;
  }
  for (auto &[F, Ptr] : Mappings) {
    EE->addGlobalMapping(F, Ptr);
    outs() << "[EE] " << F->getName() << " -> native\n";
  }
  EE->InstallLazyFunctionCreator([](const std::string &Name) -> void * {
    if (void *Ptr = simFunction(Name))
      return Ptr;
    // Стандартные функции (memset для llvm.memset) - из самого процесса
    if (void *Ptr = sys::DynamicLibrary::SearchForAddressOfSymbol(Name))
      return Ptr;
    errs() << "[EE] unresolved external function " << Name << '\n';
    return nullptr;
  });
  EE->finalizeObject();

  outs() << "[EE] Run @app with " << (UseJIT ? "MCJIT" : "Interpreter")
         << '\n';
  outs().flush();
  simInit();
  EE->runFunction(AppFunc, {});
  simExit();
  delete EE;
  return 0;
}
