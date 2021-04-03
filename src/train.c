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

struct s_train {
	char num[3]; //num d'identification du train
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
	t->num[2]= '\0';
	fgetc(fichierTrain); //on recup l'espace
	t->chemin = initItneraireTrain(r, fichierTrain);
	if (tailTrainReseau(r) != NULL) {
		tailTrainReseau(r)->next = t;
	}
	t->previous = tailTrainReseau(r);
	t->next = NULL;
	for (int i = 0 ; i < 10 ; i++ ){
		t->place[i] = initPlace(r, fichierVoyageur);
	}
	fgetc(fichierVoyageur);
	return t;
}

int sauvTrain(Reseau r, FILE* fichierTrain, FILE* fichierVoyageur){
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
		sauvVoyageur(t, fichierVoyageur);
		tSauv = t->next;
		free(t);
		t = tSauv;
	}
	return 0;
}

int suppTrain(Reseau r, char* idIdentification){
	int trouve = 0;
	Train t = headTrainReseau(r);
	for (int i = 0; i < nbTrainReseau(r); ++i)
	{
		if (!strcmp(t->num, idIdentification)){
			trouve = 1;
			if (!trainPasVide(t)) {
				for (int i = 0; i < 10; ++i)
				{
					free(t->place[i]);
				}
				free(t->chemin);
				if (i == 0){
					t->next->previous = NULL;
					t=enleverTrainHead(r, t);
				} else if (i == nbTrainReseau(r)-1) {
					t->previous->next = NULL;
					t=enleverTrainTail(r, t);
				} else{
					t->previous->next = t->next;
					t->next->previous = t->previous;
					enleverTrain(r);
				}
				free(t);
			} else {
				printf("ERROR : IL Y A DES VOYAGEUR SUR CE TRAIN\nSUPPRESSION IMPOSSIBLE\n");
			}
		}
		t = trainNext(t);
	}
	if (trouve == 0) {
		printf("PAS DE TRAIN AVEC CE NUMERO\n");
		return 1;
	}	
	return 0;
}


Train ajouterTrain(Reseau r){
	Train t = (Train) malloc(sizeof(struct s_train));
	Itineraire it = creerItineraireVide();
	int num = nbTrainReseau(r)+1;
	int cpt = 0;
	while (num > 9){
		num = num - 10;
		cpt++;
	}
	t->num[0]=65 + cpt;
	t->num[1]=48 + num;
	t->num[2]='\0';

	cpt=1;
	int i = 0;
	char nomDep[30] = {0};
	char nomArv[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#            Voici la liste des Gares          #\n");
	printf("################################################\n");
	printf("\n");
	Gare g = gareHead(r);
	Gare g2;
	Trajet tr;
	for (int i=0; i<tailleReseau(r); i++){
		printf("%s | ",nomDeGare(g));
		g=gareNext(g);
	}
	printf("\n\n");
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare de Depart       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomDep);
	fflush(stdin);
	g = rechercheGare(r, nomDep);
	if (g == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		free(t);
		exit(1);
	}
	while (cpt == 1){
		printf("\n");
		printf("################################################\n");
		printf("#      Voici la liste des gares disponible     #\n");
		printf("################################################\n");	
		printf("\n");
		tr = trajetHeadDeLaGare(g);
		for (int i=0; i < nbTrajetDeLaGare(g) ; i++){
			printf("%s-%s en %d minutes\n",nomDeGare(g), nomDeGare(gareArvDuTrajet(tr)), tempsDuTrajet(tr));
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
		tr = rechercheTrajet(g,g2);
		if (tr != NULL ){
			ajouteTrajetItineraire(it, g, tr);
			g = g2;
			i++;
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
	t->chemin = it;
	for (int i = 1; i < 11; ++i)
	{
		t->place[i-1]=creerPlaceVide(t,i);
	}
	t->previous = tailTrainReseau(r);
	(tailTrainReseau(r))->next = t;
	ajtTrain(r, t);
	return t;
}


Train rechercheTrain(Reseau r, char* id){
	Train t = headTrainReseau(r);
	Train tSauv = NULL;
	for (int i = 0; i < nbTrainReseau(r); ++i)
	{
		if (!strcmp(t->num, id)){
			tSauv = t;
		}
	}
	return tSauv;
}

int trainPasVide(Train t){
	int pasVide = 0;
	for (int i=0 ; i < 10; i++){
		if (nbVoyageurSurLaPlace(t->place[i]) > 0) {
			pasVide = 1;
		}
	}
	return pasVide;
}

int gareDansTrain(Gare g, Train t){
	int trouve = 0;
	Gare gTest = gareDepItineraire(t->chemin);
	if (!strcmp(nomDeGare(g), nomDeGare(gTest))) {
			trouve = 1;
		}
	for (int i = 0; i < nbEtapeItineraire(t->chemin); ++i) {
		gTest = gareArvDuTrajet(listeTrajetItineraire(cheminTrain(t),i));
		if (!strcmp(nomDeGare(g), nomDeGare(gTest))) {
			trouve = 1;
		}
	}
	return trouve;
}

int trajetDansTrain(Trajet tr, Gare g, Train t){
	int trouve = 0;
	Gare gTest = gareDepItineraire(t->chemin);
	Trajet trTest;
	for (int i = 0; i < nbEtapeItineraire(t->chemin); ++i)
	{
		trTest = listeTrajetItineraire(t->chemin, i);
		if (!strcmp(nomDeGare(gareArvDuTrajet(trTest)), nomDeGare(gareArvDuTrajet(tr)))) {
			if (!strcmp(nomDeGare(g),nomDeGare(gTest))) {
				trouve = 1;
			}
		}
		gTest = gareArvDuTrajet(trTest);
	}
	return trouve;
}

int verifierTrainTrajet(Reseau r, Gare g, Trajet tr){
	Train t = headTrainReseau(r);
	int pb = 0;
	while (t != NULL) {
		if (gareDansTrain(g, t)){
			if (trainPasVide(t)){
				printf("Le Train %s utilise le trajet %s-%s et il y a des passagers dedans\n", idTrain(t), nomDeGare(g), nomDeGare(gareArvDuTrajet(tr)));
				pb = 1;
			} else {
				printf("Le Train %s utilise le trajet %s-%s mais il n'y a pas de passagers\n",idTrain(t), nomDeGare(g),nomDeGare(gareArvDuTrajet(tr)));
			}
		}
		t = t->next;
	}
	return pb;
}

int verifierTrain(Reseau r, Gare g){
	Train t = headTrainReseau(r);
	int pb = 0;
	while (t != NULL) {
		if (gareDansTrain(g, t)){
			if (trainPasVide(t)){
				printf("Le Train %s passe par la Gare %s et il y a des passagers dedans\n", idTrain(t), nomDeGare(g));
				pb = 1;
			} else {
				printf("Le Train %s passe par la Gare %s mais il n'y a pas de passagers\n",idTrain(t), nomDeGare(g) );
			}
		}
		t = t->next;
	}
	return pb;
}

int suppGareDansTrain(Reseau r,Gare g){
	Train t;
	Train tSauv= headTrainReseau(r);
	Gare gTest;
	for ( int j = 0; j < nbTrainReseau(r) ; j++){
		gTest = gareDepItineraire(tSauv->chemin);
		t = tSauv;
		if (gareDansTrain(g, t)) {
			if (nbEtapeItineraire(t->chemin) < 4 ){
				printf("\n");
				printf("********************** WARNING *********************\n");
				printf("*             Le train %s est supprimee            *\n", t->num);
				printf("****************************************************\n");
				printf("\n");
				tSauv = t->next;
				suppTrain(r, t->num);
				j--;
			} else {
				for (int i = 0 ; i < nbEtapeItineraire(t->chemin) ; i++ ){
					if (!strcmp(nomDeGare(gTest),nomDeGare(g))) {
						modifItineraireTrain(t, i);
					}
				gTest = gareArvDuTrajet(listeTrajetItineraire(t->chemin, i));
				}
				if (!strcmp(nomDeGare(gTest),nomDeGare(g))) {
					modifItineraireTrain(t, nbEtapeItineraire(t->chemin));
				}
				tSauv = t->next;
			}		
		} else {
			tSauv = t->next;
		}
	}
}

int suppTrajetDansTrain(Reseau r, Gare g, Trajet tr){
	return 0;
}






//accesseur ###############################################

Place placeDuTrain(Train t, int rang){
	return t->place[rang];
}

char* idTrain(Train t){
	return t->num;
}

Itineraire cheminTrain(Train t){
	return t->chemin;
}

Train trainNext(Train t){
	return t->next;
}

Train trainPrevious(Train t){
	return t->previous;
}