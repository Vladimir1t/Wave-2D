// Безоконная реализация sim.h для воспроизводимого сбора трассы:
// фиксированный seed для simRand, пиксели никуда не выводятся,
// программа завершается через SIM_FRAMES кадров (по умолчанию 10),
// после чего atexit-обработчик логгера сохраняет статистику.
// Логика app.c исполняется ровно та же, что и с SDL-окном.

#include "../sim.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int frame = 0;
static int frameLimit = 10;

void simInit() {
  const char *s = getenv("SIM_FRAMES");
  if (s)
    frameLimit = atoi(s);
  srand(12345);
}

void simExit() {}

void simFlush() {
  if (++frame >= frameLimit) {
    fprintf(stderr, "[sim] %d frames done\n", frame);
    exit(0);
  }
}

void simPutPixel(int x, int y, int argb) {
  (void)argb;
  assert(0 <= x && x < SIM_X_SIZE && "Out of range");
  assert(0 <= y && y < SIM_Y_SIZE && "Out of range");
}

int simRand() { return rand(); }
int simHasClick() { return 0; }
int simGetClick() { return 0; }
