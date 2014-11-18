#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "general.h"

// Pour comparer deux mains, il suffit de regarder l'indice pair le plus élevé
// S'il y a égalité, on regarde la valeur

int main(){

	
	int compositionMain[TAILLECOMBINAISON] = { 0, 5, 0, 11, 0, 12, 0, 2, 0, 4, 0 };
	Table desk;

	srand(time(NULL));

	initialiserTable(&desk);
	blindEntree(&desk);
	afficherTable(&desk);
	resetTour(&desk);
	blindEntree(&desk);
	afficherTable(&desk);


	desk.numero[0].probabilite = 20;
	afficherMises(&desk);
	puts("\n");
	choixParoleIA(&desk, 0);
	puts("\n");
	afficherTable(&desk);


	system("pause");
	return 0;
}

void choixParoleIA(Table *desk, int numJoueur){
	int nombre = 0;
	int miseAsuivre = miseASuivre(desk);
	int mise = 0;

	nombre = (rand() % 100) + 1;

	if (nombre < (desk->numero[numJoueur].probabilite) / 4)		// Grosse relance 3 x la mise à suivre
		mise = (3 * miseAsuivre);


	else if (nombre < (desk->numero[numJoueur].probabilite) / 3)			//  Relance 2x la mise à suivre
		mise = 2 * miseAsuivre;

	else if (nombre <= desk->numero[numJoueur].probabilite){
		if (desk->mise[desk->numero[numJoueur].position] < miseAsuivre)		// S'il n'a pas misé le minimum pour suivre il le fait
			mise = miseAsuivre - desk->mise[desk->numero[numJoueur].position];
		else															  // Sinon il checke 
			mise = 0;
	}

	else // Il se couche
		mise = -1;
	printf("%d\n", nombre);
	miser(desk, numJoueur, mise);				// La fonction miser fait en sorte que s'il n'a pas assez, il misera ce qui lui reste
}

void influenceArgentIA(Table *desk, int numJoueur){
	int influence = 0; 
	int nombreRandom = (rand() % 6) - 3; // pour que l'ordinateur varie un peu dans une situation donnée 
	int argentRestant = desk->numero[numJoueur].argent;
	int pot = desk->pot;

	if (argentRestant < (ARGENT / 4)){		// S'il est en train de perdre, il joue plus sauvagemment
		if (argentRestant < (2 * pot))
			influence = 10;
		else if (argentRestant < pot)
			influence = 5;
		else if (argentRestant > (2 * pot))
			influence = -10;
		else if (argentRestant > pot)
			influence = -5;
	}

	else if (argentRestant > (ARGENT*(NBJOUEURS-1) + ARGENT / NBJOUEURS)){	// S'il gagne largement, il joue plus agressivement
		 if (argentRestant > (2 * pot))
			influence = 15;
		else if (argentRestant > pot)
			influence = 10;
	}

	else if (argentRestant > ARGENT){	// S'il s'en sort correctement, il joue tranquillement
		if (argentRestant < (2 * pot))
			influence = -5;
		else if (argentRestant < pot)
			influence = - 2;
		else if (argentRestant > (2 * pot))
			influence = 5;
		else if (argentRestant > pot)
			influence = 2;

	}

	desk->numero[numJoueur].probabilite += influence + nombreRandom;
}

void influenceMiseAdvIA(Table *desk, int numJoueur){
	int influence = 0;
	int grosseMise = miseASuivre(desk);
	int miseJoueur = desk->mise[desk->numero[numJoueur].position];

	if (grosseMise > (4 * miseJoueur) && grosseMise != MISEDEPART)
		influence = -15;
	else if (grosseMise > (2 * miseJoueur) && grosseMise != MISEDEPART)
		influence = -5;
	desk->numero[numJoueur].probabilite += influence;
}

void influenceMiseIA(Table *desk, int numJoueur){
	int influence = 0; 
	int miseJoueur = desk->mise[desk->numero[numJoueur].position];
	
	if (miseJoueur > (10 * MISEDEPART))
		influence = 

	desk->numero[numJoueur].probabilite += influence;
}

void influencePositionIA(Table *desk, int numJoueur){
	int influence = 0; 
	int position = desk->numero[numJoueur].position;

	if (position == (NBJOUEURS - 2))
		influence = 10; 
	else if (position == NBJOUEURS - 1)
		influence = -10;
	else if (position == MISEUR)
		influence = -5;
		
	desk->numero[numJoueur].probabilite += influence;
}

time_t tpsReaction(time_t tpsA, time_t tpsB){
	return tpsB - tpsA;
}

void influenceTpsReactionIA(Table *desk, int numJoueur, time_t tps){
	int i; 
	int influence = 0; 

	if (tps > 10)
		influence = 4;
	if (tps > 5)
		influence = 2;

	desk->numero[numJoueur].probabilite += influence;
}

void calculProba(Table *desk, int numJoueur){ // incomplete
	int i;
	int combinaison = meilleureCombinaison(desk, numJoueur);
	int probaCombinaison[NBCOMBINAISONS] = {55, 70, 85, 90, 95, 96, 97, 99, 100};
	
	desk->numero[numJoueur].probabilite = probaCombinaison[combinaison];
	influenceArgentIA(desk, numJoueur);
	influenceMiseAdvIA(desk, numJoueur);
	influencePositionIA(desk, numJoueur);
	influenceValeurCartesIA(desk, numJoueur);
}

int meilleureCombinaison(Table *desk, int numJoueur){
	int i;
	int combinaison = 0; 
	for (i = 0; i < desk->numero[numJoueur].taille; i = +2){
		if (desk->numero[numJoueur].mainAnalysee[i] > combinaison)
			combinaison = desk->numero[numJoueur].mainAnalysee[i];
	}
	return combinaison;
}

void influenceValeurCartesIA(Table *desk, int numJoueur){
	int combinaison = meilleureCombinaison(desk, numJoueur);
	int nombreRandom = (rand() % 5) - 2;
	int valeur = 0; 
	int influence = -8 + nombreRandom;

	valeur = desk->numero[numJoueur].mainAnalysee[combinaison + 1];
	influence += valeur;
	desk->numero[numJoueur].probabilite += influence;
}
