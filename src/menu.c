#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "pwd.h"
#include "reseau.h"
#include "parcoursGraphe.h"
//########## FONCTIONS DE GESTION DES MENUS ###############
//########## FONCTIONS D AFFICHAGE DES MENUS ##############
void afficheMenuPrincipal(){
	printf("###########################################\n");
	printf("#                                         #\n");
	printf("#            1:ADMINISTRATEUR             #\n");
	printf("#                                         #\n");
	printf("#            2:CONTROLEUR                 #\n");
	printf("#                                         #\n");
	printf("#            3:CLIENT                     #\n");
	printf("#                                         #\n");
	printf("#            4:QUITTER                    #\n");
	printf("#                                         #\n");
	printf("#         choisissez un menu              #\n");
	printf("#                                         #\n");
	printf("###########################################\n");
	printf("\n");
}
void afficheMenuAdmin(){
	printf("###########################################\n");
	printf("#                                         #\n");
	printf("#   Bienvenue sur le menu ADMINISTRATEUR  #\n");
	printf("#                                         #\n");
	printf("#          1: GESTION DE TRAJET           #\n");
	printf("#                                         #\n");
	printf("#         2: EXPORTATION DONNEES          #\n");
	printf("#                                         #\n");
	printf("#           3: ADMINISTRATION             #\n");
	printf("#                                         #\n");
	printf("#        4: RETOUR MENU PRINCIPAL         #\n");
	printf("#                                         #\n");
	printf("#           choisissez un menu            #\n");
	printf("#                                         #\n");
	printf("###########################################\n");
	printf("\n");
}
void afficheMenuControleur(){
	printf("###########################################\n");
	printf("#                                         #\n");
	printf("#     Bienvenue sur le menu CONTROLEUR    #\n");
	printf("#                                         #\n");
	printf("#              1:RECHERCHE                #\n");
	printf("#                                         #\n");
	printf("#           2: ADMINISTRATION             #\n");
	printf("#                                         #\n");
	printf("#        3: RETOUR MENU PRINCIPAL         #\n");
	printf("#                                         #\n");
	printf("#           choisissez un menu            #\n");
	printf("#                                         #\n");
	printf("###########################################\n");
		printf("\n");
}
void afficheMenuClient(){
	printf("###########################################\n");
	printf("#                                         #\n");
	printf("#       Bienvenue sur le menu CLIENT      #\n");
	printf("#                                         #\n");
	printf("#          1:RECHERCHE ET CHOIX           #\n");
	printf("#                                         #\n");
	printf("#      2: RESERVATION ET MODIFICATION     #\n");
	printf("#                                         #\n");
	printf("#        3: RETOUR MENU PRINCIPAL         #\n");
	printf("#                                         #\n");
	printf("#           choisissez un menu            #\n");
	printf("#                                         #\n");
	printf("###########################################\n");
	printf("\n");
}
void afficheErreurMenu(){
	printf("###########################################\n");
	printf("# Vous n'avez pas choisi un menu correct  #\n");
	printf("###########################################\n");
}
void afficheMessageQuitter(){
	printf("###########################################\n");
	printf("#       A BIENTOT SUR NOTRE RESEAU        #\n");
	printf("###########################################\n");
}

//##########################################################
//######### MENUS DE LA PARTIE ADMINISTRATEUR ##############

/* fonction du menu adminverification
  cette fonction ca utiliser verifierpwdAdmin pour autoriser a l'acces au menu administrateur a l'utilisateur */
int menuAdminVerification(Reseau r){
	//on informe l'utilisateur qui rentre sur un menu prive
	int cpt = 0;
	printf("\n");
	printf("###########################################\n");
	printf("# Vous avez choisi le menu ADMINISTRATEUR #\n");
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
				long option =0 ;
 				printf("###########################################\n");
 				printf("#          voulez vous reessayer ?        #\n");
 				printf("#                 1- OUI                  #\n");
 				printf("#                 2- NON                  #\n");
 				printf("###########################################\n");
				printf("\n");
 				option=lireLong();
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
 			menuAdmin(r);
 			cpt=-1;
 		}
	}
	
	return 0;
}

int menuAdmin(Reseau r){
	int event = 1 ;
	long choixMenu;
	while(event != -1){
		afficheMenuAdmin();
		choixMenu=lireLong();
		printf("\n");
		switch(choixMenu)
		{
			case 1:
				menuGestionTrajet(r);
				break;
			case 2:
				menuExportationJSON();
				break;
			case 3:
				menuGestionAdministration();
				break;
			case 4:
				event = -1;
				break;
			default:
				afficheErreurMenu();
				break;
		}
	printf("\n");
	}
	return 0;
}

int menuGestionTrajet(Reseau r){
	printf("\n");
	printf("################################################\n");
	printf("#            Que voulez vous faire ?           #\n");
	printf("#                                              #\n");
	printf("#       1- Ajouter une Gare                    #\n");
	printf("#       2- Suprimer une Gare                   #\n");
	printf("#       3- Ajouter un trajet aller-retour      #\n");
	printf("#       4- Suprimer un trajet aller-retour     #\n");
	printf("#       5- RETOUR                              #\n");
	printf("################################################\n");
	printf("\n");
	int choixMenu = lireLong();
	switch(choixMenu) {
		case 1:
			menuAjouteGare(r);
			break;
		default:
			menuGestionTrajet(r);
			break;
	}
	printf("\n");
	return 0;
}

int menuAjouteGare(Reseau r){
	int cpt = 0;
	char* nom;
	while (cpt !=1) {
		nom="";
		printf("\n");
		printf("################################################\n");
		printf("#            Indiquez le nom de la Gare        #\n");
		printf("#              que vous voulez ajouter         #\n");
		printf("################################################\n");
		printf("\n");
		lire(nom,30,stdin); //Pb avec lire
		printf("Voulez vous vraiment creer la gare : '%s' ? \n 1- OUI \n 2- NON \n", nom);
		cpt = lireLong();
		printf("\n");
	}
	ajouterUneGare(r, nom);
	printf("\n");
	printf("################################################\n");
	printf("#          Votre gare a bien ete ajoute        #\n");
	printf("#           1- Ajouter une autre gare          #\n");
	printf("#           2- RETOUR                          #\n");
	printf("################################################\n");
	printf("\n");
	cpt = lireLong();
	switch (cpt) {
		case 1:
			menuAjouteGare(r);
			break;
		default :
			menuGestionTrajet(r);
	}
}

int menuExportationJSON(){
	return 0;
}

int menuGestionAdministration(){
	return 0;
}

//######################################################
//######### MENUS DE LA PARTIE CONTROLEUR ##############

int menuControleurVerification(){
	//on informe l'utilisateur qui rentre sur un menu prive
	int cpt = 0;
	printf("\n");
	printf("###########################################\n");
	printf("#   Vous avez choisi le menu CONTROLEUR   #\n");
	printf("#       Vous etes sur un menu prive       #\n");
	printf("###########################################\n");
	printf("\n");
	while(cpt != (-1))
	{
		// on verifie la valeur de retour de verifierPwdControleur pour savoir si l'utilisateur a saisi le bon mot de passe et login
 		cpt=verifierLogControleur();
 		// si le mot de passe ou le login est faux on demande a l'utilisateur si il veut reesayer la saisie car une erreur de frappe peut arriver
 		if(cpt==1)
 		{
 			int choix =0;
 			while(choix != 1){
				long option  ;
 				printf("###########################################\n");
 				printf("#          voulez vous reessayer ?        #\n");
 				printf("#                 1- OUI                  #\n");
 				printf("#                 2- NON                  #\n");
 				printf("###########################################\n");
				printf("\n");
 				option=lireLong();
				printf("\n");

				/* si l'utilisateur ne choisit pas un choix propose on lui repose la question 
				   si il choisit 1 on le laisse dans la boucle qui lance la verification du mot de passe et de l'identifiant
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
 		/* si le mot de passe  et l'identifiant sont  correct on lance la fonction menuControleur
 		 lorsque la fonction menuControleur ce termine on sort de la boucle
 		 pour finir la fonction menuControleurVerification ce qui nous ramene dans la fonction main du programme */
 		else{
 			menuControleur();
 			cpt=-1;
 		}
	}
	
	return 0;

}
int menuControleur(){
	int event = 1 ;
	long choixMenu;
	while(event != -1){
		afficheMenuControleur();
		choixMenu=lireLong();
		printf("\n");
		switch(choixMenu)
		{
			case 1:
				menuRechercheControleur();
				break;
			case 2:
				menuAdministrationControleur();
				break;
			case 3:
				event = -1;
				break;
			default:
				afficheErreurMenu();
				break;
		}
	printf("\n");
	
	}
	return 0;
}

int menuRechercheControleur(){
	return 0;
}

int menuAdministrationControleur(){
	return 0;
}

//######### MENUS DE LA PARTIE CLIENT ##############

int menuClient(){
	int event = 1 ;
	long choixMenu;
	while(event != -1){
		afficheMenuClient();
		choixMenu=lireLong();
		printf("\n");
		switch(choixMenu)
		{
			case 1:
				menuRechercheEtChoix();
				break;
			case 2:
				menuReservationEtModification();
				break;
			case 3:
				event = -1;
				break;
			default:
				afficheErreurMenu();
				break;
		}
	printf("\n");
	
	}
	return 0;
}

int menuRechercheEtChoix(){
	return 0;
}

int menuReservationEtModification(){
	return 0;
}