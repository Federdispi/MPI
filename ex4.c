#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])   {
    int rang,nb_proc,code,valeur,tag;

    MPI_Status statut;
    code = MPI_Init(&argc,&argv);
    code = MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code = MPI_Comm_rank(MPI_COMM_WORLD,&rang);

    int processus = 2;

    int val = 200;

    if (processus == rang) {
        MPI_Send(&val, 1, MPI_INT, (rang + 1) % nb_proc, tag, MPI_COMM_WORLD);
        MPI_Recv(&val, 1, MPI_INT, nb_proc - 1, tag, MPI_COMM_WORLD, &statut);
        printf("Le message a fait le tour de l'anneau\n");
    } else {
        int rang_proc = (rang + nb_proc - 1) % nb_proc;
        MPI_Recv(&val, 1, MPI_INT, rang_proc, tag, MPI_COMM_WORLD, &statut);
        printf("Processus %d a recu %d de %d\n", rang, val, rang_proc);
        MPI_Send(&val, 1, MPI_INT, (rang + 1) % nb_proc, tag, MPI_COMM_WORLD);
    }
    
    code = MPI_Finalize();
    exit(0);
}   