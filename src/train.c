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
	Voyageur head; //le voyageur en tete de liste
	Voyageur tail; //le voyaguer en queue de liste
	int nbPlace; //le nb de place totale du train
	int nbPassagers; //le nb de passager dans le train
};