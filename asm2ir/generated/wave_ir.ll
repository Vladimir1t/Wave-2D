; ModuleID = 'wave32_pure'
source_filename = "wave32_pure"

define void @wave32_app(ptr %0) {
start:
  %r.ptr = getelementptr i32, ptr %0, i32 0
  store i32 0, ptr %r.ptr, align 4
  %r.ptr1 = getelementptr i32, ptr %0, i32 1
  store i32 1, ptr %r.ptr1, align 4
  %r.ptr2 = getelementptr i32, ptr %0, i32 2
  store i32 2, ptr %r.ptr2, align 4
  %r.ptr3 = getelementptr i32, ptr %0, i32 3
  store i32 3, ptr %r.ptr3, align 4
  %r.ptr4 = getelementptr i32, ptr %0, i32 4
  store i32 65536, ptr %r.ptr4, align 4
  %r.ptr5 = getelementptr i32, ptr %0, i32 5
  store i32 0, ptr %r.ptr5, align 4
  %r.ptr6 = getelementptr i32, ptr %0, i32 6
  store i32 406, ptr %r.ptr6, align 4
  %r.ptr7 = getelementptr i32, ptr %0, i32 7
  store i32 128, ptr %r.ptr7, align 4
  %r.ptr8 = getelementptr i32, ptr %0, i32 8
  store i32 0, ptr %r.ptr8, align 4
  %r.ptr9 = getelementptr i32, ptr %0, i32 9
  store i32 0, ptr %r.ptr9, align 4
  br label %pool_y

pool_y:                                           ; preds = %pool_next_y, %start
  %r.ptr10 = getelementptr i32, ptr %0, i32 9
  %r = load i32, ptr %r.ptr10, align 4
  %1 = icmp slt i32 %r, 256
  %2 = zext i1 %1 to i32
  %r.ptr11 = getelementptr i32, ptr %0, i32 10
  store i32 %2, ptr %r.ptr11, align 4
  %r.ptr12 = getelementptr i32, ptr %0, i32 10
  %r13 = load i32, ptr %r.ptr12, align 4
  %3 = icmp ne i32 %r13, 0
  br i1 %3, label %pool_y_body, label %pool_done

pool_y_body:                                      ; preds = %pool_y
  %r.ptr14 = getelementptr i32, ptr %0, i32 11
  store i32 0, ptr %r.ptr14, align 4
  br label %pool_x

pool_x:                                           ; preds = %pool_cell, %pool_y_body
  %r.ptr15 = getelementptr i32, ptr %0, i32 11
  %r16 = load i32, ptr %r.ptr15, align 4
  %4 = icmp slt i32 %r16, 512
  %5 = zext i1 %4 to i32
  %r.ptr17 = getelementptr i32, ptr %0, i32 10
  store i32 %5, ptr %r.ptr17, align 4
  %r.ptr18 = getelementptr i32, ptr %0, i32 10
  %r19 = load i32, ptr %r.ptr18, align 4
  %6 = icmp ne i32 %r19, 0
  br i1 %6, label %pool_cell, label %pool_next_y

pool_cell:                                        ; preds = %pool_x
  %r.ptr20 = getelementptr i32, ptr %0, i32 11
  %r21 = load i32, ptr %r.ptr20, align 4
  %7 = icmp eq i32 %r21, 0
  %8 = zext i1 %7 to i32
  %r.ptr22 = getelementptr i32, ptr %0, i32 12
  store i32 %8, ptr %r.ptr22, align 4
  %r.ptr23 = getelementptr i32, ptr %0, i32 9
  %r24 = load i32, ptr %r.ptr23, align 4
  %9 = icmp eq i32 %r24, 0
  %10 = zext i1 %9 to i32
  %r.ptr25 = getelementptr i32, ptr %0, i32 13
  store i32 %10, ptr %r.ptr25, align 4
  %r.ptr26 = getelementptr i32, ptr %0, i32 13
  %r27 = load i32, ptr %r.ptr26, align 4
  %r.ptr28 = getelementptr i32, ptr %0, i32 12
  %r29 = load i32, ptr %r.ptr28, align 4
  %11 = or i32 %r29, %r27
  %r.ptr30 = getelementptr i32, ptr %0, i32 12
  store i32 %11, ptr %r.ptr30, align 4
  %r.ptr31 = getelementptr i32, ptr %0, i32 11
  %r32 = load i32, ptr %r.ptr31, align 4
  %12 = icmp eq i32 %r32, 511
  %13 = zext i1 %12 to i32
  %r.ptr33 = getelementptr i32, ptr %0, i32 13
  store i32 %13, ptr %r.ptr33, align 4
  %r.ptr34 = getelementptr i32, ptr %0, i32 13
  %r35 = load i32, ptr %r.ptr34, align 4
  %r.ptr36 = getelementptr i32, ptr %0, i32 12
  %r37 = load i32, ptr %r.ptr36, align 4
  %14 = or i32 %r37, %r35
  %r.ptr38 = getelementptr i32, ptr %0, i32 12
  store i32 %14, ptr %r.ptr38, align 4
  %r.ptr39 = getelementptr i32, ptr %0, i32 9
  %r40 = load i32, ptr %r.ptr39, align 4
  %15 = icmp eq i32 %r40, 255
  %16 = zext i1 %15 to i32
  %r.ptr41 = getelementptr i32, ptr %0, i32 13
  store i32 %16, ptr %r.ptr41, align 4
  %r.ptr42 = getelementptr i32, ptr %0, i32 13
  %r43 = load i32, ptr %r.ptr42, align 4
  %r.ptr44 = getelementptr i32, ptr %0, i32 12
  %r45 = load i32, ptr %r.ptr44, align 4
  %17 = or i32 %r45, %r43
  %r.ptr46 = getelementptr i32, ptr %0, i32 12
  store i32 %17, ptr %r.ptr46, align 4
  %r.ptr47 = getelementptr i32, ptr %0, i32 11
  %r48 = load i32, ptr %r.ptr47, align 4
  %18 = sub i32 %r48, 256
  %r.ptr49 = getelementptr i32, ptr %0, i32 9
  %r50 = load i32, ptr %r.ptr49, align 4
  %19 = sub i32 %r50, 128
  %20 = mul i32 %19, %19
  %21 = mul i32 %18, %18
  %22 = add i32 %21, %20
  %23 = icmp slt i32 %22, 1156
  %24 = zext i1 %23 to i32
  %r.ptr51 = getelementptr i32, ptr %0, i32 13
  store i32 %24, ptr %r.ptr51, align 4
  %r.ptr52 = getelementptr i32, ptr %0, i32 13
  %r53 = load i32, ptr %r.ptr52, align 4
  %r.ptr54 = getelementptr i32, ptr %0, i32 12
  %r55 = load i32, ptr %r.ptr54, align 4
  %25 = or i32 %r55, %r53
  %r.ptr56 = getelementptr i32, ptr %0, i32 12
  store i32 %25, ptr %r.ptr56, align 4
  %r.ptr57 = getelementptr i32, ptr %0, i32 11
  %r58 = load i32, ptr %r.ptr57, align 4
  %26 = sub i32 %r58, 60
  %r.ptr59 = getelementptr i32, ptr %0, i32 9
  %r60 = load i32, ptr %r.ptr59, align 4
  %27 = sub i32 %r60, 55
  %28 = mul i32 %27, %27
  %29 = mul i32 %26, %26
  %30 = add i32 %29, %28
  %31 = icmp slt i32 %30, 484
  %32 = zext i1 %31 to i32
  %r.ptr61 = getelementptr i32, ptr %0, i32 13
  store i32 %32, ptr %r.ptr61, align 4
  %r.ptr62 = getelementptr i32, ptr %0, i32 13
  %r63 = load i32, ptr %r.ptr62, align 4
  %r.ptr64 = getelementptr i32, ptr %0, i32 12
  %r65 = load i32, ptr %r.ptr64, align 4
  %33 = or i32 %r65, %r63
  %r.ptr66 = getelementptr i32, ptr %0, i32 12
  store i32 %33, ptr %r.ptr66, align 4
  %r.ptr67 = getelementptr i32, ptr %0, i32 11
  %r68 = load i32, ptr %r.ptr67, align 4
  %34 = sub i32 %r68, 442
  %r.ptr69 = getelementptr i32, ptr %0, i32 9
  %r70 = load i32, ptr %r.ptr69, align 4
  %35 = sub i32 %r70, 201
  %36 = mul i32 %35, %35
  %37 = mul i32 %34, %34
  %38 = add i32 %37, %36
  %39 = icmp slt i32 %38, 324
  %40 = zext i1 %39 to i32
  %r.ptr71 = getelementptr i32, ptr %0, i32 13
  store i32 %40, ptr %r.ptr71, align 4
  %r.ptr72 = getelementptr i32, ptr %0, i32 13
  %r73 = load i32, ptr %r.ptr72, align 4
  %r.ptr74 = getelementptr i32, ptr %0, i32 12
  %r75 = load i32, ptr %r.ptr74, align 4
  %41 = or i32 %r75, %r73
  %r.ptr76 = getelementptr i32, ptr %0, i32 12
  store i32 %41, ptr %r.ptr76, align 4
  %r.ptr77 = getelementptr i32, ptr %0, i32 12
  %r78 = load i32, ptr %r.ptr77, align 4
  %42 = sub i32 %r78, 1
  %r.ptr79 = getelementptr i32, ptr %0, i32 14
  store i32 %42, ptr %r.ptr79, align 4
  %r.ptr80 = getelementptr i32, ptr %0, i32 9
  %r81 = load i32, ptr %r.ptr80, align 4
  %43 = shl i32 %r81, 9
  %r.ptr82 = getelementptr i32, ptr %0, i32 15
  store i32 %43, ptr %r.ptr82, align 4
  %r.ptr83 = getelementptr i32, ptr %0, i32 11
  %r84 = load i32, ptr %r.ptr83, align 4
  %r.ptr85 = getelementptr i32, ptr %0, i32 15
  %r86 = load i32, ptr %r.ptr85, align 4
  %44 = add i32 %r86, %r84
  %r.ptr87 = getelementptr i32, ptr %0, i32 15
  store i32 %44, ptr %r.ptr87, align 4
  %r.ptr88 = getelementptr i32, ptr %0, i32 14
  %r89 = load i32, ptr %r.ptr88, align 4
  %r.ptr90 = getelementptr i32, ptr %0, i32 15
  %r91 = load i32, ptr %r.ptr90, align 4
  %r.ptr92 = getelementptr i32, ptr %0, i32 2
  %r93 = load i32, ptr %r.ptr92, align 4
  %45 = mul i32 %r93, 131072
  %46 = add i32 %45, %r91
  %47 = add i32 %46, 128
  %mem.ptr = getelementptr i32, ptr %0, i32 %47
  store i32 %r89, ptr %mem.ptr, align 4
  %r.ptr94 = getelementptr i32, ptr %0, i32 11
  %r95 = load i32, ptr %r.ptr94, align 4
  %48 = add i32 %r95, 1
  %r.ptr96 = getelementptr i32, ptr %0, i32 11
  store i32 %48, ptr %r.ptr96, align 4
  br label %pool_x

pool_next_y:                                      ; preds = %pool_x
  %r.ptr97 = getelementptr i32, ptr %0, i32 9
  %r98 = load i32, ptr %r.ptr97, align 4
  %49 = add i32 %r98, 1
  %r.ptr99 = getelementptr i32, ptr %0, i32 9
  store i32 %49, ptr %r.ptr99, align 4
  br label %pool_y

pool_done:                                        ; preds = %pool_y
  br label %frame_start

frame_start:                                      ; preds = %frame_flush, %pool_done
  %r.ptr100 = getelementptr i32, ptr %0, i32 16
  store i32 0, ptr %r.ptr100, align 4
  br label %wave_s_test

wave_s_test:                                      ; preds = %wave_done, %frame_start
  %r.ptr101 = getelementptr i32, ptr %0, i32 16
  %r102 = load i32, ptr %r.ptr101, align 4
  %50 = icmp slt i32 %r102, 2
  %51 = zext i1 %50 to i32
  %r.ptr103 = getelementptr i32, ptr %0, i32 10
  store i32 %51, ptr %r.ptr103, align 4
  %r.ptr104 = getelementptr i32, ptr %0, i32 10
  %r105 = load i32, ptr %r.ptr104, align 4
  %52 = icmp ne i32 %r105, 0
  br i1 %52, label %wave_s_body, label %rain_start

wave_s_body:                                      ; preds = %wave_s_test
  %r.ptr106 = getelementptr i32, ptr %0, i32 4
  %r107 = load i32, ptr %r.ptr106, align 4
  %53 = mul i32 %r107, 150
  %r.ptr108 = getelementptr i32, ptr %0, i32 6
  store i32 %53, ptr %r.ptr108, align 4
  %r.ptr109 = getelementptr i32, ptr %0, i32 6
  %r110 = load i32, ptr %r.ptr109, align 4
  %54 = sdiv i32 %r110, 65536
  %r.ptr111 = getelementptr i32, ptr %0, i32 6
  store i32 %54, ptr %r.ptr111, align 4
  %r.ptr112 = getelementptr i32, ptr %0, i32 6
  %r113 = load i32, ptr %r.ptr112, align 4
  %55 = add i32 %r113, 256
  %r.ptr114 = getelementptr i32, ptr %0, i32 6
  store i32 %55, ptr %r.ptr114, align 4
  %r.ptr115 = getelementptr i32, ptr %0, i32 5
  %r116 = load i32, ptr %r.ptr115, align 4
  %56 = mul i32 %r116, 80
  %r.ptr117 = getelementptr i32, ptr %0, i32 7
  store i32 %56, ptr %r.ptr117, align 4
  %r.ptr118 = getelementptr i32, ptr %0, i32 7
  %r119 = load i32, ptr %r.ptr118, align 4
  %57 = sdiv i32 %r119, 65536
  %r.ptr120 = getelementptr i32, ptr %0, i32 7
  store i32 %57, ptr %r.ptr120, align 4
  %r.ptr121 = getelementptr i32, ptr %0, i32 7
  %r122 = load i32, ptr %r.ptr121, align 4
  %58 = add i32 %r122, 128
  %r.ptr123 = getelementptr i32, ptr %0, i32 7
  store i32 %58, ptr %r.ptr123, align 4
  %r.ptr124 = getelementptr i32, ptr %0, i32 8
  %r125 = load i32, ptr %r.ptr124, align 4
  %59 = sdiv i32 %r125, 5
  %r.ptr126 = getelementptr i32, ptr %0, i32 17
  store i32 %59, ptr %r.ptr126, align 4
  %r.ptr127 = getelementptr i32, ptr %0, i32 17
  %r128 = load i32, ptr %r.ptr127, align 4
  %60 = and i32 %r128, 1
  %r.ptr129 = getelementptr i32, ptr %0, i32 17
  store i32 %60, ptr %r.ptr129, align 4
  %r.ptr130 = getelementptr i32, ptr %0, i32 17
  %r131 = load i32, ptr %r.ptr130, align 4
  %61 = mul i32 %r131, 2
  %r.ptr132 = getelementptr i32, ptr %0, i32 17
  store i32 %61, ptr %r.ptr132, align 4
  %r.ptr133 = getelementptr i32, ptr %0, i32 17
  %r134 = load i32, ptr %r.ptr133, align 4
  %62 = sub i32 %r134, 1
  %r.ptr135 = getelementptr i32, ptr %0, i32 17
  store i32 %62, ptr %r.ptr135, align 4
  %r.ptr136 = getelementptr i32, ptr %0, i32 17
  %r137 = load i32, ptr %r.ptr136, align 4
  %63 = mul i32 %r137, 500
  %r.ptr138 = getelementptr i32, ptr %0, i32 17
  store i32 %63, ptr %r.ptr138, align 4
  %r.ptr139 = getelementptr i32, ptr %0, i32 6
  %r140 = load i32, ptr %r.ptr139, align 4
  %r.ptr141 = getelementptr i32, ptr %0, i32 18
  store i32 %r140, ptr %r.ptr141, align 4
  %r.ptr142 = getelementptr i32, ptr %0, i32 7
  %r143 = load i32, ptr %r.ptr142, align 4
  %r.ptr144 = getelementptr i32, ptr %0, i32 19
  store i32 %r143, ptr %r.ptr144, align 4
  %r.ptr145 = getelementptr i32, ptr %0, i32 20
  store i32 2, ptr %r.ptr145, align 4
  %r.ptr146 = getelementptr i32, ptr %0, i32 20
  %r147 = load i32, ptr %r.ptr146, align 4
  %64 = sub i32 0, %r147
  %r.ptr148 = getelementptr i32, ptr %0, i32 21
  store i32 %64, ptr %r.ptr148, align 4
  br label %source_dy_test

source_dy_test:                                   ; preds = %source_next_y, %wave_s_body
  %r.ptr149 = getelementptr i32, ptr %0, i32 20
  %r150 = load i32, ptr %r.ptr149, align 4
  %r.ptr151 = getelementptr i32, ptr %0, i32 21
  %r152 = load i32, ptr %r.ptr151, align 4
  %65 = icmp sle i32 %r152, %r150
  %66 = zext i1 %65 to i32
  %r.ptr153 = getelementptr i32, ptr %0, i32 10
  store i32 %66, ptr %r.ptr153, align 4
  %r.ptr154 = getelementptr i32, ptr %0, i32 10
  %r155 = load i32, ptr %r.ptr154, align 4
  %67 = icmp ne i32 %r155, 0
  br i1 %67, label %source_dy_body, label %source_done

source_dy_body:                                   ; preds = %source_dy_test
  %r.ptr156 = getelementptr i32, ptr %0, i32 20
  %r157 = load i32, ptr %r.ptr156, align 4
  %68 = sub i32 0, %r157
  %r.ptr158 = getelementptr i32, ptr %0, i32 22
  store i32 %68, ptr %r.ptr158, align 4
  br label %source_dx_test

source_dx_test:                                   ; preds = %source_next_x, %source_dy_body
  %r.ptr159 = getelementptr i32, ptr %0, i32 20
  %r160 = load i32, ptr %r.ptr159, align 4
  %r.ptr161 = getelementptr i32, ptr %0, i32 22
  %r162 = load i32, ptr %r.ptr161, align 4
  %69 = icmp sle i32 %r162, %r160
  %70 = zext i1 %69 to i32
  %r.ptr163 = getelementptr i32, ptr %0, i32 10
  store i32 %70, ptr %r.ptr163, align 4
  %r.ptr164 = getelementptr i32, ptr %0, i32 10
  %r165 = load i32, ptr %r.ptr164, align 4
  %71 = icmp ne i32 %r165, 0
  br i1 %71, label %source_cell, label %source_next_y

source_cell:                                      ; preds = %source_dx_test
  %r.ptr166 = getelementptr i32, ptr %0, i32 22
  %r167 = load i32, ptr %r.ptr166, align 4
  %r.ptr168 = getelementptr i32, ptr %0, i32 18
  %r169 = load i32, ptr %r.ptr168, align 4
  %72 = add i32 %r169, %r167
  %r.ptr170 = getelementptr i32, ptr %0, i32 23
  store i32 %72, ptr %r.ptr170, align 4
  %r.ptr171 = getelementptr i32, ptr %0, i32 21
  %r172 = load i32, ptr %r.ptr171, align 4
  %r.ptr173 = getelementptr i32, ptr %0, i32 19
  %r174 = load i32, ptr %r.ptr173, align 4
  %73 = add i32 %r174, %r172
  %r.ptr175 = getelementptr i32, ptr %0, i32 24
  store i32 %73, ptr %r.ptr175, align 4
  %r.ptr176 = getelementptr i32, ptr %0, i32 22
  %r177 = load i32, ptr %r.ptr176, align 4
  %r.ptr178 = getelementptr i32, ptr %0, i32 22
  %r179 = load i32, ptr %r.ptr178, align 4
  %74 = mul i32 %r179, %r177
  %r.ptr180 = getelementptr i32, ptr %0, i32 25
  store i32 %74, ptr %r.ptr180, align 4
  %r.ptr181 = getelementptr i32, ptr %0, i32 21
  %r182 = load i32, ptr %r.ptr181, align 4
  %r.ptr183 = getelementptr i32, ptr %0, i32 21
  %r184 = load i32, ptr %r.ptr183, align 4
  %75 = mul i32 %r184, %r182
  %r.ptr185 = getelementptr i32, ptr %0, i32 13
  store i32 %75, ptr %r.ptr185, align 4
  %r.ptr186 = getelementptr i32, ptr %0, i32 13
  %r187 = load i32, ptr %r.ptr186, align 4
  %r.ptr188 = getelementptr i32, ptr %0, i32 25
  %r189 = load i32, ptr %r.ptr188, align 4
  %76 = add i32 %r189, %r187
  %r.ptr190 = getelementptr i32, ptr %0, i32 25
  store i32 %76, ptr %r.ptr190, align 4
  %r.ptr191 = getelementptr i32, ptr %0, i32 20
  %r192 = load i32, ptr %r.ptr191, align 4
  %r.ptr193 = getelementptr i32, ptr %0, i32 20
  %r194 = load i32, ptr %r.ptr193, align 4
  %77 = mul i32 %r194, %r192
  %r.ptr195 = getelementptr i32, ptr %0, i32 26
  store i32 %77, ptr %r.ptr195, align 4
  %r.ptr196 = getelementptr i32, ptr %0, i32 23
  %r197 = load i32, ptr %r.ptr196, align 4
  %78 = icmp sgt i32 %r197, 0
  %79 = zext i1 %78 to i32
  %r.ptr198 = getelementptr i32, ptr %0, i32 27
  store i32 %79, ptr %r.ptr198, align 4
  %r.ptr199 = getelementptr i32, ptr %0, i32 23
  %r200 = load i32, ptr %r.ptr199, align 4
  %80 = icmp slt i32 %r200, 511
  %81 = zext i1 %80 to i32
  %r.ptr201 = getelementptr i32, ptr %0, i32 13
  store i32 %81, ptr %r.ptr201, align 4
  %r.ptr202 = getelementptr i32, ptr %0, i32 13
  %r203 = load i32, ptr %r.ptr202, align 4
  %r.ptr204 = getelementptr i32, ptr %0, i32 27
  %r205 = load i32, ptr %r.ptr204, align 4
  %82 = and i32 %r205, %r203
  %r.ptr206 = getelementptr i32, ptr %0, i32 27
  store i32 %82, ptr %r.ptr206, align 4
  %r.ptr207 = getelementptr i32, ptr %0, i32 24
  %r208 = load i32, ptr %r.ptr207, align 4
  %83 = icmp sgt i32 %r208, 0
  %84 = zext i1 %83 to i32
  %r.ptr209 = getelementptr i32, ptr %0, i32 13
  store i32 %84, ptr %r.ptr209, align 4
  %r.ptr210 = getelementptr i32, ptr %0, i32 13
  %r211 = load i32, ptr %r.ptr210, align 4
  %r.ptr212 = getelementptr i32, ptr %0, i32 27
  %r213 = load i32, ptr %r.ptr212, align 4
  %85 = and i32 %r213, %r211
  %r.ptr214 = getelementptr i32, ptr %0, i32 27
  store i32 %85, ptr %r.ptr214, align 4
  %r.ptr215 = getelementptr i32, ptr %0, i32 24
  %r216 = load i32, ptr %r.ptr215, align 4
  %86 = icmp slt i32 %r216, 255
  %87 = zext i1 %86 to i32
  %r.ptr217 = getelementptr i32, ptr %0, i32 13
  store i32 %87, ptr %r.ptr217, align 4
  %r.ptr218 = getelementptr i32, ptr %0, i32 13
  %r219 = load i32, ptr %r.ptr218, align 4
  %r.ptr220 = getelementptr i32, ptr %0, i32 27
  %r221 = load i32, ptr %r.ptr220, align 4
  %88 = and i32 %r221, %r219
  %r.ptr222 = getelementptr i32, ptr %0, i32 27
  store i32 %88, ptr %r.ptr222, align 4
  %r.ptr223 = getelementptr i32, ptr %0, i32 26
  %r224 = load i32, ptr %r.ptr223, align 4
  %r.ptr225 = getelementptr i32, ptr %0, i32 25
  %r226 = load i32, ptr %r.ptr225, align 4
  %89 = icmp slt i32 %r226, %r224
  %90 = zext i1 %89 to i32
  %r.ptr227 = getelementptr i32, ptr %0, i32 13
  store i32 %90, ptr %r.ptr227, align 4
  %r.ptr228 = getelementptr i32, ptr %0, i32 13
  %r229 = load i32, ptr %r.ptr228, align 4
  %r.ptr230 = getelementptr i32, ptr %0, i32 27
  %r231 = load i32, ptr %r.ptr230, align 4
  %91 = and i32 %r231, %r229
  %r.ptr232 = getelementptr i32, ptr %0, i32 27
  store i32 %91, ptr %r.ptr232, align 4
  %r.ptr233 = getelementptr i32, ptr %0, i32 27
  %r234 = load i32, ptr %r.ptr233, align 4
  %92 = icmp ne i32 %r234, 0
  br i1 %92, label %source_add, label %source_next_x

source_add:                                       ; preds = %source_cell
  %r.ptr235 = getelementptr i32, ptr %0, i32 24
  %r236 = load i32, ptr %r.ptr235, align 4
  %93 = shl i32 %r236, 9
  %r.ptr237 = getelementptr i32, ptr %0, i32 15
  store i32 %93, ptr %r.ptr237, align 4
  %r.ptr238 = getelementptr i32, ptr %0, i32 23
  %r239 = load i32, ptr %r.ptr238, align 4
  %r.ptr240 = getelementptr i32, ptr %0, i32 15
  %r241 = load i32, ptr %r.ptr240, align 4
  %94 = add i32 %r241, %r239
  %r.ptr242 = getelementptr i32, ptr %0, i32 15
  store i32 %94, ptr %r.ptr242, align 4
  %r.ptr243 = getelementptr i32, ptr %0, i32 15
  %r244 = load i32, ptr %r.ptr243, align 4
  %r.ptr245 = getelementptr i32, ptr %0, i32 0
  %r246 = load i32, ptr %r.ptr245, align 4
  %95 = mul i32 %r246, 131072
  %96 = add i32 %95, %r244
  %97 = add i32 %96, 128
  %mem.ptr247 = getelementptr i32, ptr %0, i32 %97
  %mem = load i32, ptr %mem.ptr247, align 4
  %r.ptr248 = getelementptr i32, ptr %0, i32 28
  store i32 %mem, ptr %r.ptr248, align 4
  %r.ptr249 = getelementptr i32, ptr %0, i32 25
  %r250 = load i32, ptr %r.ptr249, align 4
  %r.ptr251 = getelementptr i32, ptr %0, i32 26
  %r252 = load i32, ptr %r.ptr251, align 4
  %98 = sub i32 %r252, %r250
  %r.ptr253 = getelementptr i32, ptr %0, i32 29
  store i32 %98, ptr %r.ptr253, align 4
  %r.ptr254 = getelementptr i32, ptr %0, i32 29
  %r255 = load i32, ptr %r.ptr254, align 4
  %r.ptr256 = getelementptr i32, ptr %0, i32 17
  %r257 = load i32, ptr %r.ptr256, align 4
  %99 = mul i32 %r257, %r255
  %r.ptr258 = getelementptr i32, ptr %0, i32 29
  store i32 %99, ptr %r.ptr258, align 4
  %r.ptr259 = getelementptr i32, ptr %0, i32 26
  %r260 = load i32, ptr %r.ptr259, align 4
  %r.ptr261 = getelementptr i32, ptr %0, i32 29
  %r262 = load i32, ptr %r.ptr261, align 4
  %100 = sdiv i32 %r262, %r260
  %r.ptr263 = getelementptr i32, ptr %0, i32 29
  store i32 %100, ptr %r.ptr263, align 4
  %r.ptr264 = getelementptr i32, ptr %0, i32 29
  %r265 = load i32, ptr %r.ptr264, align 4
  %r.ptr266 = getelementptr i32, ptr %0, i32 28
  %r267 = load i32, ptr %r.ptr266, align 4
  %101 = add i32 %r267, %r265
  %r.ptr268 = getelementptr i32, ptr %0, i32 28
  store i32 %101, ptr %r.ptr268, align 4
  %r.ptr269 = getelementptr i32, ptr %0, i32 28
  %r270 = load i32, ptr %r.ptr269, align 4
  %r.ptr271 = getelementptr i32, ptr %0, i32 15
  %r272 = load i32, ptr %r.ptr271, align 4
  %r.ptr273 = getelementptr i32, ptr %0, i32 0
  %r274 = load i32, ptr %r.ptr273, align 4
  %102 = mul i32 %r274, 131072
  %103 = add i32 %102, %r272
  %104 = add i32 %103, 128
  %mem.ptr275 = getelementptr i32, ptr %0, i32 %104
  store i32 %r270, ptr %mem.ptr275, align 4
  br label %source_next_x

source_next_x:                                    ; preds = %source_add, %source_cell
  %r.ptr276 = getelementptr i32, ptr %0, i32 22
  %r277 = load i32, ptr %r.ptr276, align 4
  %105 = add i32 %r277, 1
  %r.ptr278 = getelementptr i32, ptr %0, i32 22
  store i32 %105, ptr %r.ptr278, align 4
  br label %source_dx_test

source_next_y:                                    ; preds = %source_dx_test
  %r.ptr279 = getelementptr i32, ptr %0, i32 21
  %r280 = load i32, ptr %r.ptr279, align 4
  %106 = add i32 %r280, 1
  %r.ptr281 = getelementptr i32, ptr %0, i32 21
  store i32 %106, ptr %r.ptr281, align 4
  br label %source_dy_test

source_done:                                      ; preds = %source_dy_test
  %r.ptr282 = getelementptr i32, ptr %0, i32 9
  store i32 1, ptr %r.ptr282, align 4
  br label %wave_y_test

wave_y_test:                                      ; preds = %wave_next_y, %source_done
  %r.ptr283 = getelementptr i32, ptr %0, i32 9
  %r284 = load i32, ptr %r.ptr283, align 4
  %107 = icmp slt i32 %r284, 255
  %108 = zext i1 %107 to i32
  %r.ptr285 = getelementptr i32, ptr %0, i32 10
  store i32 %108, ptr %r.ptr285, align 4
  %r.ptr286 = getelementptr i32, ptr %0, i32 10
  %r287 = load i32, ptr %r.ptr286, align 4
  %109 = icmp ne i32 %r287, 0
  br i1 %109, label %wave_y_body, label %wave_done

wave_y_body:                                      ; preds = %wave_y_test
  %r.ptr288 = getelementptr i32, ptr %0, i32 11
  store i32 1, ptr %r.ptr288, align 4
  br label %wave_x_test

wave_x_test:                                      ; preds = %wave_x_body, %wave_y_body
  %r.ptr289 = getelementptr i32, ptr %0, i32 11
  %r290 = load i32, ptr %r.ptr289, align 4
  %110 = icmp slt i32 %r290, 511
  %111 = zext i1 %110 to i32
  %r.ptr291 = getelementptr i32, ptr %0, i32 10
  store i32 %111, ptr %r.ptr291, align 4
  %r.ptr292 = getelementptr i32, ptr %0, i32 10
  %r293 = load i32, ptr %r.ptr292, align 4
  %112 = icmp ne i32 %r293, 0
  br i1 %112, label %wave_x_body, label %wave_next_y

wave_x_body:                                      ; preds = %wave_x_test
  %r.ptr294 = getelementptr i32, ptr %0, i32 9
  %r295 = load i32, ptr %r.ptr294, align 4
  %113 = shl i32 %r295, 9
  %r.ptr296 = getelementptr i32, ptr %0, i32 15
  store i32 %113, ptr %r.ptr296, align 4
  %r.ptr297 = getelementptr i32, ptr %0, i32 11
  %r298 = load i32, ptr %r.ptr297, align 4
  %r.ptr299 = getelementptr i32, ptr %0, i32 15
  %r300 = load i32, ptr %r.ptr299, align 4
  %114 = add i32 %r300, %r298
  %r.ptr301 = getelementptr i32, ptr %0, i32 15
  store i32 %114, ptr %r.ptr301, align 4
  %r.ptr302 = getelementptr i32, ptr %0, i32 0
  %r303 = load i32, ptr %r.ptr302, align 4
  %r.ptr304 = getelementptr i32, ptr %0, i32 1
  %r305 = load i32, ptr %r.ptr304, align 4
  %r.ptr306 = getelementptr i32, ptr %0, i32 2
  %r307 = load i32, ptr %r.ptr306, align 4
  %r.ptr308 = getelementptr i32, ptr %0, i32 15
  %r309 = load i32, ptr %r.ptr308, align 4
  %115 = add i32 %r309, 512
  %116 = mul i32 %r303, 131072
  %117 = add i32 %116, %115
  %118 = add i32 %117, 128
  %mem.ptr310 = getelementptr i32, ptr %0, i32 %118
  %mem311 = load i32, ptr %mem.ptr310, align 4
  %119 = add i32 %r309, -512
  %120 = mul i32 %r303, 131072
  %121 = add i32 %120, %119
  %122 = add i32 %121, 128
  %mem.ptr312 = getelementptr i32, ptr %0, i32 %122
  %mem313 = load i32, ptr %mem.ptr312, align 4
  %123 = add i32 %mem313, %mem311
  %124 = add i32 %r309, 1
  %125 = mul i32 %r303, 131072
  %126 = add i32 %125, %124
  %127 = add i32 %126, 128
  %mem.ptr314 = getelementptr i32, ptr %0, i32 %127
  %mem315 = load i32, ptr %mem.ptr314, align 4
  %128 = add i32 %r309, -1
  %129 = mul i32 %r303, 131072
  %130 = add i32 %129, %128
  %131 = add i32 %130, 128
  %mem.ptr316 = getelementptr i32, ptr %0, i32 %131
  %mem317 = load i32, ptr %mem.ptr316, align 4
  %132 = add i32 %mem317, %mem315
  %133 = add i32 %132, %123
  %134 = mul i32 %r305, 131072
  %135 = add i32 %134, %r309
  %136 = add i32 %135, 128
  %mem.ptr318 = getelementptr i32, ptr %0, i32 %136
  %mem319 = load i32, ptr %mem.ptr318, align 4
  %137 = ashr i32 %133, 1
  %138 = sub i32 %137, %mem319
  %139 = ashr i32 %138, 6
  %140 = sub i32 %138, %139
  %141 = mul i32 %r307, 131072
  %142 = add i32 %141, %r309
  %143 = add i32 %142, 128
  %mem.ptr320 = getelementptr i32, ptr %0, i32 %143
  %mem321 = load i32, ptr %mem.ptr320, align 4
  %144 = and i32 %140, %mem321
  %145 = mul i32 %r305, 131072
  %146 = add i32 %145, %r309
  %147 = add i32 %146, 128
  %mem.ptr322 = getelementptr i32, ptr %0, i32 %147
  store i32 %144, ptr %mem.ptr322, align 4
  %r.ptr323 = getelementptr i32, ptr %0, i32 11
  %r324 = load i32, ptr %r.ptr323, align 4
  %148 = add i32 %r324, 1
  %r.ptr325 = getelementptr i32, ptr %0, i32 11
  store i32 %148, ptr %r.ptr325, align 4
  br label %wave_x_test

wave_next_y:                                      ; preds = %wave_x_test
  %r.ptr326 = getelementptr i32, ptr %0, i32 9
  %r327 = load i32, ptr %r.ptr326, align 4
  %149 = add i32 %r327, 1
  %r.ptr328 = getelementptr i32, ptr %0, i32 9
  store i32 %149, ptr %r.ptr328, align 4
  br label %wave_y_test

wave_done:                                        ; preds = %wave_y_test
  %r.ptr329 = getelementptr i32, ptr %0, i32 0
  %r330 = load i32, ptr %r.ptr329, align 4
  %r.ptr331 = getelementptr i32, ptr %0, i32 13
  store i32 %r330, ptr %r.ptr331, align 4
  %r.ptr332 = getelementptr i32, ptr %0, i32 1
  %r333 = load i32, ptr %r.ptr332, align 4
  %r.ptr334 = getelementptr i32, ptr %0, i32 0
  store i32 %r333, ptr %r.ptr334, align 4
  %r.ptr335 = getelementptr i32, ptr %0, i32 13
  %r336 = load i32, ptr %r.ptr335, align 4
  %r.ptr337 = getelementptr i32, ptr %0, i32 1
  store i32 %r336, ptr %r.ptr337, align 4
  %r.ptr338 = getelementptr i32, ptr %0, i32 5
  %r339 = load i32, ptr %r.ptr338, align 4
  %150 = ashr i32 %r339, 8
  %r.ptr340 = getelementptr i32, ptr %0, i32 13
  store i32 %150, ptr %r.ptr340, align 4
  %r.ptr341 = getelementptr i32, ptr %0, i32 13
  %r342 = load i32, ptr %r.ptr341, align 4
  %r.ptr343 = getelementptr i32, ptr %0, i32 4
  %r344 = load i32, ptr %r.ptr343, align 4
  %151 = sub i32 %r344, %r342
  %r.ptr345 = getelementptr i32, ptr %0, i32 4
  store i32 %151, ptr %r.ptr345, align 4
  %r.ptr346 = getelementptr i32, ptr %0, i32 4
  %r347 = load i32, ptr %r.ptr346, align 4
  %152 = ashr i32 %r347, 8
  %r.ptr348 = getelementptr i32, ptr %0, i32 13
  store i32 %152, ptr %r.ptr348, align 4
  %r.ptr349 = getelementptr i32, ptr %0, i32 13
  %r350 = load i32, ptr %r.ptr349, align 4
  %r.ptr351 = getelementptr i32, ptr %0, i32 5
  %r352 = load i32, ptr %r.ptr351, align 4
  %153 = add i32 %r352, %r350
  %r.ptr353 = getelementptr i32, ptr %0, i32 5
  store i32 %153, ptr %r.ptr353, align 4
  %r.ptr354 = getelementptr i32, ptr %0, i32 8
  %r355 = load i32, ptr %r.ptr354, align 4
  %154 = add i32 %r355, 1
  %r.ptr356 = getelementptr i32, ptr %0, i32 8
  store i32 %154, ptr %r.ptr356, align 4
  %r.ptr357 = getelementptr i32, ptr %0, i32 16
  %r358 = load i32, ptr %r.ptr357, align 4
  %155 = add i32 %r358, 1
  %r.ptr359 = getelementptr i32, ptr %0, i32 16
  store i32 %155, ptr %r.ptr359, align 4
  br label %wave_s_test

rain_start:                                       ; preds = %wave_s_test
  %rand = call i32 @simRand()
  %r.ptr360 = getelementptr i32, ptr %0, i32 30
  store i32 %rand, ptr %r.ptr360, align 4
  %r.ptr361 = getelementptr i32, ptr %0, i32 30
  %r362 = load i32, ptr %r.ptr361, align 4
  %156 = srem i32 %r362, 4
  %r.ptr363 = getelementptr i32, ptr %0, i32 30
  store i32 %156, ptr %r.ptr363, align 4
  %r.ptr364 = getelementptr i32, ptr %0, i32 30
  %r365 = load i32, ptr %r.ptr364, align 4
  %157 = icmp eq i32 %r365, 0
  %158 = zext i1 %157 to i32
  %r.ptr366 = getelementptr i32, ptr %0, i32 10
  store i32 %158, ptr %r.ptr366, align 4
  %r.ptr367 = getelementptr i32, ptr %0, i32 10
  %r368 = load i32, ptr %r.ptr367, align 4
  %159 = icmp ne i32 %r368, 0
  br i1 %159, label %rain_setup, label %draw_start

rain_setup:                                       ; preds = %rain_start
  %rand369 = call i32 @simRand()
  %r.ptr370 = getelementptr i32, ptr %0, i32 18
  store i32 %rand369, ptr %r.ptr370, align 4
  %r.ptr371 = getelementptr i32, ptr %0, i32 18
  %r372 = load i32, ptr %r.ptr371, align 4
  %160 = srem i32 %r372, 510
  %r.ptr373 = getelementptr i32, ptr %0, i32 18
  store i32 %160, ptr %r.ptr373, align 4
  %r.ptr374 = getelementptr i32, ptr %0, i32 18
  %r375 = load i32, ptr %r.ptr374, align 4
  %161 = add i32 %r375, 1
  %r.ptr376 = getelementptr i32, ptr %0, i32 18
  store i32 %161, ptr %r.ptr376, align 4
  %rand377 = call i32 @simRand()
  %r.ptr378 = getelementptr i32, ptr %0, i32 19
  store i32 %rand377, ptr %r.ptr378, align 4
  %r.ptr379 = getelementptr i32, ptr %0, i32 19
  %r380 = load i32, ptr %r.ptr379, align 4
  %162 = srem i32 %r380, 254
  %r.ptr381 = getelementptr i32, ptr %0, i32 19
  store i32 %162, ptr %r.ptr381, align 4
  %r.ptr382 = getelementptr i32, ptr %0, i32 19
  %r383 = load i32, ptr %r.ptr382, align 4
  %163 = add i32 %r383, 1
  %r.ptr384 = getelementptr i32, ptr %0, i32 19
  store i32 %163, ptr %r.ptr384, align 4
  %r.ptr385 = getelementptr i32, ptr %0, i32 20
  store i32 4, ptr %r.ptr385, align 4
  %r.ptr386 = getelementptr i32, ptr %0, i32 17
  store i32 2000, ptr %r.ptr386, align 4
  %r.ptr387 = getelementptr i32, ptr %0, i32 20
  %r388 = load i32, ptr %r.ptr387, align 4
  %164 = sub i32 0, %r388
  %r.ptr389 = getelementptr i32, ptr %0, i32 21
  store i32 %164, ptr %r.ptr389, align 4
  br label %rain_dy_test

rain_dy_test:                                     ; preds = %rain_next_y, %rain_setup
  %r.ptr390 = getelementptr i32, ptr %0, i32 20
  %r391 = load i32, ptr %r.ptr390, align 4
  %r.ptr392 = getelementptr i32, ptr %0, i32 21
  %r393 = load i32, ptr %r.ptr392, align 4
  %165 = icmp sle i32 %r393, %r391
  %166 = zext i1 %165 to i32
  %r.ptr394 = getelementptr i32, ptr %0, i32 10
  store i32 %166, ptr %r.ptr394, align 4
  %r.ptr395 = getelementptr i32, ptr %0, i32 10
  %r396 = load i32, ptr %r.ptr395, align 4
  %167 = icmp ne i32 %r396, 0
  br i1 %167, label %rain_dy_body, label %rain_done

rain_dy_body:                                     ; preds = %rain_dy_test
  %r.ptr397 = getelementptr i32, ptr %0, i32 20
  %r398 = load i32, ptr %r.ptr397, align 4
  %168 = sub i32 0, %r398
  %r.ptr399 = getelementptr i32, ptr %0, i32 22
  store i32 %168, ptr %r.ptr399, align 4
  br label %rain_dx_test

rain_dx_test:                                     ; preds = %rain_next_x, %rain_dy_body
  %r.ptr400 = getelementptr i32, ptr %0, i32 20
  %r401 = load i32, ptr %r.ptr400, align 4
  %r.ptr402 = getelementptr i32, ptr %0, i32 22
  %r403 = load i32, ptr %r.ptr402, align 4
  %169 = icmp sle i32 %r403, %r401
  %170 = zext i1 %169 to i32
  %r.ptr404 = getelementptr i32, ptr %0, i32 10
  store i32 %170, ptr %r.ptr404, align 4
  %r.ptr405 = getelementptr i32, ptr %0, i32 10
  %r406 = load i32, ptr %r.ptr405, align 4
  %171 = icmp ne i32 %r406, 0
  br i1 %171, label %rain_cell, label %rain_next_y

rain_cell:                                        ; preds = %rain_dx_test
  %r.ptr407 = getelementptr i32, ptr %0, i32 22
  %r408 = load i32, ptr %r.ptr407, align 4
  %r.ptr409 = getelementptr i32, ptr %0, i32 18
  %r410 = load i32, ptr %r.ptr409, align 4
  %172 = add i32 %r410, %r408
  %r.ptr411 = getelementptr i32, ptr %0, i32 23
  store i32 %172, ptr %r.ptr411, align 4
  %r.ptr412 = getelementptr i32, ptr %0, i32 21
  %r413 = load i32, ptr %r.ptr412, align 4
  %r.ptr414 = getelementptr i32, ptr %0, i32 19
  %r415 = load i32, ptr %r.ptr414, align 4
  %173 = add i32 %r415, %r413
  %r.ptr416 = getelementptr i32, ptr %0, i32 24
  store i32 %173, ptr %r.ptr416, align 4
  %r.ptr417 = getelementptr i32, ptr %0, i32 22
  %r418 = load i32, ptr %r.ptr417, align 4
  %r.ptr419 = getelementptr i32, ptr %0, i32 22
  %r420 = load i32, ptr %r.ptr419, align 4
  %174 = mul i32 %r420, %r418
  %r.ptr421 = getelementptr i32, ptr %0, i32 25
  store i32 %174, ptr %r.ptr421, align 4
  %r.ptr422 = getelementptr i32, ptr %0, i32 21
  %r423 = load i32, ptr %r.ptr422, align 4
  %r.ptr424 = getelementptr i32, ptr %0, i32 21
  %r425 = load i32, ptr %r.ptr424, align 4
  %175 = mul i32 %r425, %r423
  %r.ptr426 = getelementptr i32, ptr %0, i32 13
  store i32 %175, ptr %r.ptr426, align 4
  %r.ptr427 = getelementptr i32, ptr %0, i32 13
  %r428 = load i32, ptr %r.ptr427, align 4
  %r.ptr429 = getelementptr i32, ptr %0, i32 25
  %r430 = load i32, ptr %r.ptr429, align 4
  %176 = add i32 %r430, %r428
  %r.ptr431 = getelementptr i32, ptr %0, i32 25
  store i32 %176, ptr %r.ptr431, align 4
  %r.ptr432 = getelementptr i32, ptr %0, i32 20
  %r433 = load i32, ptr %r.ptr432, align 4
  %r.ptr434 = getelementptr i32, ptr %0, i32 20
  %r435 = load i32, ptr %r.ptr434, align 4
  %177 = mul i32 %r435, %r433
  %r.ptr436 = getelementptr i32, ptr %0, i32 26
  store i32 %177, ptr %r.ptr436, align 4
  %r.ptr437 = getelementptr i32, ptr %0, i32 23
  %r438 = load i32, ptr %r.ptr437, align 4
  %178 = icmp sgt i32 %r438, 0
  %179 = zext i1 %178 to i32
  %r.ptr439 = getelementptr i32, ptr %0, i32 27
  store i32 %179, ptr %r.ptr439, align 4
  %r.ptr440 = getelementptr i32, ptr %0, i32 23
  %r441 = load i32, ptr %r.ptr440, align 4
  %180 = icmp slt i32 %r441, 511
  %181 = zext i1 %180 to i32
  %r.ptr442 = getelementptr i32, ptr %0, i32 13
  store i32 %181, ptr %r.ptr442, align 4
  %r.ptr443 = getelementptr i32, ptr %0, i32 13
  %r444 = load i32, ptr %r.ptr443, align 4
  %r.ptr445 = getelementptr i32, ptr %0, i32 27
  %r446 = load i32, ptr %r.ptr445, align 4
  %182 = and i32 %r446, %r444
  %r.ptr447 = getelementptr i32, ptr %0, i32 27
  store i32 %182, ptr %r.ptr447, align 4
  %r.ptr448 = getelementptr i32, ptr %0, i32 24
  %r449 = load i32, ptr %r.ptr448, align 4
  %183 = icmp sgt i32 %r449, 0
  %184 = zext i1 %183 to i32
  %r.ptr450 = getelementptr i32, ptr %0, i32 13
  store i32 %184, ptr %r.ptr450, align 4
  %r.ptr451 = getelementptr i32, ptr %0, i32 13
  %r452 = load i32, ptr %r.ptr451, align 4
  %r.ptr453 = getelementptr i32, ptr %0, i32 27
  %r454 = load i32, ptr %r.ptr453, align 4
  %185 = and i32 %r454, %r452
  %r.ptr455 = getelementptr i32, ptr %0, i32 27
  store i32 %185, ptr %r.ptr455, align 4
  %r.ptr456 = getelementptr i32, ptr %0, i32 24
  %r457 = load i32, ptr %r.ptr456, align 4
  %186 = icmp slt i32 %r457, 255
  %187 = zext i1 %186 to i32
  %r.ptr458 = getelementptr i32, ptr %0, i32 13
  store i32 %187, ptr %r.ptr458, align 4
  %r.ptr459 = getelementptr i32, ptr %0, i32 13
  %r460 = load i32, ptr %r.ptr459, align 4
  %r.ptr461 = getelementptr i32, ptr %0, i32 27
  %r462 = load i32, ptr %r.ptr461, align 4
  %188 = and i32 %r462, %r460
  %r.ptr463 = getelementptr i32, ptr %0, i32 27
  store i32 %188, ptr %r.ptr463, align 4
  %r.ptr464 = getelementptr i32, ptr %0, i32 26
  %r465 = load i32, ptr %r.ptr464, align 4
  %r.ptr466 = getelementptr i32, ptr %0, i32 25
  %r467 = load i32, ptr %r.ptr466, align 4
  %189 = icmp slt i32 %r467, %r465
  %190 = zext i1 %189 to i32
  %r.ptr468 = getelementptr i32, ptr %0, i32 13
  store i32 %190, ptr %r.ptr468, align 4
  %r.ptr469 = getelementptr i32, ptr %0, i32 13
  %r470 = load i32, ptr %r.ptr469, align 4
  %r.ptr471 = getelementptr i32, ptr %0, i32 27
  %r472 = load i32, ptr %r.ptr471, align 4
  %191 = and i32 %r472, %r470
  %r.ptr473 = getelementptr i32, ptr %0, i32 27
  store i32 %191, ptr %r.ptr473, align 4
  %r.ptr474 = getelementptr i32, ptr %0, i32 27
  %r475 = load i32, ptr %r.ptr474, align 4
  %192 = icmp ne i32 %r475, 0
  br i1 %192, label %rain_add, label %rain_next_x

rain_add:                                         ; preds = %rain_cell
  %r.ptr476 = getelementptr i32, ptr %0, i32 24
  %r477 = load i32, ptr %r.ptr476, align 4
  %193 = shl i32 %r477, 9
  %r.ptr478 = getelementptr i32, ptr %0, i32 15
  store i32 %193, ptr %r.ptr478, align 4
  %r.ptr479 = getelementptr i32, ptr %0, i32 23
  %r480 = load i32, ptr %r.ptr479, align 4
  %r.ptr481 = getelementptr i32, ptr %0, i32 15
  %r482 = load i32, ptr %r.ptr481, align 4
  %194 = add i32 %r482, %r480
  %r.ptr483 = getelementptr i32, ptr %0, i32 15
  store i32 %194, ptr %r.ptr483, align 4
  %r.ptr484 = getelementptr i32, ptr %0, i32 15
  %r485 = load i32, ptr %r.ptr484, align 4
  %r.ptr486 = getelementptr i32, ptr %0, i32 0
  %r487 = load i32, ptr %r.ptr486, align 4
  %195 = mul i32 %r487, 131072
  %196 = add i32 %195, %r485
  %197 = add i32 %196, 128
  %mem.ptr488 = getelementptr i32, ptr %0, i32 %197
  %mem489 = load i32, ptr %mem.ptr488, align 4
  %r.ptr490 = getelementptr i32, ptr %0, i32 28
  store i32 %mem489, ptr %r.ptr490, align 4
  %r.ptr491 = getelementptr i32, ptr %0, i32 25
  %r492 = load i32, ptr %r.ptr491, align 4
  %r.ptr493 = getelementptr i32, ptr %0, i32 26
  %r494 = load i32, ptr %r.ptr493, align 4
  %198 = sub i32 %r494, %r492
  %r.ptr495 = getelementptr i32, ptr %0, i32 29
  store i32 %198, ptr %r.ptr495, align 4
  %r.ptr496 = getelementptr i32, ptr %0, i32 29
  %r497 = load i32, ptr %r.ptr496, align 4
  %r.ptr498 = getelementptr i32, ptr %0, i32 17
  %r499 = load i32, ptr %r.ptr498, align 4
  %199 = mul i32 %r499, %r497
  %r.ptr500 = getelementptr i32, ptr %0, i32 29
  store i32 %199, ptr %r.ptr500, align 4
  %r.ptr501 = getelementptr i32, ptr %0, i32 26
  %r502 = load i32, ptr %r.ptr501, align 4
  %r.ptr503 = getelementptr i32, ptr %0, i32 29
  %r504 = load i32, ptr %r.ptr503, align 4
  %200 = sdiv i32 %r504, %r502
  %r.ptr505 = getelementptr i32, ptr %0, i32 29
  store i32 %200, ptr %r.ptr505, align 4
  %r.ptr506 = getelementptr i32, ptr %0, i32 29
  %r507 = load i32, ptr %r.ptr506, align 4
  %r.ptr508 = getelementptr i32, ptr %0, i32 28
  %r509 = load i32, ptr %r.ptr508, align 4
  %201 = add i32 %r509, %r507
  %r.ptr510 = getelementptr i32, ptr %0, i32 28
  store i32 %201, ptr %r.ptr510, align 4
  %r.ptr511 = getelementptr i32, ptr %0, i32 28
  %r512 = load i32, ptr %r.ptr511, align 4
  %r.ptr513 = getelementptr i32, ptr %0, i32 15
  %r514 = load i32, ptr %r.ptr513, align 4
  %r.ptr515 = getelementptr i32, ptr %0, i32 0
  %r516 = load i32, ptr %r.ptr515, align 4
  %202 = mul i32 %r516, 131072
  %203 = add i32 %202, %r514
  %204 = add i32 %203, 128
  %mem.ptr517 = getelementptr i32, ptr %0, i32 %204
  store i32 %r512, ptr %mem.ptr517, align 4
  br label %rain_next_x

rain_next_x:                                      ; preds = %rain_add, %rain_cell
  %r.ptr518 = getelementptr i32, ptr %0, i32 22
  %r519 = load i32, ptr %r.ptr518, align 4
  %205 = add i32 %r519, 1
  %r.ptr520 = getelementptr i32, ptr %0, i32 22
  store i32 %205, ptr %r.ptr520, align 4
  br label %rain_dx_test

rain_next_y:                                      ; preds = %rain_dx_test
  %r.ptr521 = getelementptr i32, ptr %0, i32 21
  %r522 = load i32, ptr %r.ptr521, align 4
  %206 = add i32 %r522, 1
  %r.ptr523 = getelementptr i32, ptr %0, i32 21
  store i32 %206, ptr %r.ptr523, align 4
  br label %rain_dy_test

rain_done:                                        ; preds = %rain_dy_test
  br label %draw_start

draw_start:                                       ; preds = %rain_done, %rain_start
  %r.ptr524 = getelementptr i32, ptr %0, i32 9
  store i32 0, ptr %r.ptr524, align 4
  br label %draw_y_test

draw_y_test:                                      ; preds = %draw_next_y, %draw_start
  %r.ptr525 = getelementptr i32, ptr %0, i32 9
  %r526 = load i32, ptr %r.ptr525, align 4
  %207 = icmp slt i32 %r526, 256
  %208 = zext i1 %207 to i32
  %r.ptr527 = getelementptr i32, ptr %0, i32 10
  store i32 %208, ptr %r.ptr527, align 4
  %r.ptr528 = getelementptr i32, ptr %0, i32 10
  %r529 = load i32, ptr %r.ptr528, align 4
  %209 = icmp ne i32 %r529, 0
  br i1 %209, label %draw_y_body, label %frame_flush

draw_y_body:                                      ; preds = %draw_y_test
  %r.ptr530 = getelementptr i32, ptr %0, i32 11
  store i32 0, ptr %r.ptr530, align 4
  br label %draw_x_test

draw_x_test:                                      ; preds = %draw_next_x, %draw_y_body
  %r.ptr531 = getelementptr i32, ptr %0, i32 11
  %r532 = load i32, ptr %r.ptr531, align 4
  %210 = icmp slt i32 %r532, 512
  %211 = zext i1 %210 to i32
  %r.ptr533 = getelementptr i32, ptr %0, i32 10
  store i32 %211, ptr %r.ptr533, align 4
  %r.ptr534 = getelementptr i32, ptr %0, i32 10
  %r535 = load i32, ptr %r.ptr534, align 4
  %212 = icmp ne i32 %r535, 0
  br i1 %212, label %draw_cell, label %draw_next_y

draw_cell:                                        ; preds = %draw_x_test
  %r.ptr536 = getelementptr i32, ptr %0, i32 9
  %r537 = load i32, ptr %r.ptr536, align 4
  %213 = shl i32 %r537, 9
  %r.ptr538 = getelementptr i32, ptr %0, i32 15
  store i32 %213, ptr %r.ptr538, align 4
  %r.ptr539 = getelementptr i32, ptr %0, i32 11
  %r540 = load i32, ptr %r.ptr539, align 4
  %r.ptr541 = getelementptr i32, ptr %0, i32 15
  %r542 = load i32, ptr %r.ptr541, align 4
  %214 = add i32 %r542, %r540
  %r.ptr543 = getelementptr i32, ptr %0, i32 15
  store i32 %214, ptr %r.ptr543, align 4
  %r.ptr544 = getelementptr i32, ptr %0, i32 15
  %r545 = load i32, ptr %r.ptr544, align 4
  %r.ptr546 = getelementptr i32, ptr %0, i32 2
  %r547 = load i32, ptr %r.ptr546, align 4
  %215 = mul i32 %r547, 131072
  %216 = add i32 %215, %r545
  %217 = add i32 %216, 128
  %mem.ptr548 = getelementptr i32, ptr %0, i32 %217
  %mem549 = load i32, ptr %mem.ptr548, align 4
  %r.ptr550 = getelementptr i32, ptr %0, i32 14
  store i32 %mem549, ptr %r.ptr550, align 4
  %r.ptr551 = getelementptr i32, ptr %0, i32 14
  %r552 = load i32, ptr %r.ptr551, align 4
  %218 = icmp ne i32 %r552, 0
  %219 = zext i1 %218 to i32
  %r.ptr553 = getelementptr i32, ptr %0, i32 10
  store i32 %219, ptr %r.ptr553, align 4
  %r.ptr554 = getelementptr i32, ptr %0, i32 10
  %r555 = load i32, ptr %r.ptr554, align 4
  %220 = icmp ne i32 %r555, 0
  br i1 %220, label %draw_water, label %draw_land

draw_water:                                       ; preds = %draw_cell
  %r.ptr556 = getelementptr i32, ptr %0, i32 15
  %r557 = load i32, ptr %r.ptr556, align 4
  %r.ptr558 = getelementptr i32, ptr %0, i32 0
  %r559 = load i32, ptr %r.ptr558, align 4
  %221 = add i32 %r557, 512
  %222 = mul i32 %r559, 131072
  %223 = add i32 %222, %221
  %224 = add i32 %223, 128
  %mem.ptr560 = getelementptr i32, ptr %0, i32 %224
  %mem561 = load i32, ptr %mem.ptr560, align 4
  %225 = add i32 %r557, -512
  %226 = mul i32 %r559, 131072
  %227 = add i32 %226, %225
  %228 = add i32 %227, 128
  %mem.ptr562 = getelementptr i32, ptr %0, i32 %228
  %mem563 = load i32, ptr %mem.ptr562, align 4
  %229 = sub i32 %mem563, %mem561
  %230 = add i32 %r557, 1
  %231 = mul i32 %r559, 131072
  %232 = add i32 %231, %230
  %233 = add i32 %232, 128
  %mem.ptr564 = getelementptr i32, ptr %0, i32 %233
  %mem565 = load i32, ptr %mem.ptr564, align 4
  %234 = add i32 %r557, -1
  %235 = mul i32 %r559, 131072
  %236 = add i32 %235, %234
  %237 = add i32 %236, 128
  %mem.ptr566 = getelementptr i32, ptr %0, i32 %237
  %mem567 = load i32, ptr %mem.ptr566, align 4
  %238 = sub i32 %mem567, %mem565
  %239 = add i32 %238, %229
  %240 = add i32 %r557, 0
  %241 = mul i32 %r559, 131072
  %242 = add i32 %241, %240
  %243 = add i32 %242, 128
  %mem.ptr568 = getelementptr i32, ptr %0, i32 %243
  %mem569 = load i32, ptr %mem.ptr568, align 4
  %244 = ashr i32 %mem569, 4
  %245 = ashr i32 %239, 2
  %246 = add i32 90, %245
  %247 = add i32 %246, %244
  %248 = icmp slt i32 %247, 0
  %249 = select i1 %248, i32 0, i32 %247
  %250 = icmp sgt i32 %249, 255
  %251 = select i1 %250, i32 255, i32 %249
  %252 = mul i32 %251, %251
  %253 = mul i32 %252, %251
  %254 = ashr i32 %253, 16
  %255 = ashr i32 %252, 8
  %256 = add i32 30, %255
  %257 = icmp slt i32 %256, 0
  %258 = select i1 %257, i32 0, i32 %256
  %259 = icmp sgt i32 %258, 255
  %260 = select i1 %259, i32 255, i32 %258
  %261 = add i32 80, %251
  %262 = icmp slt i32 %261, 0
  %263 = select i1 %262, i32 0, i32 %261
  %264 = icmp sgt i32 %263, 255
  %265 = select i1 %264, i32 255, i32 %263
  %266 = shl i32 %260, 8
  %267 = shl i32 %254, 16
  %268 = or i32 -16777216, %267
  %269 = or i32 %268, %266
  %270 = or i32 %269, %265
  %r.ptr570 = getelementptr i32, ptr %0, i32 31
  store i32 %270, ptr %r.ptr570, align 4
  br label %draw_boat_check

draw_land:                                        ; preds = %draw_cell
  %r.ptr571 = getelementptr i32, ptr %0, i32 31
  store i32 -3626642, ptr %r.ptr571, align 4
  br label %draw_boat_check

draw_boat_check:                                  ; preds = %draw_land, %draw_water
  %r.ptr572 = getelementptr i32, ptr %0, i32 6
  %r573 = load i32, ptr %r.ptr572, align 4
  %r.ptr574 = getelementptr i32, ptr %0, i32 11
  %r575 = load i32, ptr %r.ptr574, align 4
  %271 = sub i32 %r575, %r573
  %r.ptr576 = getelementptr i32, ptr %0, i32 7
  %r577 = load i32, ptr %r.ptr576, align 4
  %r.ptr578 = getelementptr i32, ptr %0, i32 9
  %r579 = load i32, ptr %r.ptr578, align 4
  %272 = sub i32 %r579, %r577
  %273 = mul i32 %272, %272
  %274 = mul i32 %271, %271
  %275 = add i32 %274, %273
  %276 = icmp slt i32 %275, 4
  %277 = zext i1 %276 to i32
  %r.ptr580 = getelementptr i32, ptr %0, i32 10
  store i32 %277, ptr %r.ptr580, align 4
  %r.ptr581 = getelementptr i32, ptr %0, i32 10
  %r582 = load i32, ptr %r.ptr581, align 4
  %278 = icmp ne i32 %r582, 0
  br i1 %278, label %draw_boat, label %draw_shown

draw_boat:                                        ; preds = %draw_boat_check
  %r.ptr583 = getelementptr i32, ptr %0, i32 31
  store i32 -44992, ptr %r.ptr583, align 4
  br label %draw_shown

draw_shown:                                       ; preds = %draw_boat, %draw_boat_check
  %r.ptr584 = getelementptr i32, ptr %0, i32 15
  %r585 = load i32, ptr %r.ptr584, align 4
  %r.ptr586 = getelementptr i32, ptr %0, i32 3
  %r587 = load i32, ptr %r.ptr586, align 4
  %279 = mul i32 %r587, 131072
  %280 = add i32 %279, %r585
  %281 = add i32 %280, 128
  %mem.ptr588 = getelementptr i32, ptr %0, i32 %281
  %mem589 = load i32, ptr %mem.ptr588, align 4
  %r.ptr590 = getelementptr i32, ptr %0, i32 28
  store i32 %mem589, ptr %r.ptr590, align 4
  %r.ptr591 = getelementptr i32, ptr %0, i32 28
  %r592 = load i32, ptr %r.ptr591, align 4
  %r.ptr593 = getelementptr i32, ptr %0, i32 31
  %r594 = load i32, ptr %r.ptr593, align 4
  %282 = icmp ne i32 %r594, %r592
  %283 = zext i1 %282 to i32
  %r.ptr595 = getelementptr i32, ptr %0, i32 10
  store i32 %283, ptr %r.ptr595, align 4
  %r.ptr596 = getelementptr i32, ptr %0, i32 10
  %r597 = load i32, ptr %r.ptr596, align 4
  %284 = icmp ne i32 %r597, 0
  br i1 %284, label %draw_changed, label %draw_next_x

draw_changed:                                     ; preds = %draw_shown
  %r.ptr598 = getelementptr i32, ptr %0, i32 31
  %r599 = load i32, ptr %r.ptr598, align 4
  %r.ptr600 = getelementptr i32, ptr %0, i32 15
  %r601 = load i32, ptr %r.ptr600, align 4
  %r.ptr602 = getelementptr i32, ptr %0, i32 3
  %r603 = load i32, ptr %r.ptr602, align 4
  %285 = mul i32 %r603, 131072
  %286 = add i32 %285, %r601
  %287 = add i32 %286, 128
  %mem.ptr604 = getelementptr i32, ptr %0, i32 %287
  store i32 %r599, ptr %mem.ptr604, align 4
  %r.ptr605 = getelementptr i32, ptr %0, i32 11
  %r606 = load i32, ptr %r.ptr605, align 4
  %288 = mul i32 %r606, 3
  %r.ptr607 = getelementptr i32, ptr %0, i32 32
  store i32 %288, ptr %r.ptr607, align 4
  %r.ptr608 = getelementptr i32, ptr %0, i32 9
  %r609 = load i32, ptr %r.ptr608, align 4
  %289 = mul i32 %r609, 3
  %r.ptr610 = getelementptr i32, ptr %0, i32 33
  store i32 %289, ptr %r.ptr610, align 4
  %r.ptr611 = getelementptr i32, ptr %0, i32 34
  store i32 0, ptr %r.ptr611, align 4
  br label %pixel_y_test

pixel_y_test:                                     ; preds = %pixel_next_y, %draw_changed
  %r.ptr612 = getelementptr i32, ptr %0, i32 34
  %r613 = load i32, ptr %r.ptr612, align 4
  %290 = icmp slt i32 %r613, 3
  %291 = zext i1 %290 to i32
  %r.ptr614 = getelementptr i32, ptr %0, i32 10
  store i32 %291, ptr %r.ptr614, align 4
  %r.ptr615 = getelementptr i32, ptr %0, i32 10
  %r616 = load i32, ptr %r.ptr615, align 4
  %292 = icmp ne i32 %r616, 0
  br i1 %292, label %pixel_y_body, label %draw_next_x

pixel_y_body:                                     ; preds = %pixel_y_test
  %r.ptr617 = getelementptr i32, ptr %0, i32 35
  store i32 0, ptr %r.ptr617, align 4
  br label %pixel_x_test

pixel_x_test:                                     ; preds = %pixel_body, %pixel_y_body
  %r.ptr618 = getelementptr i32, ptr %0, i32 35
  %r619 = load i32, ptr %r.ptr618, align 4
  %293 = icmp slt i32 %r619, 3
  %294 = zext i1 %293 to i32
  %r.ptr620 = getelementptr i32, ptr %0, i32 10
  store i32 %294, ptr %r.ptr620, align 4
  %r.ptr621 = getelementptr i32, ptr %0, i32 10
  %r622 = load i32, ptr %r.ptr621, align 4
  %295 = icmp ne i32 %r622, 0
  br i1 %295, label %pixel_body, label %pixel_next_y

pixel_body:                                       ; preds = %pixel_x_test
  %r.ptr623 = getelementptr i32, ptr %0, i32 35
  %r624 = load i32, ptr %r.ptr623, align 4
  %r.ptr625 = getelementptr i32, ptr %0, i32 32
  %r626 = load i32, ptr %r.ptr625, align 4
  %296 = add i32 %r626, %r624
  %r.ptr627 = getelementptr i32, ptr %0, i32 36
  store i32 %296, ptr %r.ptr627, align 4
  %r.ptr628 = getelementptr i32, ptr %0, i32 34
  %r629 = load i32, ptr %r.ptr628, align 4
  %r.ptr630 = getelementptr i32, ptr %0, i32 33
  %r631 = load i32, ptr %r.ptr630, align 4
  %297 = add i32 %r631, %r629
  %r.ptr632 = getelementptr i32, ptr %0, i32 37
  store i32 %297, ptr %r.ptr632, align 4
  %r.ptr633 = getelementptr i32, ptr %0, i32 36
  %r634 = load i32, ptr %r.ptr633, align 4
  %r.ptr635 = getelementptr i32, ptr %0, i32 37
  %r636 = load i32, ptr %r.ptr635, align 4
  %r.ptr637 = getelementptr i32, ptr %0, i32 31
  %r638 = load i32, ptr %r.ptr637, align 4
  call void @simPutPixel(i32 %r634, i32 %r636, i32 %r638)
  %r.ptr639 = getelementptr i32, ptr %0, i32 35
  %r640 = load i32, ptr %r.ptr639, align 4
  %298 = add i32 %r640, 1
  %r.ptr641 = getelementptr i32, ptr %0, i32 35
  store i32 %298, ptr %r.ptr641, align 4
  br label %pixel_x_test

pixel_next_y:                                     ; preds = %pixel_x_test
  %r.ptr642 = getelementptr i32, ptr %0, i32 34
  %r643 = load i32, ptr %r.ptr642, align 4
  %299 = add i32 %r643, 1
  %r.ptr644 = getelementptr i32, ptr %0, i32 34
  store i32 %299, ptr %r.ptr644, align 4
  br label %pixel_y_test

draw_next_x:                                      ; preds = %pixel_y_test, %draw_shown
  %r.ptr645 = getelementptr i32, ptr %0, i32 11
  %r646 = load i32, ptr %r.ptr645, align 4
  %300 = add i32 %r646, 1
  %r.ptr647 = getelementptr i32, ptr %0, i32 11
  store i32 %300, ptr %r.ptr647, align 4
  br label %draw_x_test

draw_next_y:                                      ; preds = %draw_x_test
  %r.ptr648 = getelementptr i32, ptr %0, i32 9
  %r649 = load i32, ptr %r.ptr648, align 4
  %301 = add i32 %r649, 1
  %r.ptr650 = getelementptr i32, ptr %0, i32 9
  store i32 %301, ptr %r.ptr650, align 4
  br label %draw_y_test

frame_flush:                                      ; preds = %draw_y_test
  call void @simFlush()
  br label %frame_start

unused_halt:                                      ; No predecessors!
  ret void
}

declare i32 @simRand()

declare void @simPutPixel(i32, i32, i32)

declare void @simFlush()
