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
#define MT 3
#endif

#ifndef RANDSEED
#define RANDSEED 1
#endif
/* Measure the collective performance of multiple invocations */
#ifndef NREP
#define NREP 10
#endif

/* routine to measure performance of*/
void test1(double * a,int N)
;
/* macro for the value of routien parameter */
#ifndef SIZE
#define SIZE 510
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
  double* a;
  int N;
  double* a_buf;
  int a_size, a_rep;

  /* parameter initializations */
  srand(RANDSEED);
  N = SIZE;
  a_size=16*((15+(N*N+(1+N)))/16);
  a_rep=CacheSZ / a_size + 1;
  a_buf = (double*) calloc(a_size*a_rep, sizeof(double));
  #define DO_FLUSH 1
  __pt_flush_buffer = (double*) malloc(CacheSZ * sizeof(double));

  for(__pt_i0=0; __pt_i0 < CacheSZ; ++__pt_i0) {
    __pt_flush_buffer[__pt_i0] = ((__pt_i0 % 3) == 2) ? -1 : __pt_i0 % 2;
  }

  /* Multiple Timings */
  for (__pt_MT_ivar=0; __pt_MT_ivar<MT; ++__pt_MT_ivar) {
    srand(RANDSEED);
    for (__pt_i0=0; __pt_i0<a_size *a_rep; ++__pt_i0)
    {
      a_buf[__pt_i0] = rand();;
    }
    a = a_buf;
    /* code to flush the cache */
    __pt_flush_bufferVal = 0;
    for (__pt_i0=0; __pt_i0 < CacheSZ; ++__pt_i0)
      __pt_flush_bufferVal += __pt_flush_buffer[__pt_i0];
    assert(__pt_flush_bufferVal < 10);

    /* Timer start */
    __timer_begin = GetWallTime();
    /* Timing loop */
    for (__pt_NREP_ivar=0; __pt_NREP_ivar<NREP; ++__pt_NREP_ivar) {
      test1 (a,N);
      if (__pt_i0 < a_rep-1)
        a += a_size;
      else a = a_buf;
    }
    /* Timer end */
    __timer_end = GetWallTime();
    /* result of a single timing */
    __timer_diff[__pt_MT_ivar] = (__timer_end-__timer_begin)/NREP;
  }
  /* flops of computation */
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
  return(0);
}
