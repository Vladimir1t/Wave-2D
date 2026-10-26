// СГЕНЕРИРОВАНО irgen/ir2cpp из app-opt.ll - не редактировать вручную.
// Строит функции логического модуля, вызываемые при исполнении:
//   @putCell @drawFrame @app
// Не попали (встроены при -O2, во время исполнения не вызываются):
//   @clamp255 @isInsideCircle @initPool @addDrop @waveStep @waterColor

#include "app_ir_gen.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

namespace {

Function *fn_llvm_lifetime_start_p0;
Function *fn_simPutPixel;
Function *fn_llvm_memset_p0_i64;
Function *fn_simRand;
Function *fn_simFlush;
Function *fn_llvm_umin_i32;
Function *fn_putCell;
Function *fn_drawFrame;
Function *fn_app;

// putCell
void build_putCell(IRBuilder<> &B, Function *F) {
  LLVMContext &Ctx = B.getContext();
  Value *v0 = F->getArg(0);
  Value *v1 = F->getArg(1);
  Value *v2 = F->getArg(2);

  // Базовые блоки в исходном порядке
  BasicBlock *bb3 = BasicBlock::Create(Ctx, "", F);

  // 3:
  B.SetInsertPoint(bb3);
  // %4 = mul nsw i32 %0, 3
  Value *v4 = B.CreateMul(v0, B.getInt32(3), "", false, true);
  // %5 = mul nsw i32 %1, 3
  Value *v5 = B.CreateMul(v1, B.getInt32(3), "", false, true);
  // tail call void @simPutPixel(i32 noundef %4, i32 noundef %5, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v4, v5, v2})->setTailCall();
  // %6 = add nsw i32 %4, 1
  Value *v6 = B.CreateAdd(v4, B.getInt32(1), "", false, true);
  // tail call void @simPutPixel(i32 noundef %6, i32 noundef %5, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v6, v5, v2})->setTailCall();
  // %7 = add nsw i32 %4, 2
  Value *v7 = B.CreateAdd(v4, B.getInt32(2), "", false, true);
  // tail call void @simPutPixel(i32 noundef %7, i32 noundef %5, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v7, v5, v2})->setTailCall();
  // %8 = add nsw i32 %5, 1
  Value *v8 = B.CreateAdd(v5, B.getInt32(1), "", false, true);
  // tail call void @simPutPixel(i32 noundef %4, i32 noundef %8, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v4, v8, v2})->setTailCall();
  // tail call void @simPutPixel(i32 noundef %6, i32 noundef %8, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v6, v8, v2})->setTailCall();
  // tail call void @simPutPixel(i32 noundef %7, i32 noundef %8, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v7, v8, v2})->setTailCall();
  // %9 = add nsw i32 %5, 2
  Value *v9 = B.CreateAdd(v5, B.getInt32(2), "", false, true);
  // tail call void @simPutPixel(i32 noundef %4, i32 noundef %9, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v4, v9, v2})->setTailCall();
  // tail call void @simPutPixel(i32 noundef %6, i32 noundef %9, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v6, v9, v2})->setTailCall();
  // tail call void @simPutPixel(i32 noundef %7, i32 noundef %9, i32 noundef %2) #10
  B.CreateCall(fn_simPutPixel, {v7, v9, v2})->setTailCall();
  // ret void
  B.CreateRetVoid();
}

// drawFrame
void build_drawFrame(IRBuilder<> &B, Function *F) {
  LLVMContext &Ctx = B.getContext();
  Value *v0 = F->getArg(0);
  Value *v1 = F->getArg(1);
  Value *v2 = F->getArg(2);
  Value *v3 = F->getArg(3);
  Value *v4 = F->getArg(4);

  // Базовые блоки в исходном порядке
  BasicBlock *bb5 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb6 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb13 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb14 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb17 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb23 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb54 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb65 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb67 = BasicBlock::Create(Ctx, "", F);

  // 5:
  B.SetInsertPoint(bb5);
  // br label %6
  B.CreateBr(bb6);

  // 6:
  B.SetInsertPoint(bb6);
  // %7 = phi i64 [ 0, %5 ], [ %15, %14 ]
  PHINode *v7 = B.CreatePHI(B.getInt64Ty(), 2);
  // %8 = shl nuw nsw i64 %7, 9
  Value *v8 = B.CreateShl(v7, B.getInt64(9LL), "", true, true);
  // %9 = trunc i64 %7 to i32
  Value *v9 = B.CreateTrunc(v7, B.getInt32Ty());
  // %10 = sub i32 %9, %4
  Value *v10 = B.CreateSub(v9, v4);
  // %11 = mul nsw i32 %10, %10
  Value *v11 = B.CreateMul(v10, v10, "", false, true);
  // %12 = trunc i64 %7 to i32
  Value *v12 = B.CreateTrunc(v7, B.getInt32Ty());
  // br label %17
  B.CreateBr(bb17);

  // 17:
  B.SetInsertPoint(bb17);
  // %18 = phi i64 [ 0, %6 ], [ %68, %67 ]
  PHINode *v18 = B.CreatePHI(B.getInt64Ty(), 2);
  // %19 = add nuw nsw i64 %18, %8
  Value *v19 = B.CreateAdd(v18, v8, "", true, true);
  // %20 = getelementptr inbounds i32, ptr %1, i64 %19
  Value *v20 = B.CreateGEP(B.getInt32Ty(), v1, {v19}, "", true);
  // %21 = load i32, ptr %20, align 4
  Value *v21 = B.CreateAlignedLoad(B.getInt32Ty(), v20, MaybeAlign(4));
  // %22 = icmp eq i32 %21, 0
  Value *v22 = B.CreateICmp(CmpInst::ICMP_EQ, v21, B.getInt32(0));
  // br i1 %22, label %54, label %23
  B.CreateCondBr(v22, bb54, bb23);

  // 23:
  B.SetInsertPoint(bb23);
  // %24 = getelementptr i32, ptr %0, i64 %19
  Value *v24 = B.CreateGEP(B.getInt32Ty(), v0, {v19}, "", false);
  // %25 = getelementptr i32, ptr %24, i64 -1
  Value *v25 = B.CreateGEP(B.getInt32Ty(), v24, {B.getInt64(-1LL)}, "", false);
  // %26 = load i32, ptr %25, align 4
  Value *v26 = B.CreateAlignedLoad(B.getInt32Ty(), v25, MaybeAlign(4));
  // %27 = getelementptr i32, ptr %24, i64 1
  Value *v27 = B.CreateGEP(B.getInt32Ty(), v24, {B.getInt64(1LL)}, "", false);
  // %28 = load i32, ptr %27, align 4
  Value *v28 = B.CreateAlignedLoad(B.getInt32Ty(), v27, MaybeAlign(4));
  // %29 = getelementptr i32, ptr %24, i64 -512
  Value *v29 = B.CreateGEP(B.getInt32Ty(), v24, {B.getInt64(-512LL)}, "", false);
  // %30 = load i32, ptr %29, align 4
  Value *v30 = B.CreateAlignedLoad(B.getInt32Ty(), v29, MaybeAlign(4));
  // %31 = getelementptr i32, ptr %24, i64 512
  Value *v31 = B.CreateGEP(B.getInt32Ty(), v24, {B.getInt64(512LL)}, "", false);
  // %32 = load i32, ptr %31, align 4
  Value *v32 = B.CreateAlignedLoad(B.getInt32Ty(), v31, MaybeAlign(4));
  // %33 = add i32 %26, %30
  Value *v33 = B.CreateAdd(v26, v30);
  // %34 = add i32 %28, %32
  Value *v34 = B.CreateAdd(v28, v32);
  // %35 = sub i32 %33, %34
  Value *v35 = B.CreateSub(v33, v34);
  // %36 = ashr i32 %35, 2
  Value *v36 = B.CreateAShr(v35, B.getInt32(2));
  // %37 = add nsw i32 %36, 90
  Value *v37 = B.CreateAdd(v36, B.getInt32(90), "", false, true);
  // %38 = load i32, ptr %24, align 4
  Value *v38 = B.CreateAlignedLoad(B.getInt32Ty(), v24, MaybeAlign(4));
  // %39 = ashr i32 %38, 4
  Value *v39 = B.CreateAShr(v38, B.getInt32(4));
  // %40 = add nsw i32 %37, %39
  Value *v40 = B.CreateAdd(v37, v39, "", false, true);
  // %41 = icmp slt i32 %40, 0
  Value *v41 = B.CreateICmp(CmpInst::ICMP_SLT, v40, B.getInt32(0));
  // %42 = tail call i32 @llvm.umin.i32(i32 %40, i32 255)
  CallInst *v42 = B.CreateCall(fn_llvm_umin_i32, {v40, B.getInt32(255)});
  v42->setTailCall();
  // %43 = select i1 %41, i32 0, i32 %42
  Value *v43 = B.CreateSelect(v41, B.getInt32(0), v42);
  // %44 = mul nuw nsw i32 %43, %43
  Value *v44 = B.CreateMul(v43, v43, "", true, true);
  // %45 = mul nuw nsw i32 %44, %43
  Value *v45 = B.CreateMul(v44, v43, "", true, true);
  // %46 = and i32 %45, 16711680
  Value *v46 = B.CreateAnd(v45, B.getInt32(16711680));
  // %47 = lshr i32 %44, 8
  Value *v47 = B.CreateLShr(v44, B.getInt32(8));
  // %48 = tail call i32 @llvm.umin.i32(i32 %47, i32 225)
  CallInst *v48 = B.CreateCall(fn_llvm_umin_i32, {v47, B.getInt32(225)});
  v48->setTailCall();
  // %49 = tail call i32 @llvm.umin.i32(i32 %43, i32 175)
  CallInst *v49 = B.CreateCall(fn_llvm_umin_i32, {v43, B.getInt32(175)});
  v49->setTailCall();
  // %50 = shl nuw nsw i32 %48, 8
  Value *v50 = B.CreateShl(v48, B.getInt32(8), "", true, true);
  // %51 = add nuw nsw i32 %49, -16769456
  Value *v51 = B.CreateAdd(v49, B.getInt32(-16769456), "", true, true);
  // %52 = or disjoint i32 %51, %46
  Value *v52 = B.CreateOr(v51, v46);
  cast<PossiblyDisjointInst>(v52)->setIsDisjoint(true);
  // %53 = add nuw nsw i32 %52, %50
  Value *v53 = B.CreateAdd(v52, v50, "", true, true);
  // br label %54
  B.CreateBr(bb54);

  // 54:
  B.SetInsertPoint(bb54);
  // %55 = phi i32 [ %53, %23 ], [ -3626642, %17 ]
  PHINode *v55 = B.CreatePHI(B.getInt32Ty(), 2);
  // %56 = trunc i64 %18 to i32
  Value *v56 = B.CreateTrunc(v18, B.getInt32Ty());
  // %57 = sub i32 %56, %3
  Value *v57 = B.CreateSub(v56, v3);
  // %58 = mul nsw i32 %57, %57
  Value *v58 = B.CreateMul(v57, v57, "", false, true);
  // %59 = add nuw nsw i32 %58, %11
  Value *v59 = B.CreateAdd(v58, v11, "", true, true);
  // %60 = icmp ugt i32 %59, 3
  Value *v60 = B.CreateICmp(CmpInst::ICMP_UGT, v59, B.getInt32(3));
  // %61 = select i1 %60, i32 %55, i32 -44992
  Value *v61 = B.CreateSelect(v60, v55, B.getInt32(-44992));
  // %62 = getelementptr inbounds i32, ptr %2, i64 %19
  Value *v62 = B.CreateGEP(B.getInt32Ty(), v2, {v19}, "", true);
  // %63 = load i32, ptr %62, align 4
  Value *v63 = B.CreateAlignedLoad(B.getInt32Ty(), v62, MaybeAlign(4));
  // %64 = icmp eq i32 %61, %63
  Value *v64 = B.CreateICmp(CmpInst::ICMP_EQ, v61, v63);
  // br i1 %64, label %67, label %65
  B.CreateCondBr(v64, bb67, bb65);

  // 65:
  B.SetInsertPoint(bb65);
  // store i32 %61, ptr %62, align 4
  B.CreateAlignedStore(v61, v62, MaybeAlign(4));
  // %66 = trunc i64 %18 to i32
  Value *v66 = B.CreateTrunc(v18, B.getInt32Ty());
  // tail call void @putCell(i32 noundef %66, i32 noundef %12, i32 noundef %61)
  B.CreateCall(fn_putCell, {v66, v12, v61})->setTailCall();
  // br label %67
  B.CreateBr(bb67);

  // 67:
  B.SetInsertPoint(bb67);
  // %68 = add nuw nsw i64 %18, 1
  Value *v68 = B.CreateAdd(v18, B.getInt64(1LL), "", true, true);
  // %69 = icmp eq i64 %68, 512
  Value *v69 = B.CreateICmp(CmpInst::ICMP_EQ, v68, B.getInt64(512LL));
  // br i1 %69, label %14, label %17
  B.CreateCondBr(v69, bb14, bb17);

  // 14:
  B.SetInsertPoint(bb14);
  // %15 = add nuw nsw i64 %7, 1
  Value *v15 = B.CreateAdd(v7, B.getInt64(1LL), "", true, true);
  // %16 = icmp eq i64 %15, 256
  Value *v16 = B.CreateICmp(CmpInst::ICMP_EQ, v15, B.getInt64(256LL));
  // br i1 %16, label %13, label %6
  B.CreateCondBr(v16, bb13, bb6);

  // 13:
  B.SetInsertPoint(bb13);
  // ret void
  B.CreateRetVoid();

  // Входящие значения phi
  v7->addIncoming(B.getInt64(0LL), bb5);
  v7->addIncoming(v15, bb14);
  v18->addIncoming(B.getInt64(0LL), bb6);
  v18->addIncoming(v68, bb67);
  v55->addIncoming(v53, bb23);
  v55->addIncoming(B.getInt32(-3626642), bb17);
}

// app
void build_app(IRBuilder<> &B, Function *F) {
  LLVMContext &Ctx = B.getContext();

  // Базовые блоки в исходном порядке
  BasicBlock *bb0 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb5 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb17 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb20 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb23 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb25 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb27 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb28 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb53 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb57 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb85 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb92 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb97 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb105 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb109 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb116 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb122 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb130 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb133 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb139 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb142 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb150 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb157 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb164 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb167 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb175 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb178 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb185 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb215 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb218 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb220 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb267 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb270 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb296 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb302 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb304 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb323 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb335 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb343 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb348 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb356 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb361 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb369 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb374 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb381 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb385 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb393 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb397 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb405 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb409 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb417 = BasicBlock::Create(Ctx, "", F);
  BasicBlock *bb420 = BasicBlock::Create(Ctx, "", F);

  // 0:
  B.SetInsertPoint(bb0);
  // %1 = alloca [131072 x i32], align 16
  AllocaInst *v1 = B.CreateAlloca(ArrayType::get(B.getInt32Ty(), 131072));
  v1->setAlignment(Align(16));
  // %2 = alloca [131072 x i32], align 16
  AllocaInst *v2 = B.CreateAlloca(ArrayType::get(B.getInt32Ty(), 131072));
  v2->setAlignment(Align(16));
  // %3 = alloca [131072 x i32], align 16
  AllocaInst *v3 = B.CreateAlloca(ArrayType::get(B.getInt32Ty(), 131072));
  v3->setAlignment(Align(16));
  // %4 = alloca [131072 x i32], align 16
  AllocaInst *v4 = B.CreateAlloca(ArrayType::get(B.getInt32Ty(), 131072));
  v4->setAlignment(Align(16));
  // call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %1) #10
  B.CreateCall(fn_llvm_lifetime_start_p0, {B.getInt64(524288LL), v1});
  // call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(524288) %1, i8 0, i64 524288, i1 false)
  B.CreateCall(fn_llvm_memset_p0_i64, {v1, B.getInt8(0), B.getInt64(524288LL), B.getInt1(false)});
  // call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %2) #10
  B.CreateCall(fn_llvm_lifetime_start_p0, {B.getInt64(524288LL), v2});
  // call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(524288) %2, i8 0, i64 524288, i1 false)
  B.CreateCall(fn_llvm_memset_p0_i64, {v2, B.getInt8(0), B.getInt64(524288LL), B.getInt1(false)});
  // call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %3) #10
  B.CreateCall(fn_llvm_lifetime_start_p0, {B.getInt64(524288LL), v3});
  // call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(524288) %3, i8 0, i64 524288, i1 false)
  B.CreateCall(fn_llvm_memset_p0_i64, {v3, B.getInt8(0), B.getInt64(524288LL), B.getInt1(false)});
  // call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %4) #10
  B.CreateCall(fn_llvm_lifetime_start_p0, {B.getInt64(524288LL), v4});
  // call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(524288) %4, i8 0, i64 524288, i1 false)
  B.CreateCall(fn_llvm_memset_p0_i64, {v4, B.getInt8(0), B.getInt64(524288LL), B.getInt1(false)});
  // br label %5
  B.CreateBr(bb5);

  // 5:
  B.SetInsertPoint(bb5);
  // %6 = phi i64 [ 0, %0 ], [ %18, %17 ]
  PHINode *v6 = B.CreatePHI(B.getInt64Ty(), 2);
  // %7 = icmp eq i64 %6, 0
  Value *v7 = B.CreateICmp(CmpInst::ICMP_EQ, v6, B.getInt64(0LL));
  // %8 = add nsw i64 %6, -128
  Value *v8 = B.CreateAdd(v6, B.getInt64(-128LL), "", false, true);
  // %9 = mul nsw i64 %8, %8
  Value *v9 = B.CreateMul(v8, v8, "", false, true);
  // %10 = add nsw i64 %6, -55
  Value *v10 = B.CreateAdd(v6, B.getInt64(-55LL), "", false, true);
  // %11 = mul nsw i64 %10, %10
  Value *v11 = B.CreateMul(v10, v10, "", false, true);
  // %12 = add nsw i64 %6, -201
  Value *v12 = B.CreateAdd(v6, B.getInt64(-201LL), "", false, true);
  // %13 = mul nsw i64 %12, %12
  Value *v13 = B.CreateMul(v12, v12, "", false, true);
  // %14 = shl nuw nsw i64 %6, 9
  Value *v14 = B.CreateShl(v6, B.getInt64(9LL), "", true, true);
  // %15 = icmp eq i64 %6, 255
  Value *v15 = B.CreateICmp(CmpInst::ICMP_EQ, v6, B.getInt64(255LL));
  // %16 = getelementptr i32, ptr %3, i64 %14
  Value *v16 = B.CreateGEP(B.getInt32Ty(), v3, {v14}, "", false);
  // br label %23
  B.CreateBr(bb23);

  // 23:
  B.SetInsertPoint(bb23);
  // %24 = phi i64 [ 0, %5 ], [ %51, %28 ]
  PHINode *v24 = B.CreatePHI(B.getInt64Ty(), 2);
  // br i1 %7, label %28, label %25
  B.CreateCondBr(v7, bb28, bb25);

  // 25:
  B.SetInsertPoint(bb25);
  // %26 = trunc i64 %24 to i32
  Value *v26 = B.CreateTrunc(v24, B.getInt32Ty());
  // switch i32 %26, label %27 [
  // i32 511, label %28
  // i32 0, label %28
  // ]
  SwitchInst *sw0 = B.CreateSwitch(v26, bb27, 2);
  sw0->addCase(B.getInt32(511), bb28);
  sw0->addCase(B.getInt32(0), bb28);

  // 27:
  B.SetInsertPoint(bb27);
  // br label %28
  B.CreateBr(bb28);

  // 28:
  B.SetInsertPoint(bb28);
  // %29 = phi i1 [ true, %25 ], [ %15, %27 ], [ true, %23 ], [ true, %25 ]
  PHINode *v29 = B.CreatePHI(B.getInt1Ty(), 4);
  // %30 = add nsw i64 %24, -256
  Value *v30 = B.CreateAdd(v24, B.getInt64(-256LL), "", false, true);
  // %31 = mul nsw i64 %30, %30
  Value *v31 = B.CreateMul(v30, v30, "", false, true);
  // %32 = add nuw nsw i64 %31, %9
  Value *v32 = B.CreateAdd(v31, v9, "", true, true);
  // %33 = trunc i64 %32 to i32
  Value *v33 = B.CreateTrunc(v32, B.getInt32Ty());
  // %34 = icmp ult i32 %33, 1156
  Value *v34 = B.CreateICmp(CmpInst::ICMP_ULT, v33, B.getInt32(1156));
  // %35 = or i1 %34, %29
  Value *v35 = B.CreateOr(v34, v29);
  // %36 = add nsw i64 %24, -60
  Value *v36 = B.CreateAdd(v24, B.getInt64(-60LL), "", false, true);
  // %37 = mul nsw i64 %36, %36
  Value *v37 = B.CreateMul(v36, v36, "", false, true);
  // %38 = add nuw nsw i64 %37, %11
  Value *v38 = B.CreateAdd(v37, v11, "", true, true);
  // %39 = trunc i64 %38 to i32
  Value *v39 = B.CreateTrunc(v38, B.getInt32Ty());
  // %40 = icmp ult i32 %39, 484
  Value *v40 = B.CreateICmp(CmpInst::ICMP_ULT, v39, B.getInt32(484));
  // %41 = or i1 %40, %35
  Value *v41 = B.CreateOr(v40, v35);
  // %42 = add nsw i64 %24, -442
  Value *v42 = B.CreateAdd(v24, B.getInt64(-442LL), "", false, true);
  // %43 = mul nsw i64 %42, %42
  Value *v43 = B.CreateMul(v42, v42, "", false, true);
  // %44 = add nuw nsw i64 %43, %13
  Value *v44 = B.CreateAdd(v43, v13, "", true, true);
  // %45 = trunc i64 %44 to i32
  Value *v45 = B.CreateTrunc(v44, B.getInt32Ty());
  // %46 = icmp ult i32 %45, 324
  Value *v46 = B.CreateICmp(CmpInst::ICMP_ULT, v45, B.getInt32(324));
  // %47 = or i1 %46, %41
  Value *v47 = B.CreateOr(v46, v41);
  // %48 = xor i1 %47, true
  Value *v48 = B.CreateXor(v47, B.getInt1(true));
  // %49 = sext i1 %48 to i32
  Value *v49 = B.CreateSExt(v48, B.getInt32Ty());
  // %50 = getelementptr i32, ptr %16, i64 %24
  Value *v50 = B.CreateGEP(B.getInt32Ty(), v16, {v24}, "", false);
  // store i32 %49, ptr %50, align 4
  B.CreateAlignedStore(v49, v50, MaybeAlign(4));
  // %51 = add nuw nsw i64 %24, 1
  Value *v51 = B.CreateAdd(v24, B.getInt64(1LL), "", true, true);
  // %52 = icmp eq i64 %51, 512
  Value *v52 = B.CreateICmp(CmpInst::ICMP_EQ, v51, B.getInt64(512LL));
  // br i1 %52, label %17, label %23
  B.CreateCondBr(v52, bb17, bb23);

  // 17:
  B.SetInsertPoint(bb17);
  // %18 = add nuw nsw i64 %6, 1
  Value *v18 = B.CreateAdd(v6, B.getInt64(1LL), "", true, true);
  // %19 = icmp eq i64 %18, 256
  Value *v19 = B.CreateICmp(CmpInst::ICMP_EQ, v18, B.getInt64(256LL));
  // br i1 %19, label %20, label %5
  B.CreateCondBr(v19, bb20, bb5);

  // 20:
  B.SetInsertPoint(bb20);
  // %21 = getelementptr inbounds i8, ptr %3, i64 2052
  Value *v21 = B.CreateGEP(B.getInt8Ty(), v3, {B.getInt64(2052LL)}, "", true);
  // %22 = getelementptr inbounds i8, ptr %3, i64 522236
  Value *v22 = B.CreateGEP(B.getInt8Ty(), v3, {B.getInt64(522236LL)}, "", true);
  // br label %57
  B.CreateBr(bb57);

  // 57:
  B.SetInsertPoint(bb57);
  // %58 = phi ptr [ %1, %20 ], [ %59, %302 ]
  PHINode *v58 = B.CreatePHI(B.getPtrTy(), 2);
  // %59 = phi ptr [ %2, %20 ], [ %58, %302 ]
  PHINode *v59 = B.CreatePHI(B.getPtrTy(), 2);
  // %60 = phi i1 [ true, %20 ], [ %303, %302 ]
  PHINode *v60 = B.CreatePHI(B.getInt1Ty(), 2);
  // %61 = phi i32 [ 0, %20 ], [ %301, %302 ]
  PHINode *v61 = B.CreatePHI(B.getInt32Ty(), 2);
  // %62 = phi i32 [ 0, %20 ], [ %300, %302 ]
  PHINode *v62 = B.CreatePHI(B.getInt32Ty(), 2);
  // %63 = phi i32 [ 65536, %20 ], [ %298, %302 ]
  PHINode *v63 = B.CreatePHI(B.getInt32Ty(), 2);
  // %64 = mul nsw i32 %63, 150
  Value *v64 = B.CreateMul(v63, B.getInt32(150), "", false, true);
  // %65 = sdiv i32 %64, 65536
  Value *v65 = B.CreateSDiv(v64, B.getInt32(65536));
  // %66 = add nsw i32 %65, 256
  Value *v66 = B.CreateAdd(v65, B.getInt32(256), "", false, true);
  // %67 = mul nsw i32 %62, 80
  Value *v67 = B.CreateMul(v62, B.getInt32(80), "", false, true);
  // %68 = sdiv i32 %67, 65536
  Value *v68 = B.CreateSDiv(v67, B.getInt32(65536));
  // %69 = add nsw i32 %68, 128
  Value *v69 = B.CreateAdd(v68, B.getInt32(128), "", false, true);
  // %70 = udiv i32 %61, 5
  Value *v70 = B.CreateUDiv(v61, B.getInt32(5));
  // %71 = shl nuw nsw i32 %70, 1
  Value *v71 = B.CreateShl(v70, B.getInt32(1), "", true, true);
  // %72 = and i32 %71, 2
  Value *v72 = B.CreateAnd(v71, B.getInt32(2));
  // %73 = mul nuw nsw i32 %72, 500
  Value *v73 = B.CreateMul(v72, B.getInt32(500), "", true, true);
  // %74 = add nsw i32 %73, -500
  Value *v74 = B.CreateAdd(v73, B.getInt32(-500), "", false, true);
  // %75 = add nsw i32 %65, 255
  Value *v75 = B.CreateAdd(v65, B.getInt32(255), "", false, true);
  // %76 = add nsw i32 %65, 257
  Value *v76 = B.CreateAdd(v65, B.getInt32(257), "", false, true);
  // %77 = icmp sgt i32 %62, -104039
  Value *v77 = B.CreateICmp(CmpInst::ICMP_SGT, v62, B.getInt32(-104039));
  // %78 = icmp slt i32 %62, 104858
  Value *v78 = B.CreateICmp(CmpInst::ICMP_SLT, v62, B.getInt32(104858));
  // %79 = shl nsw i32 %68, 9
  Value *v79 = B.CreateShl(v68, B.getInt32(9), "", false, true);
  // %80 = add nsw i32 %79, 65024
  Value *v80 = B.CreateAdd(v79, B.getInt32(65024), "", false, true);
  // %81 = add nsw i32 %65, 254
  Value *v81 = B.CreateAdd(v65, B.getInt32(254), "", false, true);
  // %82 = icmp ult i32 %81, 510
  Value *v82 = B.CreateICmp(CmpInst::ICMP_ULT, v81, B.getInt32(510));
  // %83 = select i1 %82, i1 %77, i1 false
  Value *v83 = B.CreateSelect(v82, v77, B.getInt1(false));
  // %84 = select i1 %83, i1 %78, i1 false
  Value *v84 = B.CreateSelect(v83, v78, B.getInt1(false));
  // br i1 %84, label %85, label %92
  B.CreateCondBr(v84, bb85, bb92);

  // 85:
  B.SetInsertPoint(bb85);
  // %86 = ashr exact i32 %74, 1
  Value *v86 = B.CreateAShr(v74, B.getInt32(1), "", true);
  // %87 = add nuw nsw i32 %75, %80
  Value *v87 = B.CreateAdd(v75, v80, "", true, true);
  // %88 = zext nneg i32 %87 to i64
  Value *v88 = B.CreateZExt(v87, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v88)->setNonNeg(true);
  // %89 = getelementptr inbounds i32, ptr %58, i64 %88
  Value *v89 = B.CreateGEP(B.getInt32Ty(), v58, {v88}, "", true);
  // %90 = load i32, ptr %89, align 4
  Value *v90 = B.CreateAlignedLoad(B.getInt32Ty(), v89, MaybeAlign(4));
  // %91 = add nsw i32 %90, %86
  Value *v91 = B.CreateAdd(v90, v86, "", false, true);
  // store i32 %91, ptr %89, align 4
  B.CreateAlignedStore(v91, v89, MaybeAlign(4));
  // br label %92
  B.CreateBr(bb92);

  // 92:
  B.SetInsertPoint(bb92);
  // %93 = add nsw i32 %65, 255
  Value *v93 = B.CreateAdd(v65, B.getInt32(255), "", false, true);
  // %94 = icmp ult i32 %93, 510
  Value *v94 = B.CreateICmp(CmpInst::ICMP_ULT, v93, B.getInt32(510));
  // %95 = select i1 %94, i1 %77, i1 false
  Value *v95 = B.CreateSelect(v94, v77, B.getInt1(false));
  // %96 = select i1 %95, i1 %78, i1 false
  Value *v96 = B.CreateSelect(v95, v78, B.getInt1(false));
  // br i1 %96, label %97, label %105
  B.CreateCondBr(v96, bb97, bb105);

  // 97:
  B.SetInsertPoint(bb97);
  // %98 = mul nsw i32 %74, 3
  Value *v98 = B.CreateMul(v74, B.getInt32(3), "", false, true);
  // %99 = ashr exact i32 %98, 2
  Value *v99 = B.CreateAShr(v98, B.getInt32(2), "", true);
  // %100 = add nuw nsw i32 %66, %80
  Value *v100 = B.CreateAdd(v66, v80, "", true, true);
  // %101 = zext nneg i32 %100 to i64
  Value *v101 = B.CreateZExt(v100, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v101)->setNonNeg(true);
  // %102 = getelementptr inbounds i32, ptr %58, i64 %101
  Value *v102 = B.CreateGEP(B.getInt32Ty(), v58, {v101}, "", true);
  // %103 = load i32, ptr %102, align 4
  Value *v103 = B.CreateAlignedLoad(B.getInt32Ty(), v102, MaybeAlign(4));
  // %104 = add nsw i32 %103, %99
  Value *v104 = B.CreateAdd(v103, v99, "", false, true);
  // store i32 %104, ptr %102, align 4
  B.CreateAlignedStore(v104, v102, MaybeAlign(4));
  // br label %105
  B.CreateBr(bb105);

  // 105:
  B.SetInsertPoint(bb105);
  // %106 = icmp ult i32 %66, 510
  Value *v106 = B.CreateICmp(CmpInst::ICMP_ULT, v66, B.getInt32(510));
  // %107 = select i1 %106, i1 %77, i1 false
  Value *v107 = B.CreateSelect(v106, v77, B.getInt1(false));
  // %108 = select i1 %107, i1 %78, i1 false
  Value *v108 = B.CreateSelect(v107, v78, B.getInt1(false));
  // br i1 %108, label %109, label %116
  B.CreateCondBr(v108, bb109, bb116);

  // 109:
  B.SetInsertPoint(bb109);
  // %110 = ashr exact i32 %74, 1
  Value *v110 = B.CreateAShr(v74, B.getInt32(1), "", true);
  // %111 = add nuw nsw i32 %76, %80
  Value *v111 = B.CreateAdd(v76, v80, "", true, true);
  // %112 = zext nneg i32 %111 to i64
  Value *v112 = B.CreateZExt(v111, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v112)->setNonNeg(true);
  // %113 = getelementptr inbounds i32, ptr %58, i64 %112
  Value *v113 = B.CreateGEP(B.getInt32Ty(), v58, {v112}, "", true);
  // %114 = load i32, ptr %113, align 4
  Value *v114 = B.CreateAlignedLoad(B.getInt32Ty(), v113, MaybeAlign(4));
  // %115 = add nsw i32 %114, %110
  Value *v115 = B.CreateAdd(v114, v110, "", false, true);
  // store i32 %115, ptr %113, align 4
  B.CreateAlignedStore(v115, v113, MaybeAlign(4));
  // br label %116
  B.CreateBr(bb116);

  // 116:
  B.SetInsertPoint(bb116);
  // %117 = icmp sgt i32 %62, -104858
  Value *v117 = B.CreateICmp(CmpInst::ICMP_SGT, v62, B.getInt32(-104858));
  // %118 = icmp slt i32 %62, 104039
  Value *v118 = B.CreateICmp(CmpInst::ICMP_SLT, v62, B.getInt32(104039));
  // %119 = shl nuw nsw i32 %69, 9
  Value *v119 = B.CreateShl(v69, B.getInt32(9), "", true, true);
  // %120 = select i1 %82, i1 %117, i1 false
  Value *v120 = B.CreateSelect(v82, v117, B.getInt1(false));
  // %121 = select i1 %120, i1 %118, i1 false
  Value *v121 = B.CreateSelect(v120, v118, B.getInt1(false));
  // br i1 %121, label %122, label %130
  B.CreateCondBr(v121, bb122, bb130);

  // 122:
  B.SetInsertPoint(bb122);
  // %123 = mul nsw i32 %74, 3
  Value *v123 = B.CreateMul(v74, B.getInt32(3), "", false, true);
  // %124 = ashr exact i32 %123, 2
  Value *v124 = B.CreateAShr(v123, B.getInt32(2), "", true);
  // %125 = add nuw nsw i32 %75, %119
  Value *v125 = B.CreateAdd(v75, v119, "", true, true);
  // %126 = zext nneg i32 %125 to i64
  Value *v126 = B.CreateZExt(v125, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v126)->setNonNeg(true);
  // %127 = getelementptr inbounds i32, ptr %58, i64 %126
  Value *v127 = B.CreateGEP(B.getInt32Ty(), v58, {v126}, "", true);
  // %128 = load i32, ptr %127, align 4
  Value *v128 = B.CreateAlignedLoad(B.getInt32Ty(), v127, MaybeAlign(4));
  // %129 = add nsw i32 %128, %124
  Value *v129 = B.CreateAdd(v128, v124, "", false, true);
  // store i32 %129, ptr %127, align 4
  B.CreateAlignedStore(v129, v127, MaybeAlign(4));
  // br label %130
  B.CreateBr(bb130);

  // 130:
  B.SetInsertPoint(bb130);
  // %131 = select i1 %94, i1 %117, i1 false
  Value *v131 = B.CreateSelect(v94, v117, B.getInt1(false));
  // %132 = select i1 %131, i1 %118, i1 false
  Value *v132 = B.CreateSelect(v131, v118, B.getInt1(false));
  // br i1 %132, label %133, label %139
  B.CreateCondBr(v132, bb133, bb139);

  // 133:
  B.SetInsertPoint(bb133);
  // %134 = add nuw nsw i32 %66, %119
  Value *v134 = B.CreateAdd(v66, v119, "", true, true);
  // %135 = zext nneg i32 %134 to i64
  Value *v135 = B.CreateZExt(v134, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v135)->setNonNeg(true);
  // %136 = getelementptr inbounds i32, ptr %58, i64 %135
  Value *v136 = B.CreateGEP(B.getInt32Ty(), v58, {v135}, "", true);
  // %137 = load i32, ptr %136, align 4
  Value *v137 = B.CreateAlignedLoad(B.getInt32Ty(), v136, MaybeAlign(4));
  // %138 = add nsw i32 %137, %74
  Value *v138 = B.CreateAdd(v137, v74, "", false, true);
  // store i32 %138, ptr %136, align 4
  B.CreateAlignedStore(v138, v136, MaybeAlign(4));
  // br label %139
  B.CreateBr(bb139);

  // 139:
  B.SetInsertPoint(bb139);
  // %140 = select i1 %106, i1 %117, i1 false
  Value *v140 = B.CreateSelect(v106, v117, B.getInt1(false));
  // %141 = select i1 %140, i1 %118, i1 false
  Value *v141 = B.CreateSelect(v140, v118, B.getInt1(false));
  // br i1 %141, label %142, label %150
  B.CreateCondBr(v141, bb142, bb150);

  // 142:
  B.SetInsertPoint(bb142);
  // %143 = mul nsw i32 %74, 3
  Value *v143 = B.CreateMul(v74, B.getInt32(3), "", false, true);
  // %144 = ashr exact i32 %143, 2
  Value *v144 = B.CreateAShr(v143, B.getInt32(2), "", true);
  // %145 = add nuw nsw i32 %76, %119
  Value *v145 = B.CreateAdd(v76, v119, "", true, true);
  // %146 = zext nneg i32 %145 to i64
  Value *v146 = B.CreateZExt(v145, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v146)->setNonNeg(true);
  // %147 = getelementptr inbounds i32, ptr %58, i64 %146
  Value *v147 = B.CreateGEP(B.getInt32Ty(), v58, {v146}, "", true);
  // %148 = load i32, ptr %147, align 4
  Value *v148 = B.CreateAlignedLoad(B.getInt32Ty(), v147, MaybeAlign(4));
  // %149 = add nsw i32 %148, %144
  Value *v149 = B.CreateAdd(v148, v144, "", false, true);
  // store i32 %149, ptr %147, align 4
  B.CreateAlignedStore(v149, v147, MaybeAlign(4));
  // br label %150
  B.CreateBr(bb150);

  // 150:
  B.SetInsertPoint(bb150);
  // %151 = icmp sgt i32 %62, -105677
  Value *v151 = B.CreateICmp(CmpInst::ICMP_SGT, v62, B.getInt32(-105677));
  // %152 = icmp slt i32 %62, 103220
  Value *v152 = B.CreateICmp(CmpInst::ICMP_SLT, v62, B.getInt32(103220));
  // %153 = shl nsw i32 %68, 9
  Value *v153 = B.CreateShl(v68, B.getInt32(9), "", false, true);
  // %154 = add nsw i32 %153, 66048
  Value *v154 = B.CreateAdd(v153, B.getInt32(66048), "", false, true);
  // %155 = select i1 %82, i1 %151, i1 false
  Value *v155 = B.CreateSelect(v82, v151, B.getInt1(false));
  // %156 = select i1 %155, i1 %152, i1 false
  Value *v156 = B.CreateSelect(v155, v152, B.getInt1(false));
  // br i1 %156, label %157, label %164
  B.CreateCondBr(v156, bb157, bb164);

  // 157:
  B.SetInsertPoint(bb157);
  // %158 = ashr exact i32 %74, 1
  Value *v158 = B.CreateAShr(v74, B.getInt32(1), "", true);
  // %159 = add nuw nsw i32 %75, %154
  Value *v159 = B.CreateAdd(v75, v154, "", true, true);
  // %160 = zext nneg i32 %159 to i64
  Value *v160 = B.CreateZExt(v159, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v160)->setNonNeg(true);
  // %161 = getelementptr inbounds i32, ptr %58, i64 %160
  Value *v161 = B.CreateGEP(B.getInt32Ty(), v58, {v160}, "", true);
  // %162 = load i32, ptr %161, align 4
  Value *v162 = B.CreateAlignedLoad(B.getInt32Ty(), v161, MaybeAlign(4));
  // %163 = add nsw i32 %162, %158
  Value *v163 = B.CreateAdd(v162, v158, "", false, true);
  // store i32 %163, ptr %161, align 4
  B.CreateAlignedStore(v163, v161, MaybeAlign(4));
  // br label %164
  B.CreateBr(bb164);

  // 164:
  B.SetInsertPoint(bb164);
  // %165 = select i1 %94, i1 %151, i1 false
  Value *v165 = B.CreateSelect(v94, v151, B.getInt1(false));
  // %166 = select i1 %165, i1 %152, i1 false
  Value *v166 = B.CreateSelect(v165, v152, B.getInt1(false));
  // br i1 %166, label %167, label %175
  B.CreateCondBr(v166, bb167, bb175);

  // 167:
  B.SetInsertPoint(bb167);
  // %168 = mul nsw i32 %74, 3
  Value *v168 = B.CreateMul(v74, B.getInt32(3), "", false, true);
  // %169 = ashr exact i32 %168, 2
  Value *v169 = B.CreateAShr(v168, B.getInt32(2), "", true);
  // %170 = add nuw nsw i32 %66, %154
  Value *v170 = B.CreateAdd(v66, v154, "", true, true);
  // %171 = zext nneg i32 %170 to i64
  Value *v171 = B.CreateZExt(v170, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v171)->setNonNeg(true);
  // %172 = getelementptr inbounds i32, ptr %58, i64 %171
  Value *v172 = B.CreateGEP(B.getInt32Ty(), v58, {v171}, "", true);
  // %173 = load i32, ptr %172, align 4
  Value *v173 = B.CreateAlignedLoad(B.getInt32Ty(), v172, MaybeAlign(4));
  // %174 = add nsw i32 %173, %169
  Value *v174 = B.CreateAdd(v173, v169, "", false, true);
  // store i32 %174, ptr %172, align 4
  B.CreateAlignedStore(v174, v172, MaybeAlign(4));
  // br label %175
  B.CreateBr(bb175);

  // 175:
  B.SetInsertPoint(bb175);
  // %176 = select i1 %106, i1 %151, i1 false
  Value *v176 = B.CreateSelect(v106, v151, B.getInt1(false));
  // %177 = select i1 %176, i1 %152, i1 false
  Value *v177 = B.CreateSelect(v176, v152, B.getInt1(false));
  // br i1 %177, label %178, label %185
  B.CreateCondBr(v177, bb178, bb185);

  // 178:
  B.SetInsertPoint(bb178);
  // %179 = ashr exact i32 %74, 1
  Value *v179 = B.CreateAShr(v74, B.getInt32(1), "", true);
  // %180 = add nuw nsw i32 %76, %154
  Value *v180 = B.CreateAdd(v76, v154, "", true, true);
  // %181 = zext nneg i32 %180 to i64
  Value *v181 = B.CreateZExt(v180, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v181)->setNonNeg(true);
  // %182 = getelementptr inbounds i32, ptr %58, i64 %181
  Value *v182 = B.CreateGEP(B.getInt32Ty(), v58, {v181}, "", true);
  // %183 = load i32, ptr %182, align 4
  Value *v183 = B.CreateAlignedLoad(B.getInt32Ty(), v182, MaybeAlign(4));
  // %184 = add nsw i32 %183, %179
  Value *v184 = B.CreateAdd(v183, v179, "", false, true);
  // store i32 %184, ptr %182, align 4
  B.CreateAlignedStore(v184, v182, MaybeAlign(4));
  // br label %185
  B.CreateBr(bb185);

  // 185:
  B.SetInsertPoint(bb185);
  // %186 = getelementptr i8, ptr %59, i64 2052
  Value *v186 = B.CreateGEP(B.getInt8Ty(), v59, {B.getInt64(2052LL)}, "", false);
  // %187 = getelementptr i8, ptr %59, i64 522236
  Value *v187 = B.CreateGEP(B.getInt8Ty(), v59, {B.getInt64(522236LL)}, "", false);
  // %188 = getelementptr i8, ptr %58, i64 2048
  Value *v188 = B.CreateGEP(B.getInt8Ty(), v58, {B.getInt64(2048LL)}, "", false);
  // %189 = getelementptr i8, ptr %58, i64 522232
  Value *v189 = B.CreateGEP(B.getInt8Ty(), v58, {B.getInt64(522232LL)}, "", false);
  // %190 = getelementptr i8, ptr %58, i64 2056
  Value *v190 = B.CreateGEP(B.getInt8Ty(), v58, {B.getInt64(2056LL)}, "", false);
  // %191 = getelementptr i8, ptr %58, i64 522240
  Value *v191 = B.CreateGEP(B.getInt8Ty(), v58, {B.getInt64(522240LL)}, "", false);
  // %192 = getelementptr i8, ptr %58, i64 4
  Value *v192 = B.CreateGEP(B.getInt8Ty(), v58, {B.getInt64(4LL)}, "", false);
  // %193 = getelementptr i8, ptr %58, i64 520188
  Value *v193 = B.CreateGEP(B.getInt8Ty(), v58, {B.getInt64(520188LL)}, "", false);
  // %194 = getelementptr i8, ptr %58, i64 4100
  Value *v194 = B.CreateGEP(B.getInt8Ty(), v58, {B.getInt64(4100LL)}, "", false);
  // %195 = getelementptr i8, ptr %58, i64 524284
  Value *v195 = B.CreateGEP(B.getInt8Ty(), v58, {B.getInt64(524284LL)}, "", false);
  // %196 = icmp ult ptr %186, %189
  Value *v196 = B.CreateICmp(CmpInst::ICMP_ULT, v186, v189);
  // %197 = icmp ult ptr %188, %187
  Value *v197 = B.CreateICmp(CmpInst::ICMP_ULT, v188, v187);
  // %198 = and i1 %196, %197
  Value *v198 = B.CreateAnd(v196, v197);
  // %199 = icmp ult ptr %186, %191
  Value *v199 = B.CreateICmp(CmpInst::ICMP_ULT, v186, v191);
  // %200 = icmp ult ptr %190, %187
  Value *v200 = B.CreateICmp(CmpInst::ICMP_ULT, v190, v187);
  // %201 = and i1 %199, %200
  Value *v201 = B.CreateAnd(v199, v200);
  // %202 = or i1 %198, %201
  Value *v202 = B.CreateOr(v198, v201);
  // %203 = icmp ult ptr %186, %193
  Value *v203 = B.CreateICmp(CmpInst::ICMP_ULT, v186, v193);
  // %204 = icmp ult ptr %192, %187
  Value *v204 = B.CreateICmp(CmpInst::ICMP_ULT, v192, v187);
  // %205 = and i1 %203, %204
  Value *v205 = B.CreateAnd(v203, v204);
  // %206 = or i1 %202, %205
  Value *v206 = B.CreateOr(v202, v205);
  // %207 = icmp ult ptr %186, %195
  Value *v207 = B.CreateICmp(CmpInst::ICMP_ULT, v186, v195);
  // %208 = icmp ult ptr %194, %187
  Value *v208 = B.CreateICmp(CmpInst::ICMP_ULT, v194, v187);
  // %209 = and i1 %207, %208
  Value *v209 = B.CreateAnd(v207, v208);
  // %210 = or i1 %206, %209
  Value *v210 = B.CreateOr(v206, v209);
  // %211 = icmp ult ptr %186, %22
  Value *v211 = B.CreateICmp(CmpInst::ICMP_ULT, v186, v22);
  // %212 = icmp ult ptr %21, %187
  Value *v212 = B.CreateICmp(CmpInst::ICMP_ULT, v21, v187);
  // %213 = and i1 %211, %212
  Value *v213 = B.CreateAnd(v211, v212);
  // %214 = or i1 %210, %213
  Value *v214 = B.CreateOr(v210, v213);
  // br label %215
  B.CreateBr(bb215);

  // 215:
  B.SetInsertPoint(bb215);
  // %216 = phi i64 [ %268, %267 ], [ 1, %185 ]
  PHINode *v216 = B.CreatePHI(B.getInt64Ty(), 2);
  // %217 = shl nuw nsw i64 %216, 9
  Value *v217 = B.CreateShl(v216, B.getInt64(9LL), "", true, true);
  // br i1 %214, label %218, label %220
  B.CreateCondBr(v214, bb218, bb220);

  // 220:
  B.SetInsertPoint(bb220);
  // %221 = phi i64 [ %265, %220 ], [ 0, %215 ]
  PHINode *v221 = B.CreatePHI(B.getInt64Ty(), 2);
  // %222 = or disjoint i64 %221, 1
  Value *v222 = B.CreateOr(v221, B.getInt64(1LL));
  cast<PossiblyDisjointInst>(v222)->setIsDisjoint(true);
  // %223 = add nuw nsw i64 %222, %217
  Value *v223 = B.CreateAdd(v222, v217, "", true, true);
  // %224 = getelementptr i32, ptr %58, i64 %223
  Value *v224 = B.CreateGEP(B.getInt32Ty(), v58, {v223}, "", false);
  // %225 = getelementptr i32, ptr %224, i64 -1
  Value *v225 = B.CreateGEP(B.getInt32Ty(), v224, {B.getInt64(-1LL)}, "", false);
  // %226 = getelementptr i32, ptr %224, i64 3
  Value *v226 = B.CreateGEP(B.getInt32Ty(), v224, {B.getInt64(3LL)}, "", false);
  // %227 = load <4 x i32>, ptr %225, align 4
  Value *v227 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v225, MaybeAlign(4));
  // %228 = load <4 x i32>, ptr %226, align 4
  Value *v228 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v226, MaybeAlign(4));
  // %229 = getelementptr i32, ptr %224, i64 1
  Value *v229 = B.CreateGEP(B.getInt32Ty(), v224, {B.getInt64(1LL)}, "", false);
  // %230 = getelementptr i32, ptr %224, i64 5
  Value *v230 = B.CreateGEP(B.getInt32Ty(), v224, {B.getInt64(5LL)}, "", false);
  // %231 = load <4 x i32>, ptr %229, align 4
  Value *v231 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v229, MaybeAlign(4));
  // %232 = load <4 x i32>, ptr %230, align 4
  Value *v232 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v230, MaybeAlign(4));
  // %233 = add nsw <4 x i32> %231, %227
  Value *v233 = B.CreateAdd(v231, v227, "", false, true);
  // %234 = add nsw <4 x i32> %232, %228
  Value *v234 = B.CreateAdd(v232, v228, "", false, true);
  // %235 = getelementptr i32, ptr %224, i64 -512
  Value *v235 = B.CreateGEP(B.getInt32Ty(), v224, {B.getInt64(-512LL)}, "", false);
  // %236 = getelementptr i32, ptr %224, i64 -508
  Value *v236 = B.CreateGEP(B.getInt32Ty(), v224, {B.getInt64(-508LL)}, "", false);
  // %237 = load <4 x i32>, ptr %235, align 4
  Value *v237 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v235, MaybeAlign(4));
  // %238 = load <4 x i32>, ptr %236, align 4
  Value *v238 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v236, MaybeAlign(4));
  // %239 = add nsw <4 x i32> %233, %237
  Value *v239 = B.CreateAdd(v233, v237, "", false, true);
  // %240 = add nsw <4 x i32> %234, %238
  Value *v240 = B.CreateAdd(v234, v238, "", false, true);
  // %241 = getelementptr i32, ptr %224, i64 512
  Value *v241 = B.CreateGEP(B.getInt32Ty(), v224, {B.getInt64(512LL)}, "", false);
  // %242 = getelementptr i32, ptr %224, i64 516
  Value *v242 = B.CreateGEP(B.getInt32Ty(), v224, {B.getInt64(516LL)}, "", false);
  // %243 = load <4 x i32>, ptr %241, align 4
  Value *v243 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v241, MaybeAlign(4));
  // %244 = load <4 x i32>, ptr %242, align 4
  Value *v244 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v242, MaybeAlign(4));
  // %245 = add nsw <4 x i32> %239, %243
  Value *v245 = B.CreateAdd(v239, v243, "", false, true);
  // %246 = add nsw <4 x i32> %240, %244
  Value *v246 = B.CreateAdd(v240, v244, "", false, true);
  // %247 = ashr <4 x i32> %245, <i32 1, i32 1, i32 1, i32 1>
  Value *v247 = B.CreateAShr(v245, ConstantVector::getSplat(ElementCount::getFixed(4), B.getInt32(1)));
  // %248 = ashr <4 x i32> %246, <i32 1, i32 1, i32 1, i32 1>
  Value *v248 = B.CreateAShr(v246, ConstantVector::getSplat(ElementCount::getFixed(4), B.getInt32(1)));
  // %249 = getelementptr inbounds i32, ptr %59, i64 %223
  Value *v249 = B.CreateGEP(B.getInt32Ty(), v59, {v223}, "", true);
  // %250 = getelementptr inbounds i32, ptr %249, i64 4
  Value *v250 = B.CreateGEP(B.getInt32Ty(), v249, {B.getInt64(4LL)}, "", true);
  // %251 = load <4 x i32>, ptr %249, align 4
  Value *v251 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v249, MaybeAlign(4));
  // %252 = load <4 x i32>, ptr %250, align 4
  Value *v252 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v250, MaybeAlign(4));
  // %253 = sub nsw <4 x i32> %247, %251
  Value *v253 = B.CreateSub(v247, v251, "", false, true);
  // %254 = sub nsw <4 x i32> %248, %252
  Value *v254 = B.CreateSub(v248, v252, "", false, true);
  // %255 = ashr <4 x i32> %253, <i32 6, i32 6, i32 6, i32 6>
  Value *v255 = B.CreateAShr(v253, ConstantVector::getSplat(ElementCount::getFixed(4), B.getInt32(6)));
  // %256 = ashr <4 x i32> %254, <i32 6, i32 6, i32 6, i32 6>
  Value *v256 = B.CreateAShr(v254, ConstantVector::getSplat(ElementCount::getFixed(4), B.getInt32(6)));
  // %257 = sub nsw <4 x i32> %253, %255
  Value *v257 = B.CreateSub(v253, v255, "", false, true);
  // %258 = sub nsw <4 x i32> %254, %256
  Value *v258 = B.CreateSub(v254, v256, "", false, true);
  // %259 = getelementptr inbounds i32, ptr %3, i64 %223
  Value *v259 = B.CreateGEP(B.getInt32Ty(), v3, {v223}, "", true);
  // %260 = getelementptr inbounds i32, ptr %259, i64 4
  Value *v260 = B.CreateGEP(B.getInt32Ty(), v259, {B.getInt64(4LL)}, "", true);
  // %261 = load <4 x i32>, ptr %259, align 4
  Value *v261 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v259, MaybeAlign(4));
  // %262 = load <4 x i32>, ptr %260, align 4
  Value *v262 = B.CreateAlignedLoad(FixedVectorType::get(B.getInt32Ty(), 4), v260, MaybeAlign(4));
  // %263 = and <4 x i32> %257, %261
  Value *v263 = B.CreateAnd(v257, v261);
  // %264 = and <4 x i32> %258, %262
  Value *v264 = B.CreateAnd(v258, v262);
  // store <4 x i32> %263, ptr %249, align 4
  B.CreateAlignedStore(v263, v249, MaybeAlign(4));
  // store <4 x i32> %264, ptr %250, align 4
  B.CreateAlignedStore(v264, v250, MaybeAlign(4));
  // %265 = add nuw i64 %221, 8
  Value *v265 = B.CreateAdd(v221, B.getInt64(8LL), "", true, false);
  // %266 = icmp eq i64 %265, 504
  Value *v266 = B.CreateICmp(CmpInst::ICMP_EQ, v265, B.getInt64(504LL));
  // br i1 %266, label %218, label %220
  B.CreateCondBr(v266, bb218, bb220);

  // 218:
  B.SetInsertPoint(bb218);
  // %219 = phi i64 [ 1, %215 ], [ 505, %220 ]
  PHINode *v219 = B.CreatePHI(B.getInt64Ty(), 2);
  // br label %270
  B.CreateBr(bb270);

  // 270:
  B.SetInsertPoint(bb270);
  // %271 = phi i64 [ %294, %270 ], [ %219, %218 ]
  PHINode *v271 = B.CreatePHI(B.getInt64Ty(), 2);
  // %272 = add nuw nsw i64 %271, %217
  Value *v272 = B.CreateAdd(v271, v217, "", true, true);
  // %273 = getelementptr i32, ptr %58, i64 %272
  Value *v273 = B.CreateGEP(B.getInt32Ty(), v58, {v272}, "", false);
  // %274 = getelementptr i32, ptr %273, i64 -1
  Value *v274 = B.CreateGEP(B.getInt32Ty(), v273, {B.getInt64(-1LL)}, "", false);
  // %275 = load i32, ptr %274, align 4
  Value *v275 = B.CreateAlignedLoad(B.getInt32Ty(), v274, MaybeAlign(4));
  // %276 = getelementptr i32, ptr %273, i64 1
  Value *v276 = B.CreateGEP(B.getInt32Ty(), v273, {B.getInt64(1LL)}, "", false);
  // %277 = load i32, ptr %276, align 4
  Value *v277 = B.CreateAlignedLoad(B.getInt32Ty(), v276, MaybeAlign(4));
  // %278 = add nsw i32 %277, %275
  Value *v278 = B.CreateAdd(v277, v275, "", false, true);
  // %279 = getelementptr i32, ptr %273, i64 -512
  Value *v279 = B.CreateGEP(B.getInt32Ty(), v273, {B.getInt64(-512LL)}, "", false);
  // %280 = load i32, ptr %279, align 4
  Value *v280 = B.CreateAlignedLoad(B.getInt32Ty(), v279, MaybeAlign(4));
  // %281 = add nsw i32 %278, %280
  Value *v281 = B.CreateAdd(v278, v280, "", false, true);
  // %282 = getelementptr i32, ptr %273, i64 512
  Value *v282 = B.CreateGEP(B.getInt32Ty(), v273, {B.getInt64(512LL)}, "", false);
  // %283 = load i32, ptr %282, align 4
  Value *v283 = B.CreateAlignedLoad(B.getInt32Ty(), v282, MaybeAlign(4));
  // %284 = add nsw i32 %281, %283
  Value *v284 = B.CreateAdd(v281, v283, "", false, true);
  // %285 = ashr i32 %284, 1
  Value *v285 = B.CreateAShr(v284, B.getInt32(1));
  // %286 = getelementptr inbounds i32, ptr %59, i64 %272
  Value *v286 = B.CreateGEP(B.getInt32Ty(), v59, {v272}, "", true);
  // %287 = load i32, ptr %286, align 4
  Value *v287 = B.CreateAlignedLoad(B.getInt32Ty(), v286, MaybeAlign(4));
  // %288 = sub nsw i32 %285, %287
  Value *v288 = B.CreateSub(v285, v287, "", false, true);
  // %289 = ashr i32 %288, 6
  Value *v289 = B.CreateAShr(v288, B.getInt32(6));
  // %290 = sub nsw i32 %288, %289
  Value *v290 = B.CreateSub(v288, v289, "", false, true);
  // %291 = getelementptr inbounds i32, ptr %3, i64 %272
  Value *v291 = B.CreateGEP(B.getInt32Ty(), v3, {v272}, "", true);
  // %292 = load i32, ptr %291, align 4
  Value *v292 = B.CreateAlignedLoad(B.getInt32Ty(), v291, MaybeAlign(4));
  // %293 = and i32 %290, %292
  Value *v293 = B.CreateAnd(v290, v292);
  // store i32 %293, ptr %286, align 4
  B.CreateAlignedStore(v293, v286, MaybeAlign(4));
  // %294 = add nuw nsw i64 %271, 1
  Value *v294 = B.CreateAdd(v271, B.getInt64(1LL), "", true, true);
  // %295 = icmp eq i64 %294, 511
  Value *v295 = B.CreateICmp(CmpInst::ICMP_EQ, v294, B.getInt64(511LL));
  // br i1 %295, label %267, label %270
  B.CreateCondBr(v295, bb267, bb270);

  // 267:
  B.SetInsertPoint(bb267);
  // %268 = add nuw nsw i64 %216, 1
  Value *v268 = B.CreateAdd(v216, B.getInt64(1LL), "", true, true);
  // %269 = icmp eq i64 %268, 255
  Value *v269 = B.CreateICmp(CmpInst::ICMP_EQ, v268, B.getInt64(255LL));
  // br i1 %269, label %296, label %215
  B.CreateCondBr(v269, bb296, bb215);

  // 296:
  B.SetInsertPoint(bb296);
  // %297 = ashr i32 %62, 8
  Value *v297 = B.CreateAShr(v62, B.getInt32(8));
  // %298 = sub nsw i32 %63, %297
  Value *v298 = B.CreateSub(v63, v297, "", false, true);
  // %299 = ashr i32 %298, 8
  Value *v299 = B.CreateAShr(v298, B.getInt32(8));
  // %300 = add nsw i32 %299, %62
  Value *v300 = B.CreateAdd(v299, v62, "", false, true);
  // %301 = add nuw nsw i32 %61, 1
  Value *v301 = B.CreateAdd(v61, B.getInt32(1), "", true, true);
  // br i1 %60, label %302, label %53
  B.CreateCondBr(v60, bb302, bb53);

  // 53:
  B.SetInsertPoint(bb53);
  // %54 = tail call i32 (...) @simRand() #10
  CallInst *v54 = B.CreateCall(fn_simRand, {});
  v54->setTailCall();
  // %55 = and i32 %54, 3
  Value *v55 = B.CreateAnd(v54, B.getInt32(3));
  // %56 = icmp eq i32 %55, 0
  Value *v56 = B.CreateICmp(CmpInst::ICMP_EQ, v55, B.getInt32(0));
  // br i1 %56, label %304, label %420
  B.CreateCondBr(v56, bb304, bb420);

  // 304:
  B.SetInsertPoint(bb304);
  // %305 = tail call i32 (...) @simRand() #10
  CallInst *v305 = B.CreateCall(fn_simRand, {});
  v305->setTailCall();
  // %306 = srem i32 %305, 510
  Value *v306 = B.CreateSRem(v305, B.getInt32(510));
  // %307 = add nsw i32 %306, 1
  Value *v307 = B.CreateAdd(v306, B.getInt32(1), "", false, true);
  // %308 = tail call i32 (...) @simRand() #10
  CallInst *v308 = B.CreateCall(fn_simRand, {});
  v308->setTailCall();
  // %309 = srem i32 %308, 254
  Value *v309 = B.CreateSRem(v308, B.getInt32(254));
  // %310 = add nsw i32 %309, 1
  Value *v310 = B.CreateAdd(v309, B.getInt32(1), "", false, true);
  // %311 = add nsw i32 %306, -3
  Value *v311 = B.CreateAdd(v306, B.getInt32(-3), "", false, true);
  // %312 = icmp ult i32 %311, 510
  Value *v312 = B.CreateICmp(CmpInst::ICMP_ULT, v311, B.getInt32(510));
  // %313 = add nsw i32 %306, -2
  Value *v313 = B.CreateAdd(v306, B.getInt32(-2), "", false, true);
  // %314 = icmp ult i32 %313, 510
  Value *v314 = B.CreateICmp(CmpInst::ICMP_ULT, v313, B.getInt32(510));
  // %315 = add nsw i32 %306, -1
  Value *v315 = B.CreateAdd(v306, B.getInt32(-1), "", false, true);
  // %316 = icmp ult i32 %315, 510
  Value *v316 = B.CreateICmp(CmpInst::ICMP_ULT, v315, B.getInt32(510));
  // %317 = icmp ult i32 %306, 510
  Value *v317 = B.CreateICmp(CmpInst::ICMP_ULT, v306, B.getInt32(510));
  // %318 = icmp ult i32 %307, 510
  Value *v318 = B.CreateICmp(CmpInst::ICMP_ULT, v307, B.getInt32(510));
  // %319 = add nsw i32 %306, 2
  Value *v319 = B.CreateAdd(v306, B.getInt32(2), "", false, true);
  // %320 = icmp ult i32 %319, 510
  Value *v320 = B.CreateICmp(CmpInst::ICMP_ULT, v319, B.getInt32(510));
  // %321 = add nsw i32 %306, 3
  Value *v321 = B.CreateAdd(v306, B.getInt32(3), "", false, true);
  // %322 = icmp ult i32 %321, 510
  Value *v322 = B.CreateICmp(CmpInst::ICMP_ULT, v321, B.getInt32(510));
  // br label %323
  B.CreateBr(bb323);

  // 323:
  B.SetInsertPoint(bb323);
  // %324 = phi i32 [ -4, %304 ], [ %418, %417 ]
  PHINode *v324 = B.CreatePHI(B.getInt32Ty(), 2);
  // %325 = add nsw i32 %310, %324
  Value *v325 = B.CreateAdd(v310, v324, "", false, true);
  // %326 = mul nsw i32 %324, %324
  Value *v326 = B.CreateMul(v324, v324, "", false, true);
  // %327 = icmp sgt i32 %325, 0
  Value *v327 = B.CreateICmp(CmpInst::ICMP_SGT, v325, B.getInt32(0));
  // %328 = icmp slt i32 %325, 255
  Value *v328 = B.CreateICmp(CmpInst::ICMP_SLT, v325, B.getInt32(255));
  // %329 = shl nuw nsw i32 %325, 9
  Value *v329 = B.CreateShl(v325, B.getInt32(9), "", true, true);
  // %330 = add i32 %307, %329
  Value *v330 = B.CreateAdd(v307, v329);
  // %331 = select i1 %312, i1 %327, i1 false
  Value *v331 = B.CreateSelect(v312, v327, B.getInt1(false));
  // %332 = select i1 %331, i1 %328, i1 false
  Value *v332 = B.CreateSelect(v331, v328, B.getInt1(false));
  // %333 = icmp ult i32 %326, 7
  Value *v333 = B.CreateICmp(CmpInst::ICMP_ULT, v326, B.getInt32(7));
  // %334 = select i1 %332, i1 %333, i1 false
  Value *v334 = B.CreateSelect(v332, v333, B.getInt1(false));
  // br i1 %334, label %335, label %343
  B.CreateCondBr(v334, bb335, bb343);

  // 335:
  B.SetInsertPoint(bb335);
  // %336 = sub nuw nsw i32 7, %326
  Value *v336 = B.CreateSub(B.getInt32(7), v326, "", true, true);
  // %337 = mul nuw nsw i32 %336, 125
  Value *v337 = B.CreateMul(v336, B.getInt32(125), "", true, true);
  // %338 = add nsw i32 %330, -3
  Value *v338 = B.CreateAdd(v330, B.getInt32(-3), "", false, true);
  // %339 = zext nneg i32 %338 to i64
  Value *v339 = B.CreateZExt(v338, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v339)->setNonNeg(true);
  // %340 = getelementptr inbounds i32, ptr %59, i64 %339
  Value *v340 = B.CreateGEP(B.getInt32Ty(), v59, {v339}, "", true);
  // %341 = load i32, ptr %340, align 4
  Value *v341 = B.CreateAlignedLoad(B.getInt32Ty(), v340, MaybeAlign(4));
  // %342 = add nsw i32 %341, %337
  Value *v342 = B.CreateAdd(v341, v337, "", false, true);
  // store i32 %342, ptr %340, align 4
  B.CreateAlignedStore(v342, v340, MaybeAlign(4));
  // br label %343
  B.CreateBr(bb343);

  // 343:
  B.SetInsertPoint(bb343);
  // %344 = select i1 %314, i1 %327, i1 false
  Value *v344 = B.CreateSelect(v314, v327, B.getInt1(false));
  // %345 = select i1 %344, i1 %328, i1 false
  Value *v345 = B.CreateSelect(v344, v328, B.getInt1(false));
  // %346 = icmp ult i32 %326, 12
  Value *v346 = B.CreateICmp(CmpInst::ICMP_ULT, v326, B.getInt32(12));
  // %347 = select i1 %345, i1 %346, i1 false
  Value *v347 = B.CreateSelect(v345, v346, B.getInt1(false));
  // br i1 %347, label %348, label %356
  B.CreateCondBr(v347, bb348, bb356);

  // 348:
  B.SetInsertPoint(bb348);
  // %349 = sub nuw nsw i32 12, %326
  Value *v349 = B.CreateSub(B.getInt32(12), v326, "", true, true);
  // %350 = mul nuw nsw i32 %349, 125
  Value *v350 = B.CreateMul(v349, B.getInt32(125), "", true, true);
  // %351 = add nsw i32 %330, -2
  Value *v351 = B.CreateAdd(v330, B.getInt32(-2), "", false, true);
  // %352 = zext nneg i32 %351 to i64
  Value *v352 = B.CreateZExt(v351, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v352)->setNonNeg(true);
  // %353 = getelementptr inbounds i32, ptr %59, i64 %352
  Value *v353 = B.CreateGEP(B.getInt32Ty(), v59, {v352}, "", true);
  // %354 = load i32, ptr %353, align 4
  Value *v354 = B.CreateAlignedLoad(B.getInt32Ty(), v353, MaybeAlign(4));
  // %355 = add nsw i32 %354, %350
  Value *v355 = B.CreateAdd(v354, v350, "", false, true);
  // store i32 %355, ptr %353, align 4
  B.CreateAlignedStore(v355, v353, MaybeAlign(4));
  // br label %356
  B.CreateBr(bb356);

  // 356:
  B.SetInsertPoint(bb356);
  // %357 = select i1 %316, i1 %327, i1 false
  Value *v357 = B.CreateSelect(v316, v327, B.getInt1(false));
  // %358 = select i1 %357, i1 %328, i1 false
  Value *v358 = B.CreateSelect(v357, v328, B.getInt1(false));
  // %359 = icmp ult i32 %326, 15
  Value *v359 = B.CreateICmp(CmpInst::ICMP_ULT, v326, B.getInt32(15));
  // %360 = select i1 %358, i1 %359, i1 false
  Value *v360 = B.CreateSelect(v358, v359, B.getInt1(false));
  // br i1 %360, label %361, label %369
  B.CreateCondBr(v360, bb361, bb369);

  // 361:
  B.SetInsertPoint(bb361);
  // %362 = sub nuw nsw i32 15, %326
  Value *v362 = B.CreateSub(B.getInt32(15), v326, "", true, true);
  // %363 = mul nuw nsw i32 %362, 125
  Value *v363 = B.CreateMul(v362, B.getInt32(125), "", true, true);
  // %364 = add nuw nsw i32 %306, %329
  Value *v364 = B.CreateAdd(v306, v329, "", true, true);
  // %365 = zext nneg i32 %364 to i64
  Value *v365 = B.CreateZExt(v364, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v365)->setNonNeg(true);
  // %366 = getelementptr inbounds i32, ptr %59, i64 %365
  Value *v366 = B.CreateGEP(B.getInt32Ty(), v59, {v365}, "", true);
  // %367 = load i32, ptr %366, align 4
  Value *v367 = B.CreateAlignedLoad(B.getInt32Ty(), v366, MaybeAlign(4));
  // %368 = add nsw i32 %367, %363
  Value *v368 = B.CreateAdd(v367, v363, "", false, true);
  // store i32 %368, ptr %366, align 4
  B.CreateAlignedStore(v368, v366, MaybeAlign(4));
  // br label %369
  B.CreateBr(bb369);

  // 369:
  B.SetInsertPoint(bb369);
  // %370 = select i1 %317, i1 %327, i1 false
  Value *v370 = B.CreateSelect(v317, v327, B.getInt1(false));
  // %371 = select i1 %370, i1 %328, i1 false
  Value *v371 = B.CreateSelect(v370, v328, B.getInt1(false));
  // %372 = icmp ult i32 %326, 16
  Value *v372 = B.CreateICmp(CmpInst::ICMP_ULT, v326, B.getInt32(16));
  // %373 = select i1 %371, i1 %372, i1 false
  Value *v373 = B.CreateSelect(v371, v372, B.getInt1(false));
  // br i1 %373, label %374, label %381
  B.CreateCondBr(v373, bb374, bb381);

  // 374:
  B.SetInsertPoint(bb374);
  // %375 = sub nuw nsw i32 16, %326
  Value *v375 = B.CreateSub(B.getInt32(16), v326, "", true, true);
  // %376 = mul nuw nsw i32 %375, 125
  Value *v376 = B.CreateMul(v375, B.getInt32(125), "", true, true);
  // %377 = zext nneg i32 %330 to i64
  Value *v377 = B.CreateZExt(v330, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v377)->setNonNeg(true);
  // %378 = getelementptr inbounds i32, ptr %59, i64 %377
  Value *v378 = B.CreateGEP(B.getInt32Ty(), v59, {v377}, "", true);
  // %379 = load i32, ptr %378, align 4
  Value *v379 = B.CreateAlignedLoad(B.getInt32Ty(), v378, MaybeAlign(4));
  // %380 = add nsw i32 %379, %376
  Value *v380 = B.CreateAdd(v379, v376, "", false, true);
  // store i32 %380, ptr %378, align 4
  B.CreateAlignedStore(v380, v378, MaybeAlign(4));
  // br label %381
  B.CreateBr(bb381);

  // 381:
  B.SetInsertPoint(bb381);
  // %382 = select i1 %318, i1 %327, i1 false
  Value *v382 = B.CreateSelect(v318, v327, B.getInt1(false));
  // %383 = select i1 %382, i1 %328, i1 false
  Value *v383 = B.CreateSelect(v382, v328, B.getInt1(false));
  // %384 = select i1 %383, i1 %359, i1 false
  Value *v384 = B.CreateSelect(v383, v359, B.getInt1(false));
  // br i1 %384, label %385, label %393
  B.CreateCondBr(v384, bb385, bb393);

  // 385:
  B.SetInsertPoint(bb385);
  // %386 = sub nuw nsw i32 15, %326
  Value *v386 = B.CreateSub(B.getInt32(15), v326, "", true, true);
  // %387 = mul nuw nsw i32 %386, 125
  Value *v387 = B.CreateMul(v386, B.getInt32(125), "", true, true);
  // %388 = add nsw i32 %330, 1
  Value *v388 = B.CreateAdd(v330, B.getInt32(1), "", false, true);
  // %389 = zext nneg i32 %388 to i64
  Value *v389 = B.CreateZExt(v388, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v389)->setNonNeg(true);
  // %390 = getelementptr inbounds i32, ptr %59, i64 %389
  Value *v390 = B.CreateGEP(B.getInt32Ty(), v59, {v389}, "", true);
  // %391 = load i32, ptr %390, align 4
  Value *v391 = B.CreateAlignedLoad(B.getInt32Ty(), v390, MaybeAlign(4));
  // %392 = add nsw i32 %391, %387
  Value *v392 = B.CreateAdd(v391, v387, "", false, true);
  // store i32 %392, ptr %390, align 4
  B.CreateAlignedStore(v392, v390, MaybeAlign(4));
  // br label %393
  B.CreateBr(bb393);

  // 393:
  B.SetInsertPoint(bb393);
  // %394 = select i1 %320, i1 %327, i1 false
  Value *v394 = B.CreateSelect(v320, v327, B.getInt1(false));
  // %395 = select i1 %394, i1 %328, i1 false
  Value *v395 = B.CreateSelect(v394, v328, B.getInt1(false));
  // %396 = select i1 %395, i1 %346, i1 false
  Value *v396 = B.CreateSelect(v395, v346, B.getInt1(false));
  // br i1 %396, label %397, label %405
  B.CreateCondBr(v396, bb397, bb405);

  // 397:
  B.SetInsertPoint(bb397);
  // %398 = sub nuw nsw i32 12, %326
  Value *v398 = B.CreateSub(B.getInt32(12), v326, "", true, true);
  // %399 = mul nuw nsw i32 %398, 125
  Value *v399 = B.CreateMul(v398, B.getInt32(125), "", true, true);
  // %400 = add nsw i32 %330, 2
  Value *v400 = B.CreateAdd(v330, B.getInt32(2), "", false, true);
  // %401 = zext nneg i32 %400 to i64
  Value *v401 = B.CreateZExt(v400, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v401)->setNonNeg(true);
  // %402 = getelementptr inbounds i32, ptr %59, i64 %401
  Value *v402 = B.CreateGEP(B.getInt32Ty(), v59, {v401}, "", true);
  // %403 = load i32, ptr %402, align 4
  Value *v403 = B.CreateAlignedLoad(B.getInt32Ty(), v402, MaybeAlign(4));
  // %404 = add nsw i32 %403, %399
  Value *v404 = B.CreateAdd(v403, v399, "", false, true);
  // store i32 %404, ptr %402, align 4
  B.CreateAlignedStore(v404, v402, MaybeAlign(4));
  // br label %405
  B.CreateBr(bb405);

  // 405:
  B.SetInsertPoint(bb405);
  // %406 = select i1 %322, i1 %327, i1 false
  Value *v406 = B.CreateSelect(v322, v327, B.getInt1(false));
  // %407 = select i1 %406, i1 %328, i1 false
  Value *v407 = B.CreateSelect(v406, v328, B.getInt1(false));
  // %408 = select i1 %407, i1 %333, i1 false
  Value *v408 = B.CreateSelect(v407, v333, B.getInt1(false));
  // br i1 %408, label %409, label %417
  B.CreateCondBr(v408, bb409, bb417);

  // 409:
  B.SetInsertPoint(bb409);
  // %410 = sub nuw nsw i32 7, %326
  Value *v410 = B.CreateSub(B.getInt32(7), v326, "", true, true);
  // %411 = mul nuw nsw i32 %410, 125
  Value *v411 = B.CreateMul(v410, B.getInt32(125), "", true, true);
  // %412 = add nsw i32 %330, 3
  Value *v412 = B.CreateAdd(v330, B.getInt32(3), "", false, true);
  // %413 = zext nneg i32 %412 to i64
  Value *v413 = B.CreateZExt(v412, B.getInt64Ty());
  cast<PossiblyNonNegInst>(v413)->setNonNeg(true);
  // %414 = getelementptr inbounds i32, ptr %59, i64 %413
  Value *v414 = B.CreateGEP(B.getInt32Ty(), v59, {v413}, "", true);
  // %415 = load i32, ptr %414, align 4
  Value *v415 = B.CreateAlignedLoad(B.getInt32Ty(), v414, MaybeAlign(4));
  // %416 = add nsw i32 %415, %411
  Value *v416 = B.CreateAdd(v415, v411, "", false, true);
  // store i32 %416, ptr %414, align 4
  B.CreateAlignedStore(v416, v414, MaybeAlign(4));
  // br label %417
  B.CreateBr(bb417);

  // 417:
  B.SetInsertPoint(bb417);
  // %418 = add nsw i32 %324, 1
  Value *v418 = B.CreateAdd(v324, B.getInt32(1), "", false, true);
  // %419 = icmp eq i32 %324, 4
  Value *v419 = B.CreateICmp(CmpInst::ICMP_EQ, v324, B.getInt32(4));
  // br i1 %419, label %420, label %323
  B.CreateCondBr(v419, bb420, bb323);

  // 420:
  B.SetInsertPoint(bb420);
  // call void @drawFrame(ptr noundef %59, ptr noundef nonnull %3, ptr noundef nonnull %4, i32 noundef %66, i32 noundef %69)
  B.CreateCall(fn_drawFrame, {v59, v3, v4, v66, v69});
  // tail call void (...) @simFlush() #10
  B.CreateCall(fn_simFlush, {})->setTailCall();
  // br label %302
  B.CreateBr(bb302);

  // 302:
  B.SetInsertPoint(bb302);
  // %303 = xor i1 %60, true
  Value *v303 = B.CreateXor(v60, B.getInt1(true));
  // br label %57
  B.CreateBr(bb57);

  // Входящие значения phi
  v6->addIncoming(B.getInt64(0LL), bb0);
  v6->addIncoming(v18, bb17);
  v24->addIncoming(B.getInt64(0LL), bb5);
  v24->addIncoming(v51, bb28);
  v29->addIncoming(B.getInt1(true), bb25);
  v29->addIncoming(v15, bb27);
  v29->addIncoming(B.getInt1(true), bb23);
  v29->addIncoming(B.getInt1(true), bb25);
  v58->addIncoming(v1, bb20);
  v58->addIncoming(v59, bb302);
  v59->addIncoming(v2, bb20);
  v59->addIncoming(v58, bb302);
  v60->addIncoming(B.getInt1(true), bb20);
  v60->addIncoming(v303, bb302);
  v61->addIncoming(B.getInt32(0), bb20);
  v61->addIncoming(v301, bb302);
  v62->addIncoming(B.getInt32(0), bb20);
  v62->addIncoming(v300, bb302);
  v63->addIncoming(B.getInt32(65536), bb20);
  v63->addIncoming(v298, bb302);
  v216->addIncoming(v268, bb267);
  v216->addIncoming(B.getInt64(1LL), bb185);
  v219->addIncoming(B.getInt64(1LL), bb215);
  v219->addIncoming(B.getInt64(505LL), bb220);
  v221->addIncoming(v265, bb220);
  v221->addIncoming(B.getInt64(0LL), bb215);
  v271->addIncoming(v294, bb270);
  v271->addIncoming(v219, bb218);
  v324->addIncoming(B.getInt32(-4), bb304);
  v324->addIncoming(v418, bb417);
}

} // namespace

Function *generateApp(Module &M) {
  IRBuilder<> B(M.getContext());

  // Внешние функции: графический интерфейс sim.h и интринсики
  // void (i64, ptr) @llvm.lifetime.start.p0
  fn_llvm_lifetime_start_p0 = Function::Create(FunctionType::get(B.getVoidTy(), {B.getInt64Ty(), B.getPtrTy()}, false), Function::ExternalLinkage, "llvm.lifetime.start.p0", M);
  // void (i32, i32, i32) @simPutPixel
  fn_simPutPixel = Function::Create(FunctionType::get(B.getVoidTy(), {B.getInt32Ty(), B.getInt32Ty(), B.getInt32Ty()}, false), Function::ExternalLinkage, "simPutPixel", M);
  // void (ptr, i8, i64, i1) @llvm.memset.p0.i64
  fn_llvm_memset_p0_i64 = Function::Create(FunctionType::get(B.getVoidTy(), {B.getPtrTy(), B.getInt8Ty(), B.getInt64Ty(), B.getInt1Ty()}, false), Function::ExternalLinkage, "llvm.memset.p0.i64", M);
  // i32 (...) @simRand
  fn_simRand = Function::Create(FunctionType::get(B.getInt32Ty(), {}, true), Function::ExternalLinkage, "simRand", M);
  // void (...) @simFlush
  fn_simFlush = Function::Create(FunctionType::get(B.getVoidTy(), {}, true), Function::ExternalLinkage, "simFlush", M);
  // i32 (i32, i32) @llvm.umin.i32
  fn_llvm_umin_i32 = Function::Create(FunctionType::get(B.getInt32Ty(), {B.getInt32Ty(), B.getInt32Ty()}, false), Function::ExternalLinkage, "llvm.umin.i32", M);

  // Функции логического модуля
  fn_putCell = Function::Create(FunctionType::get(B.getVoidTy(), {B.getInt32Ty(), B.getInt32Ty(), B.getInt32Ty()}, false), Function::ExternalLinkage, "putCell", M);
  fn_putCell->setDSOLocal(true);
  fn_drawFrame = Function::Create(FunctionType::get(B.getVoidTy(), {B.getPtrTy(), B.getPtrTy(), B.getPtrTy(), B.getInt32Ty(), B.getInt32Ty()}, false), Function::ExternalLinkage, "drawFrame", M);
  fn_drawFrame->setDSOLocal(true);
  fn_app = Function::Create(FunctionType::get(B.getVoidTy(), {}, false), Function::ExternalLinkage, "app", M);
  fn_app->setDSOLocal(true);

  build_putCell(B, fn_putCell);
  build_drawFrame(B, fn_drawFrame);
  build_app(B, fn_app);
  return fn_app;
}
