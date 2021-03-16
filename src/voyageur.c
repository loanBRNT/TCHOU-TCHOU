#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "train.h"
#include "voyageur.h"

struct s_voyageur {
	char id[4]; //le num d'identification
	char nom[30]; //le nom du voyageur
	char prenom[20]; //le prenom du voyageur
	Itineraire voyage; //l'itineraire du voyageur
	Voyageur next;
};

struct s_place {
	Voyageur head;
	int nbVoyageur;
	char numPlace[4];
};


Place initPlace(FILE* fichierVoyageur){
	Place p = (Place) malloc(sizeof(struct s_place));
	Voyageur v;
	for (int i = 0; i < 3; ++i)
	{
		p->numPlace[i]=fgetc(fichierVoyageur);
	}
	p->nbVoyageur = 0;
	if (fgetc(fichierVoyageur) == '\n'){
		p->head = NULL;
	} else {
		char c = ' ';
		while ( c != '\n' ) {
			v = initVoyageur(p, fichierVoyageur);
			if (p->nbVoyageur == 0){
				p->head = v;
			}
			p->nbVoyageur++;
			c = fgetc(fichierVoyageur);
		}
	}
	return p;
}



Voyageur initVoyageur(Place p, FILE* fichierVoyageur) {
	Voyageur v = (Voyageur) malloc(sizeof(struct s_voyageur));
	char c;
	int i;
	i = 0;
	c = fgetc(fichierVoyageur);
	do {
		v->nom[i] = c;
		i++;
		c = fgetc(fichierVoyageur);
	} while ( c != ':');
	v->nom[i] = '\0';
	i = 0;
	c = fgetc(fichierVoyageur);
	do {
		v->prenom[i] = c;
		i++;
		c = fgetc(fichierVoyageur);
	} while ( c != ':');
	v->prenom[i] = '\0';
	i = 0;
	c = fgetc(fichierVoyageur);
	do {
		v->id[i] = c;
		i++;
		c = fgetc(fichierVoyageur);
	} while ( c != ':');
	//parametrer itineraire
	return v;
}