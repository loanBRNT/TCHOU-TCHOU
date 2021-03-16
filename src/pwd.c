#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pwd.h"

void viderBuffer(){
	int c=0;
	while (c!= '\n' && c != EOF)
		c = getchar();
}

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
        else
        	viderBuffer();
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
    	viderBuffer();
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

long lireLong()
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire
 
    if (lire(nombreTexte, 100,stdin))
    {
        // Si lecture du texte ok, convertir le nombre en long et le retourner
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        // Si problème de lecture, renvoyer 0
        return 0;
    }
}

int verifierPwdAdmin(){
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
	lire(loginPropose,20,stdin);
	fflush(stdin);
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
		lire(pwdPropose,20,stdin);
		fflush(stdin);
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
			printf("# vous etes connecte au menu administrateur #\n");
			printf("#############################################\n");
			printf("\n");
			return 0;
		}
	}
}

int verifierLogControleur(){
	int numControleur;
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
	lire(loginPropose,20,stdin);
	fflush(stdin);
	printf("\n");

	if(loginPropose[0]=='a'){
		id=fopen("sauv/controleur1.txt","r");
		numControleur=1;
		if(id == NULL)
		{
			fclose(id);
			printf("############################################\n");
			printf("#      Impossible d'ouvrir le fichier      #\n");
			printf("############################################\n");
			printf("\n");
			return 5;
		}
	}
	else if(loginPropose[0]=='b'){
		id=fopen("sauv/controleur2.txt","r");
		numControleur=2;
		if(id == NULL)
		{
			fclose(id);
			printf("############################################\n");
			printf("#      Impossible d'ouvrir le fichier      #\n");
			printf("############################################\n");
			printf("\n");
			return 5;
		}
	}
	else if(loginPropose[0]=='c'){
		id=fopen("sauv/controleur3.txt","r");
		numControleur=3;
		if(id == NULL)
		{
			fclose(id);
			printf("############################################\n");
			printf("#      Impossible d'ouvrir le fichier      #\n");
			printf("############################################\n");
			printf("\n");
			return 5;
		}
	}
	else{
		printf("############################################\n");
		printf("#           identifiant inconnu            #\n");
		printf("############################################\n");
		printf("\n");
		return 5;
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
		return 5;
	}
	else{
		//demande a l'utilisateur de rentrer son mot de passe
		printf("####################################################\n");
		printf("#       veuillez saisir votre mot de passe :       #\n");
		printf("####################################################\n");
		printf("\n");
		lire(pwdPropose,20,stdin);
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
			return 5;
		}
		else
		{
			fclose(id);
			printf("#############################################\n");
			printf("#   vous etes connecte au menu controleur   #\n");
			printf("#############################################\n");
			printf("\n");
			return numControleur;
		}
	}
}

void modiferDonnee(char* nomFile,int index ,char* texte){
	char ligne[20];
	int i=0;
	FILE* id = NULL;
	FILE* temp = NULL;
	id=fopen(nomFile,"r");
	temp=fopen("sauv/temporaire.txt","w");
	while(fgets(ligne,20,id) != NULL) // on lit le fichier tant qu'il n'y a pas d'erreur
	{
		if(i==index){
			fprintf(temp, "%s\n",texte);
		}
		else{
			fprintf(temp, "%s",ligne);
		}
		i++;
	}
	fclose(id);
	fclose(temp);
	remove(nomFile);
	rename("sauv/temporaire.txt",nomFile);
}
