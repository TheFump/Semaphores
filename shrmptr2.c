#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
//voir shrmpte2.c pour explications sur déclarations qui sont identiques
key_t key; 
int shmid;
int* data;


printf("start\n");
//get smp
//get key
key = ftok("sharemem1.c", 11);
if(key == -1) perror("error ftok");
//creation
shmid=shmget(key, 20*sizeof(int), 0666|IPC_EXCL) ;
if(shmid==-1) perror("error shmid)") ;
//get segment
data = shmat(shmid, (void*)0, 0);
if(data == (int*)-1) perror("error shmat");


//lecture 
int i,j;

for(j=0; j<5; j++)
	{
		int* tab2 = data+data[j]; //on récupère le début du tableau et le déplacement via data[j]
		//affichage des valeurs :
		printf("L'adresse de %d est %p, ",j, tab2);fflush(stdout);
		for(i=0; i<3; i++)
		{
		printf("\n");
		printf("Vecteur %d case %d = %d", j, i, tab2[i]);fflush(stdout);
		}
		printf("\n");
	}	


//libération
shmdt(data);
shmctl(shmid, IPC_RMID, 0);
return 0;
}
