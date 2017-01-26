#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
#pragma omp critical
	{
   printf("Bonjour, thread %d!\n", omp_get_thread_num());
// #pragma omp barrier
   printf("Au revoir, thread %d!\n", omp_get_thread_num());
	}

  return 0;
}
