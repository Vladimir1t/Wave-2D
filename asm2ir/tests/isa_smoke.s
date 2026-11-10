; Unit test of all data, compare, memory, special and control-flow instructions.
; A correct run draws one pixel with ARGB=197 and one with ARGB=1,
; then flushes. A failed assertion draws only one red pixel.
start:
  mov %a, 21
  mov %b, 4
  add %c, %a, %b
  eq %ok, %c, 25
  br %ok, sub_test, fail
sub_test:
  sub %c, %a, %b
  eq %ok, %c, 17
  br %ok, mul_test, fail
mul_test:
  mul %c, %a, %b
  eq %ok, %c, 84
  br %ok, div_test, fail
div_test:
  div %c, %a, %b
  eq %ok, %c, 5
  br %ok, mod_test, fail
mod_test:
  mod %c, %a, %b
  eq %ok, %c, 1
  br %ok, and_test, fail
and_test:
  and %c, %a, %b
  eq %ok, %c, 4
  br %ok, or_test, fail
or_test:
  or %c, %a, %b
  eq %ok, %c, 21
  br %ok, shl_test, fail
shl_test:
  shl %c, %b, 3
  eq %ok, %c, 32
  br %ok, ashr_test, fail
ashr_test:
  ashr %c, -8, 2
  eq %ok, %c, -2
  br %ok, lt_test, fail
lt_test:
  lt %ok, %b, %a
  br %ok, le_test, fail
le_test:
  le %ok, %b, 4
  br %ok, gt_test, fail
gt_test:
  gt %ok, %a, %b
  br %ok, ge_test, fail
ge_test:
  ge %ok, %a, 21
  br %ok, ne_test, fail
ne_test:
  ne %ok, %a, %b
  br %ok, circle_test, fail
circle_test:
  circle %ok, 12, 9, 10, 10, 3
  br %ok, mem_test, fail
mem_test:
  mov %cur, 0
  mov %prev, 1
  mov %water, 2
  mov %i, 513
  st %water, %i, -1
  st %cur, 512, 100
  st %cur, 514, 100
  st %cur, 1, 100
  st %cur, 1025, 100
  stencil %cur, %prev, %water, %i
  ld %c, %prev, %i
  eq %ok, %c, 197
  br %ok, shade_test, fail
shade_test:
  shade %color, %prev, %i
  ; For neighbors zero, slope zero, 90+(197>>4)=102.
  ; r=16,g=70,b=182 => 0xFF1046B6.
  eq %ok, %color, 0xFF1046B6
  br %ok, success, fail
success:
  pixel 0, 0, %c
  pixel 1, 0, %ok
  flush
  halt
fail:
  pixel 0, 0, 0xFFFF0000
  flush
  halt
