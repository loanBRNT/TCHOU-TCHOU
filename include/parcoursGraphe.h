#ifndef PARCOURS_GRAPHE_H
#define PARCOURS_GRAPHE_H

typedef struct s_itineraire* Itineraire;

typedef struct s_sommet* Sommet;

typedef struct s_ensemble* Ensemble;

//On ajoute un sommet à l'ensemble (graphe) , selon le trajet qui y amene et le sommet Pere (le sommet correspondant a la gare de depart du trajet)
int ajoutSommet(Ensemble, Trajet, Sommet); 

//mis a jour de la distance entre le sommet et la gare Gdep (si elle est plus rapide via le nouv sommet pere)
int majDistance(Trajet, Sommet, Sommet); 

int testVoisin(Ensemble, Sommet); //on reharde les voisins (voisins = s'il y a un trajet qui les relie) du sommet donné en parametre

Gare rechercheGare(Reseau, char*); //retourne la gare avec le nom correspondant au char* passé en parametre ou NULL si elle n'existe pas

Trajet rechercheTrajet(Gare, Gare); //retourne le trajet qui va de la 1ere Gare passé en parametre au 2nd. Ou NULL s'il n'exsite pas

/*fonction initiale de la recherche d'un itineraire, elle initialise tout l'algo de recherche
 en fonction du reseau a etudier et de la gare de de pet celle d'arv, elle contient egalement la boucle d'execution de l'algo et retourne l'itineraire */
Itineraire rechercheItinireraire(Reseau, Gare, Gare);

Ensemble initialisationGraphe(Gare); //Initialise l'ensemble graphe autour de la Gare de Depart

void freeGrapheRecherche(Ensemble); //libere la memoire prise par le graphe et les sommets


Itineraire creerItineraireVide(); //creer un itineraire vide (init des trains)

#endif