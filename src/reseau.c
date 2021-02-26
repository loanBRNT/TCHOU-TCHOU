#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "reseauAccesseur.h"
#include "parcoursGraphe.h"

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
	char gareArrive[30]; //La gare d'arrivee du trajet
	Trajet next; //Indique le trajet suivant de la même gare. Par convention le dernier pointe sur NULL
};

struct s_reseau{
	Gare head; //Indice de la premiere gare
	Gare tail;
	int size; //taille du reseau (nombe de gare)
};

//ZONE DES ACCESSEURS (reseauAccesseur.h) 

/*
	Permet d'acceder aux parametres des structures hors des fichiers .c tout en maintenant la declaration opaque
*/

Gare gareHead(Reseau r){
	return (r->head);
}

Gare gareTail(Reseau r){
	return (r->tail);
}

int tailleReseau(Reseau r){
	return (r->size);
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

char* gareArvDuTrajet(Trajet tr){
	return (tr->gareArrive);
}

Trajet trajetNext(Trajet tr){
	return (tr->next);
}
//Zone code gestion du reseau (reseau.h)


int initTrajet(Gare gareDepart, FILE* fichierTrajet){
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
	//systeme de lecture du format
	//lecture du nom de la gare d'arrivee
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

int initGare(Reseau ensembleGare, FILE* fichierReseau, FILE* fichierTrajet){
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
	char cr;
	// on initialise les trajets de cette nouvelle gare
	do {
		initTrajet(g,fichierTrajet);
		cr = fgetc(fichierTrajet);
	} while (cr != '/');
	return 0;
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
		initGare(ensembleGare, fichierReseau, fichierTrajet);
	}
	//Fermeture des fichiers
	fclose(fichierReseau);
	fclose(fichierTrajet);
	return ensembleGare;
}

Reseau sauvReseau(Reseau ensembleGare){
	//Alloc + ouverture des fichiers
	Gare gA = ensembleGare->head;
	Trajet tr;
	FILE* fichierReseau = fopen("sauv/reseau.txt","w+");
	FILE* fichierTrajet = fopen("sauv/trajet.txt","w+");
	if (fichierReseau == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER RESEAU\n");
		return ensembleGare;
	}
	if (fichierTrajet == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER RESEAU\n");
		return ensembleGare;
	}
	//ecriture dans le fichier reseau.txt (sauvegarde des noms de gare et de l'ordre)
	for (int i = 0; i < ensembleGare->size; ++i) {
		fprintf(fichierReseau,"%s\n",gA->nomGARE);
		tr = gA->headListeTrajet;
		printf("\n%s : ",gA->nomGARE);
		for (int j = 0; j < gA->nbTrajet; j++) {
			//ecriture des trajets de la gare dans trajets.txt
			fprintf(fichierTrajet, "\n");
			fprintf(fichierTrajet, "%s-%d\n",tr->gareArrive, tr->ponderation);
			printf("%s-",tr->gareArrive);
			tr = tr->next;
		}
		fprintf(fichierTrajet, "/\n");
		gA=gA->next;
	}
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

int ajouterUnTrajet(Reseau r, Gare g, char* arrive, int temps){
	//on verifie que le char* correspond bien à une gare et que le trajet ne soit pas déjà existant
	if (rechercheGare(r,arrive) == NULL) {
		printf("La gare d'arrivee n'existe pas\n");
		return 1;
	}
	if (rechercheTrajet(g,arrive) != NULL) {
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
	int i=-1;
	do {
		i++;
		tr1->gareArrive[i] = arrive[i];
	} while (arrive[i] != '\0');
	i=-1;
	tr1->next=NULL;
	//On raccroche a la gare correspondante
	if (g->nbTrajet == 0){
		g->headListeTrajet = tr1;
	} else {
		g->tailListeTrajet->next = tr1;
	}
	g->tailListeTrajet = tr1;
	g->nbTrajet++;
	return 0;
}
int retirerUnTrajet(Gare act, char* nom){
	//on verifie que le trajet existe bien
	Trajet tr = rechercheTrajet(act, nom);
	if (tr == NULL) {
		printf("Le trajet n'existe pas !\n");
		return 1;
	}
	Trajet sauv = tr;
	int compteur=0;
	int rangInf = 0;
	//on compte le nombre de trajet après le notre dans la liste
	while (sauv->next != NULL) {
		compteur++;
		sauv = sauv->next;
	}
	// on calcule le rang du trajet juste avant le notre
	rangInf = (act->nbTrajet - compteur) - 1;
	sauv = act->headListeTrajet;
	// on re parcours la liste pour se placer au trajet juste avant celui à retirer
	for (int i = 0 ; i < rangInf ; i++) {
		sauv = sauv->next;
	}
	//on raccorde le précendent du trajet à retirer au suivant de trajet à retirer
	sauv->next = tr->next;
	//on libere la memoire
	free(tr);
	act->nbTrajet--;
	return 0;
}

int retirerUneGare(Reseau r, char* nom){
	//On verifie que la gare existe et qu'il y en a au moins 3
	Gare g = rechercheGare(r,nom);
	if (g == NULL) {
		printf("LA gare n'existe pas !\n");
		return 1;
	}
	if (r->size == 2){
		printf("Vous ne pouvez avoir moins de 2 gares dans votre réseau !\n");
		return 1;
	}
	//on raccorde les précédents et suivants ensemble
	(g->previous)->next= g->next;
	if ( r->tail != g) {
		g->next->previous=g->previous;
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
		t = rechercheTrajet(act,nom);
		if (t != NULL) {
			retirerUnTrajet(act, nom);
		}
		act = act->next;
	}
	return 0;
}