
#include "compute.h"
#include "graphics.h"
#include "debug.h"
#include "ocl.h"

#define DEFAULT_NUM_THREADS 4

unsigned version = 0;

void first_touch_omp (void);

int compute_v0 (void);
int compute_v1 (void);
int compute_v2 (void);

void_func_t first_touch [] = {
  NULL,
  first_touch_omp,
  NULL
};

int_func_t compute [] = {
  compute_v0,
  compute_v1,
  compute_v2
};

char *version_name [] = {
  "Séquentielle",
  "OpenMP",
  "OpenCL"
};

unsigned opencl_used [] = {
  0,
  0,
  1
};

///////////////////////////// Version séquentielle simple


int compute_v0 (void)
{
  // Transposée
  for (int i = 0; i < DIM; i++)
    for (int j = 0; j < DIM; j++)
      next_img (i, j) = cur_img (j, i);

  swap_images ();
  
  return 1; // on ne s'arrête jamais
}

///////////////////////////// Version OpenMP avec omp for

void first_touch_omp ()
{
  int i,j ;

#pragma omp parallel for
  for(i=0; i<DIM ; i++) {
    for(j=0; j < DIM ; j += 512)
      cur_img (i, j) = 0 ;
  }
}

int compute_v1 (void)
{
  // Transposée
  #pragma omp parallel for
  for (int i = 0; i < DIM; i++)
    for (int j = 0; j < DIM; j++)
      next_img (i, j) = cur_img (j, i);

  swap_images ();
  
  return 1; // on ne s'arrête jamais
}


///////////////////////////// Version OpenCL

int compute_v2 (void)
{
  ocl_compute ();

  return 1;
}
