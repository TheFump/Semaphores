#include <fcntl.h>
#include <stdio.h>
int main(){
//déclaration
int tab1[10]={11,22,33,44,55,66,77,88,99,1000};
int i,fd;

fd=open("titi.dat",O_RDWR|O_CREAT|O_TRUNC,0666);//permission de création, d'écriture et de lecture
write (fd,tab1,10*sizeof(int)); //ecriture de 10 entiers
close(fd);//fermeture du fichiers

return 0;
}

