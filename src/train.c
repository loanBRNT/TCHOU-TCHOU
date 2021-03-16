#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "train.h"
#include "reseauAccesseur.h"
#include "itineraireAccesseur.h"
#include "voyageur.h"

struct s_train {
	char num[2]; //num d'identification du train
	Itineraire chemin; //l'itineraire du train
	Place place[10];
	Train next; //le train suivant dans la liste
	Train previous; //le train precedent dans la liste
};

Itineraire initItneraireTrain(Reseau r, FILE* fichierTrain){
	Itineraire ch = creerItineraireVide();
	char nomDep[20];
	char nomArv[20];
	char c;
	int i;
	Trajet tr;
	Gare g1, g2;
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
		g1 = rechercheGare(r, nomDep);
		g2 = rechercheGare(r, nomArv);
		tr = rechercheTrajet(g1, g2);
		ajouteTrajetItineraire(ch, g1, tr);
	}
	fgetc(fichierTrain); //on prend le saut de ligne
	return ch;
}


Train initTrain(Reseau r, FILE* fichierTrain, FILE* fichierVoyageur){
	Train t = (Train) malloc(sizeof(struct s_train));
	if (t == NULL){
		printf("ERREUR ALLOCATION MEMOIRE TRAIN\n");
		return NULL;
	}
	///on recup l'id du train
	t->num[0]= fgetc(fichierTrain);
	t->num[1]= fgetc(fichierTrain);
	fgetc(fichierTrain); //on recup l'espace
	t->chemin = initItneraireTrain(r, fichierTrain);
	if (tailTrainReseau(r) != NULL) {
		tailTrainReseau(r)->next = t;
	}
	t->previous = tailTrainReseau(r);
	t->next = NULL;
	for (int i = 0 ; i < 10 ; i++ ){
		//t->place[i] = initPlace(fichierVoyageur);
	}
	//fgetc(fichierVoyageur);
	return t;
}

int sauvTrain(Reseau r, FILE* fichierTrain){
	Train t = headTrainReseau(r);
	Train tSauv;
	Gare g;
	Trajet tr;
	for (int i = 0; i < nbTrainReseau(r); ++i)
	{
		fprintf(fichierTrain, "%c%c ",t->num[0],t->num[1]);
		g = gareDepItineraire(t->chemin);
		for (int i = 0; i < nbEtapeItineraire(t->chemin); ++i)
		{
			tr = listeTrajetItineraire(t->chemin, i);
			fprintf(fichierTrain, "%s-%s:",nomDeGare(g),nomDeGare(gareArvDuTrajet(tr)));
			g = gareArvDuTrajet(tr);
		}
		fprintf(fichierTrain, "\n");
		tSauv = t->next;
		free(t);
		t = tSauv;
	}
	return 0;
}