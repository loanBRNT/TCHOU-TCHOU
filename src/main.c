#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "pwd.h"
#include "reseau.h"
#include "menu.h"

/* 
    Commande de compilation avec gcc :
    gcc src/main.c -o bin/prog -I include -L lib -lmingw32
    gcc src/* -o prog -I include -L lib -lmingw32
*/ 


int main(int argc, char const *argv[])
{
	/* initialisation du reseau*/
	initReseau();
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
	return 0;
}