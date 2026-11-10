#pragma once
// Stand-alone subset of the stable LLVM C API.  When LLVM development
// headers are installed, use the upstream declarations; the fallback makes
// this coursework buildable against the system libLLVM runtime as well.
#if __has_include(<llvm-c/Core.h>) && __has_include(<llvm-c/ExecutionEngine.h>)
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#else
#include <stddef.h>
#include <stdint.h>
extern "C" {
typedef int LLVMBool;
typedef struct LLVMOpaqueContext *LLVMContextRef;
typedef struct LLVMOpaqueModule *LLVMModuleRef;
typedef struct LLVMOpaqueType *LLVMTypeRef;
typedef struct LLVMOpaqueValue *LLVMValueRef;
typedef struct LLVMOpaqueBasicBlock *LLVMBasicBlockRef;
typedef struct LLVMOpaqueBuilder *LLVMBuilderRef;
typedef struct LLVMOpaqueExecutionEngine *LLVMExecutionEngineRef;
typedef enum { LLVMAbortProcessAction = 0, LLVMPrintMessageAction = 1, LLVMReturnStatusAction = 2 } LLVMVerifierFailureAction;
typedef enum {LLVMIntEQ=32, LLVMIntNE=33, LLVMIntUGT=34, LLVMIntUGE=35, LLVMIntULT=36, LLVMIntULE=37, LLVMIntSGT=38, LLVMIntSGE=39, LLVMIntSLT=40, LLVMIntSLE=41} LLVMIntPredicate;
LLVMContextRef LLVMContextCreate(void);
void LLVMContextDispose(LLVMContextRef);
LLVMModuleRef LLVMModuleCreateWithNameInContext(const char *,LLVMContextRef);
void LLVMDisposeModule(LLVMModuleRef);
LLVMTypeRef LLVMInt32TypeInContext(LLVMContextRef);
LLVMTypeRef LLVMInt64TypeInContext(LLVMContextRef);
LLVMTypeRef LLVMVoidTypeInContext(LLVMContextRef);
LLVMTypeRef LLVMPointerType(LLVMTypeRef,unsigned);
LLVMTypeRef LLVMFunctionType(LLVMTypeRef,LLVMTypeRef *,unsigned,LLVMBool);
LLVMValueRef LLVMAddFunction(LLVMModuleRef,const char *,LLVMTypeRef);
LLVMValueRef LLVMGetNamedFunction(LLVMModuleRef,const char *);
LLVMValueRef LLVMGetParam(LLVMValueRef,unsigned);
LLVMValueRef LLVMConstInt(LLVMTypeRef,unsigned long long,LLVMBool);
LLVMBasicBlockRef LLVMAppendBasicBlockInContext(LLVMContextRef,LLVMValueRef,const char *);
LLVMBuilderRef LLVMCreateBuilderInContext(LLVMContextRef);
void LLVMDisposeBuilder(LLVMBuilderRef);
void LLVMPositionBuilderAtEnd(LLVMBuilderRef,LLVMBasicBlockRef);
LLVMValueRef LLVMBuildCall2(LLVMBuilderRef,LLVMTypeRef,LLVMValueRef,LLVMValueRef *,unsigned,const char *);
LLVMValueRef LLVMBuildLoad2(LLVMBuilderRef,LLVMTypeRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildStore(LLVMBuilderRef,LLVMValueRef,LLVMValueRef);
LLVMValueRef LLVMBuildGEP2(LLVMBuilderRef,LLVMTypeRef,LLVMValueRef,LLVMValueRef *,unsigned,const char *);
LLVMValueRef LLVMBuildAdd(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildSub(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildMul(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildSDiv(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildSRem(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildAnd(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildOr(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildShl(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildAShr(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildICmp(LLVMBuilderRef,LLVMIntPredicate,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildZExt(LLVMBuilderRef,LLVMValueRef,LLVMTypeRef,const char *);
LLVMValueRef LLVMBuildSelect(LLVMBuilderRef,LLVMValueRef,LLVMValueRef,LLVMValueRef,const char *);
LLVMValueRef LLVMBuildBr(LLVMBuilderRef,LLVMBasicBlockRef);
LLVMValueRef LLVMBuildCondBr(LLVMBuilderRef,LLVMValueRef,LLVMBasicBlockRef,LLVMBasicBlockRef);
LLVMValueRef LLVMBuildRetVoid(LLVMBuilderRef);
LLVMBool LLVMVerifyModule(LLVMModuleRef,LLVMVerifierFailureAction,char **);
LLVMBool LLVMPrintModuleToFile(LLVMModuleRef,const char *,char **);
void LLVMDisposeMessage(char *);
void LLVMLinkInMCJIT(void);
void LLVMInitializeX86TargetInfo(void);
void LLVMInitializeX86Target(void);
void LLVMInitializeX86TargetMC(void);
void LLVMInitializeX86AsmPrinter(void);
void LLVMInitializeAArch64TargetInfo(void);
void LLVMInitializeAArch64Target(void);
void LLVMInitializeAArch64TargetMC(void);
void LLVMInitializeAArch64AsmPrinter(void);
LLVMBool LLVMCreateExecutionEngineForModule(LLVMExecutionEngineRef *,LLVMModuleRef,char **);
void LLVMDisposeExecutionEngine(LLVMExecutionEngineRef);
void LLVMAddGlobalMapping(LLVMExecutionEngineRef,LLVMValueRef,void *);
uint64_t LLVMGetFunctionAddress(LLVMExecutionEngineRef,const char *);
}
#endif
