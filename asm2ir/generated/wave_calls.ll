; ModuleID = 'wave32_calls'
source_filename = "wave32_calls"

define void @wave32_app(ptr %0) {
start:
  call void @emu_mov(ptr %0, i64 4294967296, i64 0, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967297, i64 1, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967298, i64 2, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967299, i64 3, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967300, i64 65536, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967301, i64 0, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967302, i64 406, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967303, i64 128, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967304, i64 0, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967305, i64 0, i64 0, i64 0, i64 0, i64 0)
  br label %pool_y

pool_y:                                           ; preds = %pool_next_y, %start
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967305, i64 256, i64 0, i64 0, i64 0)
  %r.ptr = getelementptr i32, ptr %0, i32 10
  %r = load i32, ptr %r.ptr, align 4
  %1 = icmp ne i32 %r, 0
  br i1 %1, label %pool_y_body, label %pool_done

pool_y_body:                                      ; preds = %pool_y
  call void @emu_mov(ptr %0, i64 4294967307, i64 0, i64 0, i64 0, i64 0, i64 0)
  br label %pool_x

pool_x:                                           ; preds = %pool_cell, %pool_y_body
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967307, i64 512, i64 0, i64 0, i64 0)
  %r.ptr1 = getelementptr i32, ptr %0, i32 10
  %r2 = load i32, ptr %r.ptr1, align 4
  %2 = icmp ne i32 %r2, 0
  br i1 %2, label %pool_cell, label %pool_next_y

pool_cell:                                        ; preds = %pool_x
  call void @emu_eq(ptr %0, i64 4294967308, i64 4294967307, i64 0, i64 0, i64 0, i64 0)
  call void @emu_eq(ptr %0, i64 4294967309, i64 4294967305, i64 0, i64 0, i64 0, i64 0)
  call void @emu_or(ptr %0, i64 4294967308, i64 4294967308, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_eq(ptr %0, i64 4294967309, i64 4294967307, i64 511, i64 0, i64 0, i64 0)
  call void @emu_or(ptr %0, i64 4294967308, i64 4294967308, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_eq(ptr %0, i64 4294967309, i64 4294967305, i64 255, i64 0, i64 0, i64 0)
  call void @emu_or(ptr %0, i64 4294967308, i64 4294967308, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_circle(ptr %0, i64 4294967309, i64 4294967307, i64 4294967305, i64 256, i64 128, i64 34)
  call void @emu_or(ptr %0, i64 4294967308, i64 4294967308, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_circle(ptr %0, i64 4294967309, i64 4294967307, i64 4294967305, i64 60, i64 55, i64 22)
  call void @emu_or(ptr %0, i64 4294967308, i64 4294967308, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_circle(ptr %0, i64 4294967309, i64 4294967307, i64 4294967305, i64 442, i64 201, i64 18)
  call void @emu_or(ptr %0, i64 4294967308, i64 4294967308, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_sub(ptr %0, i64 4294967310, i64 4294967308, i64 1, i64 0, i64 0, i64 0)
  call void @emu_shl(ptr %0, i64 4294967311, i64 4294967305, i64 9, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967311, i64 4294967311, i64 4294967307, i64 0, i64 0, i64 0)
  call void @emu_st(ptr %0, i64 4294967298, i64 4294967311, i64 4294967310, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967307, i64 4294967307, i64 1, i64 0, i64 0, i64 0)
  br label %pool_x

pool_next_y:                                      ; preds = %pool_x
  call void @emu_add(ptr %0, i64 4294967305, i64 4294967305, i64 1, i64 0, i64 0, i64 0)
  br label %pool_y

pool_done:                                        ; preds = %pool_y
  br label %frame_start

frame_start:                                      ; preds = %frame_flush, %pool_done
  call void @emu_mov(ptr %0, i64 4294967312, i64 0, i64 0, i64 0, i64 0, i64 0)
  br label %wave_s_test

wave_s_test:                                      ; preds = %wave_done, %frame_start
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967312, i64 2, i64 0, i64 0, i64 0)
  %r.ptr3 = getelementptr i32, ptr %0, i32 10
  %r4 = load i32, ptr %r.ptr3, align 4
  %3 = icmp ne i32 %r4, 0
  br i1 %3, label %wave_s_body, label %rain_start

wave_s_body:                                      ; preds = %wave_s_test
  call void @emu_mul(ptr %0, i64 4294967302, i64 4294967300, i64 150, i64 0, i64 0, i64 0)
  call void @emu_div(ptr %0, i64 4294967302, i64 4294967302, i64 65536, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967302, i64 4294967302, i64 256, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967303, i64 4294967301, i64 80, i64 0, i64 0, i64 0)
  call void @emu_div(ptr %0, i64 4294967303, i64 4294967303, i64 65536, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967303, i64 4294967303, i64 128, i64 0, i64 0, i64 0)
  call void @emu_div(ptr %0, i64 4294967313, i64 4294967304, i64 5, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967313, i64 4294967313, i64 1, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967313, i64 4294967313, i64 2, i64 0, i64 0, i64 0)
  call void @emu_sub(ptr %0, i64 4294967313, i64 4294967313, i64 1, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967313, i64 4294967313, i64 500, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967314, i64 4294967302, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967315, i64 4294967303, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967316, i64 2, i64 0, i64 0, i64 0, i64 0)
  call void @emu_sub(ptr %0, i64 4294967317, i64 0, i64 4294967316, i64 0, i64 0, i64 0)
  br label %source_dy_test

source_dy_test:                                   ; preds = %source_next_y, %wave_s_body
  call void @emu_le(ptr %0, i64 4294967306, i64 4294967317, i64 4294967316, i64 0, i64 0, i64 0)
  %r.ptr5 = getelementptr i32, ptr %0, i32 10
  %r6 = load i32, ptr %r.ptr5, align 4
  %4 = icmp ne i32 %r6, 0
  br i1 %4, label %source_dy_body, label %source_done

source_dy_body:                                   ; preds = %source_dy_test
  call void @emu_sub(ptr %0, i64 4294967318, i64 0, i64 4294967316, i64 0, i64 0, i64 0)
  br label %source_dx_test

source_dx_test:                                   ; preds = %source_next_x, %source_dy_body
  call void @emu_le(ptr %0, i64 4294967306, i64 4294967318, i64 4294967316, i64 0, i64 0, i64 0)
  %r.ptr7 = getelementptr i32, ptr %0, i32 10
  %r8 = load i32, ptr %r.ptr7, align 4
  %5 = icmp ne i32 %r8, 0
  br i1 %5, label %source_cell, label %source_next_y

source_cell:                                      ; preds = %source_dx_test
  call void @emu_add(ptr %0, i64 4294967319, i64 4294967314, i64 4294967318, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967320, i64 4294967315, i64 4294967317, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967321, i64 4294967318, i64 4294967318, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967309, i64 4294967317, i64 4294967317, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967321, i64 4294967321, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967322, i64 4294967316, i64 4294967316, i64 0, i64 0, i64 0)
  call void @emu_gt(ptr %0, i64 4294967323, i64 4294967319, i64 0, i64 0, i64 0, i64 0)
  call void @emu_lt(ptr %0, i64 4294967309, i64 4294967319, i64 511, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967323, i64 4294967323, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_gt(ptr %0, i64 4294967309, i64 4294967320, i64 0, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967323, i64 4294967323, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_lt(ptr %0, i64 4294967309, i64 4294967320, i64 255, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967323, i64 4294967323, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_lt(ptr %0, i64 4294967309, i64 4294967321, i64 4294967322, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967323, i64 4294967323, i64 4294967309, i64 0, i64 0, i64 0)
  %r.ptr9 = getelementptr i32, ptr %0, i32 27
  %r10 = load i32, ptr %r.ptr9, align 4
  %6 = icmp ne i32 %r10, 0
  br i1 %6, label %source_add, label %source_next_x

source_add:                                       ; preds = %source_cell
  call void @emu_shl(ptr %0, i64 4294967311, i64 4294967320, i64 9, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967311, i64 4294967311, i64 4294967319, i64 0, i64 0, i64 0)
  call void @emu_ld(ptr %0, i64 4294967324, i64 4294967296, i64 4294967311, i64 0, i64 0, i64 0)
  call void @emu_sub(ptr %0, i64 4294967325, i64 4294967322, i64 4294967321, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967325, i64 4294967313, i64 4294967325, i64 0, i64 0, i64 0)
  call void @emu_div(ptr %0, i64 4294967325, i64 4294967325, i64 4294967322, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967324, i64 4294967324, i64 4294967325, i64 0, i64 0, i64 0)
  call void @emu_st(ptr %0, i64 4294967296, i64 4294967311, i64 4294967324, i64 0, i64 0, i64 0)
  br label %source_next_x

source_next_x:                                    ; preds = %source_add, %source_cell
  call void @emu_add(ptr %0, i64 4294967318, i64 4294967318, i64 1, i64 0, i64 0, i64 0)
  br label %source_dx_test

source_next_y:                                    ; preds = %source_dx_test
  call void @emu_add(ptr %0, i64 4294967317, i64 4294967317, i64 1, i64 0, i64 0, i64 0)
  br label %source_dy_test

source_done:                                      ; preds = %source_dy_test
  call void @emu_mov(ptr %0, i64 4294967305, i64 1, i64 0, i64 0, i64 0, i64 0)
  br label %wave_y_test

wave_y_test:                                      ; preds = %wave_next_y, %source_done
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967305, i64 255, i64 0, i64 0, i64 0)
  %r.ptr11 = getelementptr i32, ptr %0, i32 10
  %r12 = load i32, ptr %r.ptr11, align 4
  %7 = icmp ne i32 %r12, 0
  br i1 %7, label %wave_y_body, label %wave_done

wave_y_body:                                      ; preds = %wave_y_test
  call void @emu_mov(ptr %0, i64 4294967307, i64 1, i64 0, i64 0, i64 0, i64 0)
  br label %wave_x_test

wave_x_test:                                      ; preds = %wave_x_body, %wave_y_body
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967307, i64 511, i64 0, i64 0, i64 0)
  %r.ptr13 = getelementptr i32, ptr %0, i32 10
  %r14 = load i32, ptr %r.ptr13, align 4
  %8 = icmp ne i32 %r14, 0
  br i1 %8, label %wave_x_body, label %wave_next_y

wave_x_body:                                      ; preds = %wave_x_test
  call void @emu_shl(ptr %0, i64 4294967311, i64 4294967305, i64 9, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967311, i64 4294967311, i64 4294967307, i64 0, i64 0, i64 0)
  call void @emu_stencil(ptr %0, i64 4294967296, i64 4294967297, i64 4294967298, i64 4294967311, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967307, i64 4294967307, i64 1, i64 0, i64 0, i64 0)
  br label %wave_x_test

wave_next_y:                                      ; preds = %wave_x_test
  call void @emu_add(ptr %0, i64 4294967305, i64 4294967305, i64 1, i64 0, i64 0, i64 0)
  br label %wave_y_test

wave_done:                                        ; preds = %wave_y_test
  call void @emu_mov(ptr %0, i64 4294967309, i64 4294967296, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967296, i64 4294967297, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967297, i64 4294967309, i64 0, i64 0, i64 0, i64 0)
  call void @emu_ashr(ptr %0, i64 4294967309, i64 4294967301, i64 8, i64 0, i64 0, i64 0)
  call void @emu_sub(ptr %0, i64 4294967300, i64 4294967300, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_ashr(ptr %0, i64 4294967309, i64 4294967300, i64 8, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967301, i64 4294967301, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967304, i64 4294967304, i64 1, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967312, i64 4294967312, i64 1, i64 0, i64 0, i64 0)
  br label %wave_s_test

rain_start:                                       ; preds = %wave_s_test
  call void @emu_rand(ptr %0, i64 4294967326, i64 0, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mod(ptr %0, i64 4294967326, i64 4294967326, i64 4, i64 0, i64 0, i64 0)
  call void @emu_eq(ptr %0, i64 4294967306, i64 4294967326, i64 0, i64 0, i64 0, i64 0)
  %r.ptr15 = getelementptr i32, ptr %0, i32 10
  %r16 = load i32, ptr %r.ptr15, align 4
  %9 = icmp ne i32 %r16, 0
  br i1 %9, label %rain_setup, label %draw_start

rain_setup:                                       ; preds = %rain_start
  call void @emu_rand(ptr %0, i64 4294967314, i64 0, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mod(ptr %0, i64 4294967314, i64 4294967314, i64 510, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967314, i64 4294967314, i64 1, i64 0, i64 0, i64 0)
  call void @emu_rand(ptr %0, i64 4294967315, i64 0, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mod(ptr %0, i64 4294967315, i64 4294967315, i64 254, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967315, i64 4294967315, i64 1, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967316, i64 4, i64 0, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967313, i64 2000, i64 0, i64 0, i64 0, i64 0)
  call void @emu_sub(ptr %0, i64 4294967317, i64 0, i64 4294967316, i64 0, i64 0, i64 0)
  br label %rain_dy_test

rain_dy_test:                                     ; preds = %rain_next_y, %rain_setup
  call void @emu_le(ptr %0, i64 4294967306, i64 4294967317, i64 4294967316, i64 0, i64 0, i64 0)
  %r.ptr17 = getelementptr i32, ptr %0, i32 10
  %r18 = load i32, ptr %r.ptr17, align 4
  %10 = icmp ne i32 %r18, 0
  br i1 %10, label %rain_dy_body, label %rain_done

rain_dy_body:                                     ; preds = %rain_dy_test
  call void @emu_sub(ptr %0, i64 4294967318, i64 0, i64 4294967316, i64 0, i64 0, i64 0)
  br label %rain_dx_test

rain_dx_test:                                     ; preds = %rain_next_x, %rain_dy_body
  call void @emu_le(ptr %0, i64 4294967306, i64 4294967318, i64 4294967316, i64 0, i64 0, i64 0)
  %r.ptr19 = getelementptr i32, ptr %0, i32 10
  %r20 = load i32, ptr %r.ptr19, align 4
  %11 = icmp ne i32 %r20, 0
  br i1 %11, label %rain_cell, label %rain_next_y

rain_cell:                                        ; preds = %rain_dx_test
  call void @emu_add(ptr %0, i64 4294967319, i64 4294967314, i64 4294967318, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967320, i64 4294967315, i64 4294967317, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967321, i64 4294967318, i64 4294967318, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967309, i64 4294967317, i64 4294967317, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967321, i64 4294967321, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967322, i64 4294967316, i64 4294967316, i64 0, i64 0, i64 0)
  call void @emu_gt(ptr %0, i64 4294967323, i64 4294967319, i64 0, i64 0, i64 0, i64 0)
  call void @emu_lt(ptr %0, i64 4294967309, i64 4294967319, i64 511, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967323, i64 4294967323, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_gt(ptr %0, i64 4294967309, i64 4294967320, i64 0, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967323, i64 4294967323, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_lt(ptr %0, i64 4294967309, i64 4294967320, i64 255, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967323, i64 4294967323, i64 4294967309, i64 0, i64 0, i64 0)
  call void @emu_lt(ptr %0, i64 4294967309, i64 4294967321, i64 4294967322, i64 0, i64 0, i64 0)
  call void @emu_and(ptr %0, i64 4294967323, i64 4294967323, i64 4294967309, i64 0, i64 0, i64 0)
  %r.ptr21 = getelementptr i32, ptr %0, i32 27
  %r22 = load i32, ptr %r.ptr21, align 4
  %12 = icmp ne i32 %r22, 0
  br i1 %12, label %rain_add, label %rain_next_x

rain_add:                                         ; preds = %rain_cell
  call void @emu_shl(ptr %0, i64 4294967311, i64 4294967320, i64 9, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967311, i64 4294967311, i64 4294967319, i64 0, i64 0, i64 0)
  call void @emu_ld(ptr %0, i64 4294967324, i64 4294967296, i64 4294967311, i64 0, i64 0, i64 0)
  call void @emu_sub(ptr %0, i64 4294967325, i64 4294967322, i64 4294967321, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967325, i64 4294967313, i64 4294967325, i64 0, i64 0, i64 0)
  call void @emu_div(ptr %0, i64 4294967325, i64 4294967325, i64 4294967322, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967324, i64 4294967324, i64 4294967325, i64 0, i64 0, i64 0)
  call void @emu_st(ptr %0, i64 4294967296, i64 4294967311, i64 4294967324, i64 0, i64 0, i64 0)
  br label %rain_next_x

rain_next_x:                                      ; preds = %rain_add, %rain_cell
  call void @emu_add(ptr %0, i64 4294967318, i64 4294967318, i64 1, i64 0, i64 0, i64 0)
  br label %rain_dx_test

rain_next_y:                                      ; preds = %rain_dx_test
  call void @emu_add(ptr %0, i64 4294967317, i64 4294967317, i64 1, i64 0, i64 0, i64 0)
  br label %rain_dy_test

rain_done:                                        ; preds = %rain_dy_test
  br label %draw_start

draw_start:                                       ; preds = %rain_done, %rain_start
  call void @emu_mov(ptr %0, i64 4294967305, i64 0, i64 0, i64 0, i64 0, i64 0)
  br label %draw_y_test

draw_y_test:                                      ; preds = %draw_next_y, %draw_start
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967305, i64 256, i64 0, i64 0, i64 0)
  %r.ptr23 = getelementptr i32, ptr %0, i32 10
  %r24 = load i32, ptr %r.ptr23, align 4
  %13 = icmp ne i32 %r24, 0
  br i1 %13, label %draw_y_body, label %frame_flush

draw_y_body:                                      ; preds = %draw_y_test
  call void @emu_mov(ptr %0, i64 4294967307, i64 0, i64 0, i64 0, i64 0, i64 0)
  br label %draw_x_test

draw_x_test:                                      ; preds = %draw_next_x, %draw_y_body
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967307, i64 512, i64 0, i64 0, i64 0)
  %r.ptr25 = getelementptr i32, ptr %0, i32 10
  %r26 = load i32, ptr %r.ptr25, align 4
  %14 = icmp ne i32 %r26, 0
  br i1 %14, label %draw_cell, label %draw_next_y

draw_cell:                                        ; preds = %draw_x_test
  call void @emu_shl(ptr %0, i64 4294967311, i64 4294967305, i64 9, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967311, i64 4294967311, i64 4294967307, i64 0, i64 0, i64 0)
  call void @emu_ld(ptr %0, i64 4294967310, i64 4294967298, i64 4294967311, i64 0, i64 0, i64 0)
  call void @emu_ne(ptr %0, i64 4294967306, i64 4294967310, i64 0, i64 0, i64 0, i64 0)
  %r.ptr27 = getelementptr i32, ptr %0, i32 10
  %r28 = load i32, ptr %r.ptr27, align 4
  %15 = icmp ne i32 %r28, 0
  br i1 %15, label %draw_water, label %draw_land

draw_water:                                       ; preds = %draw_cell
  call void @emu_shade(ptr %0, i64 4294967327, i64 4294967296, i64 4294967311, i64 0, i64 0, i64 0)
  br label %draw_boat_check

draw_land:                                        ; preds = %draw_cell
  call void @emu_mov(ptr %0, i64 4294967327, i64 4291340654, i64 0, i64 0, i64 0, i64 0)
  br label %draw_boat_check

draw_boat_check:                                  ; preds = %draw_land, %draw_water
  call void @emu_circle(ptr %0, i64 4294967306, i64 4294967307, i64 4294967305, i64 4294967302, i64 4294967303, i64 2)
  %r.ptr29 = getelementptr i32, ptr %0, i32 10
  %r30 = load i32, ptr %r.ptr29, align 4
  %16 = icmp ne i32 %r30, 0
  br i1 %16, label %draw_boat, label %draw_shown

draw_boat:                                        ; preds = %draw_boat_check
  call void @emu_mov(ptr %0, i64 4294967327, i64 4294922304, i64 0, i64 0, i64 0, i64 0)
  br label %draw_shown

draw_shown:                                       ; preds = %draw_boat, %draw_boat_check
  call void @emu_ld(ptr %0, i64 4294967324, i64 4294967299, i64 4294967311, i64 0, i64 0, i64 0)
  call void @emu_ne(ptr %0, i64 4294967306, i64 4294967327, i64 4294967324, i64 0, i64 0, i64 0)
  %r.ptr31 = getelementptr i32, ptr %0, i32 10
  %r32 = load i32, ptr %r.ptr31, align 4
  %17 = icmp ne i32 %r32, 0
  br i1 %17, label %draw_changed, label %draw_next_x

draw_changed:                                     ; preds = %draw_shown
  call void @emu_st(ptr %0, i64 4294967299, i64 4294967311, i64 4294967327, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967328, i64 4294967307, i64 3, i64 0, i64 0, i64 0)
  call void @emu_mul(ptr %0, i64 4294967329, i64 4294967305, i64 3, i64 0, i64 0, i64 0)
  call void @emu_mov(ptr %0, i64 4294967330, i64 0, i64 0, i64 0, i64 0, i64 0)
  br label %pixel_y_test

pixel_y_test:                                     ; preds = %pixel_next_y, %draw_changed
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967330, i64 3, i64 0, i64 0, i64 0)
  %r.ptr33 = getelementptr i32, ptr %0, i32 10
  %r34 = load i32, ptr %r.ptr33, align 4
  %18 = icmp ne i32 %r34, 0
  br i1 %18, label %pixel_y_body, label %draw_next_x

pixel_y_body:                                     ; preds = %pixel_y_test
  call void @emu_mov(ptr %0, i64 4294967331, i64 0, i64 0, i64 0, i64 0, i64 0)
  br label %pixel_x_test

pixel_x_test:                                     ; preds = %pixel_body, %pixel_y_body
  call void @emu_lt(ptr %0, i64 4294967306, i64 4294967331, i64 3, i64 0, i64 0, i64 0)
  %r.ptr35 = getelementptr i32, ptr %0, i32 10
  %r36 = load i32, ptr %r.ptr35, align 4
  %19 = icmp ne i32 %r36, 0
  br i1 %19, label %pixel_body, label %pixel_next_y

pixel_body:                                       ; preds = %pixel_x_test
  call void @emu_add(ptr %0, i64 4294967332, i64 4294967328, i64 4294967331, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967333, i64 4294967329, i64 4294967330, i64 0, i64 0, i64 0)
  call void @emu_pixel(ptr %0, i64 4294967332, i64 4294967333, i64 4294967327, i64 0, i64 0, i64 0)
  call void @emu_add(ptr %0, i64 4294967331, i64 4294967331, i64 1, i64 0, i64 0, i64 0)
  br label %pixel_x_test

pixel_next_y:                                     ; preds = %pixel_x_test
  call void @emu_add(ptr %0, i64 4294967330, i64 4294967330, i64 1, i64 0, i64 0, i64 0)
  br label %pixel_y_test

draw_next_x:                                      ; preds = %pixel_y_test, %draw_shown
  call void @emu_add(ptr %0, i64 4294967307, i64 4294967307, i64 1, i64 0, i64 0, i64 0)
  br label %draw_x_test

draw_next_y:                                      ; preds = %draw_x_test
  call void @emu_add(ptr %0, i64 4294967305, i64 4294967305, i64 1, i64 0, i64 0, i64 0)
  br label %draw_y_test

frame_flush:                                      ; preds = %draw_y_test
  call void @emu_flush(ptr %0, i64 0, i64 0, i64 0, i64 0, i64 0, i64 0)
  br label %frame_start

unused_halt:                                      ; No predecessors!
  ret void
}

declare void @emu_mov(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_add(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_sub(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_mul(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_div(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_mod(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_and(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_or(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_shl(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_ashr(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_eq(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_ne(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_lt(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_le(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_gt(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_ge(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_ld(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_st(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_circle(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_stencil(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_shade(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_rand(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_pixel(ptr, i64, i64, i64, i64, i64, i64)

declare void @emu_flush(ptr, i64, i64, i64, i64, i64, i64)
