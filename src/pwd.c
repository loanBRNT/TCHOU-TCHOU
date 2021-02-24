#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pwd.h"

int lire(char* chaine, int longueur ,FILE* fichier){
    char *positionEntree = NULL;
 
    // On lit le texte du fichier
    if (fgets(chaine, longueur, fichier) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

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
		lire(pwd,20,id);
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

int verifierLogControleur(){
	char pwdPropose[20];
	char pwd[20];
	char loginPropose[20];
	char login[20];
	FILE* id =NULL;
	//demande a l'utilisateur de rentrer son identifiant
	printf("####################################################\n");
	printf("#       veuillez saisir votre identifiant  :       #\n");
	printf("####################################################\n");
	printf("\n");
	scanf("%s",loginPropose);
	printf("\n");

	if(loginPropose[0]=='a'){
		id=fopen("sauv/controleur1.txt","r");
		if(id == NULL)
		{
			fclose(id);
			printf("############################################\n");
			printf("#      Impossible d'ouvrir le fichier      #\n");
			printf("############################################\n");
			printf("\n");
			return 1;
		}
	}
	else if(loginPropose[0]=='b'){
		id=fopen("sauv/controleur2.txt","r");
		if(id == NULL)
		{
			fclose(id);
			printf("############################################\n");
			printf("#      Impossible d'ouvrir le fichier      #\n");
			printf("############################################\n");
			printf("\n");
			return 1;
		}
	}
	else if(loginPropose[0]=='c'){
		id=fopen("sauv/controleur3.txt","r");
		if(id == NULL)
		{
			fclose(id);
			printf("############################################\n");
			printf("#      Impossible d'ouvrir le fichier      #\n");
			printf("############################################\n");
			printf("\n");
			return 1;
		}
	}
	else{
		printf("############################################\n");
		printf("#           identifiant inconnu            #\n");
		printf("############################################\n");
		printf("\n");
		return 1;
	}


	// on recupere l'identifiant dans le fichier controleur.txt correspondant au controleur qui se connecte
	lire(login,20,id);
	/*on compare l identifiant avec l identifiant saisie par l'utilisateur
	si ils ne sont pas identique on affiche un message d'erreur et return une valeur d'erreur
	sinon on continue la verification avec ce coup si le mot de passe 0*/
	if((strcmp(login,loginPropose)) != 0)
	{
		fclose(id);
		printf("###########################################\n");
		printf("#           identifiant invalide          #\n");
		printf("###########################################\n");
		printf("\n");
		return 1;
	}
	else{
		//demande a l'utilisateur de rentrer son mot de passe
		printf("####################################################\n");
		printf("#       veuillez saisir votre mot de passe :       #\n");
		printf("####################################################\n");
		printf("\n");
		scanf("%s",pwdPropose);
		printf("\n");
		// on recupere le mot de passe dans le fichier controleur.txt correspondant au controleur qui se connecte
		lire(pwd,20,id);
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
			printf("#   vous etes connecte au menu controleur   #\n");
			printf("#############################################\n");
			printf("\n");
			return 0;
		}
	}
}
