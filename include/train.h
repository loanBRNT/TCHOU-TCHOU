#ifndef TRAIN_H
#define TRAIN_H


typedef struct s_train* Train;

typedef struct s_place* Place;


int initItneraireTrain(Reseau r, FILE*);

Train initTrain(Reseau r, FILE*);

int sauvTrain(Reseau r, FILE*);











#endif