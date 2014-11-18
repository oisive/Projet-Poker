#ifndef GENERAL_H
#define GENERAL_H

// CARTE

enum Couleur {CARREAU, TREFLE, COEUR, PIQUE};
enum Valeur {DEUX=2, TROIS=3, QUATRE=4,CINQ=5,SIX=6,SEPT=7,HUIT=8,NEUF=9,DIX=10, VALET = 11, DAME = 12, ROI = 13, AS = 14};
enum {NBVALEURS = 13, NBCOULEURS = 4, NBCARTES = NBCOULEURS * NBVALEURS, NBCARTES_MAIN = 5, NBJOUEURS = 2, NBCOMBINAISONS = 9, TAILLECOMBINAISON = 11, ARGENT = 1000, MISEDEPART = 20, MISEUR = 0, POSITION_JOUEUR = 0};

struct Carte {
	unsigned int rang;
};
typedef struct Carte Carte;

// fonctions indispensables
Carte creerCarte(Valeur, Couleur);
const char* getValeur(const Carte*); 
const char* getCouleur(const Carte*);
unsigned int getIntVal(Carte c);
unsigned int getIntVal(const Carte*);
unsigned int getIntCoul(const Carte*);


// fonctions de confort
void afficherCarte(const Carte*);
Carte creerCarte(unsigned int rang);



// PAQUET

struct Paquet {
	Carte cartes [NBCARTES];
	bool presente[NBCARTES];
	int combien;
};
typedef struct Paquet Paquet;

enum { PLEIN = true, VIDE = false } ;
Paquet creerPaquet(bool plein);
void afficherPaquet(Paquet*);
Carte piocher(Paquet*); // au hasard



// MAIN 


enum {NBCARTESENMAIN = 5};

struct Main{
	Carte cartes_En_Main [NBCARTES_MAIN];
	int compteur;
	bool defausser[NBCARTESENMAIN];
};
typedef struct Main Main;


void completerMain(Main*, Paquet*);
void afficherMain(Main*);
Main creerMain();
void ajouterCarte(Main*, Carte*);
void changer_carte(Paquet*, Main*);
void demander_Cartes_Defausser(Paquet*, Main*);

bool estPleine(Main*);
bool main_est_correcte(Main* m);
void analyseMain(Main*); // a ecrire


// JOUEUR

struct Joueur{
	Main main; 
	int mainAnalysee[TAILLECOMBINAISON]; 
	unsigned int argent; 
	unsigned int position;
	unsigned int taille;	// vaut TAILLECOMBINAISON UTILE POUR FONCTIONS
	unsigned int probabilite;
	// les unsigned peuvent poser des pb de conversion
};
typedef struct Joueur Joueur;

void initialiserJoueur(Joueur *player);
void initialiserJoueur(Joueur *player, int pos);
Joueur creerJoueur();
Joueur creerJoueur(int pos);
void affichageJoueur(Joueur *player);


// TABLE

struct Table{
	int mise[NBJOUEURS];
	int pot;
	Joueur numero[NBJOUEURS]; 
};
typedef struct Table Table; 

void initialiserTable(Table *desk);
Table creerTable();
void afficherTable(Table *desk);
void changementPosition(Table *desk);
void updateArgent(Table *desk); // devrait devenir useless
void updatePot(Table *desk);
int calculPot(Table *desk);
void resetPot(Table *desk);
void recapJoueur(Table *desk); 
void recapJoueur(Table *desk, int pos);
int miseASuivre(Table *desk);
bool peutSuivre(Table *desk, int numJoueur);
//void faitTapis(Table *desk, int numJoueur, int decision);
void blindEntree(Table *desk);
void resetMise(Table *desk);
void resetTour(Table *desk);
void miser(Table *desk, int numJoueur, int choix);
void afficherMises(Table *desk);
bool personneAuTapis(Table *desk);
int miseJoueur(Table *desk, int numJoueur);
void choixParole(Table *desk, int numJoueur); // Joueur fictif

// Fonctions affichage choix du joueur 
void joueurCheck();
void joueurMise(int mise);
void joueurFaitTapis(int valeurTapis);
void joueurCouche();
void choixInvalide();



void creerTableauCombinaison(Main *main, int tableau[], int taille);
void initTableau(int tab[], int taille);
void classerTableau(int tab[], int taille);
void afficherTableau(int tab[], int taille);





#endif
