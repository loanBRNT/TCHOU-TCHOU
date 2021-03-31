#include <stdlib.h>
#include <stdio.h>
#include "reseau.h"
#include "parcoursGraphe.h"
#include "train.h"
#include "voyageur.h"
#include "reseauAccesseur.h"
#include "menu.h"
#include "pwd.h"
#include "reseauAccesseur.h"
#include "itineraireAccesseur.h"
#include "trainVoyageurAccesseur.h"
#include "client.h"
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
	printf("#             1: RECHERCHE                #\n");
	printf("#                                         #\n");
	printf("#             2: RESERVATION              #\n");
	printf("#                                         #\n");
	printf("#             3: MODIFICATION             #\n");
	printf("#                                         #\n");
	printf("#        4: RETOUR MENU PRINCIPAL         #\n");
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
	int event = 1 ;
	while(event != -1){
		printf("\n");
		printf("################################################\n");
		printf("#            Que voulez vous faire ?           #\n");
		printf("#                                              #\n");
		printf("#       1- Ajouter une Gare                    #\n");
		printf("#       2- Suprimer une Gare                   #\n");
		printf("#       3- Ajouter un trajet aller-retour      #\n");
		printf("#       4- Suprimer un trajet aller-retour     #\n");
		printf("#       5- Ajouter un Train                    #\n");
		printf("#       6- Supprimer un Train                  #\n");
		printf("#       7- Modifier un Train                   #\n");
		printf("#       8- RETOUR                              #\n");
		printf("################################################\n");
		printf("\n");
		Gare pt = gareHead(r);
		Trajet tr;
		for (int i=0; i<tailleReseau(r); i++){
			printf("%s : ",nomDeGare(pt));
			tr = trajetHeadDeLaGare(pt);
			for (int j=0; j<nbTrajetDeLaGare(pt); j++){
				printf("%s-",nomDeGare(gareArvDuTrajet(tr)));
				tr = trajetNext(tr);
			}
			pt = gareNext(pt);
			printf("\n");
		}
		long choixMenu = lireLong();
		switch(choixMenu) {
			case 1:
				menuAjouteGare(r);
				break;
			case 2:
				menuSupGare(r);
				break;
			case 3:
				menuAjouteTrajet(r);
				break;
			case 4:
				menuSupTrajet(r);
				break;
			case 5:
				menuAjouterTrain(r);
				break;
			case 6:
				menuSuppTrain(r);
				break;
			case 7:
				menuModifTrain(r);
				break;
			case 8:
				event = -1 ;
				break;
			default:
				afficheErreurMenu();
				break;
		}
	}
	printf("\n");
	return 0;
}

int menuAjouterTrain(Reseau r){
	printf("\n");
	printf("################################################\n");
	printf("#            Le Train que vous ajoutez         #\n");
	printf("#             n'est pas aller retour !         #\n");
	printf("################################################\n");
	printf("\n");
	ajouterTrain(r);
	return 0;
}

int menuSuppTrain(Reseau r){
	char nom[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#               Indiquez le numero du          #\n");
	printf("#             train que vous voulez supp       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s", nom);
	fflush(stdin);
	suppTrain(r, nom);
}

int menuModifTrain(Reseau r){
	char nom[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#               Indiquez le numero du          #\n");
	printf("#          train que vous voulez modifier      #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s", nom);
	fflush(stdin);
	printf("\n");
	printf("################################################\n");
	printf("#        Comment voulez vous modifier ?        #\n");
	printf("#     1- Ajouter des Trajets a la fin          #\n");
	printf("#     2- Raccourcir le Trajet                  #\n");
	printf("################################################\n");
	printf("\n");
	long cpt = lireLong();
	Train t = rechercheTrain(r, nom);
	if (t == NULL){
	printf("\n");
	printf("################################################\n");
	printf("#                  INVALIDE                    #\n");
	printf("################################################\n");
	printf("\n");
	return 1;		
	}
	if (cpt == 1){
		modifAjtTrajetFin(r, cheminTrain(t));
		return 0;
	} else if (cpt == 2){
		modifArv(r, cheminTrain(t));
		return 0;
	}
	printf("\n");
	printf("################################################\n");
	printf("#                  INVALIDE                    #\n");
	printf("################################################\n");
	printf("\n");
	return 1;
}

int menuAjouteGare(Reseau r){ //saisie sans espace et avec chiffre
	int cpt;
	long choix;
	char nom[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#            Indiquez le nom de la Gare        #\n");
	printf("#              que vous voulez ajouter         #\n");
	printf("#              29 caracteres maximum           #\n");	
	printf("################################################\n");
	printf("\n");
	scanf("%s", nom);
	fflush(stdin);
	cpt = ajouterUneGare(r, nom);
	int event = 1;
	if ( cpt == 0){
		printf("\n");
		printf("################################################\n");
		printf("#          Votre gare a bien ete ajoute        #\n");
		printf("#           1- Ajouter une autre gare          #\n");
		printf("#           2- RETOUR                          #\n");
		printf("################################################\n");
		printf("\n");
	}
	else {
		printf("\n");
		printf("################################################\n");
		printf("#          La gare n'a pas etait ajoute        #\n");
		printf("#           1- Ajouter une autre gare          #\n");
		printf("#           2- RETOUR                          #\n");
		printf("################################################\n");
		printf("\n");
	}	
	while(event != -1){	
		choix = lireLong();
		switch (choix) {
			case 1:
				menuAjouteGare(r);
				event = -1;
				break;
			case 2:
				event = -1;
				break;
			default :
				afficheErreurMenu();
				break;
		}
	}
	return 0;
}

int menuSupGare(Reseau r){
	long cpt;
	char nom[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#            Voici la liste des Gares          #\n");
	printf("################################################\n");
	printf("\n");
	Gare g = gareHead(r);
	for (int i=0; i<tailleReseau(r); i++){
		printf("%s | ",nomDeGare(g));
		g=gareNext(g);
	}
	printf("\n\n");
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare a Suprimer      #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nom);
	fflush(stdin);
	g = rechercheGare(r, nom);
	if (g == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
	} else {
		retirerUneGare(r, g);
		printf("\n");
		printf("################################################\n");
		printf("#         La Gare a bien etait retire !        #\n");
	}
	printf("#         1- Supprimmer une autre Gare         #\n");
	printf("#         2- RETOUR                            #\n");
	printf("################################################\n");
	printf("\n");
	int event = 1;
	while(event != -1){
		cpt = lireLong();
		switch (cpt) {
			case 1:
				menuSupGare(r);
				event = -1;
				break;
			case 2:
				event= -1 ;
				break;
			default :
				afficheErreurMenu();
				break;
		}
	}
	return 0;
}

int menuAjouteTrajet(Reseau r){
	char nomDep[30] = {0};
	char nomArv[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#            Voici la liste des Gares          #\n");
	printf("################################################\n");
	printf("\n");
	Gare g = gareHead(r);
	for (int i=0; i<tailleReseau(r); i++){
		printf("%s | ",nomDeGare(g));
		g=gareNext(g);
	}
	printf("\n\n");
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare de Depart       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomDep);
	fflush(stdin);
	g = rechercheGare(r, nomDep);
	if (g == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		menuGestionTrajet(r);
		return 1;
	}
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare d'Arrivee       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomArv);
	fflush(stdin);
	Gare g2 = rechercheGare(r, nomArv);
	if (g2 == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		menuGestionTrajet(r);
		return 1;
	}
	printf("\n");
	printf("################################################\n");
	printf("#    Combien de temps de trajet ? (en min)     #\n");
	printf("################################################\n");
	printf("\n");
	int tmps;
	scanf("%d",&tmps);
	fflush(stdin);
	if (tmps < 10) {
		printf("\n");
		printf("################################################\n");
		printf("#       Temps invalide ou < a 10 minutes       #\n");
		printf("################################################\n");
		printf("\n");
		menuGestionTrajet(r);
		return 1;
	}
	ajouterUnTrajet(g, g2, tmps);
	printf("\n");
	printf("******************** WARNING *******************\n");
	printf("*   Le trajet n'est parcouru par aucun Train ! *\n");
	printf("************************************************\n");
	printf("\n");
	printf("\n");
	printf("################################################\n");
	printf("#          Le trajet a bien ete ajoute         #\n");
	printf("#           1- Ajouter un autre trajet         #\n");
	printf("#           2- RETOUR                          #\n");
	printf("################################################\n");
	printf("\n");
	int event = 1;
	long cpt;
	while(event != -1){
		cpt = lireLong();
		switch (cpt) {
			case 1:
				menuAjouteTrajet(r);
				event = -1;
				break;
			case 2:
				event = -1;
				break;
			default :
				afficheErreurMenu();
				break;
		}
	}
	return 0;
}

int menuSupTrajet(Reseau r){
	char nomDep[30] = {0};
	char nomArv[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#            Voici la liste des Gares          #\n");
	printf("################################################\n");
	printf("\n");
	Gare g = gareHead(r);
	for (int i=0; i<tailleReseau(r); i++){
		printf("%s | ",nomDeGare(g));
		g=gareNext(g);
	}
	printf("\n\n");
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare de Depart       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomDep);
	fflush(stdin);
	g = rechercheGare(r, nomDep);
	if (g == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		menuGestionTrajet(r);
		return 1;
	}
	if (nbTrajetDeLaGare(g) == 0 ) {
		printf("\n");
		printf("################################################\n");
		printf("#          La Gare n'a pas de Trajets          #\n");
		printf("################################################\n");
		printf("\n");
		menuGestionTrajet(r);
		return 1;
	}
	printf("################################################\n");
	printf("#    Voici la liste des Trajets de la Gare     #\n");
	printf("################################################\n");
	Trajet tr = trajetHeadDeLaGare(g);
	for (int i=0; i < nbTrajetDeLaGare(g) ; i++){
		printf("%s-%s en %d minutes\n",nomDeGare(g), nomDeGare(gareArvDuTrajet(tr)), tempsDuTrajet(tr));
		tr = trajetNext(tr);
	}
	printf("\n\n");
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare d'arrivee       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomArv);
	fflush(stdin);
	Gare g2 = rechercheGare(r, nomArv);
	if (g2 == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		menuGestionTrajet(r);
		return 1;
	}
	if (retirerUnTrajet(g,g2) == 1){
		menuGestionTrajet(r);
		return 1;
	}
	printf("\n");
	printf("################################################\n");
	printf("#         Le trajet a bien ete Supprime        #\n");
	printf("#          1- Supprimer un autre trajet        #\n");
	printf("#          2- RETOUR                           #\n");
	printf("################################################\n");
	printf("\n");
	long cpt;
	int event =1;
	while(event != 1){
		cpt = lireLong();
		switch (cpt) {
			case 1:
				menuSupTrajet(r);
				event = -1;
				break;
			case 2:
				event = -1;
				break;
			default :
				afficheErreurMenu();
				break;
		}
	}
	return 0;
}

int menuExportationJSON(){
	return 0;
}

int menuGestionAdministration(){
	int event = 1;
	while(event != -1){
		printf("\n");
		printf("################################################\n");
		printf("# De qui voulez vous modifier les informations #\n");
		printf("#                                              #\n");
		printf("#       1- controleur 1                        #\n");
		printf("#       2- controleur 2                        #\n");
		printf("#       3- controleur 3                        #\n");
		printf("#       4- administrateur                      #\n");
		printf("#       5- RETOUR                              #\n");
		printf("################################################\n");
		printf("\n");
		int choixMenu = lireLong();
		fflush(stdin);
		switch(choixMenu) {
			case 1:
				menuChoixModification(choixMenu);
				break;
			case 2:
				menuChoixModification(choixMenu);
				break;
			case 3:
				menuChoixModification(choixMenu);
				break;
			case 4:
				menuChoixModification(choixMenu);
				break;
			case 5:
				event = -1;
				break;
			default:
				afficheErreurMenu();
				break;
		}
	}
	printf("\n");
	return 0;	
}

int menuChoixModification(int n){
	int event = 1;
	char nomFichier1[100]="sauv/controleur1.txt";
	char nomFichier2[100]="sauv/controleur2.txt";
	char nomFichier3[100]="sauv/controleur3.txt";
	char nomFichier4[100]="sauv/admin.txt";
	char ligne[20];
	FILE* id;
	if(n==1){
		id=fopen(nomFichier1,"r");
	}
	else if (n==2){
		id=fopen(nomFichier2,"r");
	}
	else if (n==3){
		id=fopen(nomFichier3,"r");
	}
	else if (n==4){
		id=fopen(nomFichier4,"r");
	}
	else{
		printf("############################################\n");
		printf("#                 erreur                   #\n");
		printf("############################################\n");
		printf("\n");
		return 1;	
	}
	printf("############################################\n");
	printf("        voici vos donnees personnelles     \n");
	while(fgets(ligne,20,id) != NULL) // on lit le fichier tant qu'il n'y a pas d'erreur
	{
		printf("%s\n",ligne);
	}
	printf("############################################\n");	
	fclose(id);
	while(event != -1){
		printf("\n");
		printf("################################################\n");
		printf("#            Que voulez vous faire ?           #\n");
		printf("#                                              #\n");
		printf("#       1- Modifier le mot de passe            #\n");
		printf("#       2- Modifier prenom                     #\n");
		printf("#       3- Modifier nom                        #\n");
		printf("#       4- RETOUR                              #\n");
		printf("################################################\n");
		printf("\n");
		int choixMenu = lireLong();
		fflush(stdin);
		switch(choixMenu) {
			case 1:
				menuModification(choixMenu,n);
				break;
			case 2:
				menuModification(choixMenu,n);
				break;
			case 3:
				menuModification(choixMenu,n);
				break;
			case 4:
				event = -1;
				break;
			default:
				afficheErreurMenu();
				break;
		}
	}
	printf("\n");
	return 0;
}

//######################################################
//######### MENUS DE LA PARTIE CONTROLEUR ##############

int menuControleurVerification(Reseau r){
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
 		fflush(stdin);
 		// si le mot de passe ou le login est faux on demande a l'utilisateur si il veut reesayer la saisie car une erreur de frappe peut arriver
 		if(cpt==5)
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
						cpt=0;
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
 			menuControleur(cpt,r);
 			cpt=-1;
 		}
	}
	return 0;
}
int menuControleur(int n, Reseau r){
	int event = 1 ;
	long choixMenu;
	while(event != -1){
		afficheMenuControleur();
		choixMenu=lireLong();
		printf("\n");
		switch(choixMenu)
		{
			case 1:
				menuRechercheControleur(r);
				break;
			case 2:
				menuChoixModification(n);
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

int menuRechercheControleur(Reseau r){
	long choix;
	char numClient[10];
	printf("\n");
	printf("################################################\n");
	printf("#            Indiquez le numero client         #\n");
	printf("#              que vous recherchez             #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s", numClient);
	printf("\n");
	fflush(stdin);
	printf("####################################################\n");
	rechercheVoyageur(r,numClient);
	printf("####################################################\n");
	int event = 1;
	printf("\n");
	printf("################################################\n");
	printf("#           1- Recherche un autre client       #\n");
	printf("#           2- RETOUR                          #\n");
	printf("################################################\n");
	printf("\n");
	while(event != -1){	
		choix = lireLong();
		switch (choix) {
			case 1:
				menuRechercheControleur(r);
				event = -1;
				break;
			case 2:
				event = -1;
				break;
			default :
				afficheErreurMenu();
				break;
		}
	}
	return 0;
}

int menuModification(int index, int n){
	char nomFichier1[100]="sauv/controleur1.txt";
	char nomFichier2[100]="sauv/controleur2.txt";
	char nomFichier3[100]="sauv/controleur3.txt";
	char nomFichier4[100]="sauv/admin.txt";
	char new[20];
	if(index==1){
		printf("############################################\n");
		printf("#veuillez saisir votre nouveau mot de passe#\n");
		printf("#           19 caracteres maximum          #\n");
		printf("############################################\n");
		printf("\n");
		lire(new,20,stdin);
		fflush(stdin);
	}
	else if(index==2){
		printf("############################################\n");
		printf("#      veuillez saisir votre prenom        #\n");
		printf("#           19 caracteres maximum          #\n");		
		printf("############################################\n");
		printf("\n");
		lire(new,20,stdin);
		fflush(stdin);	
	}
	else if(index==3){
		printf("############################################\n");
		printf("#       veuillez saisir votre nom          #\n");
		printf("#           19 caracteres maximum          #\n");	
		printf("############################################\n");
		printf("\n");
		lire(new,20,stdin);
		fflush(stdin);
	}
	else{
		printf("############################################\n");
		printf("#                 erreur                   #\n");
		printf("############################################\n");
		printf("\n");
		return 1;
	}
	if(n==1){
		modiferDonnee(nomFichier1,index ,new);
	}
	else if (n==2){
		modiferDonnee(nomFichier2,index ,new);
	}
	else if (n==3){
		modiferDonnee(nomFichier3,index ,new);
	}
	else if (n==4){
		modiferDonnee(nomFichier4,index ,new);
	}
	else{
		printf("############################################\n");
		printf("#                 erreur                   #\n");
		printf("############################################\n");
		printf("\n");
		return 1;		
	}
	printf("############################################\n");
	printf("#          Modification enregistree        #\n");
	printf("############################################\n");
	printf("\n");	
	return 0;
}


//######### MENUS DE LA PARTIE CLIENT ##############
int menuClient( Reseau r){
	int event = 1 ;
	long choixMenu;
	while(event != -1){
		afficheMenuClient();
		choixMenu=lireLong();
		printf("\n");
		switch(choixMenu)
		{
			case 1:
				menuRechercheEtChoix(r);
				break;
			case 2:
				menuReservation(r);
				break;
			case 3:
				menuModificationVoyage(r);
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

int menuRechercheEtChoix(Reseau r){
	char nomDep[30] = {0};
	char nomArv[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#            Voici la liste des Gares          #\n");
	printf("################################################\n");
	printf("\n");
	Gare g = gareHead(r);
	for (int i=0; i<tailleReseau(r); i++){
		printf("%s | ",nomDeGare(g));
		g=gareNext(g);
	}
	printf("\n\n");
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare de Depart       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomDep);
	printf("\n");
	fflush(stdin);
	g = rechercheGare(r, nomDep);
	if (g == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		return 1;
	}
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare d'Arrivee       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomArv);
	printf("\n");
	fflush(stdin);
	Gare g2 = rechercheGare(r, nomArv);
	if (g2 == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		return 1;
	}	
	Itineraire itineraireVoyageur = creerItineraireVide();
	itineraireVoyageur = rechercheItineraire(r, g, g2);
	if (itineraireVoyageur == NULL){
		return 1;
	}
	printf("####################################################\n");
	affichageVoyage(r, itineraireVoyageur);
	printf("####################################################\n");
	free(itineraireVoyageur);
	int event = 1;
	long choix;
	printf("\n");
	printf("################################################\n");
	printf("#           1- Recherche un autre Voyage       #\n");
	printf("#           2- RETOUR                          #\n");
	printf("################################################\n");
	printf("\n");
	while(event != -1){	
		choix = lireLong();
		switch (choix) {
			case 1:
				menuRechercheEtChoix(r);
				event = -1;
				break;
			case 2:
				event = -1;
				break;
			default :
				afficheErreurMenu();
				break;
		}
	}
	return 0;
}

int menuReservation(Reseau r){
	char nomDep[30] = {0};
	char nomArv[30] = {0};
	printf("\n");
	printf("################################################\n");
	printf("#            Voici la liste des Gares          #\n");
	printf("################################################\n");
	printf("\n");
	Gare g = gareHead(r);
	for (int i=0; i<tailleReseau(r); i++){
		printf("%s | ",nomDeGare(g));
		g=gareNext(g);
	}
	printf("\n\n");
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare de Depart       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomDep);
	printf("\n");
	fflush(stdin);
	g = rechercheGare(r, nomDep);
	if (g == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		return 1;
	}
	printf("################################################\n");
	printf("#      Tapez le nom de la Gare d'Arrivee       #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s",nomArv);
	fflush(stdin);
	Gare g2 = rechercheGare(r, nomArv);
	if (g2 == NULL){
		printf("\n");
		printf("################################################\n");
		printf("#             La Gare n'existe pas !           #\n");
		printf("################################################\n");
		printf("\n");
		return 1;
	}	
	Itineraire itineraireVoyageur = rechercheItineraire(r, g, g2);
	if (itineraireVoyageur == NULL) {
		return 1;
	}
	Voyageur utilisateur = creerVoyageur( r, itineraireVoyageur);
	if (utilisateur != NULL) {
		printf("\n");
		printf("Voici votre identifant voyageur : %s\n",  idVoyageur(utilisateur) );
	}
	return 0;
}

int menuModificationVoyage(Reseau r){
	long choix;
	char numClient[10];
	printf("\n");
	printf("################################################\n");
	printf("#          Indiquez votre numero client        #\n");
	printf("################################################\n");
	printf("\n");
	scanf("%s", numClient);
	printf("\n");
	fflush(stdin);
	printf("####################################################\n");
	printf("#                Voici votre trajet                #\n");
	printf("####################################################\n");
	int valeur;
	valeur = rechercheVoyageur(r,numClient);
	if(valeur==1){
		return 1;
	}
	printf("####################################################\n");
	int event = 1;
	printf("\n");
	printf("################################################\n");
	printf("#                 1- Modifier                  #\n");
	printf("#                 2- RETOUR                    #\n");
	printf("################################################\n");
	printf("\n");
	while(event != -1){	
		choix = lireLong();
		switch (choix) {
			case 1:
			// inserer fonction modification resa quand fini
				event = -1;
				break;
			case 2:
				event = -1;
				break;
			default :
				afficheErreurMenu();
				break;
		}
	}
	return 0;
}