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
	main->cartes_En_Main[main->compteur] = *carte;
	main->defausser[(main->compteur)] = false;
	main->compteur++;
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

//Demande à l'utilisateur s'il souhaite se défausser de chaque carte dans sa main
void demander_Cartes_Defausser(Paquet* p, Main* m) {
	int choix;
	int i;
	assert(main_est_correcte(m));

	for ( i = 0 ; i < NBCARTES_MAIN ; ++i ) {

		printf("Souhaitez vous defausser votre ");
		afficherCarte((&(m->cartes_En_Main[i])));
		scanf("%d",&choix); // decidé de garder ou de defausser la carte

		while (choix != 1 && choix != 0) { // vérifier si la valeur entrée est correcte
			puts("Veuillez entrer '1' ou '0'");
			scanf("%d",&choix);
			}
		if (choix == 1) {
			m->defausser[i] = true;// si vrai, la carte sera defausser
		}
	}
}

// remplace directement les cartes marquées défausser, par une nouvelle carte du paquet non piocher.
void changer_carte(Paquet* p, Main* m) {

	assert(main_est_correcte(m));
	puts("Veuillez rentrer '1' pour defausser ou '0' pour garder votre carte\n");
	demander_Cartes_Defausser(p,m);// changer le bool de défausser pour savoir quel carte sera défausser 

	unsigned int i;
		for (i = 0; i < NBCARTESENMAIN;++i) {
		if (m->defausser[i]) {
			m->compteur = i;// on fait appel à ajouterCarte qui néccesite la valeur de compteur pour désigner la position de la carte à remplacer.
			ajouterCarte(m,&(piocher(p)));//remplace la carte à l'emplacement compteur (=i) et remet le bool défausser à la valeur false.
		}
	}
	m->compteur = NBCARTESENMAIN; // le compteur sera toujours à la fin égal à NBCARTESENMAIN
	assert(main_est_correcte(m));

}
