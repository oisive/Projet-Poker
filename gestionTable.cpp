#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "unittest.h"

// Initialise la table passée en paramètre
void initialiserTable(Table *desk){
	int i;
	desk->mise[MISEUR] = MISEDEPART;
	desk->mise[(NBJOUEURS - 1)] = (MISEDEPART / 2);
	for (i = 1; i < NBJOUEURS - 1; i++){
		if (i != MISEUR && i != (NBJOUEURS - 1))	// securité
			desk->mise[i] = 0;
	}
	desk->pot = 0;
	for (i = 0; i < NBJOUEURS; i++){
		desk->numero[i].main = creerMain();
		desk->numero[i].taille = TAILLECOMBINAISON;
		desk->numero[i].mainAnalysee[desk->numero[i].taille];
		desk->numero[i].argent = ARGENT;
		desk->numero[i].probabilite = 0;
		if (desk->numero[i].position == MISEUR)
			desk->numero[i].argent -= MISEDEPART;
		else if (desk->numero[i].position == (NBJOUEURS - 1))
			desk->numero[i].argent -= (MISEDEPART / 2);
		desk->numero[i].position = i;
	}
}

// Crée une table et l'initialise DECONSEILLE PAS A JOUR
Table creerTable(){
	int i;
	Table desk;
	desk.mise[MISEUR] = MISEDEPART;
	desk.pot = calculPot(&desk);
	for (i = 0; i < NBJOUEURS; i++){
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
	for (i = 0; i < NBJOUEURS; i++){
		printf("Le joueur %d : \n", i);
		printf("Le joueur a mise %d jetons\n", desk->mise[desk->numero[i].position]);
		afficherMain(&(desk->numero[i].main));
		printf("Le joueur possede %d jetons.\n", desk->numero[i].argent);
		printf("La position du joueur est : %d.\n", desk->numero[i].position);
		puts("\n");
	}
}

// Affiche les principales infos pour le joueur PAS A JOUR
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

// Affiche les principales infos pour le joueur à la position pos PAS A JOUR
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
	for (i = 0; i < NBJOUEURS; i++){
		if (desk->numero[i].position != (NBJOUEURS - 1))
			desk->numero[i].position++;
		else desk->numero[i].position = 0;
	}
}

// Ote de la reserve l'argent que les joueurs ont misé
// devrait devenir useless 
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

int calculPot(Table *desk){
	unsigned int pot = 0;
	int i;

	for (i = 0; i < NBJOUEURS; i++){
		pot += desk->mise[i];
	}
	return pot;
}

// devrait devenir useless 
void updatePot(Table *desk){
	int i;
	for (i = 0; i < NBJOUEURS; i++){
		desk->pot += desk->mise[i];
	}
}

// Vide le pot en fin de tour
void resetPot(Table *desk){
	desk->pot = 0;
}

// Remet les mises à leurs valeurs initiales
void resetMise(Table *desk){
	int i;

	desk->mise[MISEUR] = MISEDEPART;
	desk->mise[(NBJOUEURS - 1)] = (MISEDEPART / 2);

	for (i = 1; i < (NBJOUEURS - 1) ; i++){
		if (i != MISEUR && i != (NBJOUEURS - 1))	// securité
		desk->mise[i] = 0;
	}
}

void resetProbabilite(Table *desk){
	int i;
	for (i = 1; i < NBJOUEURS; i++)
		desk->numero[i].probabilite = 0;
}

void resetTour(Table *desk){
	resetMise(desk);
	resetPot(desk);
	resetProbabilite(desk);
	changementPosition(desk);
}

// Gère la petite et la grosse blind
void blindEntree(Table *desk){  
	int i;

	for (i = 0; i < NBJOUEURS; i++){
		if (desk->numero[i].position == MISEUR){ // Grosse blind
			if (desk->numero[i].argent >= desk->mise[MISEUR]){
				desk->numero[i].argent -= desk->mise[MISEUR];
				desk->pot += desk->mise[MISEUR];
			}
			else {
				desk->mise[MISEUR] = desk->numero[i].argent;
				desk->numero[i].argent = 0;
				desk->pot += desk->mise[MISEUR];
			}
		}

		else if (desk->numero[i].position == (NBJOUEURS - 1)){  // Petite blind
			if (desk->numero[i].argent >= desk->mise[(NBJOUEURS - 1)]){
				desk->numero[i].argent -= desk->mise[(NBJOUEURS - 1)];
				desk->pot += desk->mise[(NBJOUEURS - 1)];
			}
			else {
				desk->mise[(NBJOUEURS - 1)] = desk->numero[i].argent;
				desk->numero[i].argent = 0;
				desk->pot += desk->mise[(NBJOUEURS - 1)];
			}
		}
	}
}

// Renvoie la valeur de la mise minimale à mettre pour jouer
int miseASuivre(Table *desk){
	int miseASuivre = desk->mise[MISEUR];
	int i;

	for (i = 0; i < NBJOUEURS; i++){
		if (desk->mise[i] > miseASuivre)
			miseASuivre = desk->mise[i];
	}
	return miseASuivre;
}

// Dit si le joueur a assez d'argent pour suivre la mise minimale ou non
bool peutSuivre(Table *desk, int numJoueur){
	bool booleen = true;

	if (miseASuivre(desk) > desk->numero[numJoueur].argent)
		booleen = false;

	return booleen;
}

/* FONCTION PAS TOP, A REPRENDRE A LA RIGUEUR
void faitTapis(Table *desk, int numJoueur, int decision){ // Lui demander s'il fait tapis, stocker dans décision, 0 signifie non, le reste oui
int i;
int grosseMise = miseASuivre(desk);

if (!peutSuivre(desk, numJoueur) && decision){ // S'il ne peut pas suivre mais fait tapis
desk->mise[desk->numero[numJoueur].position] = desk->numero[numJoueur].argent; // Il met tout en jeu
desk->numero[numJoueur].argent = 0;

for (i = 0; i < NBJOUEURS; i++){
if (desk->mise[desk->numero[i].position] == grosseMise){
desk->numero[i].argent += (desk->mise[desk->numero[i].position] - desk->mise[desk->numero[numJoueur].position]);
desk->mise[desk->numero[i].position] = desk->mise[desk->numero[numJoueur].position];	// Et les autres equilibrent
}
}
}
// else : rien du tout, le joueur ne continue pas le tour
}
*/

// Renvoie true si quelqu'un n'a plus d'argent
bool personneAuTapis(Table *desk){
	bool booleen = true;
	int i;
	for (i = 0; i < NBJOUEURS; i++){
		if (desk->numero[i].argent == 0)
			booleen = false;
	}
	return booleen;
}

// Gere la mise, a perfectionner surtout sur le retour utilisateur
void miser(Table *desk, int numJoueur, int choix){
	int grosseMise = miseASuivre(desk);			// Très logiquement, avec les conditions de cette fonction, si un joueur est au tapis, la plus grosse mise de la table est son tapis
	int montantArendre = 0;
	int i, j;

	if (choix == 0 && desk->mise[desk->numero[numJoueur].position] >= grosseMise)	// S'il ne mise rien et qu'il a précédemment misé assez
		joueurCheck();

	else if (choix < 0)
		joueurCouche();

	else if (choix >= desk->numero[numJoueur].argent && personneAuTapis(desk)){	// S'il mise tout ce qu'il a et que personne n'est au tapis, il fait tapis
		desk->mise[desk->numero[numJoueur].position] += desk->numero[numJoueur].argent;
		desk->pot += desk->numero[numJoueur].argent;

		for (i = 0; i < NBJOUEURS; i++)	// On parcourt les joueurs
		{
			if (i == desk->numero[numJoueur].position)
				break;
			else if (desk->mise[i] > desk->numero[numJoueur].argent){		// Si l'un a misé plus
				for (j = 0; j < NBJOUEURS; j++)					// On cherche son numéro 
				{
					if (desk->numero[j].position == i)				// Quand on l'a obtenu
					{
						montantArendre = (desk->mise[i] - desk->numero[numJoueur].argent);	// On calcule ce qu'il a misé de plus
						desk->numero[j].argent += montantArendre;	// On lui rembourse
						desk->pot -= montantArendre;	// Et on actualise le pot
					}
				}
			}
			desk->mise[i] = desk->numero[numJoueur].argent;	// Enfin, on modifie sa mise pour qu'elle corresponde au tapis
		}

		joueurFaitTapis(desk->numero[numJoueur].argent);

		desk->numero[numJoueur].argent = 0;
	}

	else if (choix + desk->mise[desk->numero[numJoueur].position] >= miseASuivre(desk) && personneAuTapis(desk)){ // S'il mise au dessus de la mise à suivre et que personne n'est au tapis
		desk->numero[numJoueur].argent -= choix;
		desk->mise[desk->numero[numJoueur].position] += choix;
		desk->pot += choix;
		joueurMise(choix);
	}

	else if (!personneAuTapis(desk) && (choix + desk->mise[desk->numero[numJoueur].position]) >= miseASuivre(desk)) { // S'il y a un tapis et qu'il mise au dessus de celui-ci
		desk->pot += (grosseMise - desk->mise[desk->numero[numJoueur].position]);  // On augmente le pot de ce qu'il lui reste à remplir pour atteindre le tapis
		desk->numero[numJoueur].argent -= (grosseMise - desk->mise[desk->numero[numJoueur].position]); // On lui retire cette somme de sa caisse
		desk->mise[desk->numero[numJoueur].position] = grosseMise;
	}

	else if (choix < 0)
		joueurCouche();

	else
		choixInvalide();
}

// Renvoie ce qu'un joueur a déjà misé ce tour-ci
int miseJoueur(Table *desk, int numJoueur){
	int mise = 0;

	mise = desk->mise[desk->numero[numJoueur].position];

	return mise;
}



void joueurCheck(){
	puts("Le joueur check.\n");
}

void joueurMise(int mise){
	printf("Le joueur mise %d.\n", mise);
}

void joueurFaitTapis(int valeurTapis){
	printf("Le joueur fait tapis a %d.\n", valeurTapis);
}

void joueurCouche(){
	puts("Le joueur jette sa main.\n");
}

void choixInvalide(){
	puts("Le choix n'est pas valide, veuillez recommencer.\n");
}

// Aide pour tester ses fonctions
void afficherMises(Table *desk){
	int i;
	for (i = 0; i < NBJOUEURS; i++){
		printf("%d ", desk->mise[i]);
	}
	puts("\n");
}
