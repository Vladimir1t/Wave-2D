// ir2cpp: генератор IR-генератора.
//
// Читает LLVM IR (app-opt.ll), находит функцию app и все функции, которые из
// неё вызываются (транзитивно, только прямые вызовы определённых функций),
// и печатает C++-код, который строит эти функции заново через IRBuilder.
// Стиль - как в SDL/IRGen/app_ir_gen.cpp из курса: перед каждым вызовом
// IRBuilder в комментарии стоит исходная строка IR.
//
//   ./ir2cpp app-opt.ll app > irgen/app_ir_gen.cpp
//
// Порядок генерации внутри функции:
//   1) все базовые блоки создаются заранее в исходном порядке;
//   2) инструкции строятся с обходом блоков в обратном постпорядке (RPO),
//      поэтому определение любого не-phi операнда уже построено;
//   3) входящие значения phi добавляются в конце функции.
// Метаданные (!tbaa, !llvm.loop) и атрибуты параметров не переносятся:
// на семантику программы они не влияют.

#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/ModuleSlotTracker.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include <map>
#include <string>

using namespace llvm;

namespace {

[[noreturn]] void fail(const Twine &Msg) {
  errs() << "ir2cpp: " << Msg << '\n';
  exit(1);
}

std::string ident(StringRef Name) {
  std::string S;
  for (char C : Name)
    S += isalnum((unsigned char)C) ? C : '_';
  return S;
}

class Emitter {
  Module &M;
  raw_ostream &OS;
  ModuleSlotTracker MST;
  std::map<const Value *, std::string> Names;

public:
  Emitter(Module &M, raw_ostream &OS) : M(M), OS(OS), MST(&M) {}

  std::string funcVar(const Function *F) { return "fn_" + ident(F->getName()); }

  std::string type(Type *T) {
    if (T->isVoidTy())
      return "B.getVoidTy()";
    if (T->isPointerTy())
      return "B.getPtrTy()";
    if (auto *IT = dyn_cast<IntegerType>(T)) {
      unsigned W = IT->getBitWidth();
      if (W == 1 || W == 8 || W == 16 || W == 32 || W == 64)
        return "B.getInt" + std::to_string(W) + "Ty()";
      return "B.getIntNTy(" + std::to_string(W) + ")";
    }
    if (auto *VT = dyn_cast<FixedVectorType>(T))
      return "FixedVectorType::get(" + type(VT->getElementType()) + ", " +
             std::to_string(VT->getNumElements()) + ")";
    if (auto *AT = dyn_cast<ArrayType>(T))
      return "ArrayType::get(" + type(AT->getElementType()) + ", " +
             std::to_string(AT->getNumElements()) + ")";
    if (auto *FT = dyn_cast<FunctionType>(T)) {
      std::string S = "FunctionType::get(" + type(FT->getReturnType()) + ", {";
      for (unsigned I = 0; I < FT->getNumParams(); I++)
        S += (I ? ", " : "") + type(FT->getParamType(I));
      return S + "}, " + (FT->isVarArg() ? "true" : "false") + ")";
    }
    std::string Str;
    raw_string_ostream SS(Str);
    T->print(SS);
    fail("unsupported type " + SS.str());
  }

  std::string constInt(const ConstantInt *C) {
    unsigned W = C->getBitWidth();
    if (W == 1)
      return std::string("B.getInt1(") + (C->isOne() ? "true" : "false") + ")";
    std::string V = std::to_string(C->getSExtValue());
    if (W == 64)
      return "B.getInt64(" + V + "LL)";
    if (W == 8 || W == 16 || W == 32)
      return "B.getInt" + std::to_string(W) + "(" + V + ")";
    return "ConstantInt::get(" + type(C->getType()) + ", " + V + ", true)";
  }

  std::string value(const Value *V) {
    auto It = Names.find(V);
    if (It != Names.end())
      return It->second;
    if (auto *F = dyn_cast<Function>(V))
      return funcVar(F);
    if (auto *C = dyn_cast<ConstantInt>(V))
      return constInt(C);
    if (isa<PoisonValue>(V))
      return "PoisonValue::get(" + type(V->getType()) + ")";
    if (isa<UndefValue>(V))
      return "UndefValue::get(" + type(V->getType()) + ")";
    if (isa<ConstantAggregateZero>(V) || isa<ConstantPointerNull>(V))
      return "Constant::getNullValue(" + type(V->getType()) + ")";
    if (auto *C = dyn_cast<Constant>(V)) {
      if (auto *VT = dyn_cast<FixedVectorType>(C->getType())) {
        if (Constant *Splat = C->getSplatValue())
          return "ConstantVector::getSplat(ElementCount::getFixed(" +
                 std::to_string(VT->getNumElements()) + "), " + value(Splat) +
                 ")";
        std::string S = "ConstantVector::get({";
        for (unsigned I = 0; I < VT->getNumElements(); I++)
          S += (I ? ", " : "") + value(C->getAggregateElement(I));
        return S + "})";
      }
    }
    std::string Str;
    raw_string_ostream SS(Str);
    V->print(SS);
    fail("unsupported operand: " + SS.str());
  }

  std::string slotName(const Value *V, const char *Prefix) {
    if (V->hasName())
      return std::string(Prefix) + "_" + ident(V->getName());
    int Slot = MST.getLocalSlot(V);
    if (Slot < 0)
      fail("value without slot");
    return Prefix + std::to_string(Slot);
  }

  static SmallVector<StringRef, 4> split(StringRef S) {
    SmallVector<StringRef, 4> Lines;
    S.split(Lines, '\n', -1, false);
    return Lines;
  }

  std::string irText(const Instruction &I) {
    std::string Str;
    raw_string_ostream SS(Str);
    I.print(SS, MST);
    SS.flush();
    size_t Md = Str.find(", !");
    if (Md != std::string::npos)
      Str.resize(Md);
    // Многострочные инструкции (switch) - каждая строка своим комментарием
    std::string Out;
    for (StringRef Line : split(Str))
      Out += (Out.empty() ? "" : "\n  // ") + Line.trim().str();
    return Out;
  }

  std::string ops(const Instruction &I, unsigned From = 0) {
    std::string S;
    for (unsigned K = From; K < I.getNumOperands(); K++)
      S += (K > From ? ", " : "") + value(I.getOperand(K));
    return S;
  }

  std::string alignOf(MaybeAlign A) {
    return "MaybeAlign(" + std::to_string(A ? A->value() : 0) + ")";
  }

  // Строка C++ для одной инструкции. Пусто для phi, у которых входы
  // дописываются в конце функции.
  void emitInstruction(const Instruction &I) {
    OS << "  // " << irText(I) << '\n';
    std::string Res;
    if (!I.getType()->isVoidTy()) {
      Res = slotName(&I, "v");
      Names[&I] = Res;
    }
    std::string Decl = "  Value *" + Res + " = ";

    if (auto *BO = dyn_cast<BinaryOperator>(&I)) {
      std::string A = value(BO->getOperand(0)), Bv = value(BO->getOperand(1));
      std::string Op = BO->getOpcodeName();
      auto boolStr = [](bool X) { return X ? "true" : "false"; };
      switch (BO->getOpcode()) {
      case Instruction::Add:
      case Instruction::Sub:
      case Instruction::Mul:
      case Instruction::Shl: {
        std::string Fn = Op == "add"   ? "CreateAdd"
                         : Op == "sub" ? "CreateSub"
                         : Op == "mul" ? "CreateMul"
                                       : "CreateShl";
        OS << Decl << "B." << Fn << "(" << A << ", " << Bv;
        if (BO->hasNoUnsignedWrap() || BO->hasNoSignedWrap())
          OS << ", \"\", " << boolStr(BO->hasNoUnsignedWrap()) << ", "
             << boolStr(BO->hasNoSignedWrap());
        OS << ");\n";
        break;
      }
      case Instruction::SDiv:
      case Instruction::UDiv:
      case Instruction::LShr:
      case Instruction::AShr: {
        std::string Fn = Op == "sdiv"   ? "CreateSDiv"
                         : Op == "udiv" ? "CreateUDiv"
                         : Op == "lshr" ? "CreateLShr"
                                        : "CreateAShr";
        OS << Decl << "B." << Fn << "(" << A << ", " << Bv;
        if (BO->isExact())
          OS << ", \"\", true";
        OS << ");\n";
        break;
      }
      case Instruction::Or:
        OS << Decl << "B.CreateOr(" << A << ", " << Bv << ");\n";
        if (cast<PossiblyDisjointInst>(BO)->isDisjoint())
          OS << "  cast<PossiblyDisjointInst>(" << Res
             << ")->setIsDisjoint(true);\n";
        break;
      case Instruction::And:
      case Instruction::Xor:
      case Instruction::SRem:
      case Instruction::URem: {
        std::string Fn = Op == "and"    ? "CreateAnd"
                         : Op == "xor"  ? "CreateXor"
                         : Op == "srem" ? "CreateSRem"
                                        : "CreateURem";
        OS << Decl << "B." << Fn << "(" << A << ", " << Bv << ");\n";
        break;
      }
      default:
        fail(std::string("unsupported binary operator: ") + Op);
      }
      return;
    }
    if (auto *Cmp = dyn_cast<ICmpInst>(&I)) {
      OS << Decl << "B.CreateICmp(CmpInst::ICMP_"
         << StringRef(CmpInst::getPredicateName(Cmp->getPredicate())).upper()
         << ", " << ops(I) << ");\n";
      return;
    }
    if (isa<SelectInst>(I)) {
      OS << Decl << "B.CreateSelect(" << ops(I) << ");\n";
      return;
    }
    if (auto *Cast = dyn_cast<CastInst>(&I)) {
      const char *Op = Cast->getOpcodeName();
      std::string Fn = std::string("Create") + (char)toupper(Op[0]) + (Op + 1);
      if (Cast->getOpcode() == Instruction::ZExt)
        Fn = "CreateZExt";
      else if (Cast->getOpcode() == Instruction::SExt)
        Fn = "CreateSExt";
      OS << Decl << "B." << Fn << "(" << value(Cast->getOperand(0)) << ", "
         << type(Cast->getType()) << ");\n";
      if (auto *NN = dyn_cast<PossiblyNonNegInst>(Cast); NN && NN->hasNonNeg())
        OS << "  cast<PossiblyNonNegInst>(" << Res << ")->setNonNeg(true);\n";
      return;
    }
    if (auto *LI = dyn_cast<LoadInst>(&I)) {
      OS << Decl << "B.CreateAlignedLoad(" << type(LI->getType()) << ", "
         << value(LI->getPointerOperand()) << ", " << alignOf(LI->getAlign())
         << ");\n";
      return;
    }
    if (auto *SI = dyn_cast<StoreInst>(&I)) {
      OS << "  B.CreateAlignedStore(" << value(SI->getValueOperand()) << ", "
         << value(SI->getPointerOperand()) << ", " << alignOf(SI->getAlign())
         << ");\n";
      return;
    }
    if (auto *GEP = dyn_cast<GetElementPtrInst>(&I)) {
      OS << Decl << "B.CreateGEP(" << type(GEP->getSourceElementType()) << ", "
         << value(GEP->getPointerOperand()) << ", {" << ops(I, 1) << "}, \"\", "
         << (GEP->isInBounds() ? "true" : "false") << ");\n";
      return;
    }
    if (auto *AI = dyn_cast<AllocaInst>(&I)) {
      OS << "  AllocaInst *" << Res << " = B.CreateAlloca("
         << type(AI->getAllocatedType()) << ");\n";
      OS << "  " << Res << "->setAlignment(Align(" << AI->getAlign().value()
         << "));\n";
      return;
    }
    if (auto *Phi = dyn_cast<PHINode>(&I)) {
      OS << "  PHINode *" << Res << " = B.CreatePHI(" << type(Phi->getType())
         << ", " << Phi->getNumIncomingValues() << ");\n";
      return;
    }
    if (auto *Call = dyn_cast<CallInst>(&I)) {
      Function *Callee = Call->getCalledFunction();
      if (!Callee)
        fail("indirect calls are not supported");
      std::string Call_ = "B.CreateCall(" + funcVar(Callee) + ", {";
      for (unsigned K = 0; K < Call->arg_size(); K++)
        Call_ += (K ? ", " : "") + value(Call->getArgOperand(K));
      Call_ += "})";
      if (Res.empty()) {
        OS << "  " << Call_ << (Call->isTailCall() ? "->setTailCall()" : "")
           << ";\n";
      } else {
        OS << "  CallInst *" << Res << " = " << Call_ << ";\n";
        if (Call->isTailCall())
          OS << "  " << Res << "->setTailCall();\n";
      }
      return;
    }
    if (auto *Br = dyn_cast<BranchInst>(&I)) {
      if (Br->isUnconditional())
        OS << "  B.CreateBr(" << value(Br->getSuccessor(0)) << ");\n";
      else
        OS << "  B.CreateCondBr(" << value(Br->getCondition()) << ", "
           << value(Br->getSuccessor(0)) << ", " << value(Br->getSuccessor(1))
           << ");\n";
      return;
    }
    if (auto *Sw = dyn_cast<SwitchInst>(&I)) {
      std::string Var = "sw" + std::to_string(Tmp++);
      OS << "  SwitchInst *" << Var << " = B.CreateSwitch("
         << value(Sw->getCondition()) << ", " << value(Sw->getDefaultDest())
         << ", " << Sw->getNumCases() << ");\n";
      for (auto &Case : Sw->cases())
        OS << "  " << Var << "->addCase(" << value(Case.getCaseValue()) << ", "
           << value(Case.getCaseSuccessor()) << ");\n";
      return;
    }
    if (auto *Ret = dyn_cast<ReturnInst>(&I)) {
      if (Ret->getReturnValue())
        OS << "  B.CreateRet(" << value(Ret->getReturnValue()) << ");\n";
      else
        OS << "  B.CreateRetVoid();\n";
      return;
    }
    if (auto *SV = dyn_cast<ShuffleVectorInst>(&I)) {
      OS << Decl << "B.CreateShuffleVector(" << value(SV->getOperand(0))
         << ", " << value(SV->getOperand(1)) << ", ArrayRef<int>{";
      ArrayRef<int> Mask = SV->getShuffleMask();
      for (unsigned K = 0; K < Mask.size(); K++)
        OS << (K ? ", " : "") << Mask[K];
      OS << "});\n";
      return;
    }
    if (isa<InsertElementInst>(I)) {
      OS << Decl << "B.CreateInsertElement(" << ops(I) << ");\n";
      return;
    }
    if (isa<ExtractElementInst>(I)) {
      OS << Decl << "B.CreateExtractElement(" << ops(I) << ");\n";
      return;
    }
    fail(std::string("unsupported instruction: ") + I.getOpcodeName());
  }

  void emitFunction(Function &F) {
    MST.incorporateFunction(F);
    Names.clear();
    OS << "\n// " << F.getName() << "\n";
    OS << "void build_" << ident(F.getName()) << "(IRBuilder<> &B, "
       << "Function *F) {\n";
    OS << "  LLVMContext &Ctx = B.getContext();\n";
    for (Argument &A : F.args()) {
      std::string N = slotName(&A, "v");
      Names[&A] = N;
      OS << "  Value *" << N << " = F->getArg(" << A.getArgNo() << ");\n";
    }
    OS << "\n  // Базовые блоки в исходном порядке\n";
    for (BasicBlock &BB : F) {
      std::string N = slotName(&BB, "bb");
      Names[&BB] = N;
      OS << "  BasicBlock *" << N << " = BasicBlock::Create(Ctx, \"\", F);\n";
    }

    ReversePostOrderTraversal<Function *> RPO(&F);
    for (BasicBlock *BB : RPO) {
      std::string Str;
      raw_string_ostream SS(Str);
      BB->printAsOperand(SS, false, MST);
      OS << "\n  // " << SS.str().substr(1) << ":\n";
      OS << "  B.SetInsertPoint(" << Names[BB] << ");\n";
      for (Instruction &I : *BB)
        emitInstruction(I);
    }

    bool HasPhi = false;
    for (BasicBlock &BB : F)
      for (PHINode &Phi : BB.phis()) {
        if (!HasPhi)
          OS << "\n  // Входящие значения phi\n";
        HasPhi = true;
        for (unsigned K = 0; K < Phi.getNumIncomingValues(); K++)
          OS << "  " << Names[&Phi] << "->addIncoming("
             << value(Phi.getIncomingValue(K)) << ", "
             << value(Phi.getIncomingBlock(K)) << ");\n";
      }
    OS << "}\n";
  }

  void run(StringRef Root, StringRef Input) {
    Function *RootF = M.getFunction(Root);
    if (!RootF || RootF->isDeclaration())
      fail("no definition of @" + Root);

    // Функции, достижимые из Root по прямым вызовам.
    SetVector<Function *> Defined, Declared;
    SmallVector<Function *, 8> Work{RootF};
    Defined.insert(RootF);
    while (!Work.empty()) {
      Function *F = Work.pop_back_val();
      for (Instruction &I : instructions(F))
        if (auto *Call = dyn_cast<CallInst>(&I))
          if (Function *Callee = Call->getCalledFunction()) {
            if (Callee->isDeclaration())
              Declared.insert(Callee);
            else if (Defined.insert(Callee))
              Work.push_back(Callee);
          }
    }
    // Порядок как в исходном модуле
    SmallVector<Function *, 8> Defs, Decls;
    for (Function &F : M) {
      if (Defined.count(&F))
        Defs.push_back(&F);
      else if (Declared.count(&F))
        Decls.push_back(&F);
    }

    OS << "// СГЕНЕРИРОВАНО irgen/ir2cpp из " << Input
       << " - не редактировать вручную.\n"
          "// Строит функции логического модуля, вызываемые при исполнении:\n"
          "//  ";
    for (Function *F : Defs)
      OS << " @" << F->getName();
    OS << "\n// Не попали (встроены при -O2, во время исполнения не "
          "вызываются):\n//  ";
    for (Function &F : M)
      if (!F.isDeclaration() && !Defined.count(&F))
        OS << " @" << F.getName();
    OS << "\n\n#include \"app_ir_gen.h\"\n\n"
          "#include \"llvm/IR/Constants.h\"\n"
          "#include \"llvm/IR/IRBuilder.h\"\n"
          "#include \"llvm/IR/Instructions.h\"\n\n"
          "using namespace llvm;\n\n"
          "namespace {\n";

    // Глобальные указатели на функции модуля, чтобы тела могли ссылаться
    // на любые функции независимо от порядка построения.
    OS << "\n";
    for (Function *F : Decls)
      OS << "Function *" << funcVar(F) << ";\n";
    for (Function *F : Defs)
      OS << "Function *" << funcVar(F) << ";\n";

    for (Function *F : Defs)
      emitFunction(*F);

    OS << "\n} // namespace\n\n"
          "Function *generateApp(Module &M) {\n"
          "  IRBuilder<> B(M.getContext());\n\n"
          "  // Внешние функции: графический интерфейс sim.h и интринсики\n";
    for (Function *F : Decls) {
      OS << "  // " << *F->getFunctionType() << " @" << F->getName() << '\n';
      OS << "  " << funcVar(F) << " = Function::Create("
         << type(F->getFunctionType()) << ", Function::ExternalLinkage, \""
         << F->getName() << "\", M);\n";
    }
    OS << "\n  // Функции логического модуля\n";
    for (Function *F : Defs) {
      OS << "  " << funcVar(F) << " = Function::Create("
         << type(F->getFunctionType()) << ", Function::ExternalLinkage, \""
         << F->getName() << "\", M);\n";
      if (F->isDSOLocal())
        OS << "  " << funcVar(F) << "->setDSOLocal(true);\n";
    }
    OS << '\n';
    for (Function *F : Defs)
      OS << "  build_" << ident(F->getName()) << "(B, " << funcVar(F)
         << ");\n";
    OS << "  return " << funcVar(RootF) << ";\n}\n";
  }

private:
  unsigned Tmp = 0;
};

} // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    errs() << "usage: ir2cpp <input.ll> <root function>\n";
    return 1;
  }
  LLVMContext Ctx;
  SMDiagnostic Err;
  std::unique_ptr<Module> M = parseIRFile(argv[1], Err, Ctx);
  if (!M) {
    Err.print(argv[0], errs());
    return 1;
  }
  Emitter(*M, outs()).run(argv[2], argv[1]);
  return 0;
}
