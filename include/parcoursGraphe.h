#ifndef PARCOURS_GRAPHE_H
#define PARCOURS_GRAPHE_H

typedef struct s_itineraire* Itineraire;

typedef struct s_sommet* Sommet;

typedef struct s_ensemble* Ensemble;


Gare rechercheGare(Reseau, char*); //retourne la gare avec le nom correspondant au char* passé en parametre ou NULL si elle n'existe pas

Trajet rechercheTrajet(Gare, char*); //retourne le trajet qui va de la Gare passé en parametre au char*. Ou NULL s'il n'exsite pas






#endif