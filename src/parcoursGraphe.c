#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "reseauAccesseur.h"
#include "parcoursGraphe.h"

struct s_itineraire{
	Gare depart; //gare de depart de l'itineraire
	Gare arrive; //gare d'arrivée
	int temps; //temps de trajet
	Trajet liste[30]; //liste des trajets
};

struct s_sommet{
	Gare gare; //A quelle gare correspond le sommet
	Trajet chemin; //le chemin qui amene à cette gare depuis la gare precedente
	int etat; //0 si jamais fait, 1 si deja fait,
	int distance; //distance a la gare de depart
	Sommet next;
	Sommet previous;
};

struct s_ensemble{
	int nbSommets; //nb de sommets (nb de gare)
	Sommet head; //sommet en tete de liste
	Sommet tail; //sommet en queue de liste
};

Ensemble initialisationGraphe(Reseau r, Gare gDep){
	Ensemble graphe = (Ensemble) malloc(sizeof(struct s_ensemble));
	Sommet racine = (Sommet) malloc(sizeof(struct s_sommet));
	racine->gare = gDep;
	racine->distance = 0;
	racine->etat = 1;
	Trajet tr;
}



Itineraire rechercheItinireraire(Reseau r, Gare gDep, Gare gArv){ 
//Pour l'appeller on peut passer en parametre rechercheItineraire(reseau, rechercheGare(reseau, char* nom),rechercheGare(reseau, char* nom) )
	if (gDep == NULL || gArv == NULL) {
		printf("Au moins une des gares n'exsitent pas\n");
		return NULL;
	}
	Itineraire itineraire = (Itineraire) malloc(sizeof(struct s_itineraire));
	itineraire->depart = gDep;
	itineraire->arrive = gArv;
	Ensemble graphe = initialisationGraphe(r, gDep);
}






































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