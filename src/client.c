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
	Gare g = gareDepItineraire(voyage);
	for (int i = 0; i < nbEtapeItineraire(voyage); ++i)
	{
		tr = listeTrajetItineraire(voyage, i);
		t = rechercheTrain(r,g, tr);
		if (i == 0 ){
			printf("Depart de la gare %s via le train %s direction %s\n", nomDeGare(g) ,idTrain(t), nomDeGare(gareArvDuTrajet(tr)) );
		} else {
			if (strcmp(idTrain(t),idTrain(tSauv))) {
				printf("Correspondance a la gare %s avec le train %s direction %s \n",nomDeGare(g), idTrain(t), nomDeGare(gareArvDuTrajet(tr)) );
			}
		}
		g = gareArvDuTrajet(tr);
		tSauv = t ;
	}
	printf("Arrive a la gare %s en %d minutes\n",gareArvItineraire(voyage), tempsItineraire(voyage) );
}

Train rechercheTrain(Reseau r,Gare gDepTr, Trajet tr){
	Train t = headTrainReseau(r);
	Train tSauv = NULL;
	Gare gTrain;
	Gare gDepTrain;
	int tempsTrajet;
	for (int i = 0; i < nbTrainReseau(r); ++i) {
		gDepTrain = gareDepItineraire(cheminTrain(t));
		for (int j = 0; j < nbEtapeItineraire(cheminTrain(t)); ++j) {
			gTrain = gareArvDuTrajet(listeTrajetItineraire(cheminTrain(t), j ));
			if (!strcmp(nomDeGare(gTrain), nomDeGare(gareArvDuTrajet(tr)))) {
				if ( !strcmp(nomDeGare(gDepTr), nomDeGare(gDepTrain))) {
					if (tSauv == NULL){
						tSauv = t;
						tempsTrajet = tempsDuTrajet(listeTrajetItineraire(cheminTrain(t), j ));
					} else {
						if ( tempsDuTrajet(listeTrajetItineraire(cheminTrain(t), j )) < tempsTrajet) {
							tempsTrajet = tempsDuTrajet(listeTrajetItineraire(cheminTrain(t), j ));
							tSauv = t;
						}
					}
				}
			}
			gDepTrain = gTrain;
		}
		t = trainNext(t);
	}
	return tSauv;
}

int reservation(Reseau r, Itineraire it){
	char nom[30];
	char prenom[20];
	printf("\n\n");
	printf("################################################\n");
	printf("#               Indiquez votre Nom             #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nom);
	fflush(stdin);
	printf("\n\n");
	printf("################################################\n");
	printf("#             Indiquez votre Prenom            #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",prenom);
	fflush(stdin);
	char * id = tirerNumVoyageur(r);
	creerVoyageur(nom, prenom, id, it);
}




char* tirerNumVoyageur(Reseau r){
	Train t = headTrainReseau(r);
	Place p;
	char id[5];
	int nbVoyageur = 0;
	for (int i = 0; i < nbTrainReseau(r); ++i) {
		for (int j = 0; j < 10; ++j) {
			nbVoyageur = nbVoyageur + nbVoyageurSurLaPlace(placeDuTrain(t,j));
		}
		t = trainNext(t);
	}
	nbVoyageur++;
	itoa(nbVoyageur, id, 10);
	id[4]='\0';
	for (int i = strlen(id); i < 4; ++i) {
		id[3]=id[2];
		id[2]=id[1];
		id[1]=id[0];
		id[0]='0';
	}
	int cpt = 0;
	do {
		nbVoyageur = nbVoyageur - 1000;
		cpt++;
	} while (nbVoyageur > 0);
	id[0]=64 + cpt; //utilisation du code ascii
	char* iden = id;
	return iden;
}