#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])   {
    int rang,nb_proc,code,valeur,tag,i;
       

    MPI_Status statut;
    code = MPI_Init(&argc,&argv);
    code = MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code = MPI_Comm_rank(MPI_COMM_WORLD,&rang);
    
    if(rang == 0){
        for (int i = 1; i < nb_proc; i++)
        {
            int val = 0;
            MPI_Send(&val,1,MPI_INT,i,tag,MPI_COMM_WORLD);
            printf("Moi, processus %d je me synchronise avec le processus %d \n",rang,i);
            MPI_Recv(&val, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &statut);
            if (val == 0) {
                printf("Le processus %d est synchronisé\n",i);
            }
        }
        
    }
    else {
        int val;
        MPI_Recv(&val,1,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
        if(val == 0) {
            MPI_Send(&val, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        }
    }

    code = MPI_Finalize();
}   