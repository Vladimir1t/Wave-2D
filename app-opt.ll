; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local noundef i32 @clamp255(i32 noundef %0) local_unnamed_addr #0 {
  %2 = icmp slt i32 %0, 0
  %3 = tail call i32 @llvm.umin.i32(i32 %0, i32 255)
  %4 = select i1 %2, i32 0, i32 %3
  ret i32 %4
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable
define dso_local i32 @isInsideCircle(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #0 {
  %6 = sub nsw i32 %0, %2
  %7 = sub nsw i32 %1, %3
  %8 = mul nsw i32 %6, %6
  %9 = mul nsw i32 %7, %7
  %10 = add nuw nsw i32 %9, %8
  %11 = mul nsw i32 %4, %4
  %12 = icmp ult i32 %10, %11
  %13 = zext i1 %12 to i32
  ret i32 %13
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nofree norecurse nosync nounwind memory(argmem: write) uwtable
define dso_local void @initPool(ptr nocapture noundef writeonly %0) local_unnamed_addr #2 {
  br label %2

2:                                                ; preds = %1, %15
  %3 = phi i64 [ 0, %1 ], [ %16, %15 ]
  %4 = icmp eq i64 %3, 0
  %5 = add nsw i64 %3, -128
  %6 = mul nsw i64 %5, %5
  %7 = add nsw i64 %3, -55
  %8 = mul nsw i64 %7, %7
  %9 = add nsw i64 %3, -201
  %10 = mul nsw i64 %9, %9
  %11 = shl nuw nsw i64 %3, 9
  %12 = icmp eq i64 %3, 255
  %13 = getelementptr i32, ptr %0, i64 %11
  br label %18

14:                                               ; preds = %15
  ret void

15:                                               ; preds = %23
  %16 = add nuw nsw i64 %3, 1
  %17 = icmp eq i64 %16, 256
  br i1 %17, label %14, label %2, !llvm.loop !5

18:                                               ; preds = %2, %23
  %19 = phi i64 [ 0, %2 ], [ %46, %23 ]
  br i1 %4, label %23, label %20

20:                                               ; preds = %18
  %21 = trunc i64 %19 to i32
  switch i32 %21, label %22 [
    i32 511, label %23
    i32 0, label %23
  ]

22:                                               ; preds = %20
  br label %23

23:                                               ; preds = %20, %20, %18, %22
  %24 = phi i1 [ true, %20 ], [ %12, %22 ], [ true, %18 ], [ true, %20 ]
  %25 = add nsw i64 %19, -256
  %26 = mul nsw i64 %25, %25
  %27 = add nuw nsw i64 %26, %6
  %28 = trunc i64 %27 to i32
  %29 = icmp ult i32 %28, 1156
  %30 = or i1 %29, %24
  %31 = add nsw i64 %19, -60
  %32 = mul nsw i64 %31, %31
  %33 = add nuw nsw i64 %32, %8
  %34 = trunc i64 %33 to i32
  %35 = icmp ult i32 %34, 484
  %36 = or i1 %35, %30
  %37 = add nsw i64 %19, -442
  %38 = mul nsw i64 %37, %37
  %39 = add nuw nsw i64 %38, %10
  %40 = trunc i64 %39 to i32
  %41 = icmp ult i32 %40, 324
  %42 = or i1 %41, %36
  %43 = xor i1 %42, true
  %44 = sext i1 %43 to i32
  %45 = getelementptr i32, ptr %13, i64 %19
  store i32 %44, ptr %45, align 4, !tbaa !7
  %46 = add nuw nsw i64 %19, 1
  %47 = icmp eq i64 %46, 512
  br i1 %47, label %15, label %18, !llvm.loop !11
}

; Function Attrs: nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable
define dso_local void @addDrop(ptr nocapture noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #3 {
  %6 = sub nsw i32 0, %3
  %7 = icmp slt i32 %3, 0
  br i1 %7, label %17, label %8

8:                                                ; preds = %5
  %9 = mul nsw i32 %3, %3
  br label %10

10:                                               ; preds = %18, %8
  %11 = phi i32 [ %6, %8 ], [ %19, %18 ]
  %12 = add nsw i32 %11, %2
  %13 = mul nsw i32 %11, %11
  %14 = icmp sgt i32 %12, 0
  %15 = icmp slt i32 %12, 255
  %16 = shl nuw nsw i32 %12, 9
  br label %21

17:                                               ; preds = %18, %5
  ret void

18:                                               ; preds = %41
  %19 = add i32 %11, 1
  %20 = icmp eq i32 %11, %3
  br i1 %20, label %17, label %10, !llvm.loop !12

21:                                               ; preds = %10, %41
  %22 = phi i32 [ %6, %10 ], [ %42, %41 ]
  %23 = add nsw i32 %22, %1
  %24 = mul nsw i32 %22, %22
  %25 = add nuw nsw i32 %24, %13
  %26 = add i32 %23, -1
  %27 = icmp ult i32 %26, 510
  %28 = select i1 %27, i1 %14, i1 false
  %29 = select i1 %28, i1 %15, i1 false
  %30 = icmp ult i32 %25, %9
  %31 = select i1 %29, i1 %30, i1 false
  br i1 %31, label %32, label %41

32:                                               ; preds = %21
  %33 = sub nsw i32 %9, %25
  %34 = mul nsw i32 %33, %4
  %35 = sdiv i32 %34, %9
  %36 = add nuw nsw i32 %23, %16
  %37 = zext nneg i32 %36 to i64
  %38 = getelementptr inbounds i32, ptr %0, i64 %37
  %39 = load i32, ptr %38, align 4, !tbaa !7
  %40 = add nsw i32 %39, %35
  store i32 %40, ptr %38, align 4, !tbaa !7
  br label %41

41:                                               ; preds = %32, %21
  %42 = add i32 %22, 1
  %43 = icmp eq i32 %22, %3
  br i1 %43, label %18, label %21, !llvm.loop !13
}

; Function Attrs: nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable
define dso_local void @waveStep(ptr nocapture noundef readonly %0, ptr nocapture noundef %1, ptr nocapture noundef readonly %2) local_unnamed_addr #3 {
  %4 = getelementptr i8, ptr %1, i64 2052
  %5 = getelementptr i8, ptr %1, i64 522236
  %6 = getelementptr i8, ptr %0, i64 4
  %7 = getelementptr i8, ptr %0, i64 524284
  %8 = getelementptr i8, ptr %2, i64 2052
  %9 = getelementptr i8, ptr %2, i64 522236
  %10 = icmp ult ptr %4, %7
  %11 = icmp ult ptr %6, %5
  %12 = and i1 %10, %11
  %13 = icmp ult ptr %4, %9
  %14 = icmp ult ptr %8, %5
  %15 = and i1 %13, %14
  %16 = or i1 %12, %15
  br label %17

17:                                               ; preds = %3, %70
  %18 = phi i64 [ 1, %3 ], [ %71, %70 ]
  %19 = shl nuw nsw i64 %18, 9
  br i1 %16, label %20, label %22

20:                                               ; preds = %22, %17
  %21 = phi i64 [ 1, %17 ], [ 505, %22 ]
  br label %73

22:                                               ; preds = %17, %22
  %23 = phi i64 [ %67, %22 ], [ 0, %17 ]
  %24 = or disjoint i64 %23, 1
  %25 = add nuw nsw i64 %24, %19
  %26 = getelementptr i32, ptr %0, i64 %25
  %27 = getelementptr i32, ptr %26, i64 -1
  %28 = getelementptr i32, ptr %26, i64 3
  %29 = load <4 x i32>, ptr %27, align 4, !tbaa !7, !alias.scope !14
  %30 = load <4 x i32>, ptr %28, align 4, !tbaa !7, !alias.scope !14
  %31 = getelementptr i32, ptr %26, i64 1
  %32 = getelementptr i32, ptr %26, i64 5
  %33 = load <4 x i32>, ptr %31, align 4, !tbaa !7, !alias.scope !14
  %34 = load <4 x i32>, ptr %32, align 4, !tbaa !7, !alias.scope !14
  %35 = add nsw <4 x i32> %33, %29
  %36 = add nsw <4 x i32> %34, %30
  %37 = getelementptr i32, ptr %26, i64 -512
  %38 = getelementptr i32, ptr %26, i64 -508
  %39 = load <4 x i32>, ptr %37, align 4, !tbaa !7, !alias.scope !14
  %40 = load <4 x i32>, ptr %38, align 4, !tbaa !7, !alias.scope !14
  %41 = add nsw <4 x i32> %35, %39
  %42 = add nsw <4 x i32> %36, %40
  %43 = getelementptr i32, ptr %26, i64 512
  %44 = getelementptr i32, ptr %26, i64 516
  %45 = load <4 x i32>, ptr %43, align 4, !tbaa !7, !alias.scope !14
  %46 = load <4 x i32>, ptr %44, align 4, !tbaa !7, !alias.scope !14
  %47 = add nsw <4 x i32> %41, %45
  %48 = add nsw <4 x i32> %42, %46
  %49 = ashr <4 x i32> %47, <i32 1, i32 1, i32 1, i32 1>
  %50 = ashr <4 x i32> %48, <i32 1, i32 1, i32 1, i32 1>
  %51 = getelementptr inbounds i32, ptr %1, i64 %25
  %52 = getelementptr inbounds i32, ptr %51, i64 4
  %53 = load <4 x i32>, ptr %51, align 4, !tbaa !7, !alias.scope !17, !noalias !19
  %54 = load <4 x i32>, ptr %52, align 4, !tbaa !7, !alias.scope !17, !noalias !19
  %55 = sub nsw <4 x i32> %49, %53
  %56 = sub nsw <4 x i32> %50, %54
  %57 = ashr <4 x i32> %55, <i32 6, i32 6, i32 6, i32 6>
  %58 = ashr <4 x i32> %56, <i32 6, i32 6, i32 6, i32 6>
  %59 = sub nsw <4 x i32> %55, %57
  %60 = sub nsw <4 x i32> %56, %58
  %61 = getelementptr inbounds i32, ptr %2, i64 %25
  %62 = getelementptr inbounds i32, ptr %61, i64 4
  %63 = load <4 x i32>, ptr %61, align 4, !tbaa !7, !alias.scope !21
  %64 = load <4 x i32>, ptr %62, align 4, !tbaa !7, !alias.scope !21
  %65 = and <4 x i32> %59, %63
  %66 = and <4 x i32> %60, %64
  store <4 x i32> %65, ptr %51, align 4, !tbaa !7, !alias.scope !17, !noalias !19
  store <4 x i32> %66, ptr %52, align 4, !tbaa !7, !alias.scope !17, !noalias !19
  %67 = add nuw i64 %23, 8
  %68 = icmp eq i64 %67, 504
  br i1 %68, label %20, label %22, !llvm.loop !22

69:                                               ; preds = %70
  ret void

70:                                               ; preds = %73
  %71 = add nuw nsw i64 %18, 1
  %72 = icmp eq i64 %71, 255
  br i1 %72, label %69, label %17, !llvm.loop !25

73:                                               ; preds = %20, %73
  %74 = phi i64 [ %97, %73 ], [ %21, %20 ]
  %75 = add nuw nsw i64 %74, %19
  %76 = getelementptr i32, ptr %0, i64 %75
  %77 = getelementptr i32, ptr %76, i64 -1
  %78 = load i32, ptr %77, align 4, !tbaa !7
  %79 = getelementptr i32, ptr %76, i64 1
  %80 = load i32, ptr %79, align 4, !tbaa !7
  %81 = add nsw i32 %80, %78
  %82 = getelementptr i32, ptr %76, i64 -512
  %83 = load i32, ptr %82, align 4, !tbaa !7
  %84 = add nsw i32 %81, %83
  %85 = getelementptr i32, ptr %76, i64 512
  %86 = load i32, ptr %85, align 4, !tbaa !7
  %87 = add nsw i32 %84, %86
  %88 = ashr i32 %87, 1
  %89 = getelementptr inbounds i32, ptr %1, i64 %75
  %90 = load i32, ptr %89, align 4, !tbaa !7
  %91 = sub nsw i32 %88, %90
  %92 = ashr i32 %91, 6
  %93 = sub nsw i32 %91, %92
  %94 = getelementptr inbounds i32, ptr %2, i64 %75
  %95 = load i32, ptr %94, align 4, !tbaa !7
  %96 = and i32 %93, %95
  store i32 %96, ptr %89, align 4, !tbaa !7
  %97 = add nuw nsw i64 %74, 1
  %98 = icmp eq i64 %97, 511
  br i1 %98, label %70, label %73, !llvm.loop !26
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable
define dso_local i32 @waterColor(ptr nocapture noundef readonly %0, i32 noundef %1) local_unnamed_addr #4 {
  %3 = sext i32 %1 to i64
  %4 = getelementptr i32, ptr %0, i64 %3
  %5 = getelementptr i32, ptr %4, i64 -1
  %6 = load i32, ptr %5, align 4, !tbaa !7
  %7 = getelementptr i32, ptr %4, i64 1
  %8 = load i32, ptr %7, align 4, !tbaa !7
  %9 = getelementptr i32, ptr %4, i64 -512
  %10 = load i32, ptr %9, align 4, !tbaa !7
  %11 = getelementptr i32, ptr %4, i64 512
  %12 = load i32, ptr %11, align 4, !tbaa !7
  %13 = add i32 %6, %10
  %14 = add i32 %8, %12
  %15 = sub i32 %13, %14
  %16 = ashr i32 %15, 2
  %17 = add nsw i32 %16, 90
  %18 = load i32, ptr %4, align 4, !tbaa !7
  %19 = ashr i32 %18, 4
  %20 = add nsw i32 %17, %19
  %21 = icmp slt i32 %20, 0
  %22 = tail call i32 @llvm.umin.i32(i32 %20, i32 255)
  %23 = select i1 %21, i32 0, i32 %22
  %24 = mul nuw nsw i32 %23, %23
  %25 = mul nuw nsw i32 %24, %23
  %26 = and i32 %25, 16711680
  %27 = lshr i32 %24, 8
  %28 = tail call i32 @llvm.umin.i32(i32 %27, i32 225)
  %29 = tail call i32 @llvm.umin.i32(i32 %23, i32 175)
  %30 = shl nuw nsw i32 %28, 8
  %31 = or disjoint i32 %26, -16769456
  %32 = or disjoint i32 %30, %29
  %33 = add nsw i32 %31, %32
  ret i32 %33
}

; Function Attrs: nounwind uwtable
define dso_local void @putCell(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #5 {
  %4 = mul nsw i32 %0, 3
  %5 = mul nsw i32 %1, 3
  tail call void @simPutPixel(i32 noundef %4, i32 noundef %5, i32 noundef %2) #10
  %6 = add nsw i32 %4, 1
  tail call void @simPutPixel(i32 noundef %6, i32 noundef %5, i32 noundef %2) #10
  %7 = add nsw i32 %4, 2
  tail call void @simPutPixel(i32 noundef %7, i32 noundef %5, i32 noundef %2) #10
  %8 = add nsw i32 %5, 1
  tail call void @simPutPixel(i32 noundef %4, i32 noundef %8, i32 noundef %2) #10
  tail call void @simPutPixel(i32 noundef %6, i32 noundef %8, i32 noundef %2) #10
  tail call void @simPutPixel(i32 noundef %7, i32 noundef %8, i32 noundef %2) #10
  %9 = add nsw i32 %5, 2
  tail call void @simPutPixel(i32 noundef %4, i32 noundef %9, i32 noundef %2) #10
  tail call void @simPutPixel(i32 noundef %6, i32 noundef %9, i32 noundef %2) #10
  tail call void @simPutPixel(i32 noundef %7, i32 noundef %9, i32 noundef %2) #10
  ret void
}

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #6

; Function Attrs: nounwind uwtable
define dso_local void @drawFrame(ptr nocapture noundef readonly %0, ptr nocapture noundef readonly %1, ptr nocapture noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #5 {
  br label %6

6:                                                ; preds = %5, %14
  %7 = phi i64 [ 0, %5 ], [ %15, %14 ]
  %8 = shl nuw nsw i64 %7, 9
  %9 = trunc i64 %7 to i32
  %10 = sub i32 %9, %4
  %11 = mul nsw i32 %10, %10
  %12 = trunc i64 %7 to i32
  br label %17

13:                                               ; preds = %14
  ret void

14:                                               ; preds = %67
  %15 = add nuw nsw i64 %7, 1
  %16 = icmp eq i64 %15, 256
  br i1 %16, label %13, label %6, !llvm.loop !27

17:                                               ; preds = %6, %67
  %18 = phi i64 [ 0, %6 ], [ %68, %67 ]
  %19 = add nuw nsw i64 %18, %8
  %20 = getelementptr inbounds i32, ptr %1, i64 %19
  %21 = load i32, ptr %20, align 4, !tbaa !7
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %54, label %23

23:                                               ; preds = %17
  %24 = getelementptr i32, ptr %0, i64 %19
  %25 = getelementptr i32, ptr %24, i64 -1
  %26 = load i32, ptr %25, align 4, !tbaa !7
  %27 = getelementptr i32, ptr %24, i64 1
  %28 = load i32, ptr %27, align 4, !tbaa !7
  %29 = getelementptr i32, ptr %24, i64 -512
  %30 = load i32, ptr %29, align 4, !tbaa !7
  %31 = getelementptr i32, ptr %24, i64 512
  %32 = load i32, ptr %31, align 4, !tbaa !7
  %33 = add i32 %26, %30
  %34 = add i32 %28, %32
  %35 = sub i32 %33, %34
  %36 = ashr i32 %35, 2
  %37 = add nsw i32 %36, 90
  %38 = load i32, ptr %24, align 4, !tbaa !7
  %39 = ashr i32 %38, 4
  %40 = add nsw i32 %37, %39
  %41 = icmp slt i32 %40, 0
  %42 = tail call i32 @llvm.umin.i32(i32 %40, i32 255)
  %43 = select i1 %41, i32 0, i32 %42
  %44 = mul nuw nsw i32 %43, %43
  %45 = mul nuw nsw i32 %44, %43
  %46 = and i32 %45, 16711680
  %47 = lshr i32 %44, 8
  %48 = tail call i32 @llvm.umin.i32(i32 %47, i32 225)
  %49 = tail call i32 @llvm.umin.i32(i32 %43, i32 175)
  %50 = shl nuw nsw i32 %48, 8
  %51 = add nuw nsw i32 %49, -16769456
  %52 = or disjoint i32 %51, %46
  %53 = add nuw nsw i32 %52, %50
  br label %54

54:                                               ; preds = %17, %23
  %55 = phi i32 [ %53, %23 ], [ -3626642, %17 ]
  %56 = trunc i64 %18 to i32
  %57 = sub i32 %56, %3
  %58 = mul nsw i32 %57, %57
  %59 = add nuw nsw i32 %58, %11
  %60 = icmp ugt i32 %59, 3
  %61 = select i1 %60, i32 %55, i32 -44992
  %62 = getelementptr inbounds i32, ptr %2, i64 %19
  %63 = load i32, ptr %62, align 4, !tbaa !7
  %64 = icmp eq i32 %61, %63
  br i1 %64, label %67, label %65

65:                                               ; preds = %54
  store i32 %61, ptr %62, align 4, !tbaa !7
  %66 = trunc i64 %18 to i32
  tail call void @putCell(i32 noundef %66, i32 noundef %12, i32 noundef %61)
  br label %67

67:                                               ; preds = %65, %54
  %68 = add nuw nsw i64 %18, 1
  %69 = icmp eq i64 %68, 512
  br i1 %69, label %14, label %17, !llvm.loop !28
}

; Function Attrs: noreturn nounwind uwtable
define dso_local void @app() local_unnamed_addr #7 {
  %1 = alloca [131072 x i32], align 16
  %2 = alloca [131072 x i32], align 16
  %3 = alloca [131072 x i32], align 16
  %4 = alloca [131072 x i32], align 16
  call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %1) #10
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(524288) %1, i8 0, i64 524288, i1 false)
  call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %2) #10
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(524288) %2, i8 0, i64 524288, i1 false)
  call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %3) #10
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(524288) %3, i8 0, i64 524288, i1 false)
  call void @llvm.lifetime.start.p0(i64 524288, ptr nonnull %4) #10
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(524288) %4, i8 0, i64 524288, i1 false)
  br label %5

5:                                                ; preds = %17, %0
  %6 = phi i64 [ 0, %0 ], [ %18, %17 ]
  %7 = icmp eq i64 %6, 0
  %8 = add nsw i64 %6, -128
  %9 = mul nsw i64 %8, %8
  %10 = add nsw i64 %6, -55
  %11 = mul nsw i64 %10, %10
  %12 = add nsw i64 %6, -201
  %13 = mul nsw i64 %12, %12
  %14 = shl nuw nsw i64 %6, 9
  %15 = icmp eq i64 %6, 255
  %16 = getelementptr i32, ptr %3, i64 %14
  br label %23

17:                                               ; preds = %28
  %18 = add nuw nsw i64 %6, 1
  %19 = icmp eq i64 %18, 256
  br i1 %19, label %20, label %5, !llvm.loop !5

20:                                               ; preds = %17
  %21 = getelementptr inbounds i8, ptr %3, i64 2052
  %22 = getelementptr inbounds i8, ptr %3, i64 522236
  br label %57

23:                                               ; preds = %28, %5
  %24 = phi i64 [ 0, %5 ], [ %51, %28 ]
  br i1 %7, label %28, label %25

25:                                               ; preds = %23
  %26 = trunc i64 %24 to i32
  switch i32 %26, label %27 [
    i32 511, label %28
    i32 0, label %28
  ]

27:                                               ; preds = %25
  br label %28

28:                                               ; preds = %27, %25, %25, %23
  %29 = phi i1 [ true, %25 ], [ %15, %27 ], [ true, %23 ], [ true, %25 ]
  %30 = add nsw i64 %24, -256
  %31 = mul nsw i64 %30, %30
  %32 = add nuw nsw i64 %31, %9
  %33 = trunc i64 %32 to i32
  %34 = icmp ult i32 %33, 1156
  %35 = or i1 %34, %29
  %36 = add nsw i64 %24, -60
  %37 = mul nsw i64 %36, %36
  %38 = add nuw nsw i64 %37, %11
  %39 = trunc i64 %38 to i32
  %40 = icmp ult i32 %39, 484
  %41 = or i1 %40, %35
  %42 = add nsw i64 %24, -442
  %43 = mul nsw i64 %42, %42
  %44 = add nuw nsw i64 %43, %13
  %45 = trunc i64 %44 to i32
  %46 = icmp ult i32 %45, 324
  %47 = or i1 %46, %41
  %48 = xor i1 %47, true
  %49 = sext i1 %48 to i32
  %50 = getelementptr i32, ptr %16, i64 %24
  store i32 %49, ptr %50, align 4, !tbaa !7
  %51 = add nuw nsw i64 %24, 1
  %52 = icmp eq i64 %51, 512
  br i1 %52, label %17, label %23, !llvm.loop !11

53:                                               ; preds = %296
  %54 = tail call i32 (...) @simRand() #10
  %55 = and i32 %54, 3
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %304, label %420

57:                                               ; preds = %302, %20
  %58 = phi ptr [ %1, %20 ], [ %59, %302 ]
  %59 = phi ptr [ %2, %20 ], [ %58, %302 ]
  %60 = phi i1 [ true, %20 ], [ %303, %302 ]
  %61 = phi i32 [ 0, %20 ], [ %301, %302 ]
  %62 = phi i32 [ 0, %20 ], [ %300, %302 ]
  %63 = phi i32 [ 65536, %20 ], [ %298, %302 ]
  %64 = mul nsw i32 %63, 150
  %65 = sdiv i32 %64, 65536
  %66 = add nsw i32 %65, 256
  %67 = mul nsw i32 %62, 80
  %68 = sdiv i32 %67, 65536
  %69 = add nsw i32 %68, 128
  %70 = udiv i32 %61, 5
  %71 = shl nuw nsw i32 %70, 1
  %72 = and i32 %71, 2
  %73 = mul nuw nsw i32 %72, 500
  %74 = add nsw i32 %73, -500
  %75 = add nsw i32 %65, 255
  %76 = add nsw i32 %65, 257
  %77 = icmp sgt i32 %62, -104039
  %78 = icmp slt i32 %62, 104858
  %79 = shl nsw i32 %68, 9
  %80 = add nsw i32 %79, 65024
  %81 = add nsw i32 %65, 254
  %82 = icmp ult i32 %81, 510
  %83 = select i1 %82, i1 %77, i1 false
  %84 = select i1 %83, i1 %78, i1 false
  br i1 %84, label %85, label %92

85:                                               ; preds = %57
  %86 = ashr exact i32 %74, 1
  %87 = add nuw nsw i32 %75, %80
  %88 = zext nneg i32 %87 to i64
  %89 = getelementptr inbounds i32, ptr %58, i64 %88
  %90 = load i32, ptr %89, align 4, !tbaa !7
  %91 = add nsw i32 %90, %86
  store i32 %91, ptr %89, align 4, !tbaa !7
  br label %92

92:                                               ; preds = %85, %57
  %93 = add nsw i32 %65, 255
  %94 = icmp ult i32 %93, 510
  %95 = select i1 %94, i1 %77, i1 false
  %96 = select i1 %95, i1 %78, i1 false
  br i1 %96, label %97, label %105

97:                                               ; preds = %92
  %98 = mul nsw i32 %74, 3
  %99 = ashr exact i32 %98, 2
  %100 = add nuw nsw i32 %66, %80
  %101 = zext nneg i32 %100 to i64
  %102 = getelementptr inbounds i32, ptr %58, i64 %101
  %103 = load i32, ptr %102, align 4, !tbaa !7
  %104 = add nsw i32 %103, %99
  store i32 %104, ptr %102, align 4, !tbaa !7
  br label %105

105:                                              ; preds = %97, %92
  %106 = icmp ult i32 %66, 510
  %107 = select i1 %106, i1 %77, i1 false
  %108 = select i1 %107, i1 %78, i1 false
  br i1 %108, label %109, label %116

109:                                              ; preds = %105
  %110 = ashr exact i32 %74, 1
  %111 = add nuw nsw i32 %76, %80
  %112 = zext nneg i32 %111 to i64
  %113 = getelementptr inbounds i32, ptr %58, i64 %112
  %114 = load i32, ptr %113, align 4, !tbaa !7
  %115 = add nsw i32 %114, %110
  store i32 %115, ptr %113, align 4, !tbaa !7
  br label %116

116:                                              ; preds = %109, %105
  %117 = icmp sgt i32 %62, -104858
  %118 = icmp slt i32 %62, 104039
  %119 = shl nuw nsw i32 %69, 9
  %120 = select i1 %82, i1 %117, i1 false
  %121 = select i1 %120, i1 %118, i1 false
  br i1 %121, label %122, label %130

122:                                              ; preds = %116
  %123 = mul nsw i32 %74, 3
  %124 = ashr exact i32 %123, 2
  %125 = add nuw nsw i32 %75, %119
  %126 = zext nneg i32 %125 to i64
  %127 = getelementptr inbounds i32, ptr %58, i64 %126
  %128 = load i32, ptr %127, align 4, !tbaa !7
  %129 = add nsw i32 %128, %124
  store i32 %129, ptr %127, align 4, !tbaa !7
  br label %130

130:                                              ; preds = %122, %116
  %131 = select i1 %94, i1 %117, i1 false
  %132 = select i1 %131, i1 %118, i1 false
  br i1 %132, label %133, label %139

133:                                              ; preds = %130
  %134 = add nuw nsw i32 %66, %119
  %135 = zext nneg i32 %134 to i64
  %136 = getelementptr inbounds i32, ptr %58, i64 %135
  %137 = load i32, ptr %136, align 4, !tbaa !7
  %138 = add nsw i32 %137, %74
  store i32 %138, ptr %136, align 4, !tbaa !7
  br label %139

139:                                              ; preds = %133, %130
  %140 = select i1 %106, i1 %117, i1 false
  %141 = select i1 %140, i1 %118, i1 false
  br i1 %141, label %142, label %150

142:                                              ; preds = %139
  %143 = mul nsw i32 %74, 3
  %144 = ashr exact i32 %143, 2
  %145 = add nuw nsw i32 %76, %119
  %146 = zext nneg i32 %145 to i64
  %147 = getelementptr inbounds i32, ptr %58, i64 %146
  %148 = load i32, ptr %147, align 4, !tbaa !7
  %149 = add nsw i32 %148, %144
  store i32 %149, ptr %147, align 4, !tbaa !7
  br label %150

150:                                              ; preds = %142, %139
  %151 = icmp sgt i32 %62, -105677
  %152 = icmp slt i32 %62, 103220
  %153 = shl nsw i32 %68, 9
  %154 = add nsw i32 %153, 66048
  %155 = select i1 %82, i1 %151, i1 false
  %156 = select i1 %155, i1 %152, i1 false
  br i1 %156, label %157, label %164

157:                                              ; preds = %150
  %158 = ashr exact i32 %74, 1
  %159 = add nuw nsw i32 %75, %154
  %160 = zext nneg i32 %159 to i64
  %161 = getelementptr inbounds i32, ptr %58, i64 %160
  %162 = load i32, ptr %161, align 4, !tbaa !7
  %163 = add nsw i32 %162, %158
  store i32 %163, ptr %161, align 4, !tbaa !7
  br label %164

164:                                              ; preds = %157, %150
  %165 = select i1 %94, i1 %151, i1 false
  %166 = select i1 %165, i1 %152, i1 false
  br i1 %166, label %167, label %175

167:                                              ; preds = %164
  %168 = mul nsw i32 %74, 3
  %169 = ashr exact i32 %168, 2
  %170 = add nuw nsw i32 %66, %154
  %171 = zext nneg i32 %170 to i64
  %172 = getelementptr inbounds i32, ptr %58, i64 %171
  %173 = load i32, ptr %172, align 4, !tbaa !7
  %174 = add nsw i32 %173, %169
  store i32 %174, ptr %172, align 4, !tbaa !7
  br label %175

175:                                              ; preds = %167, %164
  %176 = select i1 %106, i1 %151, i1 false
  %177 = select i1 %176, i1 %152, i1 false
  br i1 %177, label %178, label %185

178:                                              ; preds = %175
  %179 = ashr exact i32 %74, 1
  %180 = add nuw nsw i32 %76, %154
  %181 = zext nneg i32 %180 to i64
  %182 = getelementptr inbounds i32, ptr %58, i64 %181
  %183 = load i32, ptr %182, align 4, !tbaa !7
  %184 = add nsw i32 %183, %179
  store i32 %184, ptr %182, align 4, !tbaa !7
  br label %185

185:                                              ; preds = %178, %175
  %186 = getelementptr i8, ptr %59, i64 2052
  %187 = getelementptr i8, ptr %59, i64 522236
  %188 = getelementptr i8, ptr %58, i64 2048
  %189 = getelementptr i8, ptr %58, i64 522232
  %190 = getelementptr i8, ptr %58, i64 2056
  %191 = getelementptr i8, ptr %58, i64 522240
  %192 = getelementptr i8, ptr %58, i64 4
  %193 = getelementptr i8, ptr %58, i64 520188
  %194 = getelementptr i8, ptr %58, i64 4100
  %195 = getelementptr i8, ptr %58, i64 524284
  %196 = icmp ult ptr %186, %189
  %197 = icmp ult ptr %188, %187
  %198 = and i1 %196, %197
  %199 = icmp ult ptr %186, %191
  %200 = icmp ult ptr %190, %187
  %201 = and i1 %199, %200
  %202 = or i1 %198, %201
  %203 = icmp ult ptr %186, %193
  %204 = icmp ult ptr %192, %187
  %205 = and i1 %203, %204
  %206 = or i1 %202, %205
  %207 = icmp ult ptr %186, %195
  %208 = icmp ult ptr %194, %187
  %209 = and i1 %207, %208
  %210 = or i1 %206, %209
  %211 = icmp ult ptr %186, %22
  %212 = icmp ult ptr %21, %187
  %213 = and i1 %211, %212
  %214 = or i1 %210, %213
  br label %215

215:                                              ; preds = %185, %267
  %216 = phi i64 [ %268, %267 ], [ 1, %185 ]
  %217 = shl nuw nsw i64 %216, 9
  br i1 %214, label %218, label %220

218:                                              ; preds = %220, %215
  %219 = phi i64 [ 1, %215 ], [ 505, %220 ]
  br label %270

220:                                              ; preds = %215, %220
  %221 = phi i64 [ %265, %220 ], [ 0, %215 ]
  %222 = or disjoint i64 %221, 1
  %223 = add nuw nsw i64 %222, %217
  %224 = getelementptr i32, ptr %58, i64 %223
  %225 = getelementptr i32, ptr %224, i64 -1
  %226 = getelementptr i32, ptr %224, i64 3
  %227 = load <4 x i32>, ptr %225, align 4, !tbaa !7, !alias.scope !29
  %228 = load <4 x i32>, ptr %226, align 4, !tbaa !7, !alias.scope !29
  %229 = getelementptr i32, ptr %224, i64 1
  %230 = getelementptr i32, ptr %224, i64 5
  %231 = load <4 x i32>, ptr %229, align 4, !tbaa !7, !alias.scope !32
  %232 = load <4 x i32>, ptr %230, align 4, !tbaa !7, !alias.scope !32
  %233 = add nsw <4 x i32> %231, %227
  %234 = add nsw <4 x i32> %232, %228
  %235 = getelementptr i32, ptr %224, i64 -512
  %236 = getelementptr i32, ptr %224, i64 -508
  %237 = load <4 x i32>, ptr %235, align 4, !tbaa !7, !alias.scope !34
  %238 = load <4 x i32>, ptr %236, align 4, !tbaa !7, !alias.scope !34
  %239 = add nsw <4 x i32> %233, %237
  %240 = add nsw <4 x i32> %234, %238
  %241 = getelementptr i32, ptr %224, i64 512
  %242 = getelementptr i32, ptr %224, i64 516
  %243 = load <4 x i32>, ptr %241, align 4, !tbaa !7, !alias.scope !36
  %244 = load <4 x i32>, ptr %242, align 4, !tbaa !7, !alias.scope !36
  %245 = add nsw <4 x i32> %239, %243
  %246 = add nsw <4 x i32> %240, %244
  %247 = ashr <4 x i32> %245, <i32 1, i32 1, i32 1, i32 1>
  %248 = ashr <4 x i32> %246, <i32 1, i32 1, i32 1, i32 1>
  %249 = getelementptr inbounds i32, ptr %59, i64 %223
  %250 = getelementptr inbounds i32, ptr %249, i64 4
  %251 = load <4 x i32>, ptr %249, align 4, !tbaa !7, !alias.scope !38, !noalias !40
  %252 = load <4 x i32>, ptr %250, align 4, !tbaa !7, !alias.scope !38, !noalias !40
  %253 = sub nsw <4 x i32> %247, %251
  %254 = sub nsw <4 x i32> %248, %252
  %255 = ashr <4 x i32> %253, <i32 6, i32 6, i32 6, i32 6>
  %256 = ashr <4 x i32> %254, <i32 6, i32 6, i32 6, i32 6>
  %257 = sub nsw <4 x i32> %253, %255
  %258 = sub nsw <4 x i32> %254, %256
  %259 = getelementptr inbounds i32, ptr %3, i64 %223
  %260 = getelementptr inbounds i32, ptr %259, i64 4
  %261 = load <4 x i32>, ptr %259, align 4, !tbaa !7, !alias.scope !42
  %262 = load <4 x i32>, ptr %260, align 4, !tbaa !7, !alias.scope !42
  %263 = and <4 x i32> %257, %261
  %264 = and <4 x i32> %258, %262
  store <4 x i32> %263, ptr %249, align 4, !tbaa !7, !alias.scope !38, !noalias !40
  store <4 x i32> %264, ptr %250, align 4, !tbaa !7, !alias.scope !38, !noalias !40
  %265 = add nuw i64 %221, 8
  %266 = icmp eq i64 %265, 504
  br i1 %266, label %218, label %220, !llvm.loop !43

267:                                              ; preds = %270
  %268 = add nuw nsw i64 %216, 1
  %269 = icmp eq i64 %268, 255
  br i1 %269, label %296, label %215, !llvm.loop !25

270:                                              ; preds = %218, %270
  %271 = phi i64 [ %294, %270 ], [ %219, %218 ]
  %272 = add nuw nsw i64 %271, %217
  %273 = getelementptr i32, ptr %58, i64 %272
  %274 = getelementptr i32, ptr %273, i64 -1
  %275 = load i32, ptr %274, align 4, !tbaa !7
  %276 = getelementptr i32, ptr %273, i64 1
  %277 = load i32, ptr %276, align 4, !tbaa !7
  %278 = add nsw i32 %277, %275
  %279 = getelementptr i32, ptr %273, i64 -512
  %280 = load i32, ptr %279, align 4, !tbaa !7
  %281 = add nsw i32 %278, %280
  %282 = getelementptr i32, ptr %273, i64 512
  %283 = load i32, ptr %282, align 4, !tbaa !7
  %284 = add nsw i32 %281, %283
  %285 = ashr i32 %284, 1
  %286 = getelementptr inbounds i32, ptr %59, i64 %272
  %287 = load i32, ptr %286, align 4, !tbaa !7
  %288 = sub nsw i32 %285, %287
  %289 = ashr i32 %288, 6
  %290 = sub nsw i32 %288, %289
  %291 = getelementptr inbounds i32, ptr %3, i64 %272
  %292 = load i32, ptr %291, align 4, !tbaa !7
  %293 = and i32 %290, %292
  store i32 %293, ptr %286, align 4, !tbaa !7
  %294 = add nuw nsw i64 %271, 1
  %295 = icmp eq i64 %294, 511
  br i1 %295, label %267, label %270, !llvm.loop !44

296:                                              ; preds = %267
  %297 = ashr i32 %62, 8
  %298 = sub nsw i32 %63, %297
  %299 = ashr i32 %298, 8
  %300 = add nsw i32 %299, %62
  %301 = add nuw nsw i32 %61, 1
  br i1 %60, label %302, label %53

302:                                              ; preds = %296, %420
  %303 = xor i1 %60, true
  br label %57, !llvm.loop !45

304:                                              ; preds = %53
  %305 = tail call i32 (...) @simRand() #10
  %306 = srem i32 %305, 510
  %307 = add nsw i32 %306, 1
  %308 = tail call i32 (...) @simRand() #10
  %309 = srem i32 %308, 254
  %310 = add nsw i32 %309, 1
  %311 = add nsw i32 %306, -3
  %312 = icmp ult i32 %311, 510
  %313 = add nsw i32 %306, -2
  %314 = icmp ult i32 %313, 510
  %315 = add nsw i32 %306, -1
  %316 = icmp ult i32 %315, 510
  %317 = icmp ult i32 %306, 510
  %318 = icmp ult i32 %307, 510
  %319 = add nsw i32 %306, 2
  %320 = icmp ult i32 %319, 510
  %321 = add nsw i32 %306, 3
  %322 = icmp ult i32 %321, 510
  br label %323

323:                                              ; preds = %304, %417
  %324 = phi i32 [ -4, %304 ], [ %418, %417 ]
  %325 = add nsw i32 %310, %324
  %326 = mul nsw i32 %324, %324
  %327 = icmp sgt i32 %325, 0
  %328 = icmp slt i32 %325, 255
  %329 = shl nuw nsw i32 %325, 9
  %330 = add i32 %307, %329
  %331 = select i1 %312, i1 %327, i1 false
  %332 = select i1 %331, i1 %328, i1 false
  %333 = icmp ult i32 %326, 7
  %334 = select i1 %332, i1 %333, i1 false
  br i1 %334, label %335, label %343

335:                                              ; preds = %323
  %336 = sub nuw nsw i32 7, %326
  %337 = mul nuw nsw i32 %336, 125
  %338 = add nsw i32 %330, -3
  %339 = zext nneg i32 %338 to i64
  %340 = getelementptr inbounds i32, ptr %59, i64 %339
  %341 = load i32, ptr %340, align 4, !tbaa !7
  %342 = add nsw i32 %341, %337
  store i32 %342, ptr %340, align 4, !tbaa !7
  br label %343

343:                                              ; preds = %335, %323
  %344 = select i1 %314, i1 %327, i1 false
  %345 = select i1 %344, i1 %328, i1 false
  %346 = icmp ult i32 %326, 12
  %347 = select i1 %345, i1 %346, i1 false
  br i1 %347, label %348, label %356

348:                                              ; preds = %343
  %349 = sub nuw nsw i32 12, %326
  %350 = mul nuw nsw i32 %349, 125
  %351 = add nsw i32 %330, -2
  %352 = zext nneg i32 %351 to i64
  %353 = getelementptr inbounds i32, ptr %59, i64 %352
  %354 = load i32, ptr %353, align 4, !tbaa !7
  %355 = add nsw i32 %354, %350
  store i32 %355, ptr %353, align 4, !tbaa !7
  br label %356

356:                                              ; preds = %348, %343
  %357 = select i1 %316, i1 %327, i1 false
  %358 = select i1 %357, i1 %328, i1 false
  %359 = icmp ult i32 %326, 15
  %360 = select i1 %358, i1 %359, i1 false
  br i1 %360, label %361, label %369

361:                                              ; preds = %356
  %362 = sub nuw nsw i32 15, %326
  %363 = mul nuw nsw i32 %362, 125
  %364 = add nuw nsw i32 %306, %329
  %365 = zext nneg i32 %364 to i64
  %366 = getelementptr inbounds i32, ptr %59, i64 %365
  %367 = load i32, ptr %366, align 4, !tbaa !7
  %368 = add nsw i32 %367, %363
  store i32 %368, ptr %366, align 4, !tbaa !7
  br label %369

369:                                              ; preds = %361, %356
  %370 = select i1 %317, i1 %327, i1 false
  %371 = select i1 %370, i1 %328, i1 false
  %372 = icmp ult i32 %326, 16
  %373 = select i1 %371, i1 %372, i1 false
  br i1 %373, label %374, label %381

374:                                              ; preds = %369
  %375 = sub nuw nsw i32 16, %326
  %376 = mul nuw nsw i32 %375, 125
  %377 = zext nneg i32 %330 to i64
  %378 = getelementptr inbounds i32, ptr %59, i64 %377
  %379 = load i32, ptr %378, align 4, !tbaa !7
  %380 = add nsw i32 %379, %376
  store i32 %380, ptr %378, align 4, !tbaa !7
  br label %381

381:                                              ; preds = %374, %369
  %382 = select i1 %318, i1 %327, i1 false
  %383 = select i1 %382, i1 %328, i1 false
  %384 = select i1 %383, i1 %359, i1 false
  br i1 %384, label %385, label %393

385:                                              ; preds = %381
  %386 = sub nuw nsw i32 15, %326
  %387 = mul nuw nsw i32 %386, 125
  %388 = add nsw i32 %330, 1
  %389 = zext nneg i32 %388 to i64
  %390 = getelementptr inbounds i32, ptr %59, i64 %389
  %391 = load i32, ptr %390, align 4, !tbaa !7
  %392 = add nsw i32 %391, %387
  store i32 %392, ptr %390, align 4, !tbaa !7
  br label %393

393:                                              ; preds = %385, %381
  %394 = select i1 %320, i1 %327, i1 false
  %395 = select i1 %394, i1 %328, i1 false
  %396 = select i1 %395, i1 %346, i1 false
  br i1 %396, label %397, label %405

397:                                              ; preds = %393
  %398 = sub nuw nsw i32 12, %326
  %399 = mul nuw nsw i32 %398, 125
  %400 = add nsw i32 %330, 2
  %401 = zext nneg i32 %400 to i64
  %402 = getelementptr inbounds i32, ptr %59, i64 %401
  %403 = load i32, ptr %402, align 4, !tbaa !7
  %404 = add nsw i32 %403, %399
  store i32 %404, ptr %402, align 4, !tbaa !7
  br label %405

405:                                              ; preds = %397, %393
  %406 = select i1 %322, i1 %327, i1 false
  %407 = select i1 %406, i1 %328, i1 false
  %408 = select i1 %407, i1 %333, i1 false
  br i1 %408, label %409, label %417

409:                                              ; preds = %405
  %410 = sub nuw nsw i32 7, %326
  %411 = mul nuw nsw i32 %410, 125
  %412 = add nsw i32 %330, 3
  %413 = zext nneg i32 %412 to i64
  %414 = getelementptr inbounds i32, ptr %59, i64 %413
  %415 = load i32, ptr %414, align 4, !tbaa !7
  %416 = add nsw i32 %415, %411
  store i32 %416, ptr %414, align 4, !tbaa !7
  br label %417

417:                                              ; preds = %405, %409
  %418 = add nsw i32 %324, 1
  %419 = icmp eq i32 %324, 4
  br i1 %419, label %420, label %323, !llvm.loop !12

420:                                              ; preds = %417, %53
  call void @drawFrame(ptr noundef %59, ptr noundef nonnull %3, ptr noundef nonnull %4, i32 noundef %66, i32 noundef %69)
  tail call void (...) @simFlush() #10
  br label %302
}

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #8

declare i32 @simRand(...) local_unnamed_addr #6

declare void @simFlush(...) local_unnamed_addr #6

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.umin.i32(i32, i32) #9

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { nofree norecurse nosync nounwind memory(argmem: write) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nofree norecurse nosync nounwind willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { noreturn nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #9 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #10 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = !{!8, !8, i64 0}
!8 = !{!"int", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C/C++ TBAA"}
!11 = distinct !{!11, !6}
!12 = distinct !{!12, !6}
!13 = distinct !{!13, !6}
!14 = !{!15}
!15 = distinct !{!15, !16}
!16 = distinct !{!16, !"LVerDomain"}
!17 = !{!18}
!18 = distinct !{!18, !16}
!19 = !{!15, !20}
!20 = distinct !{!20, !16}
!21 = !{!20}
!22 = distinct !{!22, !6, !23, !24}
!23 = !{!"llvm.loop.isvectorized", i32 1}
!24 = !{!"llvm.loop.unroll.runtime.disable"}
!25 = distinct !{!25, !6}
!26 = distinct !{!26, !6, !23}
!27 = distinct !{!27, !6}
!28 = distinct !{!28, !6}
!29 = !{!30}
!30 = distinct !{!30, !31}
!31 = distinct !{!31, !"LVerDomain"}
!32 = !{!33}
!33 = distinct !{!33, !31}
!34 = !{!35}
!35 = distinct !{!35, !31}
!36 = !{!37}
!37 = distinct !{!37, !31}
!38 = !{!39}
!39 = distinct !{!39, !31}
!40 = !{!30, !33, !35, !37, !41}
!41 = distinct !{!41, !31}
!42 = !{!41}
!43 = distinct !{!43, !6, !23, !24}
!44 = distinct !{!44, !6, !23}
!45 = distinct !{!45, !6}
