#include <stdlib.h>
#include <stdio.h>
#include "reseau.h"

struct s_gare{
	char* nomGARE; //Le nom de la Gare
	int numId; //Numero d'identification de la gare (genre un nombre >0)
	Trajet listeTrajet; //La liste chainee des trajets passant par la gare
	Gare next; //La gare suivante (numero +1)
	Gare previous; //La gare precedente (numero -1)
};

struct s_trajet{
	int ponderation; //le temps de transport
	int gareArriveId; //La gare d'arrivee du trajet via son indice de position dans la liste
	Trajet next; //Indique le trajet suivant de la même gare. Par convention le dernier pointe sur NULL
};

struct s_reseau{
	Gare head: //Indice de la premiere gare
	int size; //taille du reseau (nombe de gare)
};