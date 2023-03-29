#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])   {
    int rang,nb_proc,code,valeur,tag,i;
    int N = 10000;

    double starttime, endtime;
       

    MPI_Status statut;
    code = MPI_Init(&argc,&argv);
    code = MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code = MPI_Comm_rank(MPI_COMM_WORLD,&rang);

    starttime = MPI_Wtime();

    tag = 10;
    valeur = 100;
    
    for(i=0;i<N;i++){
        if(rang == 0){
            MPI_Send(&valeur,1,MPI_INT,1,tag,MPI_COMM_WORLD);
            printf("Moi, processus %d j'ai envoye %d au processus 1 \n",rang,valeur);
        }
        else if (rang == 1){
            MPI_Recv(&valeur,1,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
            printf("Moi, processus %d j'ai recu %d au processus 1 \n",rang,valeur);
        }
    }

    endtime = MPI_Wtime();
    printf("temps :  %f \n",endtime - starttime);
    code = MPI_Finalize();
}   