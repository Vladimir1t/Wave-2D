// Deterministic non-graphical sim.h backend. Same seed as pass/sim_headless.c,
// plus an order-sensitive 64-bit checksum of every simPutPixel call.
#include "../sim.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
static int frames=0,limit=1;
static uint64_t pixels=0;
static FILE *traceFile=NULL;
static FILE *randFile=NULL;
static uint64_t checksum=UINT64_C(14695981039346656037);
static void consume(uint32_t v) { checksum^=v;checksum*=UINT64_C(1099511628211); }
void simInit(void) {
  const char *s=getenv("SIM_FRAMES");
  if(s) limit=atoi(s);
  assert(limit>0);
  srand(12345);
  const char *trace=getenv("SIM_TRACE");
  if(trace) traceFile=fopen(trace,"wb");
  const char *rngTrace=getenv("SIM_RAND_TRACE");
  if(rngTrace) randFile=fopen(rngTrace,"wb");
}
void simExit(void) {}
void simFlush(void) {
  if(++frames==limit) {
    printf("frames=%d pixels=%" PRIu64 " fnv64=%016" PRIx64 "\n",frames,pixels,checksum);
    fflush(stdout);
    exit(0);
  }
}
void simPutPixel(int x,int y,int argb) {
  assert(x>=0 && x<SIM_X_SIZE && y>=0 && y<SIM_Y_SIZE);
  consume((uint32_t)x);consume((uint32_t)y);consume((uint32_t)argb);
  if(traceFile) {int32_t t[3]={x,y,argb}; fwrite(t,sizeof(int32_t),3,traceFile);}
  ++pixels;
}
int simRand(void) {int r=rand();if(randFile) fprintf(randFile,"%d\n",r);return r;}
int simHasClick(void) {return 0;}
int simGetClick(void) {return 0;}
