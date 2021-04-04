#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwd.h"
#include "reseau.h"
#include "menu.h"
#include "parcoursGraphe.h"
#include "train.h"
#include "voyageur.h"
#include "reseauAccesseur.h"
#include "itineraireAccesseur.h"
#include "main.h"
#include "client.h"
#include "trainVoyageurAccesseur.h"
#include "gestionjson.h"

#define EXIT_SUCESS 0
#define EXIT_FAILURE 1

/* 
    Commande de compilation avec gcc :
    gcc src/* -o prog -I include -L lib -lmingw32
*/ 


int main(int argc, char const *argv[])
{

	/* initialisation du reseau*/
	Reseau reseau = initReseau();

	/* lance l'affichage du menu principale
	  puis demande le numero du menu souhaite et lance la fonction de gestion du menu selectionne 
	  si le numero n'est pas bon on redemande un numero de menu
	  le choix numero 4 modifie la valeur de la variable event afin de sortir de la boucle et pouvoir arreter le programme
	*/
	afficheMessageBienvenue();
	int event = 1 ;
	long choixMenu;
	while(event != -1){
		afficheMenuPrincipal();
		choixMenu=lireLong();
		printf("\n");
		switch(choixMenu)
		{
			case 1:
				menuAdminVerification(reseau);
				break;
			case 2:
				menuControleurVerification(reseau);
				break;
			case 3:
				menuClient(reseau);
				break;
			case 4:
				afficheMessageQuitter();
				event = -1;
				break;
			default:
				afficheErreurMenu();
				break;
		}
	printf("\n");
	}
	//Sauvegarde et Fermeture du Reseau (liberation de la memoire)
	sauvReseau(reseau);
	closeReseau(reseau);
	return 0;
}