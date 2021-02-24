#ifndef RESEAUACCESSEUR_H
#define RESEAUACCESSEUR_H


Gare gareHead(Reseau);

Gare gareTail(Reseau);

int tailleReseau(Reseau r);

char* nomDeGare(Gare);

int nbTrajetDeLaGare(Gare g);

Trajet trajetHeadDeLaGare(Gare g);

Trajet trajetTailDeLaGare(Gare g);

Gare gareNext(Gare g);

Gare garePrevious(Gare g);

int tempsDuTrajet(Trajet tr);

char* gareArvDuTrajet(Trajet tr);

Trajet trajetNext(Trajet tr);




#endif