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
int j;
//déclaration des variables utilisée pour le smp
key_t key; 
int shmid;
char*data;

//initailisation du tableau
int tab2[10] = {2,2,2,2,2,2,2,2,2,2};
printf("Contenu tab2:\n");
for(j=0; j<10; j++)
	{
		printf("%d,", tab2[j]);
	}
printf("\n");
//recuperation de la cle
key = ftok("sharemem1.c", 11); 
if(key == -1) perror("error ftok");
//recuperation du segment
shmid=shmget(key, 10*sizeof(int), 0666|IPC_CREAT) ; 
if(shmid==-1) perror("error shmid)") ;
//recuperation de l'adresse des données
data = shmat(shmid, (void*)0, 0); 
if(data == (char*)-1) perror("error shmat");


printf("Copie de smp dans le tableau :\n");
for(j=0; j<10; j++)// lecture dans smp
	{
		tab2[j] = data[j]; //on récupère le contenu du smp
		printf("%d,", tab2[j]); //on controle le contenu de tab2
	}
printf("\n");
//libération du smp
shmdt(data);
shmctl(shmid, IPC_RMID, 0);
return 0;
}
