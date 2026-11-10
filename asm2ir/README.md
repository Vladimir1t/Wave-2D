# Assignment 4: Wave32 ASM → LLVM IR → ExecutionEngine

Полное описание ISA, статистическое обоснование, список инструкций и схема
реализации: **[INSTRUCTION_SET.md](INSTRUCTION_SET.md)**.

## Содержимое

| Файл | Назначение |
|---|---|
| [`app.s`](app.s) | Всё приложение Wave-2D на собственном ASM |
| [`gen_app.py`](gen_app.py) | Удобно редактируемый генератор/источник полной ASM-программы |
| [`asm2ir.cpp`](asm2ir.cpp) | Парсер, симулятор и два LLVM IR генератора + MCJIT |
| [`llvm_c_api.h`](llvm_c_api.h) | LLVM C API, системные заголовки или runtime-only fallback |
| [`INSTRUCTION_SET.md`](INSTRUCTION_SET.md) | Архитектура, полная таблица инструкций и связь со статистикой |
| [`sim_hash.c`](sim_hash.c) | Headless backend с детерминированной проверкой потока пикселей |
| [`tests/isa_smoke.s`](tests/isa_smoke.s) | ISA smoke-тест |
| [`test.sh`](test.sh) | Проверка трёх режимов на исходной программе и smoke-тест |
| [`generated/wave_calls.ll`](generated/wave_calls.ll) | Пример IR с вызовами `emu_*` |
| [`generated/wave_ir.ll`](generated/wave_ir.ll) | Пример полноценного вычислительного IR |

## Сборка

Нужны C++17, Clang, LLVM с поддержкой MCJIT и `make`. Проверено на Linux с
LLVM 19 (доступной динамической библиотекой `libLLVM.so.19.1`).
На macOS используйте Homebrew LLVM, добавив `$(brew --prefix llvm)/bin`
в `PATH`. Для графической сборки отдельно требуется SDL2.

Из корня проекта:

```sh
make asm4             # собрать ASM2IR и оригинальный C-бенчмарк
make asm4-test        # сравнить 1 кадр в трех режимах с C-программой
make asm4-emit        # сгенерировать два читаемых .ll
FRAMES=20 make asm4-test
```

Или из папки `asm2ir`:

```sh
make
./asm2ir --mode sim --frames 10
./asm2ir --mode calls --frames 10 --emit generated/wave_calls.ll
./asm2ir --mode ir --frames 10 --emit generated/wave_ir.ll
make test
FRAMES=20 make test
```

Команда `--emit-only` создаёт LLVM IR без исполнения:

```sh
./asm2ir --mode calls --emit generated/wave_calls.ll --emit-only
./asm2ir --mode ir --emit generated/wave_ir.ll --emit-only
```

Дополнительно можно заменить ASM:

```sh
./asm2ir --asm tests/isa_smoke.s --mode ir --frames 1
```

## Графический запуск

Для окна SDL2 (при наличии `SDL2` development libraries):

```sh
make asm4-sdl
cd asm2ir
./asm2ir-sdl --mode ir
# либо --mode calls / --mode sim
```

Все режимы используют тот же интерфейс `sim.h`, что исходная программа.
Для тестирования окно не требуется, используется headless backend.

## Проверка

При `FRAMES=20 make test` все четыре запуска (оригинальный C + три режима)
показали один результат:

```text
frames=20 pixels=1521207 fnv64=ee84759a26cfa9d6
```

Это контроль, полученный на Linux + Clang. На другой платформе последовательность
`rand()` может отличаться, но результаты четырёх реализаций должны совпадать
**между собой**.
