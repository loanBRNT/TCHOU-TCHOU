#ifndef CLIENT_H
#define CLIENT_H


void affichageVoyage(Reseau, Itineraire);

Train rechercheTrain(Reseau, Gare, Trajet);

void modifArv(Reseau r, Itineraire it);

void modifAjtTrajetFin(Reseau r, Itineraire it);

#endif