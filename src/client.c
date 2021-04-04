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
	//on regarde 1 à  1 les trajets de notre itineraire
	for (int i = 0; i < nbEtapeItineraire(voyage); ++i)
	{
		tr = listeTrajetItineraire(voyage, i);
		t = rechercheTrainCorres(r,g, tr);
		//si on a un train passant par le trajet
		if (t != NULL) {
			if (i == 0 ){
				printf("Depart de la gare %s via le train %s direction %s\n", nomDeGare(g) ,idTrain(t), nomDeGare(gareArvDuTrajet(tr)) );
			} else {
				if (strcmp(idTrain(t),idTrain(tSauv))) {
					printf("Correspondance a la gare %s avec le train %s direction %s \n",nomDeGare(g), idTrain(t), nomDeGare(gareArvDuTrajet(tr)) );
				}
			}
			g = gareArvDuTrajet(tr);
			tSauv = t ;	
			//sinon on arrete la fonction !
		} else {
			printf("ERROR : le trajet %s - %s n'a pas de train assigne !\n", nomDeGare(g), nomDeGare(gareArvDuTrajet(tr)) );
			break;
		}
	}
	if (t != NULL){
		printf("Arrive a la gare %s en %d minutes\n",nomDeGare(gareArvItineraire(voyage)), tempsItineraire(voyage) );
	}
}

Train rechercheTrainCorres(Reseau r,Gare gDepTr, Trajet tr){
	Train t = headTrainReseau(r);
	Train tSauv = NULL;
	Gare gTrain;
	Gare gDepTrain;
	int tempsTrajet;
	//on parcourt chaque train du reseau
	for (int i = 0; i < nbTrainReseau(r); ++i) {
		gDepTrain = gareDepItineraire(cheminTrain(t));
		//on parcourt chaque trajet de l'itineraire du train
		for (int j = 0; j < nbEtapeItineraire(cheminTrain(t)); ++j) {
			gTrain = gareArvDuTrajet(listeTrajetItineraire(cheminTrain(t), j ));
			//pourchaque gare arv du trajet on la compare a notre gare a nous
			if (!strcmp(nomDeGare(gTrain), nomDeGare(gareArvDuTrajet(tr)))) {
				//si les deux arrivees sont egales, on verifie qu'elles aient le meme depart
				if ( !strcmp(nomDeGare(gDepTr), nomDeGare(gDepTrain))) {
					//si c'est le cas, on stocke le train pour le renvoyer a l'issu des boucles
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

int modifArv(Reseau r, Itineraire it){
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
			if (cpt >= nbEtapeItineraire(it)){
				printf("ERROR : la gare ne fait pas partie du trajet \n");
				return 1;
			}
		}
		changerArv(it, cpt);
		printf("\n");
		printf("################################################\n");
		printf("#    La gare d'arivee a bien etait changee     #\n");
		printf("################################################\n");	
		printf("\n");
	}	
	return 0;
}