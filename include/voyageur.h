#ifndef VOYAGEUR_H
#define VOYAGEUR_H


typedef struct s_voyageur* Voyageur;

typedef struct s_place* Place;

Voyageur initVoyageur(Place, FILE*);

Place initPlace(FILE*);











#endif