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


void affichageVoyage(Itineraire voyage){
	Trajet tr;
	Train t, tSauv;
	Train* liste;
	for (int i = 0; i < nbEtapeItineraire(voyage); ++i)
	{
		tr = listeTrajetItineraire(voyage, i);
		t = rechercheTrain(tr);
		if (i>0){
			if ( t == NULL ){
				t = tSauv;
			}
		}
		liste[i]=0;
		tSauv = t;
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

Train rechercheTrain(Trajet tr){
	return NULL;
}