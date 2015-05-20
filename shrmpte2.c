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
int* data; //on déclare cette fois en int* pour avoir un tableau d'entier, on ne soucie plus des adresses
int i, j;


//get smp
//get key
key = ftok("sharemem1.c", 11);
if(key == -1) perror("error ftok");
//creation
shmid=shmget(key, 20*sizeof(int), 0666|IPC_CREAT|IPC_EXCL) ; //20 entier : 5 "adresses" et 5*3 entiers
if(shmid== -1) perror("Création échoue error shmid)") ;
//get segment
data = shmat(shmid, (void*)0, 0);
if(data == (int*)-1) perror("error shmat");

//ecriture tableau et vecteur
for(i=0; i < 5; i++)
{
	int*tab;
	data[i] = 5+3*i; //on veut qu'il se déplace de 4 octets. On démarre à 5*4octets puis l'on incrémente de 3 pour laisser la place au contenu des vecteurs
	tab = data+ data[i];//on stocke l'adresse du début du segment + le déplacement
	for(j=0; j < 3; j++)//on initialise les vecteurs
	{		
	tab[j] = 5+3*i+j;
	}
}
		

//vérification du contenu
for(i=0; i < 5; i++)
{
	int* tab = data + data[i];
	printf("adresses : %p,", tab);fflush(stdout); //adresses
	printf("\n");
	for(j=0; j< 3; j++)//vecteurs
	{
	printf("valeurs : %d,", tab[j]);fflush(stdout);
	printf("\n");
	}
}



//temps pour le lecteur
sleep(10);

//libération
shmdt(data);
shmctl(shmid, IPC_RMID, 0);
return 0;
}
