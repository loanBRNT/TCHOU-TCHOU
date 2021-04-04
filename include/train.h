#ifndef TRAIN_H
#define TRAIN_H


typedef struct s_train* Train; //declaration Opaque de la structure Train


Itineraire initItneraireTrain(Reseau r, FILE*); 

Train initTrain(Reseau r, FILE*, FILE*);

int sauvTrain(Reseau r, FILE*, FILE*); 


Train ajouterTrain(Reseau r);

void ajtTrain(Reseau, Train); //MANIPULATION

int suppTrain(Reseau r, char* idIdentification);

void enleverTrain(Reseau r); //NANIP

Train enleverTrainHead(Reseau r, Train t ); //manip

Train enleverTrainTail(Reseau r, Train t); //manip

Train rechercheTrain(Reseau r, char* id); 

int trainPasVide(Train t);

int gareDansTrain(Gare g, Train t);

int verifierTrain(Reseau r, Gare g);

int trajetDansTrain(Trajet tr, Gare g, Train t);

int verifierTrainTrajet(Reseau r, Gare g, Trajet tr);

int suppGareDansTrain(Reseau r,Gare g);

int suppTrajetDansTrain(Reseau r, Gare g, Trajet tr);

Itineraire modifItineraireTrainTrajet(Train t, int i); //manip

Itineraire modifItineraireTrain(Train t, int i); //manip

void affichageEtatReseau(Reseau r); //A PART

#endif