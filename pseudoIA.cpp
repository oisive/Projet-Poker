#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "general.h"



int main(){

int probaCombinaison[NBCOMBINAISONS] = {55, 70, 85, 90, 95, 96, 97, 99, 100}; 
int compositionMain[TAILLECOMBINAISON] = {0, 5, 0, 11, 0, 12, 0, 2, 0, 4, 0};
Table desk; 

srand(time(NULL));

initialiserTable(&desk);
blindEntree(&desk);

desk.numero[0].probabilite = 50;
desk.mise[1] = 0;
afficherMises(&desk);
puts("\n");
choixParole(&desk, 0);
puts("\n");
afficherTable(&desk);


system("pause"); 
return 0;
}

void choixParole(Table *desk, int numJoueur){ 
	int nombre = 0;
	int miseAsuivre = miseASuivre(desk);
	int mise = 0;

	nombre = (rand() % 100) + 1; 
	
	if(nombre < (desk->numero[numJoueur].probabilite) / 4)		// Grosse relance 3 x la mise à suivre
		mise = (3 * miseAsuivre);


	else if(nombre < (desk->numero[numJoueur].probabilite) / 3)			//  Relance 2x la mise à suivre
		mise = 2 * miseAsuivre;

	else if(nombre <= desk->numero[numJoueur].probabilite){
		if(desk->mise[desk->numero[numJoueur].position] < miseAsuivre)		// S'il n'a pas misé le minimum pour suivre il le fait
			mise = miseAsuivre - desk->mise[desk->numero[numJoueur].position]; 
		else															  // Sinon il checke 
			mise = 0;
	}
	
	else // Il se couche
		mise = -1;
	printf("%d\n", nombre);
	miser(desk, numJoueur, mise);				// La fonction miser fait en sorte que s'il n'a pas assez, il misera ce qui lui reste
}


