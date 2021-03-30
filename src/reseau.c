#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "train.h"
#include "voyageur.h"
#include "reseauAccesseur.h"
#include "trainVoyageurAccesseur.h"

/*
On definit les 3 structures utiles pour manier le reseau routier ! 

s_reseau prend en charge la totalite du reseau et permet de lister des elements s_gare (des Gares) via une liste doublement chainée

s_gare permet de gerer une gare et de gérer l'ensemble des trajets passant par cette derniere (elle les gére via une seconde liste chainée)

s_trajet permet de gérer un trajet particulier il prend la gare d'arrivée et la pondération
*/

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
	Gare gArrive; //La gare d'arrivee du trajet
	Trajet next; //Indique le trajet suivant de la même gare. Par convention le dernier pointe sur NULL
};

struct s_reseau{
	Gare head; //Indice de la premiere gare
	Gare tail;
	int size; //taille du reseau (nombe de gare)
	Train headTrain; //Indice du premier train
	Train tailTrain;
	int nbTrain; //nb de train dans le reseau
	Voyageur headVoyageur;
	Voyageur tailVoyageur;
	int nbVoyageur; //nb de voyageur 
};

//ZONE DES ACCESSEURS (reseauAccesseur.h) 

/*
	Permet d'acceder aux parametres des structures hors des fichiers .c tout en maintenant la declaration opaque
*/

int nbDeVoyageur(Reseau r){
	return (r->nbVoyageur);
}

Voyageur voyageurHead(Reseau r){
	return (r->headVoyageur);
}

Voyageur voyageurTail(Reseau r){
	return (r->tailVoyageur);
}

Gare gareHead(Reseau r){
	return (r->head);
}

Gare gareTail(Reseau r){
	return (r->tail);
}

int tailleReseau(Reseau r){
	return (r->size);
}

Train headTrainReseau(Reseau r){
	return r->headTrain;
}

Train tailTrainReseau(Reseau r){
	return r->tailTrain;
}

int nbTrainReseau(Reseau r){
	return r->nbTrain;
}

char* nomDeGare(Gare g){
	return (g->nomGARE);
}

int nbTrajetDeLaGare(Gare g){
	return (g->nbTrajet);
}

Trajet trajetHeadDeLaGare(Gare g){
	return (g->headListeTrajet);
}

Trajet trajetTailDeLaGare(Gare g){
	return (g->tailListeTrajet);
}

Gare gareNext(Gare g){
	return (g->next);
}

Gare garePrevious(Gare g){
	return (g->previous);
}

int tempsDuTrajet(Trajet tr){
	return (tr->ponderation);
}

Gare gareArvDuTrajet(Trajet tr){
	return (tr->gArrive);
}

Trajet trajetNext(Trajet tr){
	return (tr->next);
}
//Zone code gestion du reseau (reseau.h)


int initTrajet(Reseau r,Gare gareDepart, FILE* fichierTrajet){
	//on cree de l'espace memoire pour un trajet
	Trajet tr = (Trajet) malloc(sizeof(struct s_trajet));
	if (tr==NULL) {
		printf("ERREUR ALLOCATION ESPACE TRAJET\n");
		return 1;
	}
	//on regarde si on avait deja mis ou non des trajets à cette gare
	if (gareDepart->nbTrajet==0) {
		gareDepart->headListeTrajet = tr;
		gareDepart->tailListeTrajet = tr;
	} else {
		gareDepart->tailListeTrajet->next = tr;
		gareDepart->tailListeTrajet = tr;
	}
	fseek(fichierTrajet, -2, SEEK_CUR);
	//systeme de lecture du format
	//lecture du nom de la gare d'arrivee
	char caractere;
	int i=0;
	int centaine;
	int dizaine;
	int unite;
	char* nom;
	do {
		caractere = fgetc(fichierTrajet);
		if (caractere !='\n') {
			nom[i] = caractere;
			i++;
		}
	} while (caractere != '-');
	nom[i-1] = '\0';
	tr->gArrive = rechercheGare(r, nom);
	//calcul de la ponderation
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

int initGare(Reseau ensembleGare, FILE* fichierReseau){
	//allocation memoire
	Gare g = (Gare) malloc(sizeof(struct s_gare));
	if (g==NULL) {
		printf("ERREUR d'alocation d'espace\n");
		return 1;
	}
	//lecture du nom de la Gare
	char caractere;
	int i = 0;
	do {
		caractere = fgetc(fichierReseau);
		g->nomGARE[i] = caractere;
		i++;
	}while (caractere != '\n');
	g->nomGARE[i-1]='\0';
	//si le reseau est vide on init la head sinon on relie l'anciene gare en queue de la liste à la nouvelle gare
	if (ensembleGare->size == 0) {
		g->previous = NULL;
		ensembleGare->head=g;
	} else {
		g->previous = ensembleGare->tail;
		(ensembleGare->tail)->next = g;
	}
	//on rajoute les dernieres informations de la nouvele gare
	ensembleGare->tail=g;
	g->next = NULL;
	ensembleGare->size++;
	g->nbTrajet = 0;
	return 0;
}

void ajtTrain(Reseau r, Train t){
	r->tailTrain = t;
	r->nbTrain++;
}

Train enleverTrainHead(Reseau r, Train t){
	r->headTrain = trainNext(t);
	r->nbTrain--;
	return t;
}

Train enleverTrainTail(Reseau r, Train t){
	r->tailTrain = trainPrevious(t);
	r->nbTrain--;
	return t;
}

void enleverTrain(Reseau r){
	r->nbTrain--;
}



Reseau initReseau(){
	//allocation memoire
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
	//On compte le nombre de ligne
	char c;
	int nbGare = 0;
	c=fgetc(fichierReseau);
	while (c != EOF){
		if (c == '\n') {
			nbGare++;
		}
		c = fgetc(fichierReseau);
	}
	rewind(fichierReseau);
	//Creation et remplissage du reseau en memoire
	ensembleGare->size=0;
	for (int i=0; i < nbGare ; i++) {
		initGare(ensembleGare, fichierReseau);
	}
	// on initialise les trajets des gares
	Gare g = ensembleGare->head;
	for (int i=0; i < ensembleGare->size ; i++) {
		do {
			//on verifie que la gare a des trajets a ajouter
			fgetc(fichierTrajet);
			if (fgetc(fichierTrajet) == '/'){
				continue;
			}
			initTrajet(ensembleGare, g, fichierTrajet);
			c = fgetc(fichierTrajet);
		} while (c != '/');
		g = g->next;
	}
	//Fermeture des fichiers
	fclose(fichierReseau);
	fclose(fichierTrajet);

	//on ouvre le fichier train
	FILE* fichierTrain = NULL;
	FILE* fichierVoyageur = NULL;
	fichierTrain = fopen("sauv/train.txt", "r");
	fichierVoyageur = fopen("sauv/voyageur.txt", "r");
	if (fichierTrain == NULL || fichierVoyageur == NULL) {
		printf("ERROR 1 : PROBLEME OUVERTURE FICHIER TRAIN ou VOYAGE\n");
	}
	//on compte le nombre de train
	int nbTrain = 0;
	c=fgetc(fichierTrain);
	while (c != EOF){
		if (c == '\n') {
			nbTrain++;
		}
		c = fgetc(fichierTrain);
	}
	rewind(fichierTrain);
	ensembleGare->nbTrain = nbTrain;
	ensembleGare->tailTrain = NULL;
	Train t;
	for (int i=0; i < nbTrain ; i++) {
		t = initTrain(ensembleGare, fichierTrain, fichierVoyageur);
		if ( i == 0){
			ensembleGare->headTrain = t;
		}
		ensembleGare->tailTrain = t;
	}
	fclose(fichierTrain);
	fclose(fichierVoyageur);
	return ensembleGare;
}

Reseau sauvReseau(Reseau ensembleGare){
	//Alloc + ouverture des fichiers
	Gare gA = ensembleGare->head;
	Trajet tr;
	FILE* fichierReseau = fopen("sauv/reseau.txt","w+");
	FILE* fichierTrajet = fopen("sauv/trajet.txt","w+");
	FILE* fichierTrain = fopen("sauv/train.txt", "w+");
	FILE* fichierVoyageur = fopen("sauv/voyageur.txt", "w+");
	if (fichierReseau == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER RESEAU\n");
		return ensembleGare;
	}
	if (fichierTrajet == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER TRAJET\n");
		return ensembleGare;
	}
	if (fichierTrain == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER TRAIN\n");
		return ensembleGare;
	}
	if (fichierVoyageur == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER Voyageur\n");
		return ensembleGare;
	}
	//ecriture dans le fichier reseau.txt (sauvegarde des noms de gare et de l'ordre)
	for (int i = 0; i < ensembleGare->size; ++i) {
		fprintf(fichierReseau,"%s\n",gA->nomGARE);
		tr = gA->headListeTrajet;
		for (int j = 0; j < gA->nbTrajet; j++) {
			//ecriture des trajets de la gare dans trajets.txt
			fprintf(fichierTrajet, "\n");
			fprintf(fichierTrajet, "%s-%d\n",tr->gArrive->nomGARE, tr->ponderation);
			tr = tr->next;
		}
		fprintf(fichierTrajet, "/\n");
		gA=gA->next;
	}
	// Sauvegarde des trains
	sauvTrain(ensembleGare, fichierTrain, fichierVoyageur);

	fclose(fichierTrajet);
	fclose(fichierReseau);
	fclose(fichierTrain);
	fclose(fichierVoyageur);
	return ensembleGare;
}

void closeReseau(Reseau ensembleGare){
	//on libere la memoire sans perdre l'adresse des elements
	Gare sauve;
	Trajet tsauve;
	while (ensembleGare->tail != NULL) {
		sauve = (ensembleGare->tail);
		if (sauve->nbTrajet != 0){
			do {
				tsauve=sauve->headListeTrajet;
				sauve->headListeTrajet = sauve->headListeTrajet->next;
				free(tsauve);
			} while (sauve->headListeTrajet != NULL);
		}
		ensembleGare->tail = ensembleGare->tail->previous;
		free(sauve);
	}
	free(ensembleGare);
}

int ajouterUneGare(Reseau r, char* nom){
	// on verifie que la gare n'existe pas
	if ((rechercheGare(r,nom)) != NULL){
		printf("La Gare existe deja\n");
		return 1;
	}
	//allocation de memoire
	Gare g = (Gare) malloc(sizeof(struct s_gare));
	if (g==NULL){
		printf("ERREUR ALLOCATION CREATION GARE\n");
		return 1;
	}
	//On entre les informations de la gare
	int i=-1;
	do {
		i++;
		g->nomGARE[i] = nom[i];
	} while (nom[i] != '\0');
	g->nbTrajet = 0;
	g->next = NULL;
	//On raccroche a la fin de la liste de gare
	g->previous = r->tail;
	r->tail->next = g;
	r->tail = g;
	r->size++;
	return 0;
}

int ajouterUnTrajet(Gare gDep, Gare gArv, int temps){
	//on verifie que le trajet ne soit pas déjà existant
	if (rechercheTrajet(gDep,gArv) != NULL) {
		printf("Le trajet existe deja !\n");
		return 1;
	}
	//allocation de memoire
	Trajet tr1 = (Trajet) malloc(sizeof(struct s_trajet));
	if (tr1==NULL){
		printf("ERREUR ALLOCATION CREATION TRAJET\n");
		return 1;
	}
	//On entre les informations du trajet
	tr1->ponderation = temps;
	tr1->gArrive = gArv;
	tr1->next= NULL;
	//On raccroche a la gare correspondante
	if (gDep->nbTrajet == 0){
		gDep->headListeTrajet = tr1;
	} else {
		gDep->tailListeTrajet->next = tr1;
	}
	gDep->tailListeTrajet = tr1;
	gDep->nbTrajet++;
	if (rechercheTrajet(gArv,gDep) == NULL) {
		ajouterUnTrajet(gArv,gDep,temps);
	}
	return 0;
}
int retirerUnTrajet(Gare gDep, Gare gArv){
	//on verifie que le trajet existe bien
	Trajet tr = rechercheTrajet(gDep, gArv);
	if (tr == NULL) {
		printf("Le trajet n'existe pas !\n");
		return 1;
	}
	Trajet sauv = gDep->headListeTrajet;
	if (strcmp(sauv->gArrive->nomGARE,gArv->nomGARE)){
		while ((strcmp(gArv->nomGARE,sauv->next->gArrive->nomGARE)) && (sauv->next != NULL)){
			sauv = sauv->next;
		}
		sauv->next = tr->next;
		if (tr->next == NULL){
			gDep->tailListeTrajet == sauv;
		}
	} else {
		if (gDep->nbTrajet == 1){
			gDep->headListeTrajet == NULL;
			gDep->tailListeTrajet == NULL;
		} else {
			gDep->headListeTrajet = gDep->headListeTrajet->next;
		}
	}
	free(tr);
	gDep->nbTrajet--;
	if (rechercheTrajet(gArv,gDep) != NULL) {
		retirerUnTrajet(gArv,gDep);
	}
	return 0;
}

int retirerUneGare(Reseau r, Gare g){
	//On verifie que la gare existe et qu'il y en a au moins 3
	if (g == NULL) {
		printf("LA gare n'existe pas !\n");
		return 1;
	}
	if (r->size == 2){
		printf("Vous ne pouvez avoir moins de 2 gares dans votre réseau !\n");
		return 1;
	}
	//on raccorde les précédents et suivants ensemble
	if ( strcmp(r->head->nomGARE, g->nomGARE)) {
		(g->previous)->next= g->next;
	} else {
		r->head = g->next;
	}
	if ( strcmp(r->tail->nomGARE, g->nomGARE)) {
		g->next->previous=g->previous;
	} else {
		r->tail = g->previous;
	}
	Trajet tr = g->headListeTrajet;
	//on libere de la memoire tous les trajets de la gare
	while (g->nbTrajet > 0) {
		g->headListeTrajet = g->headListeTrajet->next;
		free(tr);
		tr = g->headListeTrajet;
		g->nbTrajet--;
	}
	r->size--;
	//on retire la gare
	free(g);
	//On retirer les trajets qui amenaient a la gare qui vient d'etre retire
	Gare act = r->head;
	Trajet t;
	for (int i=0; i<r->size; i++){
		t = rechercheTrajet(act,g);
		if (t != NULL) {
			retirerUnTrajet(act, g);
		}
		act = act->next;
	}
	return 0;
}