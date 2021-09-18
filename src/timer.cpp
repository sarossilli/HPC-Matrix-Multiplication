#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef CS
#define CS 1000
#endif
#define CacheSZ CS*1024/sizeof(double)


#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
double GetWallTime(void)
   {
      struct timeval tp;
      static long start=0, startu;
      if (!start)
      {
         gettimeofday(&tp, NULL);
         start = tp.tv_sec;
         startu = tp.tv_usec;
         return(0.0);
      }
      gettimeofday(&tp, NULL);
      return( ((double) (tp.tv_sec - start)) + (tp.tv_usec-startu)/1000000.0 );
   }

/* Collect multiple timing samples */
#ifndef MT
#define MT 10
#endif

#ifndef RANDSEED
#define RANDSEED 1
#endif
/* Measure the collective performance of multiple invocations */
#ifndef NREP
#define NREP 30
#endif

/* routine to measure performance of*/
float test1(float*, float*,int );
/* macro for the value of routien parameter */
#ifndef SIZE1
#define SIZE1 150
#endif
/* macro for the value of routien parameter */
#ifndef SIZE2
#define SIZE2 20
#endif

int main(int argc, char **argv)
{

  /* arrays for storing results of multiple timings */
  double __timer_diff[MT];

  /* induction variable for Multiple timing */
  int __pt_MT_ivar;

  double __timer_min,__timer_avg,__timer_max;

  /* induction variable for multiple invocations in a single timing */
  int __pt_NREP_ivar;

  /* variables to support cache flushing */
  double* __pt_flush_buffer;
  double __pt_flush_bufferVal;

  /* variable for computing MFLOPS */
  double __pt_flops;

  /* induction variables */
  int __pt_i0, __pt_i1, __pt_i2;

  /*variables to store starting and ending of timing */
  double __timer_begin, __timer_end;

  /* Declaring parameters of the routine */
  float* A;
  float* B;
  int n;
  int t;
  float __pt_return;
  float* A_buf;
  int A_size, A_rep;
  float* B_buf;
  int B_size, B_rep;

  /* parameter initializations */
  srand(RANDSEED);
  t = SIZE1;
  n = t;
  A_size=16*((15+n)/16);
  A_rep=CacheSZ / A_size + 1;
  A_buf = (float*) calloc(A_size*A_rep, sizeof(float));
  B_size=16*((15+n)/16);
  B_rep=CacheSZ / B_size + 1;
  B_buf = (float*) calloc(B_size*B_rep, sizeof(float));
  #define DO_FLUSH 1
  __pt_flush_buffer = (double*) malloc(CacheSZ * sizeof(double));

  for(__pt_i0=0; __pt_i0 < CacheSZ; ++__pt_i0) {
    __pt_flush_buffer[__pt_i0] = ((__pt_i0 % 3) == 2) ? -1 : __pt_i0 % 2;
  }

  /* Multiple Timings */
  for (__pt_MT_ivar=0; __pt_MT_ivar<MT; ++__pt_MT_ivar) {
    srand(RANDSEED);
    for (__pt_i0=0; __pt_i0<A_size *A_rep; ++__pt_i0)
    {
      A_buf[__pt_i0] = rand();;
    }
    A = A_buf;
    for (__pt_i0=0; __pt_i0<B_size *B_rep; ++__pt_i0)
    {
      B_buf[__pt_i0] = rand();;
    }
    B = B_buf;
    /* code to flush the cache */
    __pt_flush_bufferVal = 0;
    for (__pt_i0=0; __pt_i0 < CacheSZ; ++__pt_i0)
      __pt_flush_bufferVal += __pt_flush_buffer[__pt_i0];
    assert(__pt_flush_bufferVal < 10);

    /* Timer start */
    __timer_begin = GetWallTime();
    /* Timing loop */
    for (__pt_NREP_ivar=0; __pt_NREP_ivar<NREP; ++__pt_NREP_ivar) {
      __pt_return= test1(A,B,n);
      if (__pt_i0 < A_rep-1)
        A += A_size;
      else A = A_buf;
      if (__pt_i0 < B_rep-1)
        B += B_size;
      else B = B_buf;
    }
    /* Timer end */
    __timer_end = GetWallTime();
    /* result of a single timing */
    __timer_diff[__pt_MT_ivar] = (__timer_end-__timer_begin)/NREP;
  }
  /* flops of computation */
  __pt_flops = 2*n*n*n;

  /* Compute minimum of multiple timings */
  __timer_min=__timer_diff[0];
  __timer_max=__timer_diff[0];
  __timer_avg=__timer_diff[0];
  for (__pt_MT_ivar=1; __pt_MT_ivar<MT; ++__pt_MT_ivar)
  {
    if (__timer_min > __timer_diff[__pt_MT_ivar])
        __timer_min = __timer_diff[__pt_MT_ivar];
    if (__timer_max < __timer_diff[__pt_MT_ivar])
        __timer_max = __timer_diff[__pt_MT_ivar];
    __timer_avg += __timer_diff[__pt_MT_ivar];
  }
  __timer_avg /= MT;


  /* output timing results */
  for (__pt_MT_ivar=0; __pt_MT_ivar < MT; ++__pt_MT_ivar)
  {
    printf("time in seconds [%d]:  %.15f\n", __pt_MT_ivar, __timer_diff[__pt_MT_ivar]);

  }
  printf("Minimum time in seconds:  %.15f\n", __timer_min);
  printf("Maximum time in seconds:  %.15f\n", __timer_max);
  printf("Average time in seconds:  %.15f\n", __timer_avg);
  printf("Maximum MFLOPS: %.15f\n", __pt_flops/__timer_min/1000000);
  printf("Minimum MFLOPS: %.15f\n", __pt_flops/__timer_max/1000000);
  printf("Average MFLOPS: %.15f\n", __pt_flops/__timer_avg/1000000);
  printf("Configuration\n"
         "-------------\n");
  printf("Cache Size: %d\n", CS);
  #ifdef DO_FLUSH
  printf("Cache Flush Method: generic\n");
  #else
  printf("Cache Flush Method: none\n");
  #endif
  printf("ARCH: generic\n");
  printf("nrep: %d\n", NREP);
  printf("mt: %d\n", MT);
  printf("Random Seed: %d\n", RANDSEED);
  return(0);
}
