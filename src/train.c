#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "voyageur.h"
#include "train.h"

struct s_train {
	int num; //num d'identification du train
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


int initTrain(Reseau r){




	initVoyageur();
	return 0;
}