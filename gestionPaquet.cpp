#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "general.h"

//  Crée un paquet
Paquet creerPaquet(bool plein) {
	srand(time(NULL)); 
	Paquet p;
	int i;
	if (!plein) {				// Paquet vide
		p.combien = 0;
		for (i = 0 ; i < NBCARTES ; ++i) 
			p.presente[i] = false;
	}
	else {										
			for (i = 0 ; i < NBCARTES ; ++i)	
			{
				p.presente[i] = true;
				p.cartes[i] = creerCarte(i);
			}

			p.combien = NBCARTES;  // Remplit le paquet et initialise tous les champs 
		}
	return p;
}

// Affiche le paquet
void afficherPaquet(Paquet* p){
	int i;
	if (p->combien == 0)
		printf("Le paquet est vide.\n\n");

	for (i = 0; i < p->combien  ;  ++i)
		afficherCarte(&p->cartes[i]);
}


// Pioche une carte dans le paquet
Carte piocher(Paquet* p) {
	assert(p->combien > 0);		// Il reste au moins une carte dans le paquet
	int rang;
	do {
		rang = rand() % NBCARTES; 
	} while (!p->presente[rang]); // Tant qu'on pioche une carte qui n'est pas présente, on en cherche une autre
	p->presente[rang] = false;	 		
	--p->combien;				// Une fois trouvée, on indique qu'elle n'est plus présente et on baisse le nombre de cartes du paquet
	return p->cartes[rang];
}

