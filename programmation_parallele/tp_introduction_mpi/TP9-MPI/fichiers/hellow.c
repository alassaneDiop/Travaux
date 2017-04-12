/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#include <stdio.h>
#include "mpi.h"

int main( int argc, char *argv[] )
{
    int rank;
    int size;
    
    /* initialiser MPI, à faire _toujours_ en tout premier du programme */
    MPI_Init(&argc,&argv);
 

    /* récupérer son propre numéro */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
        /* récupérer le nombre de processus lancés */
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
 
 // modif
 	char buf[1];
 	MPI_Status status;

	if (rank == 0) {
		buf[0] = 'A';
 		MPI_Send(buf, 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
	} else {
	 	MPI_Recv(buf, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		printf("j'ai recu %c\n", buf[0]);
	}
 // fin modif   
   
    printf( "Hello world from process %d of %d from %s\n", rank, size,processor_name );
    MPI_Finalize();
    return 0;
}
