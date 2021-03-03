#ifndef PARCOURS_GRAPHE_H
#define PARCOURS_GRAPHE_H

typedef struct s_itineraire* Itineraire;

typedef struct s_sommet* Sommet;

typedef struct s_ensemble* Ensemble;


int ajoutSommet(Ensemble, Trajet, Gare);

int majDistance(Gare, Trajet, Sommet);

int testVoisin(Ensemble, Sommet);

Gare rechercheGare(Reseau, char*); //retourne la gare avec le nom correspondant au char* passé en parametre ou NULL si elle n'existe pas

Trajet rechercheTrajet(Gare, Gare); //retourne le trajet qui va de la 1ere Gare passé en parametre au 2nd. Ou NULL s'il n'exsite pas


#endif