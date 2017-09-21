
#include "compute.h"
#include "graphics.h"
#include "debug.h"
#include "ocl.h"

#include <stdbool.h>

unsigned version = 0;


int ti=0;





void first_touch_v1 (void);
void first_touch_v2 (void);

unsigned compute_v0 (unsigned nb_iter);
unsigned compute_tuile (unsigned nb_iter);
unsigned compute_opti (unsigned nb_iter);
unsigned compute_v1 (unsigned nb_iter);
unsigned compute_tuile_v1(unsigned nb_iter);
unsigned compute_opti_v1(unsigned nb_iter);
unsigned compute_v2 (unsigned nb_iter);
unsigned compute_opti_v2(unsigned nb_iter);
unsigned compute_v3 (unsigned nb_iter);
unsigned compute_opti_v3(unsigned nb_iter);

void_func_t first_touch [] = {
  NULL,
  NULL,
  NULL,
  first_touch_v1,
  first_touch_v1,
  first_touch_v1,
  first_touch_v2,
  first_touch_v2,
  NULL,
  NULL,
};

int_func_t compute [] = {
  compute_v0,
  compute_tuile,
  compute_opti,
  compute_v1,
  compute_tuile_v1,
  compute_opti_v1,
  compute_v2,
  compute_opti_v2,
  compute_v3,
  compute_opti_v3,
};

char *version_name [] = {
  "Séquentielle",
  "Séquentielle par tuiles",
  "Séquentielle optimisée",
  "OpenMP for de base",
  "OpenMP for par tuiles",
  "OpenMP for optimisée",
  "OpenMP task tuilée",
  "OpenMP task optimisée",
  "OpenCL de base",
  "OpenCL optimisée",
};

unsigned opencl_used [] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
};

///////////////////////////// Version séquentielle simple


unsigned compute_v0 (unsigned nb_iter)
{
  for (unsigned it = 1; it <= nb_iter; it ++) { //sert à l'acceleration
  	ti++;
	int count=0;

    for (int i = 1; i < DIM-1; i++)
    {
    	for (int j = 1; j < DIM-1; j++)
		{
			if (cur_img(i-1,j-1)!=0x0)count++;
			if (cur_img(i-1,j)!=0x0)count++;
			if (cur_img(i-1,j+1)!=0x0)count++;
			if (cur_img(i,j-1)!=0x0)count++;
			if (cur_img(i,j+1)!=0x0)count++;
			if (cur_img(i+1,j-1)!=0x0)count++;
			if (cur_img(i+1,j)!=0x0)count++;
			if (cur_img(i+1,j+1)!=0x0)count++;

/* Prof naime pas cette version
				for (int a=i-1;a<=i+1;a++)
					for(int b=j-1;b<=j+1;b++)
						if ( i != a || j != b )
							if(cur_img(a,b)!=0x0)
							 	count++;
*/

			//cas ou la cellule est vivante
			if (cur_img(i,j) != 0x0)
			{
				//printf("%d) a. vivante:  pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
				//si elle n a pas 2 ou 3 voisins la cellule meurt
				if (count == 2 || count == 3) next_img(i,j)=cur_img(i,j);
				else next_img(i,j)=0x0;
			}


			else
			{
				//cas ou la cellule est morte
				//printf("%d) b. morte : pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
				//si elle n a pas 3 voisins la cellule reste morte
				if (count ==3) next_img(i,j)=0xFFFF00FF;
				else next_img(i,j)=cur_img(i,j);
			}

		count=0;
		}
	}
     swap_images ();

}

  // retourne le nombre d'étapes nécessaires à la
  // stabilisation du calcul ou bien 0 si le calcul n'est pas
  // stabilisé au bout des nb_iter itérations
  return 0;
}

///////////////////////////////Version tuilée



unsigned compute_tuile (unsigned nb_iter)
{

    for (unsigned it = 1; it <= nb_iter; it ++) {

  	ti++;
	int count=0;


    for (int k = 1; k < DIM-GRAIN; k+=GRAIN)
    {
    	for (int l = 1; l < DIM-GRAIN; l+=GRAIN)
	{
		for (int i = k; i < k+GRAIN && i < DIM-1; i++)
		{
			for (int j = l; j < l+GRAIN && j < DIM-1; j++)
			{
				if (cur_img(i-1,j-1)!=0x0)count++;
				if (cur_img(i-1,j)!=0x0)count++;
				if (cur_img(i-1,j+1)!=0x0)count++;
				if (cur_img(i,j-1)!=0x0)count++;
				if (cur_img(i,j+1)!=0x0)count++;
				if (cur_img(i+1,j-1)!=0x0)count++;
				if (cur_img(i+1,j)!=0x0)count++;
				if (cur_img(i+1,j+1)!=0x0)count++;
				
				/*switch (count):
								case 2:
									next_img(i,j)=cur_img(i,j);
									break;
								case 3:
									next_img(i,j)=0xFFFF00FF;
									break;
								default:
									next_img(i,j)=0x0;
				*/


				//cas ou la cellule est vivante et on est pas au bord du tableau
				if (cur_img(i,j) != 0x0)
				{
					//printf("%d) a. vivante:  pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
					//si elle n a pas 2 ou 3 voisins la cellule meurt
					if (count == 2 || count == 3) next_img(i,j)=cur_img(i,j);
					else next_img(i,j)=0x0;
				}

				else
				{
					//cas ou la cellule est morte
					//printf("%d) b. morte : pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
					//si elle n a pas 3 voisins la cellule reste morte
					if (count ==3) next_img(i,j)=0xFFFF00FF;
					else next_img(i,j)=cur_img(i,j);
				}

				count=0;
			}
		}
        }

     }

swap_images ();
}
  // retourne le nombre d'étapes nécessaires à la
  // stabilisation du calcul ou bien 0 si le calcul n'est pas
  // stabilisé au bout des nb_iter itérations
  return 0;
}

/////////////////////////////Version optimisé


unsigned compute_opti(unsigned nb_iter)
{
	for (unsigned it = 1; it <= nb_iter; it ++)
	{
		int count=0;//compteur de voisin d'une cellule
		//int flag[4];
		int id_tuile=0;
		int var= (DIM-2)/GRAIN; 
		
		//parcourt de tuile
		for (int k = 1; k < DIM-GRAIN; k+=GRAIN)
		{
			for (int l = 1; l < DIM-GRAIN; l+=GRAIN)
			{
				//printf("Entree stagne[%d] = %d  a k=%d et l=%d \n",id_tuile,stagne[id_tuile],k,l);
				//La tuile stagne t elle?
				if (stagne[id_tuile]!=1)
				{
					
					stagne[id_tuile]=1;
					for (int i = k; i < k+GRAIN && i < DIM-1; i++)
					{
						for (int j = l; j < l+GRAIN && j < DIM-1; j++)
						{
							//calcul nbdevoisin
							if (cur_img(i-1,j-1)!=0x0)count++;
							if (cur_img(i-1,j)!=0x0)count++;
							if (cur_img(i-1,j+1)!=0x0)count++;
							if (cur_img(i,j-1)!=0x0)count++;
							if (cur_img(i,j+1)!=0x0)count++;
							if (cur_img(i+1,j-1)!=0x0)count++;
							if (cur_img(i+1,j)!=0x0)count++;
							if (cur_img(i+1,j+1)!=0x0)count++;
							
							//cas dune cellule vivante
							if (cur_img(i,j) != 0x0)
							{
								
								if (count == 2 || count == 3) next_img(i,j)=cur_img(i,j);
								else
								{
									next_img(i,j)=0x0;
									stagne[id_tuile]=0;
								}
							}	
							//cas dune cellule morte
							else
							{
								if (count == 3)
								{
									next_img(i,j)=0xFFFF00FF;
									stagne[id_tuile]=0;
								}
								else next_img(i,j)=cur_img(i,j);
							}
							
						}
					}
					
					
				}
				
				else //si la tuile stagne
				{
					if(id_tuile==0)
					{
						if(stagne[id_tuile+1]||stagne[id_tuile + var+1])
					
						for (int i = k; i < k+GRAIN && i < DIM-1; i++)
						{
							for (int j = l; j < l+GRAIN && j < DIM-1; j++)
							{
								next_img(i,j)=cur_img(i,j);//la tuile stagne
							
							}
						}
						
					}
					
					else if  (id_tuile < var )
					{
						if ((stagne[(k-1)*var+ l]) ||(stagne[(k*var +(l-1) )])
						{
							for (int i = k; i < k+GRAIN && i < DIM-1; i++)
							{
								for (int j = l; j < l+GRAIN && j < DIM-1; j++)
								{
									next_img(i,j)=cur_img(i,j);//la tuile stagne
							
								}
							}
						}
					}
					 
					
				}
				//printf("Sortie stagne[%d] = %d  a k=%d et l=%d \n",id_tuile,stagne[id_tuile],k,l);
				id_tuile++;
				
			}
		}
		swap_images();
	}

return 0;
}










/*

unsigned compute_opti (unsigned nb_iter)
{
  

  
  int id_tuile=0;


  for (unsigned it = 1; it <= nb_iter; it ++) {

  	ti++;
	int count=0;
	

  	for (int k = 1; k < DIM; k+=GRAIN)
  	{
    	for (int l = 1; l < DIM; l+=GRAIN)
    	{
    		//si egale 0 on entre dans la tuile
    	
      		if (paschanger[id_tuile]==0 )
      			{
        		
        		for (int i = k; i < k+GRAIN && i < DIM-1; i++)
          		{
            		for (int j = l; j < l+GRAIN && j < DIM-1; j++)
            		{
		
            		    for (int a=i-1;a<=i+1;a++)
            		    for(int b=j-1;b<=j+1;b++)
            		    if ( i != a || j != b )
            		    if(cur_img(a,b)!=0x0)
            		    count++;
            		    //cas ou la cellule est vivante
                		if (cur_img(i,j) != 0x0)
                		{
                		printf("%d) a. vivante:  pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
                		//si elle n a pas 2 ou 3 voisins la cellule meurt
                			if (count == 2 || count == 3)
                			{
                				next_img(i,j)=cur_img(i,j);
                				paschanger[id_tuile]=1;
                				
                				 
                			}
                	
                			else
                			{
                				next_img(i,j)=0x0;
                				paschanger[id_tuile]=0;
                			}
                		}
                		//cas ou la cellule est morte
                		else
                		{
                			printf("%d) b. morte : pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
                			//si elle n a pas 3 voisins la cellule reste morte
                			if (count ==3)
                			{
                				next_img(i,j)=0xFFFF00FF;
                				paschanger[id_tuile]=0;
                			}
                			else
                			{
                				next_img(i,j)=cur_img(i,j);
                				paschanger[id_tuile]=1;
                			}
                		
                		}
                		
                		count=0;
                	}//END FOR (j)
            	}//END FOR (i)
        	}//END IF 
        	//printf("etat tuile %d = %d \n",id_tuile,paschanger[id_tuile]);
        	id_tuile++;

      	}
    }

swap_images ();
printf("Etape suivante\n");
}




  return 0;
}

*/


///////////////////////////// Version OpenMP for de base

void first_touch_v1 ()
{
  int i,j ;

#pragma omp parallel for
  for(i=0; i<DIM ; i++) {
    for(j=0; j < DIM ; j += 512)
      next_img (i, j) = cur_img (i, j) = 0 ;
  }
}

// Renvoie le nombre d'itérations effectuées avant stabilisation, ou 0
unsigned compute_v1(unsigned nb_iter)
{
    for (unsigned it = 1; it <= nb_iter; it ++) {
    	ti++;
  	int count=0;
    #pragma omp parallel  for
      for (int i = 1; i < DIM-1; i++)
      {
      	for (int j = 1; j < DIM-1; j++)
  		{

        	/*for (int a=i-1;a<=i+1;a++)
  					for(int b=j-1;b<=j+1;b++)
  						if ( i != a || j != b )
  							if(cur_img(a,b)!=0x0)
  							 	count++;*/
  			if (cur_img(i-1,j-1)!=0x0)count++;
			if (cur_img(i-1,j)!=0x0)count++;
			if (cur_img(i-1,j+1)!=0x0)count++;
			if (cur_img(i,j-1)!=0x0)count++;
			if (cur_img(i,j+1)!=0x0)count++;
			if (cur_img(i+1,j-1)!=0x0)count++;
			if (cur_img(i+1,j)!=0x0)count++;
			if (cur_img(i+1,j+1)!=0x0)count++;

  			//cas ou la cellule est vivante
  			if (cur_img(i,j) != 0x0)
  			{
  				//printf("%d) a. vivante:  pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
  				//si elle n a pas 2 ou 3 voisins la cellule meurt
  				if (count == 2 || count == 3) next_img(i,j)=cur_img(i,j);
  				else next_img(i,j)=0x0;
  			}


  			else
  			{
  				//cas ou la cellule est morte
  				//printf("%d) b. morte : pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
  				//si elle n a pas 3 voisins la cellule reste morte
  				if (count ==3) next_img(i,j)=0xFFFF00FF;
  				else next_img(i,j)=cur_img(i,j);
  			}

  		count=0;
  		}
  	}
       swap_images ();
}

  return 0;
}
/////////////////////////////Version OpenMP for tuilée

unsigned compute_tuile_v1 (unsigned nb_iter)
{


  	//ti++;
	int count=0;

	#pragma omp parallel for collapse(2) 
    for (int k = 1; k < DIM; k+=GRAIN)
    {
      for (int l = 1; l < DIM; l+=GRAIN)
      {
        for (int i = k; i < k+GRAIN ; i++)
        {
          if (i < DIM-1)
          {
            for (int j = l; j < l+GRAIN; j++)
            {
              if (j < DIM-1)
              {
                if (cur_img(i-1,j-1)!=0x0)count++;
				if (cur_img(i-1,j)!=0x0)count++;
				if (cur_img(i-1,j+1)!=0x0)count++;
				if (cur_img(i,j-1)!=0x0)count++;
				if (cur_img(i,j+1)!=0x0)count++;
				if (cur_img(i+1,j-1)!=0x0)count++;
				if (cur_img(i+1,j)!=0x0)count++;
				if (cur_img(i+1,j+1)!=0x0)count++;
                //cas ou la cellule est vivante et on est pas au bord du tableau
                if (cur_img(i,j) != 0x0)
                {
                  //printf("%d) a. vivante:  pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
                  //si elle n a pas 2 ou 3 voisins la cellule meurt
                  if (count == 2 || count == 3) next_img(i,j)=cur_img(i,j);
                  else next_img(i,j)=0x0;
                }
                else
                {
                  //cas ou la cellule est morte
                  //printf("%d) b. morte : pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
                  //si elle n a pas 3 voisins la cellule reste morte
                  if (count ==3) next_img(i,j)=0xFFFF00FF;
                  else next_img(i,j)=cur_img(i,j);
                }
                count=0;
              }//END IF j
            }//END FOR j
          }//END IF i
        }//END FOR i
      }
    }


swap_images ();

  // retourne le nombre d'étapes nécessaires à la
  // stabilisation du calcul ou bien 0 si le calcul n'est pas
  // stabilisé au bout des nb_iter itérations

  return 0;
}








///////////////////////////// Version OpenMP optimisée
unsigned compute_opti_v1(unsigned nb_iter)
{
  return 0;
}

///////////////////////////Version OpenMP task tuilée

unsigned compute_v2 (unsigned nb_iter)
{
	for (unsigned it = 1; it <= nb_iter; it ++) {

  #pragma omp parallel
  {

    	//ti++;
  	int i,j,count=0;
  	#pragma omp single nowait

	
      for (int k = 1; k < DIM; k+=GRAIN)
      {
        for (int l = 1; l < DIM; l+=GRAIN)
        {
        #pragma omp task private(i,j,count)
          for ( i = k; i < k+GRAIN ; i++)
          {
            if (i < DIM-1)
            {
              for ( j = l; j < l+GRAIN; j++)
              {

                if (j < DIM-1)
                {
                 
                  {

                  	if (cur_img(i-1,j-1)!=0x0)count++;
					if (cur_img(i-1,j)!=0x0)count++;
					if (cur_img(i-1,j+1)!=0x0)count++;
					if (cur_img(i,j-1)!=0x0)count++;
					if (cur_img(i,j+1)!=0x0)count++;
					if (cur_img(i+1,j-1)!=0x0)count++;
					if (cur_img(i+1,j)!=0x0)count++;
					if (cur_img(i+1,j+1)!=0x0)count++;
                  	//cas ou la cellule est vivante et on est pas au bord du tableau
                 	if (cur_img(i,j) != 0x0)
                 	{
                 	   //printf("%d) a. vivante:  pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
                 	   //si elle n a pas 2 ou 3 voisins la cellule meurt
                 	   if (count == 2 || count == 3) next_img(i,j)=cur_img(i,j);
                  	  else next_img(i,j)=0x0;
                  	}
                  	else
                  	{
                   		//cas ou la cellule est morte
                  		//printf("%d) b. morte : pixel(%d,%d) voisins count :%d \n",ti,i,j,count);
                   		//si elle n a pas 3 voisins la cellule reste morte
                    	if (count ==3) next_img(i,j)=0xFFFF00FF;
                    	else next_img(i,j)=cur_img(i,j);
                  	}
                  	count=0;
              	  }
                }//END IF j
              }//END FOR j
            }//END IF i
          }//END FOR i
        }
      }

  }
  swap_images ();

}

  return 0;
}

///////////////////////////Version OpenMP task optimisée
void first_touch_v2 ()
{

}

// Renvoie le nombre d'itérations effectuées avant stabilisation, ou 0
unsigned compute_opti_v2(unsigned nb_iter)
{
  return 0; // on ne s'arrête jamais
}


///////////////////////////// Version OpenCL de base

// Renvoie le nombre d'itérations effectuées avant stabilisation, ou 0
unsigned compute_v3 (unsigned nb_iter)
{
  return ocl_compute (nb_iter);
}

/////////////////////////////Version OpenCL optimisé

unsigned compute_opti_v3(unsigned nb_iter)
{
  return ocl_compute(nb_iter);
}
