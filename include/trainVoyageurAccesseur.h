#ifndef TRAINVOYAGEURACCESSEUR_H
#define TRAINVOYAGEURACCESSEUR_H

//struct train


Place placeDuTrain(Train t, int rang);

char* idTrain(Train t);

Itineraire cheminTrain(Train t);

Train trainNext(Train t);

Train trainPrevious(Train t);


//struct place

int nbVoyageurSurLaPlace(Place p);

char* idPlace(Place p);

Voyageur voyageurHeadPlace(Place p);

Voyageur voyageurTailPlace(Place p);

//struct Voyageur

char* idVoyageur(Voyageur v);

char* nomVoyageur(Voyageur v);

char* prenomVoyageur(Voyageur v);

Itineraire cheminVoyageur(Voyageur v);

Voyageur voyageurNext(Voyageur v);

#endif