#include <stdio.h>
#include <omp.h>

// version 1
void version1 (int t[], int N) {

	int sum = 0;
#pragma omp parallel
	for(int i = 0; i < N; i++)
		sum+=t[i];

	printf("version 1: somme = %d\n", sum);
}


// Version 2

void version2 (int t[], int N) {
	int sum = 0;
	int i = 0;

#pragma omp parallel
	{
		int mon_i;
		int ma_somme = 0;
		for(;;)
		{
#pragma omp critical
			mon_i = i++ ;
			
			if (mon_i > N)
				break;
			
			ma_somme += t[i];
		}

#pragma omp critical
	sum += ma_somme ;
	}

	printf("version 2: somme = %d\n", sum);
}

// Version 3 où on utilise le nombre de threads engagés via un appel à omp_get_num_thread()
void version3 (int t[], int N) {
	int sum = 0;

#pragma omp parallel
	{
		int mon_i;
		int ma_somme = 0;
		int nb_threads = omp_get_num_threads();

		for(mon_i = omp_get_thread_num(); mon_i < N ; mon_i += nb_threads)
			ma_somme += t[mon_i];

#pragma omp critical
		sum += ma_somme ;
	}

	printf("version 3: somme = %d\n", sum);
}

int main() {
	int tab[] = {1, 2 ,3, 4, 5};
	version1(tab, 5);
	version2(tab, 5);
	version3(tab, 5);

	return 0;
}
