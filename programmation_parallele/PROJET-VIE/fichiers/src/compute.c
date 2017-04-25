
#include "compute.h"
#include "graphics.h"
#include "debug.h"
#include "ocl.h"

#include <stdbool.h>

unsigned version = 0;

void first_touch_v1 (void);
void first_touch_v2 (void);

unsigned compute_v0 (unsigned nb_iter);
unsigned compute_v1 (unsigned nb_iter);
unsigned compute_v2 (unsigned nb_iter);
unsigned compute_v3 (unsigned nb_iter);

void_func_t first_touch [] = {
  NULL,
  first_touch_v1,
  first_touch_v2,
  NULL,
};

int_func_t compute [] = {
  compute_v0,
  compute_v1,
  compute_v2,
  compute_v3,
};

char *version_name [] = {
  "Séquentielle",
  "OpenMP",
  "OpenMP zone",
  "OpenCL",
};

unsigned opencl_used [] = {
  0,
  0,
  0,
  1,
};

///////////////////////////// Version séquentielle simple


/* unsigned compute_v0 (unsigned nb_iter) */
/* {  */
/* 	int	ti = 0; */
/* 	int count=0; */
/*     for (int i = 1; i < DIM-1; i++) */
/*     { */
/*     	for (int j = 1; j < DIM-1; j++) */
/* 		{ */
/* 	 */
/* 		 */
/* 			//cas ou la cellule est vivante */
/* 			if (cur_img(i,j)) */
/* 			{ */
/* 				for (int a=i-1;a<=i+1;a++) */
/* 				{ */
/* 					for(int b=j-1;b<=j+1;b++) if ((i!=a || j!=b) && (cur_img(a,b)==0xFFFF00FF)) count++; */
/* 				} */
/* 				#<{(| printf("%d) a. vivante:  pixel(%d,%d) voisins count :%d \n",ti,i,j,count); |)}># */
/* 				//si elle n a pas 2 ou 3 voisins la cellule meurt */
/* 				if (count == 2 || count == 3) next_img(i,j)=0xFFFF00FF; */
/* 				else next_img(i,j)=0x0; */
/* 			} */
/* 			 */
/* 	 */
/* 			else */
/* 			{ */
/* 				//cas ou la cellule est morte */
/* 				for (int a=i-1;a<=i+1;a++) */
/* 				{ */
/* 					for(int b=j-1;b<=j+1;b++) */
/* 					{ */
/* 						if ((i!=a && j!=b) && (cur_img(a,b)!=0x0)) count++; */
/* 					} */
/* 				} */
/* 				#<{(| printf("%d) b. morte : pixel(%d,%d) voisins count :%d \n",ti,i,j,count); |)}># */
/* 				//si elle n a pas 3 voisins la cellule reste morte */
/* 				if (count ==3) next_img(i,j)=0xFFFF00FF; */
/* 				else next_img(i,j)=cur_img(i,j); */
/* 			} */
/* 		 */
/* 		count=0; */
/* 		} */
/* 	} */
/*      swap_images (); */
/*       */
/*       */
/*    */
/*   // retourne le nombre d'étapes nécessaires à la */
/*   // stabilisation du calcul ou bien 0 si le calcul n'est pas */
/*   // stabilisé au bout des nb_iter itérations */
/*   return 0; */
/* } */



unsigned compute_v0 (unsigned nb_iter)
{
	int count=0;

    for (int i = 1; i < DIM-1; i++)
    {
    	for (int j = 1; j < DIM-1; j++)
		{
			for (int a=i-1;a<=i+1;a++)
				for(int b=j-1;b<=j+1;b++) 
					if ( i != a || j != b ) 
						if(cur_img(a,b)!=0x0) 
							count++;
			
			if (cur_img(i,j) != 0x0) { //cas ou la cellule est vivante
				
				//si elle n a pas 2 ou 3 voisins la cellule meurt
				if (count == 2 || count == 3)
					next_img(i,j)=cur_img(i,j);
				else
					next_img(i,j)=0x0;

			} else { //cas ou la cellule est morte

				//si elle n a pas 3 voisins la cellule reste morte
				if (count ==3)
					next_img(i,j)=0xFFFF00FF;
				else
					next_img(i,j)=cur_img(i,j);
			}
		
			count=0;
		}
	}
     swap_images ();






/*  for (unsigned it = 1; it <= nb_iter; it ++) { */
/*     for (int i = 0; i < DIM; i++) */
/*       for (int j = 0; j < DIM; j++) { */
/* //	next_img (i, j) = cur_img (j, i); */
/*  */
/* 	      if ((i>0 && i<DIM-2) && (j>0 && j<DIM-2)) { //test pour ne pas prendre les bords du tableau */
/*  */
/* 		      // rendre une cellule morte vivante */
/* 		      if ((cur_img(i, j) & 0xFF) == 0) { */
/* 				      printf("cellule morte\n"); */
/* 		      } */
/*  */
/* 		      //rendre une cellule vivante morte */
/* 		      else#<{(| (cur_img(i, j) == 0xFFFF00FF)|)}># { */
/* 				      printf("cellule vivante \n"); */
/* 		      } */
/* 	      } */
/*       } */
/*  */
/*  */
/*     swap_images (); */
/*   } */


/*   for (unsigned it = 1; it <= nb_iter; it ++) { */
/*     for (int i = 0; i < DIM; i++) */
/*       for (int j = 0; j < DIM; j++) { */
/* //	next_img (i, j) = cur_img (j, i); */
/*  */
/* 	      if ((i>0 && i<DIM-2) && (j>0 && j<DIM-2)) { //test pour ne pas prendre les bords du tableau */
/*  */
/* 		      // rendre une cellule morte vivante */
/* 		      if ((cur_img(i, j) & 0xFF) == 0) { */
/* 			      int control_sum = 0; */
/* 			      control_sum += cur_img(i-1, j-1) + cur_img(i-1, j) + cur_img(i-1, j+1) + */
/* 			      		     cur_img(i, j-1) + cur_img(i, j+1) + */
/* 			      		     cur_img(i+1, j-1) + cur_img(i+1, j) + cur_img(i+1, j+1) ; */
/*  */
/* 			      if (control_sum == 3) { // la cellule devient VIVANTE */
/* 					  cur_img(i, j) = 0xFFFF00FF|0xFF; */
/* 					  printf("cellule morte à rendre vivante\n"); */
/* 					  next_img (i, j) = cur_img (j, i); */
/* 			      } */
/* 		      } */
/*  */
/* 		      //rendre une cellule vivante morte */
/* 		      else #<{(|(cur_img(i, j) == 0xFFFF00FF)|)}># {	 */
/* 			      int control_sum = 0; */
/* 			      control_sum += cur_img(i-1, j-1) + cur_img(i-1, j) + cur_img(i-1, j+1) + */
/* 			      		     cur_img(i+1, j-1) + cur_img(i+1, j) + cur_img(i+1, j+1) + */
/* 			      		     cur_img(i, j-1) + cur_img(i, j+1) ; */
/*  */
/* 			      if (control_sum != 2 && control_sum != 3) { // la cellule devient MORTE */
/* 				      cur_img(i, j) = 0; */
/* 				      printf("cellule vivante à rendre morte \n"); */
/* 					  next_img (i, j) = cur_img (j, i); */
/* 			      } */
/*  */
/*  */
/*  */
/* 		      } */
/* 	      } */
/*       } */
/*  */
/*  */
/*     swap_images (); */
/*   } */
/*  */
/*   for (unsigned it = 1; it <= nb_iter; it ++) { */
/*     for (int i = 0; i < DIM; i++) */
/*       for (int j = 0; j < DIM; j++) { */
/* //	next_img (i, j) = cur_img (j, i); */
/*  */
/* 	      if ((i>0 && i<DIM-2) && (j>0 && j<DIM-2)) { //test pour ne pas prendre les bords du tableau */
/*  */
/* 		      // rendre une cellule morte vivante */
/* 		      if ((cur_img(i, j) & 0xFF) == 0) { */
/* 				      printf("cellule morte\n"); */
/* 		      } */
/*  */
/* 		      //rendre une cellule vivante morte */
/* //		      if (cur_img(i, j) == 0xFFFF00FF) {	 */
/* 		      else { */
/* 				      printf("cellule vivante \n"); */
/* 		      } */
/* 	      } */
/*       } */
/*  */
/*  */
/*     swap_images (); */
/*   } */

  // retourne le nombre d'étapes nécessaires à la
  // stabilisation du calcul ou bien 0 si le calcul n'est pas
  // stabilisé au bout des nb_iter itérations
  return 0;
}


///////////////////////////// Version OpenMP de base

void first_touch_v1 ()
{
  int i,j;

#pragma omp parallel for
  for(i=0; i<DIM ; i++) {
    for(j=0; j < DIM ; j += 512)
      next_img (i, j) = cur_img (i, j) = 0 ;
  }


/* 	int count=0; */
/*  */
/* #pragma omp parallel for */
/* 	for (int i = 1; i < DIM-1; i++) */
/*     { */
/*     	for (int j = 1; j < DIM-1; j+=512) */
/* 		{ */
/* 			for (int a=i-1;a<=i+1;a++) */
/* 				for(int b=j-1;b<=j+1;b++)  */
/* 					if ( i != a || j != b )  */
/* 						if(cur_img(a,b)!=0x0) */
/* #<{(| #pragma omp critical |)}># */
/* 							count++; */
/* 			 */
/* 			if (cur_img(i,j) != 0x0) { //cas ou la cellule est vivante */
/* 				 */
/* 				//si elle n a pas 2 ou 3 voisins la cellule meurt */
/* 				if (count == 2 || count == 3) */
/* #<{(| #pragma omp critical |)}># */
/* 					next_img(i,j)=cur_img(i,j); */
/* 				else */
/* #pragma omp critical */
/* 					next_img(i,j)=0x0; */
/*  */
/* 			} else { //cas ou la cellule est morte */
/*  */
/* 				//si elle n a pas 3 voisins la cellule reste morte */
/* 				if (count ==3) */
/* #pragma omp critical */
/* 					next_img(i,j)=0xFFFF00FF; */
/* 				else */
/* #pragma omp critical */
/* 					next_img(i,j)=cur_img(i,j); */
/* 			} */
/* 		 */
/* #pragma omp critical */
/* 			count=0; */
/* 		} */
/* 	} */
/*      swap_images (); */
}

// Renvoie le nombre d'itérations effectuées avant stabilisation, ou 0
unsigned compute_v1(unsigned nb_iter)
{
  return 0;
}



///////////////////////////// Version OpenMP optimisée

void first_touch_v2 ()
{

}

// Renvoie le nombre d'itérations effectuées avant stabilisation, ou 0
unsigned compute_v2(unsigned nb_iter)
{
  return 0; // on ne s'arrête jamais
}


///////////////////////////// Version OpenCL

// Renvoie le nombre d'itérations effectuées avant stabilisation, ou 0
unsigned compute_v3 (unsigned nb_iter)
{
  return ocl_compute (nb_iter);
}
