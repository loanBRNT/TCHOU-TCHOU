#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "voyageur.h"

struct s_voyageur {
	int idNum; //le num d'identification
	char nom[30]; //le nom du voyageur
	char prenom[20]; //le prenom du voyageur
	Itineraire voyage; //l'itineraire du voyageur
};

int initVoyageur() {
	return 0;
}