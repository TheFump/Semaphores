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
int** data; //on veut pouvoir stocker des adresses => TABLEAU DE POINTEURS INT !!
int i, j;

//get smp
//get key
key = ftok("sharemem1.c", 11);
if(key == -1) perror("error ftok");
//creation smp et allocation mémoire
shmid=shmget(key, 5*sizeof(int*)+15*sizeof(int), 0666|IPC_CREAT|IPC_EXCL) ; //5 pointeurs (int*) et 3*5 valeurs(int)
if(shmid== -1) perror("Création échoue error shmid)") ;
//get adresse smp
data = shmat(shmid, (void*)0, 0);
if(data == (int**)-1) perror("error shmat");


//ecriture tableau et vecteur
for(i=0; i < 5; i++)
{
	int*tab = data[i] = (int*)(data+5)+3*i; // on veut qu'il se déplace de 8 octets sur les 5 premières cases (poiteurs) puis de 4 octets (valeurs). On récupère donc les adresses tous les 3 entiers après s'etre déplacé de 5 pointeurs.
	for(j=0; j < 3; j++) //initialisation des vecteurs
	{		
	tab[j] = 5+3*i+j; 
	}
}

	

//vérification du contenu
for(i=0; i < 5; i++)
{
	int* tab = (int*)data[i];
	printf("adresses : %p,", tab);fflush(stdout); //adresses
	printf("\n");
	for(j=0; j< 3; j++)// vecteurs
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
