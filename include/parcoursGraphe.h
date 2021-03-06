#ifndef PARCOURS_GRAPHE_H
#define PARCOURS_GRAPHE_H

typedef struct s_itineraire* Itineraire;

typedef struct s_sommet* Sommet;

typedef struct s_ensemble* Ensemble;


int ajoutSommet(Ensemble, Trajet, Gare); //ajout d'un sommet dans l'algo de recherche

int majDistance(Gare, Trajet, Sommet); //mis a jour de la distance entre la gare de depart et le sommet

int testVoisin(Ensemble, Sommet); //on reharde les voisins du sommet donné en parametre

Gare rechercheGare(Reseau, char*); //retourne la gare avec le nom correspondant au char* passé en parametre ou NULL si elle n'existe pas

Trajet rechercheTrajet(Gare, Gare); //retourne le trajet qui va de la 1ere Gare passé en parametre au 2nd. Ou NULL s'il n'exsite pas

Itineraire rechercheItinireraire(Reseau, Gare, Gare);

Ensemble initialisationGraphe(Reseau, Gare);

#endif