#ifndef CLIENT_H
#define CLIENT_H


void affichageVoyage(Reseau, Itineraire);

Train rechercheTrainCorres(Reseau, Gare, Trajet);

int modifArv(Reseau r, Itineraire it);

void modifAjtTrajetFin(Reseau r, Itineraire it);

#endif