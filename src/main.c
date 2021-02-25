#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "pwd.h"
#include "reseau.h"
#include "menu.h"
#include "reseauAccesseur.h"
#include "parcoursGraphe.h"
#define EXIT_SUCESS 0
#define EXIT_FAILURE 1

/* 
    Commande de compilation avec gcc :
    gcc src/main.c -o bin/prog -I include -L lib -lmingw32
    gcc src/* -o prog -I include -L lib -lmingw32
*/ 


int main(int argc, char const *argv[])
{
	/* initialisation du reseau*/
	Reseau reseau = initReseau();
	ajouterUneGare(reseau,"Andore");
	ajouterUnTrajet(reseau,gareTail(reseau),"Paris",90);
	ajouterUnTrajet(reseau,rechercheGare(reseau,"Paris"),nomDeGare(gareTail(reseau)),90);
	/* lance l'affichage du menu principale
	  puis demande le numero du menu souhaite et lance la fonction de gestion du menu selectionne 
	  si le numero n'est pas bon on redemande un numero de menu
	  le choix numero 4 modifie la valeur de la variable event afin de sortir de la boucle et pouvoir arreter le programme
	*/
	int event = 1 ;
	int choixMenu;
	while(event != -1){
		afficheMenuPrincipal();
		scanf("%d",&choixMenu);
		printf("\n");
		switch(choixMenu)
		{
			case 1:
				menuAdminVerification();
				break;
			case 2:
				menuControleurVerification();
				break;
			case 3:
				menuClient();
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