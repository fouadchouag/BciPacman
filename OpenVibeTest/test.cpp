#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	char motdepasse[5];
	int trouve = 0;

	while(!trouve){
      printf("Mot de passe:");
	  scanf("%s",motdepasse);
	  if(strncmp(motdepasse, "Toto",4)==0){
		  trouve=1;
	  }
	}
    printf("Access Granted");
}