#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "general.h"



// 0<= compteur < NBCARTES_MAIN
// compteur est le nombre de cartes en main
// si compteur == 0 la main est vide
// sinon les cases de 0 à compteur-1 contiennent une carte


// Vérifie si le nombre de cartes en main est bien compris entre 0 et 5
bool main_est_correcte(Main* m) { 
	return 0 <= m->compteur &&  m->compteur <= NBCARTES_MAIN;
}

// Crée une main vide
Main creerMain() {
	Main main;
	main.compteur = 0;
	assert(main_est_correcte(&main));
	return main;
}

// Ajoute une carte à une main 
void ajouterCarte(Main* main, Carte *carte) {
	main->cartes_En_Main[main->compteur++] = *carte;
}

// Dit si la main est pleine ou non 
bool estPleine(Main* main) {
	return main->compteur == NBCARTES_MAIN;
}

// Tant que la main n'est pas pleine, on ajoute une carte
void completerMain(Main* main,Paquet* p){
	assert(main_est_correcte(main));
	while(! estPleine(main)) {
		ajouterCarte(main, &piocher(p));
	}
	assert(main_est_correcte(main));
}


// Affiche la main si elle existe et quelle que soit sa taille
void afficherMain(Main* main) {
	assert(main_est_correcte(main));
	int i;
	if (main->compteur == 0)
		printf("La main est vide.\n");
	for (i = 0 ; i < main->compteur ; ++i)
		afficherCarte(&(main->cartes_En_Main[i]));
}


void changer_carte(Paquet* p, Main* m) {
	int i;
	int choix = 0;
	int position; // position de la carte à modifier
	puts("Veuillez rentrer '1' pour defausser ou '0' pour garder votre carte\n");


	// Tasser les cartes qu'on garde
	for (i = 0; i < NBCARTESENMAIN; ++i) {

		printf("Souhaitez vous defausser votre ");
		afficherCarte((&(m->cartes_En_Main[i])));
		scanf("%d", &choix); // decidé de garder ou de defausser la carte


		while (choix != 1 && choix != 0) { // vérifier si la valeur entrée est correcte
			puts("Veuillez entrer '1' ou '0'");
			scanf("%d", &choix);
		}

		if (choix == 1) { // tasse la main d'un cran si le joueur entre 1
			for (position = i; position < (NBCARTESENMAIN - 1);) {
				m->cartes_En_Main[position] = m->cartes_En_Main[++position];
			}
			--m->compteur;
		}
	}
}

/*
// PAS FINIE
unsigned int defausser(int *t) { 
	unsigned int compteur;
	unsigned int position;
	unsigned int i ;
	scanf("entrez le nombre de cartes à defausser : %d",&compteur);
	for ( i = 0 ; i < compteur ; ++i ) {
		scanf("entrez la position de la carte à defausser : %d", &position);
		 if (position < 0 && position > NBCARTES_EN_MAIN) {
			 scanf("entrez une position entre 0 et 4 !! : %d", &position);
		 }
		 ;
		t[i] = position ;
	}

	return t[i];
}



void tasser_Main(Main* m) {
	int* tableau;
	defausser(tableau);
}

*/



