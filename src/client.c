#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "train.h"
#include "voyageur.h"
#include "reseauAccesseur.h"
#include "itineraireAccesseur.h"
#include "client.h"
#include "trainVoyageurAccesseur.h"


void affichageVoyage(Reseau r, Itineraire voyage){
	Trajet tr;
	Train t, tSauv;
	Train liste[20];
	Gare g = gareDepItineraire(voyage);
	for (int i = 0; i < nbEtapeItineraire(voyage); ++i)
	{
		printf("BOUCLE : %d\n",i);
		tr = listeTrajetItineraire(voyage, i);
		printf("On cherche : %s-%s\n",nomDeGare(g),nomDeGare(gareArvDuTrajet(tr)));
		t = rechercheTrain(r,g, tr);
		printf("----- %s ----\n", nomDeGare(gareArvDuTrajet(tr)));
		if (i>0){
			if ( t == NULL ){
				printf("on a deux trains qui ont ce Trajet\n");
				t = tSauv;
				printf("le roya\n");
			}
		}
		printf("----- %s ----\n", nomDeGare(gareArvDuTrajet(tr)));
		liste[i]=t;
		printf("yo\n");
		tSauv = t;
		printf("%s\n",idTrain(liste[i]));
		printf("On a cherche : %s-%s\n",nomDeGare(g),nomDeGare(gareArvDuTrajet(tr)));
		g = gareArvDuTrajet(tr);
	}
	printf("Depart de la Gare %s via le train %s,\n",nomDeGare(gareDepItineraire(voyage)), idTrain(liste[0]) );
	tSauv = liste[0];
	for (int i = 1; i < nbEtapeItineraire(voyage); ++i)
	{
		t = liste[i];
		if ( t != tSauv ){
			tr = listeTrajetItineraire(voyage, i-1);
			printf("Correspondace a la Gare %s avec le train %s,\n",nomDeGare(gareArvDuTrajet(tr)),idTrain(t));
			tSauv = t;
		}
	}
	tr = listeTrajetItineraire(voyage, nbEtapeItineraire(voyage)-1);
	printf("Arrivee a la Gare %s en %d minutes.\n", nomDeGare(gareArvDuTrajet(tr)), tempsItineraire(voyage));
}

Train rechercheTrain(Reseau r,Gare gDepTr, Trajet tr){
	Train t = headTrainReseau(r);
	Train tSauv = NULL;
	Gare gTrain;
	Gare gDepTrain;
	for (int i = 0; i < nbTrainReseau(r); ++i) {
		printf("Nouveau Train\n");
		gDepTrain = gareDepItineraire(cheminTrain(t));
		for (int j = 0; j < nbEtapeItineraire(cheminTrain(t)); ++j) {
			gTrain = gareArvDuTrajet(listeTrajetItineraire(cheminTrain(t), j ));
			printf(": %s-%s\n", nomDeGare(gDepTrain), nomDeGare(gTrain));
			if (!strcmp(nomDeGare(gTrain), nomDeGare(gareArvDuTrajet(tr)))) {
				if ( !strcmp(nomDeGare(gDepTr), nomDeGare(gDepTrain))) {
					if (tSauv == NULL){
						printf("ok\n");
						tSauv = t;
					} else {
						printf("PAS ok\n");
						return NULL;
					}
				}
			}
			gDepTrain = gTrain;
		}
		t = trainNext(t);
	}
	return tSauv;
}