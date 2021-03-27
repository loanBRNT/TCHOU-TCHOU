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
#endif