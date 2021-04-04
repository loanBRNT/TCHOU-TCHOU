#ifndef VOYAGEUR_H
#define VOYAGEUR_H


typedef struct s_voyageur* Voyageur; //décla Opaque struct Voyageur

typedef struct s_place* Place; //décla opaque Struct Place

Voyageur initVoyageur(Reseau, Place, FILE*);

Place initPlace(Reseau, FILE*);

int sauvVoyageur(Train, FILE*);

void suppVoyageur(Reseau r, char* idRecherche);

int rechercheVoyageur(Reseau , char* );

Voyageur creerVoyageur(Reseau, Itineraire);

void tirerNumVoyageur(Reseau r, Voyageur v);

Voyageur mettreSurUnePlace(Reseau r, Train t, Gare gLim, Gare gDep, Itineraire it);

Place creerPlaceVide(Train t, int i);

int ensembleVoyageur(Reseau r);

Voyageur initRepertoire(Reseau, FILE*);

int sauvRepertoire(Reseau r, FILE* fichierRepertoire);

void ajtVoyMemoire(Voyageur v, Reseau r);

void supVoyMemoire(Reseau r);

void chgHeadVoy(Reseau r, Voyageur v);

void chgTailVoy(Reseau r,Voyageur v);

Voyageur modifVoyageur(Reseau r, char* id);

#endif