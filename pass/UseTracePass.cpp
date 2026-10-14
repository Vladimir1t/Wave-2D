// Инструментирующий LLVM Pass: трасса использования IR-инструкций
// (User <- Operand) в рантайме.
//
// Перед каждой инструкцией-User (кроме phi) вставляется вызов
//     traceUse("<opcode User> <- <opcode Operand>")
// для каждого операнда, который сам является инструкцией. Аргументы функций,
// константы, глобальные переменные и метки базовых блоков в трассу не идут.
//
// Режим со звёздочкой (TRACE_PHI=1 при компиляции или -passes=use-trace-phi):
// операнд-phi заменяется на инструкции из операндов этого phi
// (рекурсивно, если там тоже phi). Пример: phi [%add, %sub] у shl даёт две
// записи "shl <- add" и "shl <- sub" вместо одной "shl <- phi".
//
// Пасс подключается в конец оптимизационного конвейера
// (registerOptimizerLastEPCallback), т.е. инструментируется уже
// оптимизированный -O2/-Os IR - тот же, что в app-opt.ll.

#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include <cstdlib>
#include <utility>

using namespace llvm;

namespace {

const char *LoggerName = "traceUse";

struct UseTracePass : public PassInfoMixin<UseTracePass> {
  bool ExpandPhi;
  explicit UseTracePass(bool ExpandPhi) : ExpandPhi(ExpandPhi) {}

  // Добавляет в Out инструкции, которые нужно записать как операнд V.
  // phi в режиме ExpandPhi раскрывается в свои входящие значения-инструкции;
  // Visited защищает от циклов phi -> phi, Seen - от повторов одной и той же
  // инструкции, пришедшей в phi по разным рёбрам.
  void collectOperand(Value *V, SmallVectorImpl<Instruction *> &Out,
                      SmallPtrSetImpl<PHINode *> &Visited,
                      SmallPtrSetImpl<Instruction *> &Seen) {
    auto *I = dyn_cast<Instruction>(V);
    if (!I)
      return;
    auto *Phi = dyn_cast<PHINode>(I);
    if (!ExpandPhi || !Phi) {
      if (Seen.insert(I).second)
        Out.push_back(I);
      return;
    }
    if (!Visited.insert(Phi).second)
      return;
    for (Value *In : Phi->incoming_values())
      collectOperand(In, Out, Visited, Seen);
  }

  bool isLoggerCall(Instruction &I) {
    auto *Call = dyn_cast<CallInst>(&I);
    if (!Call)
      return false;
    Function *Callee = Call->getCalledFunction();
    return Callee && Callee->getName() == LoggerName;
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
    LLVMContext &Ctx = M.getContext();
    IRBuilder<> Builder(Ctx);
    FunctionCallee Logger = M.getOrInsertFunction(
        LoggerName, FunctionType::get(Type::getVoidTy(Ctx),
                                      {PointerType::getUnqual(Ctx)}, false));

    StringMap<Value *> RecordStrings; // одна глобальная строка на пару
    size_t Sites = 0;

    for (Function &F : M) {
      if (F.isDeclaration())
        continue;

      // Сначала собираем все точки вставки, потом вставляем, чтобы не
      // обходить только что добавленные вызовы.
      SmallVector<std::pair<Instruction *, std::string>, 0> Records;
      for (BasicBlock &BB : F)
        for (Instruction &I : BB) {
          if (isa<PHINode>(I) || isLoggerCall(I))
            continue;
          for (Use &U : I.operands()) {
            SmallVector<Instruction *, 4> Ops;
            SmallPtrSet<PHINode *, 4> Visited;
            SmallPtrSet<Instruction *, 4> Seen;
            collectOperand(U.get(), Ops, Visited, Seen);
            for (Instruction *Op : Ops)
              Records.push_back({&I, std::string(I.getOpcodeName()) + " <- " +
                                         Op->getOpcodeName()});
          }
        }

      for (auto &[User, Text] : Records) {
        Builder.SetInsertPoint(User);
        Value *&Str = RecordStrings[Text];
        if (!Str)
          Str = Builder.CreateGlobalStringPtr(Text, "trace.rec");
        Builder.CreateCall(Logger, {Str});
      }
      Sites += Records.size();
    }

    errs() << "[UseTracePass] module " << M.getName() << ": " << Sites
           << " trace sites, " << RecordStrings.size()
           << " distinct records, phi expansion "
           << (ExpandPhi ? "ON" : "OFF") << '\n';
    if (verifyModule(M, &errs()))
      report_fatal_error("UseTracePass produced broken IR");
    return Sites ? PreservedAnalyses::none() : PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

bool phiExpansionFromEnv() {
  const char *Env = std::getenv("TRACE_PHI");
  return Env && Env[0] == '1';
}

} // namespace

// clang -O2 -fpass-plugin=./libUseTracePass.so app.c
//   (TRACE_PHI=1 в окружении включает раскрытие phi)
// opt -O2 -load-pass-plugin=./libUseTracePass.so -passes=use-trace app.ll
// opt -O2 -load-pass-plugin=./libUseTracePass.so -passes=use-trace-phi app.ll
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "UseTracePass", "1.0", [](PassBuilder &PB) {
            PB.registerOptimizerLastEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel) {
                  MPM.addPass(UseTracePass(phiExpansionFromEnv()));
                });
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "use-trace" || Name == "use-trace-phi") {
                    MPM.addPass(UseTracePass(Name == "use-trace-phi"));
                    return true;
                  }
                  return false;
                });
          }};
}
