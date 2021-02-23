#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"

struct s_gare{
	char nomGARE[30]; //Le nom de la Gare
	int nbTrajet; //Le nombre de chemin passant par cette gare
	Trajet headListeTrajet; //Premier Trajet
	Trajet tailListeTrajet; //Dernier Trajet
	Gare next; //La gare suivante (numero +1)
	Gare previous; //La gare precedente (numero -1)
};

struct s_trajet{
	int ponderation; //le temps de transport
	char gareArrive[30]; //La gare d'arrivee du trajet
	Trajet next; //Indique le trajet suivant de la même gare. Par convention le dernier pointe sur NULL
};

struct s_reseau{
	Gare head; //Indice de la premiere gare
	Gare tail;
	int size; //taille du reseau (nombe de gare)
};

int initTrajet(Gare gareDepart, FILE* fichierTrajet){
	Trajet tr = (Trajet) malloc(sizeof(struct s_trajet));
	if (tr==NULL) {
		printf("ERREUR ALLOCATION ESPACE TRAJET\n");
		return 1;
	}
	if (gareDepart->nbTrajet==0) {
		gareDepart->headListeTrajet = tr;
		gareDepart->tailListeTrajet = tr;
	} else {
		gareDepart->tailListeTrajet->next = tr;
		gareDepart->tailListeTrajet = tr;
	}
	char ligne[100] = "";
	char caractere;
	int i=0;
	int centaine;
	int dizaine;
	int unite;
	do {
		caractere = fgetc(fichierTrajet);
		if (caractere !='\n') {
			tr->gareArrive[i] = caractere;
			i++;
		}
	} while (caractere != '-');
	tr->gareArrive[i-1] = '\0';
	caractere = fgetc(fichierTrajet);
	centaine = caractere - '0';
	caractere = fgetc(fichierTrajet);
	if (caractere != '\n'){
		dizaine = caractere - '0';
		caractere = fgetc(fichierTrajet);
		if (caractere != '\n') {
			unite = (int) caractere - '0';
			tr->ponderation = centaine*100 + dizaine*10 + unite;
			caractere = fgetc(fichierTrajet);
		} else {
			tr->ponderation = centaine*10 + dizaine;
		}
	} else {
		tr->ponderation = centaine;
	}
	tr->next = NULL;
	gareDepart->nbTrajet++;
	return 0;
}

int initGare(Reseau ensembleGare, FILE* fichierReseau, FILE* fichierTrajet){
	Gare g = (Gare) malloc(sizeof(struct s_gare));
	if (g==NULL) {
		printf("ERREUR d'alocation d'espace\n");
		return 1;
	}
	char caractere;
	int i = 0;
	do {
		caractere = fgetc(fichierReseau);
		g->nomGARE[i] = caractere;
		i++;
	}while (caractere != '\n');
	g->nomGARE[i-1]='\0';
	if (ensembleGare->size == 0) {
		g->previous = NULL;
		ensembleGare->head=g;
	} else {
		g->previous = ensembleGare->tail;
		(ensembleGare->tail)->next = g;
	}
	ensembleGare->tail=g;
	g->next = NULL;
	ensembleGare->size++;
	g->nbTrajet = 0;
	char cr;
	do {
		initTrajet(g,fichierTrajet);
		cr = fgetc(fichierTrajet);
	} while (cr != '/');
	return 0;
}

Reseau initReseau(){
	FILE* fichierReseau = NULL;
	FILE* fichierTrajet = NULL;
	Reseau ensembleGare = (Reseau) malloc(sizeof(struct s_reseau));
	//Ouverture des fichiers de sauvegarde
	fichierReseau = fopen("sauv/reseau.txt", "r");
	fichierTrajet = fopen("sauv/trajet.txt", "r");
	//Verification de la bonne ouverture des fichiers de sauvegarde
	if (fichierReseau == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER RESEAU\n");
		return ensembleGare;
	}
	if (fichierTrajet == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER RESEAU\n");
		return ensembleGare;
	}

	//Creation et remplissage du reseau en memoire
	ensembleGare->size=0;
	initGare(ensembleGare, fichierReseau, fichierTrajet);
	printf("Nom de la Gare : %s;\n",ensembleGare->tail->nomGARE);
	printf("Le trajet va jusqu'a %s en %d minutes\n",ensembleGare->tail->headListeTrajet->gareArrive, ensembleGare->tail->headListeTrajet->ponderation);
	printf("Le trajet va jusqu'a %s en %d minutes\n",ensembleGare->tail->headListeTrajet->next->gareArrive, ensembleGare->tail->headListeTrajet->next->ponderation);
	initGare(ensembleGare, fichierReseau, fichierTrajet);
	printf("Nom de la Gare : %s;\n",ensembleGare->tail->nomGARE);
	printf("Le trajet va jusqu'a %s en %d minutes\n",ensembleGare->tail->headListeTrajet->gareArrive, ensembleGare->tail->headListeTrajet->ponderation);
	printf("Le trajet va jusqu'a %s en %d minutes\n",ensembleGare->tail->headListeTrajet->next->gareArrive, ensembleGare->tail->headListeTrajet->next->ponderation);
	initGare(ensembleGare, fichierReseau, fichierTrajet);
	printf("Nom de la Gare : %s;\n",ensembleGare->tail->nomGARE);
	printf("Le trajet va jusqu'a %s en %d minutes\n",ensembleGare->tail->headListeTrajet->gareArrive, ensembleGare->tail->headListeTrajet->ponderation);
	initGare(ensembleGare, fichierReseau, fichierTrajet);
	printf("Nom de la Gare : %s;\n",ensembleGare->tail->nomGARE);
	printf("Le trajet va jusqu'a %s en %d minutes\n",ensembleGare->tail->headListeTrajet->gareArrive, ensembleGare->tail->headListeTrajet->ponderation);
	//Fermeture des fichiers
	fclose(fichierReseau);
	fclose(fichierTrajet);
	return ensembleGare;
}

Reseau closeReseau(Reseau ensembleGare){
	Gare sauve;
	while (ensembleGare->tail != NULL) {
		sauve = (ensembleGare->tail);
		ensembleGare->tail = ensembleGare->tail->previous;
		free(sauve);
	}
	free(ensembleGare);
	return EXIT_SUCCESS;
}