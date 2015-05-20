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
int k;
//déclaration des variables utilisée pour le smp
key_t key; 
int shmid;
char*data;

//initailisation du tableau
int tab2[10] = {1,1,1,1,1,1,1,1,1,1};

//recuperation de la cle
key = ftok("sharemem1.c", 11); 
if(key == -1) perror("error ftok");
//recuperation du segment
shmid=shmget(key, 10*sizeof(int), 0666|IPC_CREAT) ; 
if(shmid==-1) perror("error shmid)") ;
//recuperation de l'adresse des données
data = shmat(shmid, (void*)0, 0); 
if(data == (char*)-1) perror("error shmat");


printf("Contenu de tab2:\n");
for(k=0; k<10; k++) // écriture dans smp
	{
		printf("%d,", tab2[k]); fflush(stdout); //on vérifie le contenu de tab2
		data[k] = tab2[k]; //on copie le contenu de tab2 dans le smp
		
	}

sleep(30); //sleep permettant au lecteur de s'executer
//libération du smp
shmdt(data); 
shmctl(shmid, IPC_RMID, 0);
return 0;
}
