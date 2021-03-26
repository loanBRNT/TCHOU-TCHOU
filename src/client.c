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


void modifAjtTrajetFin(Reseau r, Itineraire it){
	Gare gDep = gareArvItineraire(it);
	char nomArv[30] = {0};
	int cpt=1;
	Trajet tr;
	Gare g2;
	while (cpt == 1){
		printf("\n");
		printf("################################################\n");
		printf("#      Voici la liste des gares disponible     #\n");
		printf("################################################\n");	
		printf("\n");
		tr = trajetHeadDeLaGare(gDep);
		for (int i=0; i < nbTrajetDeLaGare(gDep) ; i++){
			printf("%s-%s en %d minutes\n",nomDeGare(gDep), nomDeGare(gareArvDuTrajet(tr)), tempsDuTrajet(tr));
			tr = trajetNext(tr);
		}
		printf("\n\n");
		printf("################################################\n");
		printf("#      Tapez le nom de la Gare Suivante        #\n");
		printf("################################################\n");
		printf("\n");
		scanf("%s",nomArv);
		fflush(stdin);
		g2 = rechercheGare(r, nomArv);
		if (g2 == NULL ){
			printf("GARE INCONNUE\n");
		} else {
			tr = rechercheTrajet(gDep,g2);
		}
		if (tr != NULL ){
			ajouteTrajetItineraire(it, gDep, tr);
			gDep = g2;
		} else {
			printf("ERREUR : Trajet inexistant\n");
		}
		printf("################################################\n");
		printf("#      Ajoutez un Trajet supplementaire ?      #\n");
		printf("#              1- OUI                          #\n");
		printf("#              2- NON                          #\n");
		printf("################################################\n");
		printf("\n");
		scanf("%d",&cpt);
		fflush(stdin);
	}
}

void modifArv(Reseau r, Itineraire it){
	int cpt = 0;
	char nom[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#  Voici la liste des etapes que vous faites   #\n");
	printf("################################################\n");	
	printf("\n");
	Gare g = gareDepItineraire(it);
	for (int i = 0; i < nbEtapeItineraire(it); ++i) {
		printf("%s | ", nomDeGare(g));
		g = gareArvDuTrajet(listeTrajetItineraire(it, i));
	}
	printf("%s",nomDeGare(g));
	printf("\n\n");
	printf("################################################\n");
	printf("#        Ou vous voulez vous arreter ?         #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nom);
	fflush(stdin);
	g = rechercheGare(r, nom);
	if (g == NULL) {
		printf("ERREUR\n");
	} else if ( !strcmp(nomDeGare(g),nomDeGare(gareDepItineraire(it)))) {
		printf("LA GARE D'ARIVEE NE PEUT PAS ETRE CELLE D'ARIVEE\n");
	} else {
		while ( strcmp(nomDeGare(g),nomDeGare(gareArvDuTrajet(listeTrajetItineraire(it, cpt))))) {
			cpt++;
		}
		changerArv(it, cpt);
		printf("%s\n",nomDeGare(gareArvItineraire(it)));
		printf("\n");
		printf("################################################\n");
		printf("#    La gare d'arivee a bien etait changee     #\n");
		printf("################################################\n");	
		printf("\n");
	}	
}