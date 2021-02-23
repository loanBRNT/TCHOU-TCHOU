#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pwd.h"

int verifierPwdAdmin(){
	char pwdPropose[20];
	char pwd[20];
	FILE* id =NULL;
	printf("veuillez saisir le mot de passe administrateur :\n");
	scanf("%s",pwdPropose);
	id=fopen("sauv/admin.txt","r");
	if(id == NULL)
	{
		fclose(id);
		printf("Impossible d'ouvrir le fichier admin.txt\n");
		return 1;
	}
	else
	{
		fgets(pwd,20,id);
		if((strcmp(pwdPropose,pwd)) != 0)
		{
			fclose(id);
			printf("le mot de passe est errone\n");
			return 1;
		}
		else
		{
			printf("vous etes connecte au menu administrateur\n");
			return 0;
		}

	}
}