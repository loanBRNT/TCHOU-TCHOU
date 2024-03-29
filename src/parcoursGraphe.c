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

struct s_itineraire{
	Gare depart; //gare de depart de l'itineraire
	Gare arrive; //gare d'arrivée
	int temps; //temps de trajet
	Trajet liste[30]; //liste des trajets
	int nbEtape;
};

struct s_sommet{
	Gare gare; //A quelle gare correspond le sommet
	Sommet pere; //la gare precedente
	int etat; //0 si jamais fait, 1 si deja fait,
	int distance; //distance a la gare de depart (-1) si infini
	Sommet next;
	Sommet previous;
};

struct s_ensemble{
	int nbSommets; //nb de sommets (nb de gare)
	Sommet head; //sommet en tete de liste
	Sommet tail; //sommet en queue de liste
};

int ajoutSommet(Ensemble graphe, Trajet tr, Sommet sPere){
	//allocation d'espace
	Sommet sommet = (Sommet) malloc(sizeof(struct s_sommet));
	if ( sommet==NULL) {
		printf("ERREUR ALLOCATION MEMOIRE GRAPHE/RACINE\n");
		return 1;
	}
	//ajout des informations du sommet
	sommet->gare = gareArvDuTrajet(tr);
	sommet->pere = sPere;
	sommet->etat = 0;
	sommet->next = NULL;
	sommet->distance = tempsDuTrajet(tr) + sPere->distance;
	sommet->previous = graphe->tail;
	graphe->tail->next = sommet; 
	graphe->tail = sommet;
	graphe->nbSommets++;
	return 0;
}

int majDistance(Trajet tr, Sommet s, Sommet sPere){ //on met a jour la distance si la nouvelle facon d'attenindre le sommet est plus rapide que l'ancienne
	if (s->distance > tempsDuTrajet(tr)+ sPere->distance){
		s->distance = tempsDuTrajet(tr) + sPere->distance;
		s->pere = sPere;
	}
	return 0;
}

int testVoisin(Ensemble graphe, Sommet sommet){
	sommet->etat = 1;
	Gare g = sommet->gare;
	Trajet tr = trajetHeadDeLaGare(g);
	Sommet s;
	int trouve;
	// on parcourt tout les trajets partant du sommet a tester
	for (int i=0; i<nbTrajetDeLaGare(g); i++) {
		s = graphe->head;
		trouve = 0;
		//pour chacun d'entre eux, on regarde si le trajet relie deux sommets existant en parcourant chaque sommet du graphe
		for (int j=0; j<graphe->nbSommets; j++){
			//si c'est le cas, on met a jour la distance entre le sommet trouve et la gare Gdep
			if (!strcmp(nomDeGare(gareArvDuTrajet(tr)),nomDeGare(s->gare))) {
				trouve = 1;
				if (s->etat == 0){ //on verif que le sommet na pas deja ete entierement fait (pour eviter de mettre a jour la distance de gdep)
					majDistance(tr,s,sommet);
				}
			}
			s = s->next;
		}
		//si aucun sommet ne correspond au trajet, alors on l'ajoute
		if (trouve == 0) {
			ajoutSommet(graphe, tr, sommet);
		}
		tr = trajetNext(tr);
	}
	return 0;	
}


Ensemble initialisationGraphe(Gare gDep){
	//alloc memoire
	Ensemble graphe = (Ensemble) malloc(sizeof(struct s_ensemble));
	Sommet racine = (Sommet) malloc(sizeof(struct s_sommet));
	if ( graphe == NULL || racine==NULL) {
		printf("ERREUR ALLOCATION MEMOIRE GRAPHE/RACINE\n");
		return NULL;
	}
	//init du sommet racine et du graphe de recherche
	racine->gare = gDep;
	racine->distance = 0;
	racine->etat = 1;
	racine->pere = NULL;
	graphe->head = racine;
	graphe->tail = racine;
	graphe->nbSommets = 1;
	//on init les premiers voisins
	testVoisin(graphe,racine);
	return graphe;
}

void freeGrapheRecherche(Ensemble graphe){
	Sommet sSup = graphe->head;
	Sommet sSauv;
	for (int i = 0 ; i < graphe->nbSommets ; i++ ){
		sSauv = sSup->next;
		free(sSup);
		sSup = sSauv;
	}
	free(graphe);
}

Itineraire rechercheItineraire(Reseau r, Gare gDep, Gare gArv){ 
//Pour l'appeller on peut passer en parametre rechercheItineraire(reseau, rechercheGare(reseau, char* nom),rechercheGare(reseau, char* nom) )
	if (gDep == NULL || gArv == NULL) {
		printf("Au moins une des gares n'exsitent pas\n");
		return NULL;
	}
	if ((nbTrajetDeLaGare(gDep) == 0) || (nbTrajetDeLaGare(gArv) == 0)) {
		printf("ERROR : UNE DES GARES ARRIVEE/DEPART NE POSSEDE PAS DE TRAJET\n");
		return NULL;
	}
	//init de l'itinieraire
	Itineraire itineraire = (Itineraire) malloc(sizeof(struct s_itineraire));
	itineraire->depart = gDep;
	itineraire->arrive = gArv;
	//on init le graphe
	Ensemble graphe = initialisationGraphe(gDep);
	Sommet sTest;
	Sommet sSauv;
	int min;
	int compteur;
	int trouve=0;
	while (trouve ==0){
		sTest = graphe->head;
		compteur = 0;
		while (sTest->etat == 1){ //on prend le premier sommet dont tous les voisins n'ont pas etait teste
			if (sTest->next == NULL) {
				printf("ERREUR AUCUN TRAJET N'A PU ETRE TROUVE ENTRE LES DEUX GARES\n");
				freeGrapheRecherche(graphe);
				return NULL;
			}
			sTest = sTest->next;
			compteur++;
		}
		sSauv = sTest; //une fois fait, on stocke sa distance a la gare de Dep dans min et son adresse dans sSauv
		min = sTest->distance;
		//on compare la distance de chaque sommet à la gare Dep, on prend le minimum pur lui verifier ses voisins
		for (int j = compteur+1 ; j < graphe->nbSommets ; j++){
			sTest = sTest->next;
			if ((min > sTest->distance)){
				if (sTest->etat == 0) { //on regarde si ce minimum n'a pas deja ete verifie
					min = sTest->distance;
					sSauv = sTest; //si c'est ok, on stocke sa valeur de distance dans min, et son adresse dans sSauv
				}
			}
		}
		if (!strcmp(nomDeGare(sSauv->gare),nomDeGare(gArv))){
			trouve = 1;
		}
		testVoisin(graphe, sSauv); //on teste les voisins du sommet a la distance minimum qui n'a pas deja ete teste
	}
	//on sauvegarde les infos dans notre structure itineraire
	itineraire->temps = sSauv->distance;
	int i = 0;
	sTest = sSauv;
	//on parcorut une fois pour savoir le nombre d'etape dans l'itineraire
	while (sTest->pere != NULL){
		i++;
		sTest = sTest->pere;
	}
	itineraire->nbEtape = i;
	//on remplit la liste des trajets, en faisant attention a l'ordre dep -> arv
	for (int j = i; j > 0; j--)
	{
		itineraire->liste[j-1] = rechercheTrajet(sSauv->pere->gare, sSauv->gare);
		sSauv = sSauv->pere;
	}
	freeGrapheRecherche(graphe); //On libere la memoire du graphe et des sommets
	return itineraire;
}

Gare rechercheGare(Reseau r, char* nom){
	Gare act = gareHead(r);
	Gare sauv=NULL;
	// on parcourt toute les gares, et on regarde si l'une des gares correspond au char* passé en parametre
	for (int i=0 ; i<tailleReseau(r);i++){
		if (!strcmp(nomDeGare(act),nom)){
			return act;
		}
		act = gareNext(act);
	}
	return sauv;
}


Trajet rechercheTrajet(Gare gDep, Gare gArv){
	//on verifie que le nb de trajet de la gare soit >0
	if (nbTrajetDeLaGare(gDep) == 0){
		return NULL;
	}
	Trajet act = trajetHeadDeLaGare(gDep);
	Trajet sauv = NULL;
	//on parcourt l'ensemble des trajets de la gare pour voir s'il y en a qui arrive à la gare donné en param
	for (int i = 0; i < nbTrajetDeLaGare(gDep); ++i)
	{
		if (!strcmp(nomDeGare(gareArvDuTrajet(act)), nomDeGare(gArv))){
			sauv = act;
		}
		act = trajetNext(act);
	}
	return sauv;
}

Itineraire creerItineraireVide(){
	Itineraire itineraire = (Itineraire) malloc(sizeof(struct s_itineraire));
	itineraire->nbEtape = 0;
	itineraire->temps = 0;
	return itineraire;
}

int ajouteTrajetItineraire(Itineraire it, Gare g, Trajet tr){
	//on regarde si c'est le premier trajet de l'itineraire
	if (it->nbEtape == 0){
		it->depart = g;
	}
	//on change l'arrivee
	it->arrive = gareArvDuTrajet(tr);
	//on place le trajet a la suite en memoire
	it->liste[it->nbEtape] = tr;
	it->nbEtape++;
	//on met a jour le temps
	it->temps = it->temps + tempsDuTrajet(tr);
	return 0;
}

Itineraire changerArv(Itineraire it, int i){
	it->nbEtape = i+1;
	it->arrive = gareArvDuTrajet(it->liste[i]);
	return it;
}

Itineraire itineraireRep(Reseau r, Itineraire it, char* nomDep, char* nomArv){
	it->depart = rechercheGare(r, nomDep);
	it->arrive = rechercheGare(r, nomArv);
	return it;
}

Itineraire modifItineraireTrain(Train t, int i){
	//on regarde si c'est la gare a enlever est au premier trajet
	if (i == 0){
		cheminTrain(t)->depart = gareArvDuTrajet(cheminTrain(t)->liste[0]);
		//on decale de 1 tous les autres trajets
		for (int j=0 ; j+1 < nbEtapeItineraire(cheminTrain(t)) ; j++) {
			cheminTrain(t)->liste[j]=cheminTrain(t)->liste[j+1];
		}
		cheminTrain(t)->nbEtape--;
	//on regarde si la gare a retirer est la derniere de l'itineraire, si oui on change l'arrivée en la ramenant à la gare précédente
	} else if (i == cheminTrain(t)->nbEtape) {
		cheminTrain(t)->arrive = gareArvDuTrajet(cheminTrain(t)->liste[cheminTrain(t)->nbEtape-2]);
		cheminTrain(t)->nbEtape--;
	//sinon, on regarde si on est plus proche du début ou de la fin
		//si c'est la fin, on ramene juste l'arrivee à la gare précédente
	} else if (i > (cheminTrain(t)->nbEtape / 2) - 1){
		cheminTrain(t)->arrive = gareArvDuTrajet(cheminTrain(t)->liste[i-2]);
		cheminTrain(t)->nbEtape = i-1;
		//si c'est le début, on ramène le départ à la gare suivante
	} else {
		cheminTrain(t)->depart = gareArvDuTrajet(cheminTrain(t)->liste[i]);
		//Et on décale tous les trajets de i+1 place
		for (int j=0 ; j+i+1 < nbEtapeItineraire(cheminTrain(t)) ; j++) {
			cheminTrain(t)->liste[j]=cheminTrain(t)->liste[j+i+1];
		}
		cheminTrain(t)->nbEtape = cheminTrain(t)->nbEtape - 1 - i;
	}
	printf("\n");
	printf("****************************** WARNING *****************************\n");
	printf("      Le train %s est raccourcit entre %s et %s\n", idTrain(t), nomDeGare(cheminTrain(t)->depart), nomDeGare(cheminTrain(t)->arrive));
	printf("********************************************************************\n");
	printf("\n");
	return cheminTrain(t);
}
	
Itineraire modifItineraireTrainTrajet(Train t, int i){
	//meme principe que la fonction précédente
	if (i == 0){
		cheminTrain(t)->depart = gareArvDuTrajet(cheminTrain(t)->liste[0]);
		for (int j=0 ; j+1 < nbEtapeItineraire(cheminTrain(t)) ; j++) {
			cheminTrain(t)->liste[j]=cheminTrain(t)->liste[j+1];
		}	
		cheminTrain(t)->nbEtape--;
	} else if (i == cheminTrain(t)->nbEtape-1){
		cheminTrain(t)->arrive = gareArvDuTrajet(cheminTrain(t)->liste[cheminTrain(t)->nbEtape-2]);
		cheminTrain(t)->nbEtape--;
	} else if (i > (nbEtapeItineraire(cheminTrain(t)) / 2)) {
		cheminTrain(t)->arrive = gareArvDuTrajet(cheminTrain(t)->liste[i-1]);
		cheminTrain(t)->nbEtape = i;
	} else {
		cheminTrain(t)->depart = gareArvDuTrajet(cheminTrain(t)->liste[i]);
		for (int j=0 ; j+i+1 < nbEtapeItineraire(cheminTrain(t)) ; j++) {
			cheminTrain(t)->liste[j]=cheminTrain(t)->liste[j+i+1];
		}
		cheminTrain(t)->nbEtape = cheminTrain(t)->nbEtape - 1 - i;
	}
	printf("\n");
	printf("****************************** WARNING *****************************\n");
	printf("      Le train %s est raccourcit entre %s et %s\n", idTrain(t), nomDeGare(cheminTrain(t)->depart), nomDeGare(cheminTrain(t)->arrive));
	printf("********************************************************************\n");
	printf("\n");
	return cheminTrain(t);
}


// ACCESSEUR ###################################

Gare gareDepItineraire(Itineraire it){
	return it->depart;
}

Gare gareArvItineraire(Itineraire it){
	return it->arrive;
}

int tempsItineraire(Itineraire it){
	return it->temps;
}

Trajet listeTrajetItineraire(Itineraire it, int rang){
	return it->liste[rang];
}

int nbEtapeItineraire(Itineraire it){
	return it->nbEtape;
}