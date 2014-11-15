#include <stdio.h>
#include <stdlib.h>
#include "general.h"



int main(){

int probaCombinaison[NBCOMBINAISONS] = {55, 70, 85, 90, 95, 96, 97, 99, 100}; 
int compositionMain[TAILLECOMBINAISON] = {0, 5, 0, 11, 0, 12, 0, 2, 0, 4, 0};
Table desk; 
initialiserTable(&desk);
recapJoueur(&desk);
puts("\n");

desk.mise[0] = 100;
desk.mise[1] = 200;
updatePot(&desk);
updateArgent(&desk);

recapJoueur(&desk);
changementPosition(&desk);
resetPot(&desk);
puts("\n"); puts("\n");

desk.mise[0] = 100;
desk.mise[1] = 50;
updatePot(&desk);
updateArgent(&desk);
recapJoueur(&desk);
changementPosition(&desk);

system("pause"); 
return 0;
}
