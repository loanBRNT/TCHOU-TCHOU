#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "pwd.h"
#include "parcoursGraphe.h"
#include "train.h"
#include "voyageur.h"
#include "reseauAccesseur.h"
#include "itineraireAccesseur.h"
#include "trainVoyageurAccesseur.h"
#include "client.h"
#include "gestionjson.h"

void voyageurJson(){
	int nbrVoyageur=0;
	int nbrtraite=1;
	FILE* id;
	FILE* fichierJson;
	id=fopen("sauv/repertoire.txt","r");
	fichierJson=fopen("sauv/voyageur.json","w");
	if (id == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER \n");
	}
	if (fichierJson == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER \n");
	}
	char c= fgetc(id);
	while (c != EOF){
		if (c == '\n'){
			nbrVoyageur++;
		}
		c = fgetc(id);
	}
	rewind(id);

	fprintf(fichierJson, "{\n \"voyageur\" : [");
	c= fgetc(id);
	while (c != EOF){
		int n=0;
		while(c != '\n'){
			if(n==0){
				fprintf(fichierJson, "{\n\"numero client\": \"");
				while(c != ':'){
					fprintf(fichierJson, "%c",c );
					c=fgetc(id);
				}
				fprintf(fichierJson, "\"," );
			}
			else if (n==1){
				fprintf(fichierJson, "\"nom\":  \"");
				while(c != ':'){
					fprintf(fichierJson, "%c",c );
					c=fgetc(id);
				}
				fprintf(fichierJson, "\"," );
			}
			else if (n==2){
				fprintf(fichierJson, "\"prenom\": \"");
				while(c != ':'){
					fprintf(fichierJson, "%c",c );
					c=fgetc(id);
				}	
				fprintf(fichierJson, "\"," );			
			}
			else if (n==3){
				fprintf(fichierJson, "\"Gare de depart\": \"");
				while(c != ':'){
					fprintf(fichierJson, "%c",c );
					c=fgetc(id);
				}
				fprintf(fichierJson, "\"," );				
			}
			else if (n==4){
				fprintf(fichierJson, "\"Gare arrivee\": \"");
				while(c != ':'){
					fprintf(fichierJson, "%c",c );
					c=fgetc(id);
				}	
				fprintf(fichierJson, "\"" );
			}
			else{
				printf("erreur\n");
			}
			n++;
			c=fgetc(id);
		}
		if(nbrtraite == nbrVoyageur){
			fprintf(fichierJson, "%c } \n",c );
		}
		else{
			fprintf(fichierJson, "%c }, \n",c );
		}
		c=fgetc(id);
		nbrtraite++;
	}
	fprintf(fichierJson, "] ");
	fprintf(fichierJson, " \n } \n");
	fclose(id);
	fclose(fichierJson);
}



void trajetJson(){
	int nbrtrain=0;
	int nbrtraite=1;
	int nbrtroncon=0;
	int nbrtroncontraite=1;
	long position;
	int n=0;
	FILE* id;
	FILE* fichierJson;
	id=fopen("sauv/train.txt","r");
	fichierJson=fopen("sauv/listeTrajet.json","w");
	if (id == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER \n");
	}
	if (fichierJson == NULL) {
		printf("Error 1 : PROBLEME OUVERTURE FICHIER \n");
	}
	char c= fgetc(id);
	while (c != EOF){
		if (c == '\n'){
			nbrtrain++;
		}
		c = fgetc(id);
	}
	rewind(id);

	fprintf(fichierJson, "{\n \"Train\" : [");
	c= fgetc(id);

	while (c != EOF){
		n=0;
		nbrtroncon=0;
		nbrtroncontraite=1;
		while (c != '\n'){
			if (c == ':'){
				nbrtroncon++;
			}
			c = fgetc(id);
		}
		rewind(id);

		while (n!=nbrtraite){
			if (c == '\n'){
				n++;
			}
			c = fgetc(id);
		}

		n=0;
		while(c != '\n'){
			if(n==0){
				fprintf(fichierJson, "{\n\"numero train\": \"");
				while(c != ' '){
					fprintf(fichierJson, "%c",c );
					c=fgetc(id);
				}
				fprintf(fichierJson, "\"," );
			}
			else {
				fprintf(fichierJson, "\"morceau de trajet n°%d\":  \"",n);
				while(c != ':'){
					fprintf(fichierJson, "%c",c );
					c=fgetc(id);
				}
				if(nbrtroncontraite==nbrtroncon){
					fprintf(fichierJson, "\"" );
				}
				else{
					fprintf(fichierJson, "\"," );
				}
				nbrtroncontraite++;

			}
			n++;
			c=fgetc(id);
		}
		if(nbrtraite == nbrtrain){
			fprintf(fichierJson, "%c } \n",c );
		}
		else{
			fprintf(fichierJson, "%c }, \n",c );
		}
		c=fgetc(id);
		nbrtraite++;
	}
	fprintf(fichierJson, "] ");
	fprintf(fichierJson, " \n } \n");
	fclose(id);
	fclose(fichierJson);

}