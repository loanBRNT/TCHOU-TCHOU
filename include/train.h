#ifndef TRAIN_H
#define TRAIN_H


typedef struct s_train* Train;


Itineraire initItneraireTrain(Reseau r, FILE*);

Train initTrain(Reseau r, FILE*, FILE*);

int sauvTrain(Reseau r, FILE*, FILE*);


Train ajouterTrain(Reseau r);

void ajtTrain(Reseau, Train);

int suppTrain(Reseau r, char* idIdentification);

void enleverTrain(Reseau r);

Train enleverTrainHead(Reseau r, Train t );

Train enleverTrainTail(Reseau r, Train t);

Train rechercheTrain(Reseau r, char* id);

int trainPasVide(Train t);

int gareDansTrain(Gare g, Train t);

int verifierTrain(Reseau r, Gare g);

int trajetDansTrain(Trajet tr, Gare g, Train t);

int verifierTrainTrajet(Reseau r, Gare g, Trajet tr);

int suppGareDansTrain(Reseau r,Gare g);

#endif