#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "reseauAccesseur.h"
#include "parcoursGraphe.h"


Gare rechercheGare(Reseau r, char* nom){
	Gare act = gareHead(r);
	Gare sauv=NULL;
	for (int i=0 ; i<tailleReseau(r);i++){
		if (!strcmp(nomDeGare(act),nom)){
			sauv = act;
		}
		act = gareNext(act);
	}
	return sauv;
}