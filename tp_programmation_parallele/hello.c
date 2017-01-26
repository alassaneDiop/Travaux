#include <stdio.h>
#include <omp.h>

int main() 
{
#pragma omp parallel
#pragma omp critical
	{
		printf("Bonjour, numero thread : %d !\n", omp_get_thread_num());
// #pragma omp barrier
		printf("Au revoir, numero thread : %d !\n", omp_get_thread_num());
	}

	return 0;
}
