CC = clang
CXX = clang++
# Уровень оптимизации app.c (можно -Os)
OPT ?= -O2
LLVM_INC ?= $(shell llvm-config --includedir)
# Сколько кадров анализировать в make stats
FRAMES ?= 20

PLUGIN = build/libUseTracePass.so

all: app app-opt.ll

# ---------------- Задание 1 ----------------

# Оптимизированный LLVM IR модуля, в котором считается кадр
app-opt.ll: app.c sim.h
	$(CC) $(OPT) -S -emit-llvm app.c -o $@

# Приложение с SDL2-окном
app: app.c start.c sim.c sim.h
	$(CC) $(OPT) app.c start.c sim.c -lSDL2 -o $@

# Запуск через интерпретатор LLVM
start.ll: start.c
	$(CC) -S -emit-llvm $^ -o $@
sim.ll: sim.c
	$(CC) -S -emit-llvm $^ -o $@
full.bc: start.ll sim.ll app-opt.ll
	llvm-link $^ -o $@

run: app
	./app

# ---------------- Задание 2: трасса User <- Operand ----------------

$(PLUGIN): pass/UseTracePass.cpp
	mkdir -p build
	$(CXX) -std=c++17 -O2 -fPIC -shared -I$(LLVM_INC) $< -o $@

# Инструментируется только app.c; start.c, sim.c и логгер - без пасса
build/app-trace.ll: app.c sim.h $(PLUGIN)
	$(CC) $(OPT) -fpass-plugin=$(PLUGIN) -S -emit-llvm app.c -o $@
build/app-trace-phi.ll: app.c sim.h $(PLUGIN)
	TRACE_PHI=1 $(CC) $(OPT) -fpass-plugin=$(PLUGIN) -S -emit-llvm app.c -o $@

# С SDL-окном: трасса пишется во время работы приложения
app-trace: build/app-trace.ll start.c sim.c pass/trace_log.c
	$(CC) -O2 $^ -lSDL2 -o $@
app-trace-phi: build/app-trace-phi.ll start.c sim.c pass/trace_log.c
	$(CC) -O2 $^ -lSDL2 -o $@

# Без окна, с фиксированным seed: воспроизводимый сбор статистики
build/app-trace-headless: build/app-trace.ll start.c pass/sim_headless.c pass/trace_log.c
	$(CC) -O2 $^ -o $@
build/app-trace-phi-headless: build/app-trace-phi.ll start.c pass/sim_headless.c pass/trace_log.c
	$(CC) -O2 $^ -o $@

stats: build/app-trace-headless build/app-trace-phi-headless
	mkdir -p stats
	TRACE_OUT=stats/basic SIM_FRAMES=$(FRAMES) TRACE_LIMIT=100000000000 ./build/app-trace-headless
	TRACE_OUT=stats/phi SIM_FRAMES=$(FRAMES) TRACE_LIMIT=100000000000 ./build/app-trace-phi-headless
	python3 pass/report.py stats/basic_ngrams.csv stats/phi_ngrams.csv --top 20 -o stats/STATS.md

clean:
	rm -rf app app-trace app-trace-phi start.ll sim.ll full.bc build

.PHONY: all run stats clean
