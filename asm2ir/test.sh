#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
frames="${FRAMES:-1}"
reference="$(SIM_FRAMES="$frames" ./native-headless 2>/dev/null | grep '^frames=')"
echo "C reference : $reference"
for mode in sim calls ir; do
  result="$(./asm2ir --mode "$mode" --frames "$frames" 2>/dev/null | grep '^frames=')"
  printf '%-12s: %s\n' "$mode" "$result"
  if [[ "$result" != "$reference" ]]; then
    echo "FAIL: $mode diverged from original app.c" >&2
    exit 1
  fi
done
mkdir -p generated
./asm2ir --mode calls --emit generated/wave_calls.ll --emit-only
./asm2ir --mode ir --emit generated/wave_ir.ll --emit-only
if grep -qE '@emu_' generated/wave_ir.ll; then
  echo 'FAIL: pure IR still calls instruction emulators' >&2
  exit 1
fi
if ! grep -q '@emu_stencil' generated/wave_calls.ll; then
  echo 'FAIL: emulation-call IR missing the stencil emulator' >&2
  exit 1
fi
expected_smoke='frames=1 pixels=2 fnv64=c4a8148fd72b52a0'
for mode in sim calls ir; do
  smoke="$(./asm2ir --asm tests/isa_smoke.s --mode "$mode" --frames 1 | grep '^frames=')"
  if [[ "$smoke" != "$expected_smoke" ]]; then
    echo "FAIL: ISA smoke test diverged in $mode: $smoke" >&2
    exit 1
  fi
done
echo "PASS: ISA smoke tests (integer arithmetic, comparisons, memory, circle, stencil, shade)."
echo "PASS: all three modes match original Wave-2D bit-for-bit on pixel stream; IR modes verified."
