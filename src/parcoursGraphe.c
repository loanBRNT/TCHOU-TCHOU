#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "reseauAccesseur.h"
#include "parcoursGraphe.h"


Gare rechercheGare(Reseau r, char* nom){
	Gare act = gareHead(r);
	Gare sauv=NULL;
	// on parcourt toute les gares, et on regarde si l'une des gares correspond au char* passé en parametre
	for (int i=0 ; i<tailleReseau(r);i++){
		if (!strcmp(nomDeGare(act),nom)){
			sauv = act;
		}
		act = gareNext(act);
	}
	return sauv;
}


Trajet rechercheTrajet(Gare g, char* nom){
	//on verifie que le nb de trajet de la gare soit >0
	if (nbTrajetDeLaGare(g) == 0){
		return NULL;
	}
	Trajet act = trajetHeadDeLaGare(g);
	Trajet sauv = NULL;
	//on parcourt l'ensemble des trajets de la gare pour voir s'il y en a qui arrive à la gare donné en param
	for (int i = 0; i < nbTrajetDeLaGare(g); ++i)
	{
		if (!strcmp(gareArvDuTrajet(act),nom)){
			sauv = act;
		}
		act = trajetNext(act);
	}
	return sauv;
}