#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h> 

int main(){
//déclaration
int i = 0, j=0;
int* map;
int fd;

fd=open("titi.dat",O_RDWR,0666); //permission en lecture et ecriture

//mmap
map = mmap(NULL, 10*sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd ,0); //on alloue 10 octets, les permission de lire, ecrire, et d'etre accédé par d'autres programmes
if(map == (int*)-1) perror("error mmap");

//modification du contenu
while(i != 99)//on attends l'entrée 99 par user
	{
		scanf("%d", &i);
		map[j]++;//on ajoute 1 j
		j++;
		if(j==10)j=0;
	}
//fermeture
munmap(map, 10*sizeof(int));
close(fd);
return 0;

}
