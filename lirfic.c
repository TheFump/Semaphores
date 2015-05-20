#include <fcntl.h>
#include <stdio.h>
int main(){

//déclaration
int tab2[10];
int i,fd;

fd=open("titi.dat",O_RDWR,0666); //permission de lire et d'ecrire

read (fd,tab2,10*sizeof(int)); //on lis dans le fichier
close(fd);//fermeture fichier

for (i=0;i<10;i++) printf("%d,",tab2[i]); //affichage du contenu de tab2
printf("\n");
return 0;
}
