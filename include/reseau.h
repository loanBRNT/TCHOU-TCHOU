#ifndef RESEAU_H
#define RESEAU_H

typedef struct s_reseau* Reseau;

typedef struct s_gare* Gare;

typedef struct s_trajet* Trajet;

int initTrajet(Gare, FILE*); //Ajoute les chemins qui partent de la gare en parametre

int initGare(Reseau, FILE*, FILE*); //Ajoute une Gare au reseau à partir du fichier

Reseau initReseau(); //Initialisation a partir des fichiers reseau.txt et trajet.txt

Reseau sauvReseau(Reseau); //Sauvegarder le reseau dans le fichier reseau.txt et trajet.t

void closeReseau(Reseau); //Liberer la memoire

#endif