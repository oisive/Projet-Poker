#ifndef GENERAL_H
#define GENERAL_H

// PAQUET

struct Paquet {
	Carte cartes [NBCARTES];
	int combien;

};
typedef struct Paquet Paquet;

enum { PLEIN = true, VIDE = false } ;

Paquet creerPaquet(bool plein);
void afficherPaquet(Paquet*);



// CARTE

enum Couleur { CARREAU, TREFLE, COEUR, PIQUE};
enum Valeur {DEUX=2, TROIS=3, QUATRE=4,CINQ=5,SIX=6,SEPT=7,HUIT=8,NEUF=9,DIX=10, VALET = 11, DAME = 12, ROI = 13, AS = 14};
enum {NBVALEURS = 13, NBCOULEURS = 4, NBCARTES = NBCOULEURS * NBVALEURS, NBCARTES_MAIN = 5};

struct Carte {
	unsigned int rang;
	unsigned int distribue;
};
typedef struct Carte Carte;

void initCarte(Carte *); 
void piocherCarte(Carte *);


// MAIN 


#define NBCARTESENMAIN 5

struct Main{
	Carte cartes[NBCARTESENMAIN];
	int note;
	int valeur1;
	int valeur2;
};
typedef struct Main Main;

void initMain(Main *);

Main *afficherMain(valeur *, couleur *); // à (finir de) coder


// JOUEUR

struct Joueur{
	Main main; 
	int argent; 
	int position;
};
typedef struct Joueur Joueur;

void initJoueur(Joueur *);


// TABLE

struct Table{
	int mise[NBJOUEURS]; 
	Joueur position[NBJOUEURS]; 
};
typedef struct Table Table; 


#endif
