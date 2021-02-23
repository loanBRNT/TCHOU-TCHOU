#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pwd.h"

int verifierPwdAdmin(){
	char pwdPropose[20];
	char pwd[20];
	FILE* id =NULL;
	//demande a l'utilisateur de rentrer le mot de passe
	printf("####################################################\n");
	printf("# veuillez saisir le mot de passe administrateur : #\n");
	printf("####################################################\n");
	printf("\n");
	scanf("%s",pwdPropose);
	printf("\n");
	id=fopen("sauv/admin.txt","r");
	// verification du l'ouverture du fichier admin.txt qui contient le mot de passe de l administrateur
	if(id == NULL)
	{
		fclose(id);
		printf("############################################\n");
		printf("# Impossible d'ouvrir le fichier admin.txt #\n");
		printf("############################################\n");
		printf("\n");
		return 1;
	}
	else
	{
		// on recupere le mot de passe dans le fichier admin.txt
		fgets(pwd,20,id);
		/*on compare le mot de passe avec le mot de passe saisie par l'utilisateur
		si ils ne sont pas identique on affiche un message d'erreur et return une valeur d'erreur
		sinon on affiche un message pour informer de la connexion et on return 0*/
		if((strcmp(pwdPropose,pwd)) != 0)
		{
			fclose(id);
			printf("###########################################\n");
			printf("#       le mot de passe est errone        #\n");
			printf("###########################################\n");
			printf("\n");
			return 1;
		}
		else
		{
			fclose(id);
			printf("#############################################\n");
			printf("# vous etes connecte au menu administrateur #\n");
			printf("#############################################\n");
			printf("\n");
			return 0;
		}

	}
}