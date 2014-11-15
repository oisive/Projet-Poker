#include <stdio.h>
#include <stdlib.h>
#include "general.h" 

// fonctions indispensables

// Créer une carte selon la valeur et la couleur
Carte creerCarte(Valeur val, Couleur coul) { 
	Carte c;
	c.rang = coul * NBVALEURS + val;
	return c;
}


// Obtenir la valeur d'une carte à partir de son rang
unsigned int getIntVal(const Carte* c) { 
	return c -> rang % NBVALEURS;
}

unsigned int getIntVal(Carte c) { 
	return c.rang % NBVALEURS + 2;
}


// Obtenir la couleur d'une carte à partir de son rang
unsigned int getIntCoul(const Carte* c) { 
	return c -> rang / NBVALEURS;
}

// Renvoie la valeur (en chaine de caractère) de la carte passée en paramètre pour affichage
const char* getValeur(const Carte* c) { 
	static char* valeurs [] = {"2", "3", "4", "5", "6", "7", "8", "9",
					"10" ,"valet", "dame", "roi", "as"};
		return valeurs[getIntVal(c)];
}

// Renvoie la couleur (en chaine de caractère) de la carte passée en paramètre pour affichage
const char* getCouleur(const Carte* c){ 
	static char* couleurs [] = {"carreau", "trefle", "coeur", "pique"};
	// couleurs[CARREAU] =="carreau"
	return couleurs[getIntCoul(c)];
}


// fonctions de confort


// Créer une carte selon le rang
Carte creerCarte(unsigned int rang) {
	Carte c;
	c.rang = rang;
	return c;
}


// Afficher la carte sous forme "valeur de couleur"
void afficherCarte(const Carte* c) { 
	printf("%s de %s\n", getValeur(c), getCouleur(c));
}
