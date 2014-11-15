/*


// main.cpp
#include <stdlib.h>
#include <stdio.h>
#include "Carte.h"
#include "paquet.h"
#include "main.h"
#include "unittest.h"

int main() {

Carte c;
	int rang;
	for (rang = 0; rang < NBCARTES; ++rang) {
		c = creerCarte(rang);
		afficherCarte(&c);
	}
	
	Carte c1,c2;
	c1 = creerCarte(DIX, PIQUE);
	c2 = creerCarte(VALET, COEUR);


	if ( getIntVal(&c1) == getIntVal(&c2))
		printf("BATAILLE \n");
	else if (getIntVal(&c1) > getIntVal(&c2))
		printf(" La premiere carte est la plus forte \n");
	else printf("la deuxième carte est la plus fort \n");

	afficherPaquet(&pile_De_Defausse);
	Paquet jeu = creerPaquet(PLEIN);
	Main joueur1 = creerMain();
	afficherMain(&joueur1);
	completerMain(&joueur1, &jeu);
	afficherMain(&joueur1);

	// assertEquals(jeu, jeu.combien == 52,"le paquet à 52 cartes"); demander au prof
	system("pause");
	return 0;

}



    //trier le tableau
    int c = couleur(coul);
    int s = suite(tab);
    //assertEquals(couleur(coul),5,"couleur(coul)=5");
    //assertEquals(suite(tab),4,"suite(tab)=4");
    //assertEquals(quintefl(couleur(coul),suite(tab)),8,"quintefl(couleur(coul),suite(tab)");
    //assertEquals(test(tab,coul),4,"test(tab,coul)=4");
    combinaison(tab,compt);
    //for(int i=0;i<5;i++){
    //    assertEquals(compt[i], 1,"combinaison(tab,compt) = 1");
    //}
    //afficher(compt);

	*/
