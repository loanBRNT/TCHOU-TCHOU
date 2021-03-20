#ifndef VOYAGEUR_H
#define VOYAGEUR_H


typedef struct s_voyageur* Voyageur;

typedef struct s_place* Place;

Voyageur initVoyageur(Reseau, Place, FILE*);

Place initPlace(Reseau, FILE*);

int sauvVoyageur(Train, FILE*);

Voyageur rechercheVoyageur(Reseau , char* );


Voyageur creerVoyageur(char* nom, char* prenom, char* identifiant, Itineraire it);




#endif