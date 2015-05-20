#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>



main(){
//déclaration des variables utilisée pour le smp
key_t key; 
pid_t pid;
int shmid;
char*data;

//initailisation des tableaux
int tab1[10] = {1,1,1,1,1,1,1,1,1,1};
int tab2[10] = {1,1,1,1,1,1,1,1,1,1};

//recuperation de la cle
key = ftok(".", "R");
if(key == -1) perror("error ftok");
//recuperation du segment
shmid=shmget(key, 10*sizeof(int), 0644|IPC_CREAT|IPC_PRIVATE) ;
if(shmid==-1) perror("Création échoue error shmid)") ;
//recuperation de l'adresse des données
data = shmat(shmid, (void*)0, 0);
if(data == (char*)-1) perror("error shmat");


int j, k;
//réalisation du fork

pid = fork();
switch(pid)
{

case 0: //fils
	printf("fils : \n");
	for(k=0; k<10; k++)
	{
		tab2[k] = 2; //on met tab2 à 2 dans toutes les cases
		printf("%d,", tab2[k]); //vérificaiton du contenu de tab2
		data[k] = tab2[k]; //on place le contenu de la case dans une case du segment de mémoire
	}
	printf("\n");
	exit(0); //on sort du fils et on signal au père la fin du programme
	break;


default: //père

usleep(500); //dors 0.5 secondes pour éviter qu'il ne se déclenche avant le fils
printf("père : \n");
for(j=0; j<10; j++)
	{
		printf("%d,", tab2[j]); //affiche tab2 != du fils
	}
	printf("\n");

usleep(500);//dors 0.5 secondes pour revenir au fils
printf("père : \n");
for(j=0; j<10; j++)
	{
		tab2[j] = data[j]; //on copie le contenu du smp dans tab2 du père
		printf("%d,", tab2[j]);//affiche tab2 : resultat idem au fils
	}
	printf("\n");

	waitpid(pid); //on attends la fin du fils
	//libération smp
	shmdt(data);  
	shmctl(shmid, IPC_RMID, 0);

}
return 0;
}








