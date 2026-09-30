CC = clang

all: app app-opt.ll

# Оптимизированный LLVM IR модуля, в котором считается кадр
app-opt.ll: app.c sim.h
	$(CC) -O2 -S -emit-llvm app.c -o $@

# Приложение с SDL2-окном
app: app.c start.c sim.c sim.h
	$(CC) -O2 app.c start.c sim.c -lSDL2 -o $@

# Запуск через интерпретатор LLVM
start.ll: start.c
	$(CC) -S -emit-llvm $^ -o $@
sim.ll: sim.c
	$(CC) -S -emit-llvm $^ -o $@
full.bc: start.ll sim.ll app-opt.ll
	llvm-link $^ -o $@

run: app
	./app

clean:
	rm -f app start.ll sim.ll full.bc

.PHONY: all run clean
