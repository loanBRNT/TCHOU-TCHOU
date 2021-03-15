#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "itineraireAccesseur.h"
#include "voyageur.h"
#include "train.h"

struct s_train {
	char num[2]; //num d'identification du train
	Itineraire chemin; //l'itineraire du train
	Place tab[10];
	Train next; //le train suivant dans la liste
	Train previous; //le train precedent dans la liste
};

struct s_place {
	Voyageur head;
	Voyageur tail;
	int numPlace;
};

int initItneraireTrain(Reseau r, FILE* fichierTrain){
	Itineraire ch = creerItineraireVide();
	char nomDep[20];
	char nomArv[20];
	char c;
	int i;
	while (c != '\n') {
		i = 0;
		c = fgetc(fichierTrain);
		do {
			nomDep[i] = c;
			c = fgetc(fichierTrain);
			i++;
		} while (c != '-');
		nomDep[i] = '\0';
		i = 0;
		c = fgetc(fichierTrain);
		do {
			nomArv[i] = c;
			c = fgetc(fichierTrain);
			i++;
		} while (c != ':');
		nomArv[i] = '\0';
		c = fgetc(fichierTrain); //on verif si il y a un autre trajet apres
		fseek(fichierTrain, -1, SEEK_CUR); //on remet le curseur au bon endroit
	}
	return 0;
}


int initTrain(Reseau r, FILE* fichierTrain){
	Train t = (Train) malloc(sizeof(struct s_train));
	if (t == NULL){
		printf("ERREUR ALLOCATION MEMOIRE TRAIN\n");
		return 1;
	}
	///on recup l'id du train
	t->num[0]= fgetc(fichierTrain);
	t->num[1]= fgetc(fichierTrain);
	fgetc(fichierTrain); //on recup l'espace
	initItneraireTrain(r, fichierTrain);
	
	initVoyageur();
	return 0;
}