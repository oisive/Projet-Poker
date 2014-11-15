#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "unittest.h"

// Initialise la table passée en paramètre
void initialiserTable(Table *desk){
	int i; 
	 desk->mise[MISEUR] = MISEDEPART;
	 desk->pot = desk->mise[MISEUR];
	for(i = 0 ; i < NBJOUEURS ; i++){
		desk->numero[i].main = creerMain();
		desk->numero[i].taille = TAILLECOMBINAISON;
		desk->numero[i].mainAnalysee[desk->numero[i].taille];
		desk->numero[i].argent = ARGENT;
		desk->numero[i].position = i;
	}
}

// Crée une table et l'initialise DECONSEILLE
Table creerTable(){
	int i; 
	Table desk;
	desk.mise[MISEUR] = MISEDEPART;
	desk.pot = desk.mise[MISEUR];
	for(i = 0 ; i < NBJOUEURS ; i++){
		desk.numero[i].main = creerMain();
		desk.numero[i].taille = TAILLECOMBINAISON;
		desk.numero[i].mainAnalysee[desk.numero[i].taille];
		desk.numero[i].argent = ARGENT;
		desk.numero[i].position = i;
	}
	return desk;
}

// Affiche la table passée en paramètre
void afficherTable(Table *desk){
	int i; 
	printf("La mise d'entree est de %d\n", desk->mise[MISEUR]);
	printf("Le pot est de %d\n", desk->pot);
	for(i = 0 ; i < NBJOUEURS ; i++){
		printf("Le joueur %d : \n", i);
		afficherMain(&(desk->numero[i].main));
		printf("Le joueur possede %d jetons.\n",  desk->numero[i].argent); 
		printf("La position du joueur est : %d.\n", desk->numero[i].position); 
		puts("\n");
	}
}

// Affiche les principales infos pour le joueur
void recapJoueur(Table *desk){
	printf("La mise d'entree est de %d\n", desk->mise[MISEUR]);
	printf("Le pot est de %d\n", desk->pot);
	puts("Recapitulatif :");
	puts("Voici votre main :");
	afficherMain(&(desk->numero[POSITION_JOUEUR].main));
	printf("Vous possedez %d jetons.\n", desk->numero[POSITION_JOUEUR].argent);
	if (desk->numero[POSITION_JOUEUR].position == MISEUR)
		{
			puts("Vous êtes la grosse blind");
		}
	else{
			puts("A vous de suivre ou non");
		}
	puts("\n");
}

// Affiche les principales infos pour le joueur à la position pos
void recapJoueur(Table *desk, int pos){
	printf("La mise d'entree est de %d\n", desk->mise[MISEUR]);
	printf("Le pot est de %d\n", desk->pot);
	puts("Recapitulatif :");
	printf("Voici la main du joueur %d:", pos);
	afficherMain(&(desk->numero[pos].main));
	printf("Vous possedez %d jetons.\n", desk->numero[pos].argent);
	if (desk->numero[pos].position == MISEUR)
	{
		puts("Il est la grosse blind.");
	}
	else{
		puts("Il n'est pas la grosse blind.");
	}
	puts("\n");
}

// Fait alterner les positions des joueurs
void changementPosition(Table *desk){
	int i;
	for(i = 0 ; i < NBJOUEURS ; i++){
		if(desk->numero[i].position != (NBJOUEURS - 1))
			desk->numero[i].position++;
		else desk->numero[i].position = 0;
	}
}

// Ote de la reserve l'argent que les joueurs ont misé
void updateArgent(Table *desk){
	int i, j;
	for (i = 0; i < NBJOUEURS; i++){ // Parcourt les joueurs
		for (j = 0; j < NBJOUEURS; j++){ // Parcourt les mises
			if (desk->numero[i].position == j){ // Si numero i est à la position j
				desk->numero[i].argent -= desk->mise[j]; // On ôte de sa reserve ce qu'il a misé
			}

		}
	}
}

void updatePot(Table *desk){
	int i;
	for (i = 0; i < NBJOUEURS; i++){
		desk->pot += desk->mise[i];
	}

}

void resetPot(Table *desk){
	desk->pot = 0;
}
