# Usage: make -C asm2ir test / run-sim / run-calls / run-ir / sdl
CXX ?= c++
# clang matches the original project Makefile. In C, argument evaluation
# order in addDrop(...,simRand(),simRand(),...) is not portable to GCC.
CC = clang
# Use llvm-config if installed. Fallback is for Debian systems which ship
# the LLVM runtime but not the llvm-dev package (the included header suffices).
LLVM_CONFIG := $(shell command -v llvm-config-19 || command -v llvm-config || true)
ifeq ($(LLVM_CONFIG),)
  LLVM_CFLAGS :=
  LLVM_LDFLAGS := -l:libLLVM.so.19.1
else
  LLVM_CFLAGS := $(shell $(LLVM_CONFIG) --cxxflags | sed 's/-fno-exceptions//g')
  LLVM_LDFLAGS := $(shell $(LLVM_CONFIG) --ldflags --libs engine mcjit native core analysis --system-libs)
endif
CXXFLAGS ?= -O2 -std=c++17 -Wall -Wextra
all: asm2ir native-headless
build:
	mkdir -p build
build/sim_hash.o: sim_hash.c ../sim.h | build
	$(CC) -O2 -c $< -o $@
asm2ir: asm2ir.cpp llvm_c_api.h build/sim_hash.o
	$(CXX) $(CXXFLAGS) $(LLVM_CFLAGS) asm2ir.cpp build/sim_hash.o $(LLVM_LDFLAGS) -o $@
native-headless: ../app.c ../sim.h build/sim_hash.o
	$(CC) -O2 ../app.c ../start.c build/sim_hash.o -o $@
run-sim: asm2ir
	./asm2ir --mode sim --frames 1
run-calls: asm2ir
	./asm2ir --mode calls --frames 1
run-ir: asm2ir
	./asm2ir --mode ir --frames 1
emit: asm2ir
	mkdir -p generated
	./asm2ir --mode calls --emit generated/wave_calls.ll --emit-only
	./asm2ir --mode ir --emit generated/wave_ir.ll --emit-only
test: all
	bash ./test.sh
# Optional interactive visual run; SDL2 development headers required.
# The normal headless target has no SDL dependency.
build/sim_sdl.o: ../sim.c ../sim.h | build
	$(CC) -O2 -c $< -o $@
asm2ir-sdl: asm2ir.cpp llvm_c_api.h build/sim_sdl.o
	$(CXX) $(CXXFLAGS) $(LLVM_CFLAGS) asm2ir.cpp build/sim_sdl.o $(LLVM_LDFLAGS) -lSDL2 -o $@
clean:
	rm -rf build asm2ir native-headless asm2ir-sdl generated
.PHONY: all run-sim run-calls run-ir emit test clean
