#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])   {
    int rang,nb_proc,code,valeur,tag;

    MPI_Status statut;
    code = MPI_Init(&argc,&argv);
    code = MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code = MPI_Comm_rank(MPI_COMM_WORLD,&rang);

    int tab[8] = {0, 1, 3, 2, 6, 7, 5, 4};
    int val = 100;

    if (rang == tab[0]) {
        MPI_Send(&val, 1, MPI_INT, tab[1], tag, MPI_COMM_WORLD);
        MPI_Recv(&val, 1, MPI_INT, tab[nb_proc - 1], tag, MPI_COMM_WORLD, &statut);
        printf("Le message a fait le tour de l'anneau\n");
    } else {
        int index;
        for (int i = 0; i < nb_proc; i++)
        {
            if (tab[i] == rang)
                index = i;
        }
        
        MPI_Recv(&val, 1, MPI_INT, tab[index - 1], tag, MPI_COMM_WORLD, &statut);
        printf("Processus %d a recu %d de %d\n", rang, val, tab[index - 1]);
        MPI_Send(&val, 1, MPI_INT, tab[(index + 1) % nb_proc], tag, MPI_COMM_WORLD);
    }
    
    code = MPI_Finalize();
    exit(0);
}   