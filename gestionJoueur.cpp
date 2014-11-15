#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "unittest.h"

// Relativement inutile, initialise un joueur en position 0 avec une main vide
void initialiserJoueur(Joueur *player){
	player->main = creerMain();
	player->taille = TAILLECOMBINAISON;
	initTableau(player->mainAnalysee, player->taille);
	player->argent = ARGENT; 
	player->position = 0;
}

// Relativement inutile, initialise un joueur en position pos passée en paramètre avec une main vide
void initialiserJoueur(Joueur *player, int pos){
	player->main = creerMain();
	player->taille = TAILLECOMBINAISON;
	initTableau(player->mainAnalysee, player->taille);
	player->argent = ARGENT; 
	player->position = pos;

}

// DECONSEILLE Relativement inutile, crée un joueur et l'initialise en position 0 avec une main vide puis le renvoie 
Joueur creerJoueur(){
	Joueur player;
	player.main = creerMain();
	player.taille = TAILLECOMBINAISON;
	initTableau(player.mainAnalysee, player.taille);
	player.argent = ARGENT; 
	player.position = 0;

	return player;
}

// DECONSEILLE Relativement inutile, crée un joueur et l'initialise en position pos passée en paramètre avec une main vide puis le renvoie
Joueur creerJoueur(int pos){
	Joueur player;
	player.main = creerMain();
	player.taille = TAILLECOMBINAISON;
	initTableau(player.mainAnalysee, player.taille);
	player.argent = ARGENT; 
	player.position = pos;
	return player;
}

//Affiche le détail d'un joueur
void affichageJoueur(Joueur *player){
	afficherMain(&(player->main));
	puts("\n"); 
	printf("Le joueur possede %d jetons.\n", player->argent); 
	printf("La position du joueur est : %d.\n", player->position); 
	puts("\n");
}
