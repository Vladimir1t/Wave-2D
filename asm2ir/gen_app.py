#!/usr/bin/env python3
"""Readable source-level assembly generator for Wave-2D (no C computation helpers)."""
from pathlib import Path

out=[]
def emit(*lines): out.extend(lines)
def section(title): emit('', '; ' + '-' * 69, '; ' + title, '; ' + '-' * 69)
def drop(prefix):
    emit(f'; Parabolic drop. Inputs: %drop_x, %drop_y, %drop_r, %drop_power and %cur',
         '  sub %dy, 0, %drop_r',
         f'{prefix}_dy_test:',
         '  le %test, %dy, %drop_r',
         f'  br %test, {prefix}_dy_body, {prefix}_done',
         f'{prefix}_dy_body:',
         '  sub %dx, 0, %drop_r',
         f'{prefix}_dx_test:',
         '  le %test, %dx, %drop_r',
         f'  br %test, {prefix}_cell, {prefix}_next_y',
         f'{prefix}_cell:',
         '  add %px, %drop_x, %dx',
         '  add %py, %drop_y, %dy',
         '  mul %d2, %dx, %dx',
         '  mul %tmp, %dy, %dy',
         '  add %d2, %d2, %tmp',
         '  mul %r2, %drop_r, %drop_r',
         '  gt %ok, %px, 0',
         '  lt %tmp, %px, 511', '  and %ok, %ok, %tmp',
         '  gt %tmp, %py, 0', '  and %ok, %ok, %tmp',
         '  lt %tmp, %py, 255', '  and %ok, %ok, %tmp',
         '  lt %tmp, %d2, %r2', '  and %ok, %ok, %tmp',
         f'  br %ok, {prefix}_add, {prefix}_next_x',
         f'{prefix}_add:',
         '  shl %idx, %py, 9', '  add %idx, %idx, %px',
         '  ld %old, %cur, %idx',
         '  sub %delta, %r2, %d2',
         '  mul %delta, %drop_power, %delta',
         '  div %delta, %delta, %r2',
         '  add %old, %old, %delta',
         '  st %cur, %idx, %old',
         f'  jmp {prefix}_next_x',
         f'{prefix}_next_x:',
         '  add %dx, %dx, 1', f'  jmp {prefix}_dx_test',
         f'{prefix}_next_y:',
         '  add %dy, %dy, 1', f'  jmp {prefix}_dy_test',
         f'{prefix}_done:')

emit('; Wave-2D custom-ISA assembly program for the WAVE32 ISA.',
     '; 1536x768 image / SCALE=3 -> 512x256 grid, four i32 buffers.',
     '; The register names are symbolic; the assembler assigns physical slots.',
     '; All stencil, lighting, drop and draw logic is in this file.',
     'start:',
     '  mov %cur, 0', '  mov %prev, 1', '  mov %water, 2', '  mov %shown, 3',
     '  mov %ox, 65536', '  mov %oy, 0',
     '  mov %bx, 406', '  mov %by, 128',
     '  mov %step, 0')
section('Construct the four-sided land mask and three circular islands')
emit('  mov %y, 0', 'pool_y:',
     '  lt %test, %y, 256', '  br %test, pool_y_body, pool_done',
     'pool_y_body:', '  mov %x, 0', 'pool_x:',
     '  lt %test, %x, 512', '  br %test, pool_cell, pool_next_y',
     'pool_cell:',
     '  eq %land, %x, 0', '  eq %tmp, %y, 0', '  or %land, %land, %tmp',
     '  eq %tmp, %x, 511', '  or %land, %land, %tmp',
     '  eq %tmp, %y, 255', '  or %land, %land, %tmp',
     '  circle %tmp, %x, %y, 256, 128, 34', '  or %land, %land, %tmp',
     '  circle %tmp, %x, %y, 60, 55, 22', '  or %land, %land, %tmp',
     '  circle %tmp, %x, %y, 442, 201, 18', '  or %land, %land, %tmp',
     '  sub %mask, %land, 1',
     '  shl %idx, %y, 9', '  add %idx, %idx, %x',
     '  st %water, %idx, %mask',
     '  add %x, %x, 1', '  jmp pool_x',
     'pool_next_y:', '  add %y, %y, 1', '  jmp pool_y',
     'pool_done:')
section('Main loop: two wave time-steps per frame')
emit('frame_start:', '  mov %s, 0',
     'wave_s_test:', '  lt %test, %s, 2',
     '  br %test, wave_s_body, rain_start',
     'wave_s_body:',
     '  mul %bx, %ox, 150', '  div %bx, %bx, 65536', '  add %bx, %bx, 256',
     '  mul %by, %oy, 80', '  div %by, %by, 65536', '  add %by, %by, 128',
     '  div %drop_power, %step, 5', '  and %drop_power, %drop_power, 1',
     '  mul %drop_power, %drop_power, 2', '  sub %drop_power, %drop_power, 1',
     '  mul %drop_power, %drop_power, 500',
     '  mov %drop_x, %bx', '  mov %drop_y, %by',
     '  mov %drop_r, 2')
section('Moving pulsating source: addDrop(cur,bx,by,2,+/-500)')
drop('source')
section('waveStep: update prev cell by cell, then swap temporal buffers')
emit('  mov %y, 1', 'wave_y_test:',
     '  lt %test, %y, 255', '  br %test, wave_y_body, wave_done',
     'wave_y_body:', '  mov %x, 1', 'wave_x_test:',
     '  lt %test, %x, 511', '  br %test, wave_x_body, wave_next_y',
     'wave_x_body:', '  shl %idx, %y, 9', '  add %idx, %idx, %x',
     '  stencil %cur, %prev, %water, %idx',
     '  add %x, %x, 1', '  jmp wave_x_test',
     'wave_next_y:', '  add %y, %y, 1', '  jmp wave_y_test',
     'wave_done:',
     '  mov %tmp, %cur', '  mov %cur, %prev', '  mov %prev, %tmp',
     '  ashr %tmp, %oy, 8', '  sub %ox, %ox, %tmp',
     '  ashr %tmp, %ox, 8', '  add %oy, %oy, %tmp',
     '  add %step, %step, 1', '  add %s, %s, 1', '  jmp wave_s_test')
section('Stochastic rain: every 4th frame on average, same simRand() as app.c')
emit('rain_start:',
     '  rand %rnd', '  mod %rnd, %rnd, 4', '  eq %test, %rnd, 0',
     '  br %test, rain_setup, draw_start',
     'rain_setup:',
     '  rand %drop_x', '  mod %drop_x, %drop_x, 510', '  add %drop_x, %drop_x, 1',
     '  rand %drop_y', '  mod %drop_y, %drop_y, 254', '  add %drop_y, %drop_y, 1',
     '  mov %drop_r, 4', '  mov %drop_power, 2000')
section('Rain drop: addDrop(cur,rand_x,rand_y,4,2000)')
drop('rain')
emit('  jmp draw_start')
section('drawFrame: compute color, mark source and redraw changed cells only')
emit('draw_start:', '  mov %y, 0',
     'draw_y_test:', '  lt %test, %y, 256',
     '  br %test, draw_y_body, frame_flush',
     'draw_y_body:', '  mov %x, 0', 'draw_x_test:',
     '  lt %test, %x, 512', '  br %test, draw_cell, draw_next_y',
     'draw_cell:', '  shl %idx, %y, 9', '  add %idx, %idx, %x',
     '  ld %mask, %water, %idx', '  ne %test, %mask, 0',
     '  br %test, draw_water, draw_land',
     'draw_water:', '  shade %color, %cur, %idx', '  jmp draw_boat_check',
     'draw_land:', '  mov %color, 0xFFC8A96E', '  jmp draw_boat_check',
     'draw_boat_check:', '  circle %test, %x, %y, %bx, %by, 2',
     '  br %test, draw_boat, draw_shown',
     'draw_boat:', '  mov %color, 0xFFFF5040', '  jmp draw_shown',
     'draw_shown:', '  ld %old, %shown, %idx',
     '  ne %test, %color, %old',
     '  br %test, draw_changed, draw_next_x',
     'draw_changed:', '  st %shown, %idx, %color',
     '  mul %pixel_x0, %x, 3', '  mul %pixel_y0, %y, 3',
     '  mov %pixel_dy, 0',
     'pixel_y_test:', '  lt %test, %pixel_dy, 3',
     '  br %test, pixel_y_body, draw_next_x',
     'pixel_y_body:', '  mov %pixel_dx, 0',
     'pixel_x_test:', '  lt %test, %pixel_dx, 3',
     '  br %test, pixel_body, pixel_next_y',
     'pixel_body:', '  add %pixel_x, %pixel_x0, %pixel_dx',
     '  add %pixel_y, %pixel_y0, %pixel_dy',
     '  pixel %pixel_x, %pixel_y, %color',
     '  add %pixel_dx, %pixel_dx, 1', '  jmp pixel_x_test',
     'pixel_next_y:', '  add %pixel_dy, %pixel_dy, 1', '  jmp pixel_y_test',
     'draw_next_x:', '  add %x, %x, 1', '  jmp draw_x_test',
     'draw_next_y:', '  add %y, %y, 1', '  jmp draw_y_test',
     'frame_flush:', '  flush', '  jmp frame_start',
     'unused_halt:', '  halt')
# Explicit fall-through edges: the assembler requires every basic block to
# end in a real control-flow instruction (just like LLVM IR).
normalized=[]
for line in out:
    if line.strip().endswith(':'):
        last=next((x.strip() for x in reversed(normalized) if x.strip() and not x.strip().startswith(';')), '')
        if last and not last.endswith(':') and not last.split()[0] in ('jmp','br','halt'):
            normalized.append('  jmp ' + line.strip()[:-1])
        elif last.endswith(':'):
            normalized.append('  jmp ' + line.strip()[:-1])
    normalized.append(line)
out=normalized
path=Path(__file__).with_name('app.s')
path.write_text('\n'.join(out) + '\n', encoding='utf-8')
print(f'Wrote {path}, {len(out)} lines')
