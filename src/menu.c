#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "pwd.h"

/* fonction du menu adminverification
  cette fonction ca utiliser verifierpwdAdmin pour autoriser a l'acces au menu administrateur a l'utilisateur */
int menuAdminVerification(){
	//on informe l'utilisateur qui rentre sur un menu prive
	int cpt = 0;
	printf("\n");
	printf("###########################################\n");
	printf("#       Vous etes sur un menu prive       #\n");
	printf("###########################################\n");
	printf("\n");
	while(cpt != (-1))
	{
		// on verifie la valeur de retour de verifierPwdAdmin pour savoir si l'utilisateur a saisi le bon mot de passe
 		cpt=verifierPwdAdmin();
 		// si le mot de passe est faux on demande a l'utilisateur si il veut reesayer la saisie car une erreur de frappe peut arriver
 		if(cpt==1)
 		{
 			int choix =0;
 			while(choix != 1){
				int option =0 ;
 				printf("###########################################\n");
 				printf("#          voulez vous reessayer ?        #\n");
 				printf("#                 1- OUI                  #\n");
 				printf("#                 2- NON                  #\n");
 				printf("###########################################\n");
				printf("\n");
 				scanf("%d",&option);
				printf("\n");

				/* si l'utilisateur ne choisit pas un choix propose on lui repose la question 
				   si il choisit 1 on le laisse dans la boucle qui lance la verification du mot de passe
				   si il choisit 2 on le sort de la boucle et on fini la fonction menuAdminVerification ce qui nous ramene dans la fonction main du programme
				*/ 
 				switch(option)
				{
					case 1:
						choix =1;
						cpt=1;
						break;
					case 2:
						choix=1;
						cpt=-1;
						break;
					default:
						printf("###########################################\n");
				 		printf("#      Vous n'avez pas choisi 1 ou 2      #\n");
						printf("###########################################\n");
						break;
 				}
 			}
 		}
 		/* si le mot de passe est correct on lance la fonction menuAdmin
 		 lorsque la fonction menuAdmin ce termine on sort de la boucle
 		 pour finir la fonction menuAdminVerification ce qui nous ramene dans la fonction main du programme */
 		else{
 			menuAdmin();
 			cpt=-1;
 		}
	}
	
	return 0;
	
}



int menuAdmin(){
	return 0;
}

int menuControleur(){
	return 0;
}

int menuClient(){
	return 0;
}