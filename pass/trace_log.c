// Рантайм для UseTracePass: принимает записи "User <- Operand" и
//  1) пишет начало трассы в текстовый файл <TRACE_OUT>_trace.txt;
//  2) на лету считает частоты паттернов - последовательностей из
//     1..5 подряд идущих записей трассы (скользящее окно);
//  3) по достижении TRACE_LIMIT записей или при exit() сохраняет
//     все счётчики в <TRACE_OUT>_ngrams.csv.
// Полная трасса - сотни миллионов записей (гигабайты текста), поэтому
// паттерны считаются в памяти, а на диск идёт только её начало.
//
// Переменные окружения:
//   TRACE_OUT   префикс выходных файлов              (по умолчанию "trace")
//   TRACE_DUMP  сколько первых записей писать в файл (по умолчанию 200000)
//   TRACE_LIMIT сколько записей анализировать        (по умолчанию 300000000)

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WINDOW 5
#define ID_BITS 12 // до 4096 разных записей, 5 * 12 бит + номер окна < 64 бит
#define MAX_RECORDS (1 << ID_BITS)
#define PTR_TABLE_BITS 14
#define NGRAM_TABLE_BITS 21

static const char *recName[MAX_RECORDS];
static int recCount = 0;

static const char *ptrKey[1 << PTR_TABLE_BITS];
static int ptrId[1 << PTR_TABLE_BITS];

static uint64_t ngramKey[1 << NGRAM_TABLE_BITS];
static uint64_t ngramCnt[1 << NGRAM_TABLE_BITS];
static long ngramDistinct = 0;

static int window[MAX_WINDOW];
static int windowFill = 0;
static uint64_t total = 0;

static uint64_t dumpLimit, traceLimit;
static const char *outPrefix;
static FILE *traceFile = NULL;
static int initialized = 0, finished = 0;

static uint64_t hash64(uint64_t x) {
  x ^= x >> 33;
  x *= 0xff51afd7ed558ccdULL;
  x ^= x >> 33;
  return x;
}

// Записи - это глобальные строки модуля, поэтому одна запись = один указатель.
static int internRecord(const char *rec) {
  uint64_t mask = (1 << PTR_TABLE_BITS) - 1;
  uint64_t h = hash64((uint64_t)(uintptr_t)rec) & mask;
  while (ptrKey[h] && ptrKey[h] != rec)
    h = (h + 1) & mask;
  if (!ptrKey[h]) {
    if (recCount == MAX_RECORDS) {
      fprintf(stderr, "[trace] too many distinct records\n");
      exit(1);
    }
    ptrKey[h] = rec;
    ptrId[h] = recCount;
    recName[recCount++] = rec;
  }
  return ptrId[h];
}

static void countNgram(uint64_t key) {
  uint64_t mask = (1 << NGRAM_TABLE_BITS) - 1;
  uint64_t h = hash64(key) & mask;
  while (ngramKey[h] && ngramKey[h] != key)
    h = (h + 1) & mask;
  if (!ngramKey[h]) {
    if (++ngramDistinct > (long)(mask * 3 / 4)) {
      fprintf(stderr, "[trace] n-gram table is full\n");
      exit(1);
    }
    ngramKey[h] = key;
  }
  ngramCnt[h]++;
}

static void dumpStats(void) {
  if (!initialized || finished)
    return;
  finished = 1;
  if (traceFile)
    fclose(traceFile);

  char path[512];
  snprintf(path, sizeof path, "%s_ngrams.csv", outPrefix);
  FILE *f = fopen(path, "w");
  if (!f) {
    perror(path);
    return;
  }
  fprintf(f, "# total_records=%llu\n", (unsigned long long)total);
  fprintf(f, "n;count;pattern\n");
  for (uint64_t i = 0; i < (1u << NGRAM_TABLE_BITS); i++) {
    if (!ngramKey[i])
      continue;
    uint64_t key = ngramKey[i];
    int n = (int)(key >> (MAX_WINDOW * ID_BITS));
    fprintf(f, "%d;%llu;", n, (unsigned long long)ngramCnt[i]);
    for (int k = n - 1; k >= 0; k--) {
      int id = (int)((key >> (k * ID_BITS)) & (MAX_RECORDS - 1));
      fprintf(f, "%s%s", recName[id], k ? " | " : "\n");
    }
  }
  fclose(f);
  fprintf(stderr,
          "[trace] %llu records, %d distinct records, %ld distinct patterns "
          "-> %s\n",
          (unsigned long long)total, recCount, ngramDistinct, path);
}

static void init(void) {
  initialized = 1;
  const char *s = getenv("TRACE_OUT");
  outPrefix = s ? s : "trace";
  s = getenv("TRACE_DUMP");
  dumpLimit = s ? strtoull(s, NULL, 10) : 200000;
  s = getenv("TRACE_LIMIT");
  traceLimit = s ? strtoull(s, NULL, 10) : 300000000ULL;
  if (dumpLimit) {
    char path[512];
    snprintf(path, sizeof path, "%s_trace.txt", outPrefix);
    traceFile = fopen(path, "w");
  }
  atexit(dumpStats);
}

void traceUse(const char *rec) {
  if (finished)
    return;
  if (!initialized)
    init();

  if (traceFile && total < dumpLimit)
    fprintf(traceFile, "%s\n", rec);

  for (int i = MAX_WINDOW - 1; i > 0; i--)
    window[i] = window[i - 1];
  window[0] = internRecord(rec);
  if (windowFill < MAX_WINDOW)
    windowFill++;

  // Окно длины n - последние n записей в порядке выполнения.
  uint64_t ids = 0;
  for (int n = 1; n <= windowFill; n++) {
    ids |= (uint64_t)window[n - 1] << ((n - 1) * ID_BITS);
    countNgram(((uint64_t)n << (MAX_WINDOW * ID_BITS)) | ids);
  }

  if (++total >= traceLimit)
    dumpStats();
}
