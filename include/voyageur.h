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

int ensembleVoyageur(Reseau r); //a part

Voyageur initRepertoire(Reseau, FILE*);

int sauvRepertoire(Reseau r, FILE* fichierRepertoire);

void ajtVoyMemoire(Voyageur v, Reseau r); //manip

void supVoyMemoire(Reseau r); //manip

void chgHeadVoy(Reseau r, Voyageur v); //manip

void chgTailVoy(Reseau r,Voyageur v); //manip

Voyageur modifVoyageur(Reseau r, char* id);

#endif