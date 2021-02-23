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
	initReseau();
	int event = 1 ;
	int choixMenu;
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
	printf("###########################################\n");
	printf("\n");
	
	while(event != -1){
		printf("###########################################\n");
		printf("#           choisissez un menu            #\n");
		printf("###########################################\n");
		printf("\n");
		scanf("%d",&choixMenu);
		printf("\n");
		switch(choixMenu)
		{
			case 1:
				printf("###########################################\n");
				printf("# Vous avez choisi le menu ADMINISTRATEUR #\n");
				printf("###########################################\n");
				menuAdmin();
				break;
			case 2:
				printf("###########################################\n");
				printf("#   Vous avez choisi le menu CONTROLEUR   #\n");
				printf("###########################################\n");
				menuControleur();
				break;
			case 3:
				printf("###########################################\n");
				printf("#     Vous avez choisi le menu CLIENT     #\n");
				printf("###########################################\n");
				menuClient();
				break;
			case 4:
				printf("###########################################\n");
				printf("#       A BIENTOT SUR NOTRE RESEAU        #\n");
				printf("###########################################\n");
				event = -1;
				break;
			default:
				printf("###########################################\n");
				printf("# Vous n'avez pas choisi un menu correct  #\n");
				printf("###########################################\n");
				break;
		}
	printf("\n");
	}

	return 0;
}