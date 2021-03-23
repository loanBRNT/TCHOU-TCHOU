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
#include "client.h"

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
		printf( "%c%c%c%c",p->numPlace[0],p->numPlace[1],p->numPlace[2],p->numPlace[3]);
		v = p->head;
		while (p->nbVoyageur > 0){
			fprintf(fichierVoyageur, "/%s:%s:%c%c%c%c:",v->nom, v->prenom, v->id[0], v->id[1], v->id[2], v->id[3]);
			printf("/%s:%s:%c%c%c%c:",v->nom, v->prenom, v->id[0], v->id[1], v->id[2], v->id[3]);
			g = gareDepItineraire(v->voyage);
			for (int i = 0; i < nbEtapeItineraire(v->voyage); ++i)
			{
				tr = listeTrajetItineraire(v->voyage, i);
				fprintf(fichierVoyageur, "%s-%s:",nomDeGare(g),nomDeGare(gareArvDuTrajet(tr)));
				printf( "%s-%s:",nomDeGare(g),nomDeGare(gareArvDuTrajet(tr)));
				g = gareArvDuTrajet(tr);
			}
			fprintf(fichierVoyageur, "/");
			printf("/");
			p->nbVoyageur--;
			v = v->next;
		}
		fprintf(fichierVoyageur, "\n");
		printf("\n");
	}
	fprintf(fichierVoyageur, "\n");
	printf("\n");
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

Voyageur mettreSurUnePlace(Reseau r, Train t, Gare gLim, Gare gDep, Itineraire it){
	Place pDef = placeDuTrain(t, 0);
	Trajet trTest, trVoy;
	Gare gDepTest, gDepVoy;
	Voyageur vTest;
	Itineraire voyageTest;
	int commun, trouve = 0;
	int j = 0;
	for (int l = 0; l < 10; ++l) {
		Place p = placeDuTrain(t, l);
		if (p->nbVoyageur == 0){
			if (trouve == 0){
				pDef = p;
			}
		} else {
			vTest = p->head;
			commun = 0;
			for (int k = 0; k < p->nbVoyageur; ++k)
			 {
			 	voyageTest = vTest->voyage;
				gDepTest = gareDepItineraire(voyageTest);
				for (int i = 0; i < nbEtapeItineraire(voyageTest); ++i) {
					j=0;
					gDepVoy = gDep;
					trTest = listeTrajetItineraire(voyageTest, i);
					printf("VOYAGEUR SUR LA PLACE %s : %s-%s\n",vTest->id, nomDeGare(gDepTest), nomDeGare(gareArvDuTrajet(trTest)));
					while (strcmp(nomDeGare(gDepVoy),nomDeGare(gLim)))	{
						trVoy = listeTrajetItineraire(it, j);
						printf("VOYAGEUR A METTRE : %s-%s\n",nomDeGare(gDepVoy), nomDeGare(gareArvDuTrajet(trVoy)));
						if (!strcmp(nomDeGare(gareArvDuTrajet(trTest)), nomDeGare(gareArvDuTrajet(trVoy)))){
							if (!strcmp(nomDeGare(gDepTest),nomDeGare(gDepVoy))){
								commun = 1;
							}
						}
						j++;
						gDepVoy = gareArvDuTrajet(trVoy);
					}
					gDepTest = gareArvDuTrajet(trTest);
				}
				vTest = vTest -> next;
			}
			if (commun == 0) {
				printf("Yo : %s\n", p->numPlace);
				trouve = 1;
				pDef = p;
			}	
		}
	}
	printf("La place choisit est : %s\n",pDef->numPlace );
	Voyageur v = (Voyageur) malloc(sizeof(struct s_voyageur));
	Itineraire itPourPlace = creerItineraireVide();
	Gare g = gareDepItineraire(it);
	j=0;
	while (strcmp(nomDeGare(gDep),nomDeGare(g))){
		trVoy = listeTrajetItineraire(it, j);
		j++;
		g = gareArvDuTrajet(trVoy);
	}
	while (strcmp(nomDeGare(gDep),nomDeGare(gLim))){
		trVoy = listeTrajetItineraire(it, j);
		ajouteTrajetItineraire(itPourPlace, gDep, trVoy);
		j++;
		gDep = gareArvDuTrajet(trVoy);
	}
	if (pDef->nbVoyageur == 0){
		pDef->head = v;
	} else {
		pDef->tail->next = v;
		pDef->tail = v;
	}
	v->next = NULL;
	pDef->nbVoyageur++;
	v->voyage = itPourPlace;
	return v;
}


Voyageur creerVoyageur(Reseau r, Itineraire it){
	Voyageur v = (Voyageur) malloc(sizeof(struct s_voyageur));
	printf("\n\n");
	printf("################################################\n");
	printf("#               Indiquez votre Nom             #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",v->nom);
	fflush(stdin);
	printf("\n\n");
	printf("################################################\n");
	printf("#             Indiquez votre Prenom            #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",v->prenom);
	fflush(stdin);
	Trajet tr;
	Train t, tSauv;
	Gare g = gareDepItineraire(it);
	Train listeT[20]; //contrainte max 20 trains differents
	Gare listeG[20];
	int cpt=1;
	for (int i = 0; i < nbEtapeItineraire(it); ++i)
	{
		tr = listeTrajetItineraire(it, i);
		t = rechercheTrain(r,g, tr);
		if (i == 0 ) {
			listeT[0]=t;
		} else if (strcmp(idTrain(t),idTrain(tSauv))) {
			listeT[cpt] = t;
			listeG[cpt-1] = g;
			cpt++;
		}
		g = gareArvDuTrajet(tr);
		tSauv = t ;
	}
	listeG[cpt-1]=g;
	g = gareDepItineraire(it);
	tirerNumVoyageur(r, v);
	for (int i = 0; i < cpt; ++i){
		printf("%d/%d\n",i,cpt );
		printf("On va chercher une place pour l'itineraire allant de %s a %s avec le train %s \n",nomDeGare(g), nomDeGare(listeG[i]), idTrain(listeT[i]));
		Voyageur vNouv = mettreSurUnePlace(r, listeT[i], listeG[i], g, it);
		for (int j = 0; j < strlen(v->nom); ++j)
		{
			vNouv->nom[j] = v->nom[j];
		}
		for (int j = 0; j < strlen(v->prenom); ++j)
		{
			vNouv->prenom[j] = v->prenom[j];
		}
		for (int j = 0; j < strlen(v->id); ++j)
		{
			vNouv->id[j] = v->id[j];
		}
		g = listeG[i];
	}
	return v;
}


void tirerNumVoyageur(Reseau r, Voyageur v){
	Train t = headTrainReseau(r);
	Place p;
	int nbVoyageur = 0;
	for (int i = 0; i < nbTrainReseau(r); ++i) {
		for (int j = 0; j < 10; ++j) {
			nbVoyageur = nbVoyageur + nbVoyageurSurLaPlace(placeDuTrain(t,j));
		}
		t = trainNext(t);
	}
	nbVoyageur++;
	itoa(nbVoyageur, v->id, 10);
	v->id[4]='\0';
	for (int i = strlen(v->id); i < 4; ++i) {
		v->id[3]=v->id[2];
		v->id[2]=v->id[1];
		v->id[1]=v->id[0];
		v->id[0]='0';
	}
	int cpt = 0;
	do {
		nbVoyageur = nbVoyageur - 1000;
		cpt++;
	} while (nbVoyageur > 0);
	v->id[0]=64 + cpt; //utilisation du code ascii
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
