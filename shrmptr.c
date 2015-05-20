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

//déclaration variables pour smp
key_t key; 
int shmid;
int** data;//on veut pouvoir stocker des adresses => TABLEAU DE POINTEURS INT !!



//get smp, voit shrmpte.c pour explications
//get key
key = ftok("sharemem1.c", 11);
if(key == -1) perror("error ftok");
//creation smp
shmid=shmget(key, 5*sizeof(int*)+15*sizeof(int), 0666|IPC_EXCL) ;
if(shmid==-1) perror("error shmid)") ;
//get segment
data = shmat(shmid, (void*)0, 0);
if(data == (int**)-1) perror("error shmat");


//lecture 
int i,j;

for(j=0; j<5; j++)//boucle pour afficher les 5 vecteurs
	{
		int* tab2 = (int*)data[j]; //on récupère l'adresse du vecteur numéro j;
		printf("L'adresse de %d est %p, ",j, tab2);fflush(stdout); //controle
		for(i=0; i<3; i++)
		{
		printf("Vecteur %d case %d = %d", j, i, tab2[i]); //on affiche a partir de l'adresse =< SEGFAULT
		}
		printf("\n");
	}	

printf("start3\n");



//libération smp
shmdt(data);
shmctl(shmid, IPC_RMID, 0);
return 0;
}
