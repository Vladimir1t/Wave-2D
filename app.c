// Двумерное волновое уравнение: "бассейн" с островами, дождём и
// пульсирующим источником, который движется по эллипсу (эффект Доплера).

#include "sim.h"

#define SCALE 3                  // размер клетки сетки в пикселях
#define W (SIM_X_SIZE / SCALE)   // ширина сетки
#define H (SIM_Y_SIZE / SCALE)   // высота сетки
#define N (W * H)

#define STEPS_PER_FRAME 2        // шагов по времени на один кадр
#define DAMP_SHIFT 6             // затухание: h -= h >> DAMP_SHIFT

#define RAIN_CHANCE 4            // капля в среднем раз в RAIN_CHANCE кадров
#define RAIN_RADIUS 4
#define RAIN_POWER 2000

#define SRC_RADIUS 2             // пульсирующий движущийся источник
#define SRC_POWER 500
#define SRC_HALF_PERIOD 5        // полупериод пульсации, в шагах
#define ORBIT_RX 150             // полуоси эллипса-траектории, в клетках
#define ORBIT_RY 80
#define ORBIT_SHIFT 8            // угловой шаг 1/256 рад за шаг
#define FIX_ONE 65536            // единица в fixed-point 16.16

#define LAND_COLOR 0xFFC8A96E    // песок: борта бассейна и острова
#define BOAT_COLOR 0xFFFF5040    // метка источника
#define WATER_MASK -1            // значения в маске water[]
#define LAND_MASK 0

int clamp255(int v) {
  if (v < 0)
    return 0;
  if (v > 255)
    return 255;
  return v;
}

int isInsideCircle(int x, int y, int cx, int cy, int r) {
  int dx = x - cx;
  int dy = y - cy;
  return dx * dx + dy * dy < r * r;
}

// Маска: -1 - вода, 0 - суша (рамка по краю и три острова).
void initPool(int *water) {
  for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++) {
      int land = x == 0 || y == 0 || x == W - 1 || y == H - 1;
      land |= isInsideCircle(x, y, W / 2, H / 2, 34);
      land |= isInsideCircle(x, y, 60, 55, 22);
      land |= isInsideCircle(x, y, W - 70, H - 55, 18);
      water[y * W + x] = land ? LAND_MASK : WATER_MASK;
    }
}

// Возмущение - "капля" с параболическим профилем.
void addDrop(int *h, int cx, int cy, int r, int power) {
  for (int dy = -r; dy <= r; dy++)
    for (int dx = -r; dx <= r; dx++) {
      int x = cx + dx;
      int y = cy + dy;
      int d2 = dx * dx + dy * dy;
      if (x > 0 && x < W - 1 && y > 0 && y < H - 1 && d2 < r * r)
        h[y * W + x] += power * (r * r - d2) / (r * r);
    }
}

// Один шаг схемы: next = (сумма 4 соседей)/2 - prev, с затуханием.
// Результат пишется поверх prev (он становится новым слоем).
void waveStep(int *cur, int *prev, int *water) {
  for (int y = 1; y < H - 1; y++)
    for (int x = 1; x < W - 1; x++) {
      int i = y * W + x;
      int v = ((cur[i - 1] + cur[i + 1] + cur[i - W] + cur[i + W]) >> 1) -
              prev[i];
      v -= v >> DAMP_SHIFT;
      prev[i] = v & water[i];
    }
}

// Цвет воды: освещение сверху-слева по наклону поверхности + высота.
int waterColor(int *h, int i) {

  int slope = (h[i - 1] - h[i + 1]) + (h[i - W] - h[i + W]);
  int s = clamp255(90 + (slope >> 2) + (h[i] >> 4));
  int r = (s * s * s) >> 16;
  int g = clamp255(30 + ((s * s) >> 8));
  int b = clamp255(80 + s);

  return 0xFF000000 | (r << 16) | (g << 8) | b;
}

void putCell(int x, int y, int argb) {
  for (int dy = 0; dy < SCALE; dy++)
    for (int dx = 0; dx < SCALE; dx++)
      simPutPixel(x * SCALE + dx, y * SCALE + dy, argb);
}

// Перерисовываются только клетки, цвет которых изменился с прошлого кадра.
void drawFrame(int *h, int *water, int *shown, int bx, int by) {

  for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++) {

      int i = y * W + x;
      int color = water[i] ? waterColor(h, i) : LAND_COLOR;

      if (isInsideCircle(x, y, bx, by, 2))
        color = BOAT_COLOR;

      if (color != shown[i]) {
        shown[i] = color;
        putCell(x, y, color);
      }
    }
}

void app(void) {

  int bufA[N] = {0};
  int bufB[N] = {0};
  int water[N] = {0};
  int shown[N] = {0};
  int *cur = bufA;
  int *prev = bufB;

  initPool(water);

  int ox = FIX_ONE;
  // точка на единичной окружности (алгоритм Минского)
  int oy = 0;
  int bx = W / 2 + ORBIT_RX;
  int by = H / 2;
  int step = 0;

  while (1) {

    for (int s = 0; s < STEPS_PER_FRAME; s++) {
      bx = W / 2 + ox * ORBIT_RX / FIX_ONE;
      by = H / 2 + oy * ORBIT_RY / FIX_ONE;
      int sign = ((step / SRC_HALF_PERIOD) & 1) * 2 - 1;
      addDrop(cur, bx, by, SRC_RADIUS, sign * SRC_POWER);

      waveStep(cur, prev, water);
      int *tmp = cur;
      cur = prev;
      prev = tmp;

      ox -= oy >> ORBIT_SHIFT;
      oy += ox >> ORBIT_SHIFT;
      step++;
    }

    if (simRand() % RAIN_CHANCE == 0)
      addDrop(cur, 1 + simRand() % (W - 2), 1 + simRand() % (H - 2),
              RAIN_RADIUS, RAIN_POWER);
    drawFrame(cur, water, shown, bx, by);
    simFlush();
  }
}
