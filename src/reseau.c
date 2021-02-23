#include <stdlib.h>
#include <stdio.h>
#include "reseau.h"

struct s_gare{
	char* nomGARE; //Le nom de la Gare
	int numId; //Numero d'identification de la gare (genre un nombre >0)
	Trajet listeTrajet; //La liste chainee des trajets passant par la gare
	Gare next; //La gare suivante (numero +1)
	Gare previous; //La gare precedente (numero -1)
};

struct s_trajet{
	int ponderation; //le temps de transport
	int gareArriveId; //La gare d'arrivee du trajet via son indice de position dans la liste
	Trajet next; //Indique le trajet suivant de la même gare. Par convention le dernier pointe sur NULL
};

struct s_reseau{
	Gare head; //Indice de la premiere gare
	int size; //taille du reseau (nombe de gare)
};

Reseau initReseau(){
	FILE* fichierReseau = NULL;
	//Ouverture des fichiers de sauvegarde
	fichierReseau = fopen("sauv/reseau.txt", "r");
	//Verification de la bonne ouverture des fichiers de sauvegarde
	if (fichierReseau == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER RESEAU\n");
		exit(EXIT_FAILURE);
	}
	//Creation et remplissage du reseau en memoire
	Reseau ensembleGare = (Reseau) malloc(sizeof(Reseau));
	ensembleGare->size=0;


	Gare g = (Gare) malloc(sizeof(Gare));
	char nomG[NB_CARAC_NOM_GARE+1];
	int numIdGare;
	int dizaine = 0;
	int unite = 0;
	char caractere;
	int i=0;
	do {
		caractere = fgetc(fichierReseau);
		printf("%c\n",caractere);
		nomG[i] = caractere;
		i++;
	} while (caractere != ' ');
	nomG[i-1]='\0';
	caractere = fgetc(fichierReseau);
	dizaine = caractere - '0';
	caractere = fgetc(fichierReseau);
	unite = caractere - '0';
	numIdGare = dizaine*10 + unite;
	g->nomGare = nomG;
	return EXIT_SUCCESS;
}