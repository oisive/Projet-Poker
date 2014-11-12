// analyseMain.cpp

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


