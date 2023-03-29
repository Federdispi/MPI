#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    int rang, nb_proc, code;
    MPI_Status statut;
    code = MPI_Init(&argc, &argv);
    code = MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);
    code = MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    int tab[10] = {0, 1, 3, 2, 6, 7, 5, 4, 9, 8};

    if (10 % nb_proc != 0) {
        printf("Le nombre de processus doit être un diviseur de 10\n");
        MPI_Finalize();
        return 0;
    }

    int local_size = 10 / nb_proc;
    MPI_Scatter(tab, local_size, MPI_INT, tab + rang * local_size, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum = 0;
    for (int i = 0; i < local_size; i++) {
        local_sum += tab[rang * local_size + i];
    }

    int global_sum;
    MPI_Allreduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("La somme est %d\n", global_sum);

    MPI_Finalize();
    return 0;
}