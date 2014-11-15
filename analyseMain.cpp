#include <stdio.h>
#include <stdlib.h>
#include "general.h"
#include "unittest.h"	


void initTableau(int tab[], int taille);
void classerTableau(int tab[], int taille);
void classerTableau5(int tab[], int taille);
void afficherTableau(int tab[], int taille);
void combinaison(int *, int*);//remplacer le int
int suite(int *);
int couleur(int *);
int quintefl(int ,int );
int test(int *, int*);
int testbis(int tab[], int compt[]);

// Crée le mignon tableau de combinaisons
void creerTableauCombinaison(Main *main, int tableau[], int taille){
	int i;
	int j = 1; 
	unsigned int valeur;
	for(i = 0 ; i < NBCARTES_MAIN ; i++)
		{
			valeur = getIntVal(main->cartes_En_Main[i]);
			tableau[j] = valeur;
			j += 2;
		}
}

// Initialise le tableau {combinaison, valeurs}
void initTableau(int tab[], int taille){
	int i; 
	for(i = 0 ; i < taille ; i++){
		if(i % 2 == 0)
			tab[i] = 0; 
		else tab[i] = -1;
	}
}

// Classe ce tableau par valeurs croissantes
void classerTableau(int tab[], int taille){
	int i, j;
	int stockage = -1;
	for(i = 1 ; i < taille ; i += 2){
		for(j = i + 2 ; j < taille ; j += 2){
			if(tab[i] > tab[j]){
				stockage = tab[i]; 
				tab[i] = tab[j]; 
				tab[j] = stockage; 
			}
		}
	}
}

//Affiche le plateau dans la console
void afficherTableau(int tab[], int taille){
    int i;
    for(i = 0 ; i < taille ; i++)
        printf("%i ",tab[i]);
}

//Analyse la main pour les paires, doubles paires, brelans, full, carre
void combinaison(int tab[], int compteur[]){
    int i, k;
    int j = 0;
    i = 0;
	
    for(i ; i +1< 5 ; i++){ // ici les 5 sont la taille du tableau
        k = i;
        while(tab[k] == tab[k+1]){
            compteur[j]++;
            k++;
        }
        j++;
        k++;
        i=k;
        if(tab[k] != tab[k+1] && k+1<5){
            k++;
            i = k;
            j++;
        }
        i--;
    }
}


//Analyse la main pour les suites
int suite(int *tab){
    int i;
    for(i = 0 ; (i + 1) < 5 ; i++){
        if(tab[i] != (tab[i+1]-1))
            return -1;
    } return 4;
}

//Analyse la main pour les couleurs
int couleur(int *tab){
    int i;
    for(i=0; i+1<5; i++){
        if(tab[i]!=tab[i+1])
            return -1;
    } return 5;
}

//Analyse la main pour les quinteflush
int quintefl(int c, int s ){
    if(c==5 && s==4)
        return 8;
    return -1;
}

//Regroupement de toutes les analyses
int test(int *val, int*coul){
	int compt[5] ={1,1,1,1,1};
    classerTableau5(val, 5);
	combinaison(val,compt);
	classerTableau5(compt,5);

	int resultat = 0;
    if(quintefl(couleur(coul),suite(val))==8)
        resultat = 8;
    else if(couleur(coul) == 5)
        resultat =  5;
    else if (suite(val) == 4)
        resultat = 4;
    else if(testbis(val,compt)==7)
		resultat = 7;
    else if(testbis(val,compt)==6)
		resultat = 6;
	else if(testbis(val,compt)==3)
		resultat = 3;
	else if(testbis(val,compt)==2)
		resultat = 2;
	else if(testbis(val,compt)==1)
		resultat = 1;
	else resultat = 0;
	
	return resultat;
}

//Conversion de la fonction combinaison en INT
 int testbis( int tab[], int compt[]){


	int d = compt[4];//[taille-1]
	int ad = compt[3];//[taille-2]
	int resultat = 0;
	if(d==4)
		resultat = 7;
	else if (d==3){
		if(ad == 2)
			resultat = 6;
		else resultat = 3;
		}
	else if (d==2){
		if(ad == 2)
			resultat = 2;
		else resultat = 1;

		}	
	return resultat;

}

 /*

 int main(){
	 
	int tab0 [5] = {1,2,5,6,8};
	int coul0[5] = {1,0,1,1,1};
	

	int tab1[5] = {2,5,6,5,1};
	int coul1[5] = {1,0,1,1,1};


	int tab2[5] = {2,5,2,5,1};
	int coul2[5] = {1,0,1,1,1};
	

	int tab3[5] = {5,4,8,4,4};
	int coul3[5] = {1,0,1,1,1};
	

	int tab4[5] ={5,2,3,4,1};
	int coul4[5] = {1,0,1,1,1};
	

	int tab5[5]= {5,8,9,2,11};
	int coul5[5] = {1,1,1,1,1};


	int tab6[5] = {5,8,5,8,5};
	int coul6[5] = {1,0,1,1,1};


	int tab7[5] = {11,5,11,11,11};
	int coul7[5] = {1,0,1,1,1};

	int tab8[5] = {9,6,7,5,8};
	int coul8[5] = {2,2,2,2,2};
	
   
		
    assertEquals(test(tab0,coul0),0,"Rien");
	assertEquals(test(tab1,coul1),1,"Paire = 1");
	assertEquals(test(tab2,coul2),2,"Double paire = 2");
	assertEquals(test(tab3,coul3),3,"Brelan = 3");
	assertEquals(test(tab4,coul4),4,"Suite = 4");
	assertEquals(test(tab5,coul5),5,"Couleur = 5");
	assertEquals(test(tab6,coul6),6,"Full = 6");
	assertEquals(test(tab7,coul7),7,"Carre = 7");
	assertEquals(test(tab8,coul8),8,"Quinte Flush = 8");
	

    system("pause");
    return 0;

}
*/
 //classer un tableau de taille 5
 void classerTableau5(int tab[], int taille){
	int i, j;
	int stockage = -1;
	for(i = 0 ; i < taille ; i++){
		for(j = i + 1 ; j < taille ; j++){
			if(tab[i] > tab[j]){
				stockage = tab[i]; 
				tab[i] = tab[j]; 
				tab[j] = stockage; 
			}
		}
	}
}
