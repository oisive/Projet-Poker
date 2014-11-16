#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "unittest.h"

// Initialise la table passée en paramètre
void initialiserTable(Table *desk){
	int i; 
	desk->mise[MISEUR] = MISEDEPART;
	for (i = 1; i < NBJOUEURS; i++){
		if (i != MISEUR)	// securité
		desk->mise[i] = 0;
	}
	desk->pot = 0;
	for(i = 0 ; i < NBJOUEURS ; i++){
		desk->numero[i].main = creerMain();
		desk->numero[i].taille = TAILLECOMBINAISON;
		desk->numero[i].mainAnalysee[desk->numero[i].taille];
		desk->numero[i].argent = ARGENT;
		if (desk->numero[i].position == MISEUR)
			desk->numero[i].argent -= MISEDEPART;
		desk->numero[i].position = i;
	}
}

// Crée une table et l'initialise DECONSEILLE
Table creerTable(){
	int i; 
	Table desk;
	desk.mise[MISEUR] = MISEDEPART;
	desk.pot = calculPot(&desk);
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
		printf("Le joueur a mise %d jetons\n", desk->mise[desk->numero[i].position]);
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
	for (i = 1; i < NBJOUEURS; i++){
		desk->mise[i] = 0;
	}
}

void resetTour(Table *desk){
	resetMise(desk);
	resetPot(desk);
	changementPosition(desk);
}

// Regarde quel joueur doit mettre la grosse blind et lui prend la valeur de la grosse blind
void blindEntree(Table *desk){
	int i;

	for (i = 0; i < NBJOUEURS; i++){
		if (desk->numero[i].position == MISEUR){
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


void faitTapis(Table *desk, int numJoueur, int decision){ // Lui demander s'il fait tapis, stocker dans décision, 0 signifie non, le reste oui
	int i;
	int grosseMise = miseASuivre(desk);

	if (!peutSuivre(desk, numJoueur) && decision){ // S'il ne peut pas suivre mais fait tapis
		desk->mise[desk->numero[numJoueur].position] = desk->numero[numJoueur].argent; // Il met tout en jeu
		for (i = 0; i < NBJOUEURS; i++){
			if (desk->mise[desk->numero[i].position] == grosseMise){
				desk->numero[i].argent += (desk->mise[desk->numero[i].position] - desk->mise[desk->numero[numJoueur].position]);
				desk->mise[desk->numero[i].position] = desk->mise[desk->numero[numJoueur].position];	// Et les autres equilibrent
			}
		}
	}
	// else : rien du tout, le joueur ne continue pas le tour
}

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
	int grosseMise = miseASuivre(desk);

	if (choix == 0 && desk->mise[desk->numero[numJoueur].position] >= grosseMise)
		joueurCheck();
	else if (choix + desk->mise[desk->numero[numJoueur].position] >= miseASuivre(desk) && personneAuTapis(desk)){
		desk->numero[numJoueur].argent -= choix;
		desk->mise[desk->numero[numJoueur].position] += choix;
		desk->pot += choix;
		joueurMise(choix);
	}
	else if (choix < 0)
		joueurCouche();
	else
		choixInvalide();
}


void joueurCheck(){
	puts("Le joueur check.\n");
}

void joueurMise(int mise){
	printf("Le joueur mise %d.\n", mise);
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
