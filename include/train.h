#ifndef TRAIN_H
#define TRAIN_H


typedef struct s_train* Train;


Itineraire initItneraireTrain(Reseau r, FILE*);

Train initTrain(Reseau r, FILE*, FILE*);

int sauvTrain(Reseau r, FILE*);











#endif