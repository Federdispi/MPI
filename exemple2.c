#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rang, nb_proc, code, valeur, tag, i;
    MPI_Status statut;
    code = MPI_Init(&argc, &argv);
    code = MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
    code = MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    tag = 100;
    valeur = 1000;
    if(rang == 0) {
        MPI_Send(&valeur, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
        printf("Processus %d envoie %d au processus 1 \n", rang, valeur);
    } else if (rang == 1) {
        MPI_Recv(&valeur, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &statut);
        printf("Processus %d recoit %d du processus 0 \n", rang, valeur);
    }
    code = MPI_Finalize();
    return 0;
}