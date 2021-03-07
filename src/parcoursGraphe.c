#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "reseauAccesseur.h"
#include "parcoursGraphe.h"

struct s_itineraire{
	Gare depart; //gare de depart de l'itineraire
	Gare arrive; //gare d'arrivée
	int temps; //temps de trajet
	Trajet liste[30]; //liste des trajets
};

struct s_sommet{
	Gare gare; //A quelle gare correspond le sommet
	Gare pere; //la gare precedente
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

int ajoutSommet(Ensemble graphe, Trajet tr, Gare g, Sommet sPere){
	//allocation d'espace
	Sommet sommet = (Sommet) malloc(sizeof(struct s_sommet));
	if ( sommet==NULL) {
		printf("ERREUR ALLOCATION MEMOIRE GRAPHE/RACINE\n");
		return 1;
	}
	//ajout des informations du sommet
	sommet->gare = gareArvDuTrajet(tr);
	sommet->pere = g;
	sommet->etat = 0;
	sommet->distance = tempsDuTrajet(tr) + sPere->distance;
	sommet->previous = graphe->tail;
	graphe->tail->next = sommet; 
	graphe->tail = sommet;
	graphe->nbSommets++;
	printf("On ajoute le sommet %s en %d min\n",nomDeGare(sommet->gare), sommet->distance);
	return 0;
}

int majDistance(Trajet tr, Sommet s, Sommet sPere){
	if (s->distance > tempsDuTrajet(tr)+ sPere->distance){
		s->distance = tempsDuTrajet(tr) + sPere->distance;
		s->pere = sPere->gare;
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
					printf("On met a jour la distance de %s qui vaut mtn %d \n", nomDeGare(s->gare), s->distance);
				}
			}
			s = s->next;
		}
		//si aucun sommet ne correspond au trajet, alors on l'ajoute
		if (trouve == 0) {
			ajoutSommet(graphe, tr, g, sommet);
		}
		tr = trajetNext(tr);
	}
	return 0;	
}


Ensemble initialisationGraphe(Reseau r, Gare gDep){
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
	graphe->head = racine;
	graphe->tail = racine;
	graphe->nbSommets = 1;
	//on init les premiers voisins
	testVoisin(graphe,racine);
	return graphe;
}



Itineraire rechercheItinireraire(Reseau r, Gare gDep, Gare gArv){ 
//Pour l'appeller on peut passer en parametre rechercheItineraire(reseau, rechercheGare(reseau, char* nom),rechercheGare(reseau, char* nom) )
	if (gDep == NULL || gArv == NULL) {
		printf("Au moins une des gares n'exsitent pas\n");
		return NULL;
	}
	//init de l'itinieraire
	Itineraire itineraire = (Itineraire) malloc(sizeof(struct s_itineraire));
	itineraire->depart = gDep;
	itineraire->arrive = gArv;
	//on init le graphe
	Ensemble graphe = initialisationGraphe(r, gDep);
	Sommet sTest;
	Sommet sSauv;
	int min;
	int compteur;
	//on fait 7 rep (a modif une fois que je saurais quand art le boucle)
	for (int i = 0; i < 7; ++i){
		sTest = graphe->head;
		compteur = 0;
		while (sTest->etat == 1){ //on prend le premier sommet dont tous les voisins n'ont pas etait teste
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
		testVoisin(graphe, sSauv); //on teste les voisins du sommet a la distance minimum qui n'a pas deja ete teste
	}
}






































Gare rechercheGare(Reseau r, char* nom){
	Gare act = gareHead(r);
	Gare sauv=NULL;
	// on parcourt toute les gares, et on regarde si l'une des gares correspond au char* passé en parametre
	for (int i=0 ; i<tailleReseau(r);i++){
		if (!strcmp(nomDeGare(act),nom)){
			sauv = act;
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