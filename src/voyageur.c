#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "train.h"
#include "voyageur.h"
#include "reseauAccesseur.h"
#include "itineraireAccesseur.h"
#include "trainVoyageurAccesseur.h"

struct s_voyageur {
	char id[5]; //le num d'identification
	char nom[30]; //le nom du voyageur
	char prenom[20]; //le prenom du voyageur
	Itineraire voyage; //l'itineraire du voyageur
	Voyageur next;
};

struct s_place {
	Voyageur head;
	Voyageur tail;
	int nbVoyageur;
	char numPlace[5];
};


Place initPlace(Reseau r, FILE* fichierVoyageur){
	Place p = (Place) malloc(sizeof(struct s_place));
	Voyageur v;
	for (int i = 0; i < 4; ++i)
	{
		p->numPlace[i]=fgetc(fichierVoyageur);
	}
	p->numPlace[4]='\0';
	p->nbVoyageur = 0;
	if (fgetc(fichierVoyageur) == '\n'){
		p->head = NULL;
		p->tail = NULL;
	} else {
		char c = ' ';
		while ( c != '\n' ) {
			v = initVoyageur(r, p, fichierVoyageur);
			if (p->nbVoyageur == 0){
				p->head = v;
			} else {
				p->tail->next = v;
			}
			p->tail = v;
			p->nbVoyageur++;
			c = fgetc(fichierVoyageur);
		}
	}
	return p;
}



Voyageur initVoyageur(Reseau r, Place p, FILE* fichierVoyageur) { //peut etre simplifie
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
	v->id[4]='\0';
	Itineraire ch = creerItineraireVide();
	char nomDep[20];
	char nomArv[20];
	i = 0;
	Trajet tr;
	Gare g1, g2;
	while (c != '/') {
		i = 0;
		c = fgetc(fichierVoyageur);
		do {
			nomDep[i] = c;
			c = fgetc(fichierVoyageur);
			i++;
		} while (c != '-');
		nomDep[i] = '\0';
		i = 0;
		c = fgetc(fichierVoyageur);
		do {
			nomArv[i] = c;
			c = fgetc(fichierVoyageur);
			i++;
		} while (c != ':');
		nomArv[i] = '\0';
		c = fgetc(fichierVoyageur); //on verif si il y a un autre trajet apres
		fseek(fichierVoyageur, -1, SEEK_CUR); //on remet le curseur au bon endroit
		g1 = rechercheGare(r, nomDep);
		g2 = rechercheGare(r, nomArv);
		tr = rechercheTrajet(g1, g2);
		ajouteTrajetItineraire(ch, g1, tr);
		v->voyage = ch;
	}
	fgetc(fichierVoyageur); //prendre le saut de ligne
	v->next = NULL;
	return v;
}

int sauvVoyageur(Train t, FILE* fichierVoyageur){
	Place p;
	Gare g;
	Trajet tr;
	Voyageur v;
	for (int i = 0; i < 10; ++i)
	{
		p = placeDuTrain(t, i);
		fprintf(fichierVoyageur, "%c%c%c%c",p->numPlace[0],p->numPlace[1],p->numPlace[2],p->numPlace[3]);
		v = p->head;
		while (p->nbVoyageur > 0){
			fprintf(fichierVoyageur, "/%s:%s:%c%c%c%c:",v->nom, v->prenom, v->id[0], v->id[1], v->id[2], v->id[3]);
			g = gareDepItineraire(v->voyage);
			for (int i = 0; i < nbEtapeItineraire(v->voyage); ++i)
			{
				tr = listeTrajetItineraire(v->voyage, i);
				fprintf(fichierVoyageur, "%s-%s:",nomDeGare(g),nomDeGare(gareArvDuTrajet(tr)));
				g = gareArvDuTrajet(tr);
			}
			fprintf(fichierVoyageur, "/");
			p->nbVoyageur--;
			v = v->next;
		}
		fprintf(fichierVoyageur, "\n");
	}
	fprintf(fichierVoyageur, "\n");
}


Voyageur rechercheVoyageur(Reseau r, char* idRecherche){
	Train t = headTrainReseau(r);
	Voyageur v, vSauv = NULL;
	Place p;
	for (int i = 0; i < nbTrainReseau(r); ++i) {
		for (int j = 0; j < 10; ++j) {
			p = placeDuTrain(t, j);
			if ( p->nbVoyageur > 0) {
				v = p->head;
				for (int k = 0; k < p->nbVoyageur+1; ++k) {
					if (!strcmp(v->id, idRecherche)){
						vSauv = v;
					}
					v = v->next;
				}
			}
		}
		t = trainNext(t);
	}
	return vSauv;
}


Voyageur creerVoyageur(char* nom, char* prenom, char* identifiant, Itineraire it){
	Voyageur v = (Voyageur) malloc(sizeof(struct s_voyageur));
		// pas finit



	return v;
}



// ACCESSEUR #####################################

int nbVoyageurSurLaPlace(Place p){
	return p->nbVoyageur;
}

char* idPlace(Place p){
	return p->numPlace;
}

Voyageur voyageurHeadPlace(Place p){
	return p->head;
}

Voyageur voyageurTailPlace(Place p){
	return p->tail;
}



char* idVoyageur(Voyageur v){
	return v->id;
}

char* nomVoyageur(Voyageur v){
	return v->nom;
}

char* prenomVoyageur(Voyageur v){
	return v->prenom;
}

Itineraire cheminVoyageur(Voyageur v){
	return v->voyage;
}

Voyageur voyageurNext(Voyageur v){
	return v->next;
}
