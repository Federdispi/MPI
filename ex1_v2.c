#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])   {
    int rang,nb_proc,code,valeur,tag,i;
    int tab[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};

    double starttime, endtime;
       

    MPI_Status statut;
    code = MPI_Init(&argc,&argv);
    code = MPI_Comm_size(MPI_COMM_WORLD,&nb_proc);
    code = MPI_Comm_rank(MPI_COMM_WORLD,&rang);

    starttime = MPI_Wtime();

    tag = 10;
    int N = 20;
    
    if(rang == 0){
        MPI_Send(&tab,N,MPI_INT,1,tag,MPI_COMM_WORLD);
        
        for (int i = 0; i < N; i++)
        {
            printf("Moi, processus %d j'ai envoyé %d au processus 1 \n",rang,tab[i]);
        }
    }
    else if (rang == 1){
        int tab2[20];
        MPI_Recv(&tab2,N,MPI_INT,0,tag,MPI_COMM_WORLD,&statut);
        for (int i = 0; i < N; i++)
        {
            printf("Moi, processus %d j'ai recu %d du processus 0 \n",rang,tab2[i]);
        }
    }
    
    endtime = MPI_Wtime();
    printf("temps :  %f \n",endtime - starttime);
    code = MPI_Finalize();
}   