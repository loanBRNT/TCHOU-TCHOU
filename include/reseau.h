#ifndef RESEAU_H
#define RESEAU_H

/*
On definit les 3 pointeurs sur 3 structures utiles pour manier le reseau routier de manière dynamique ! 

s_reseau prend en charge la totalite du reseau et permet de lister des elements s_gare (des Gares) via une liste doublement chainée

s_gare permet de gerer une gare et de gérer l'ensemble des trajets passant par cette derniere (elle les gére via une seconde liste chainée)

s_trajet permet de gérer un trajet particulier il prend la gare d'arrivée et la pondération
*/

typedef struct s_reseau* Reseau;

typedef struct s_gare* Gare;

typedef struct s_trajet* Trajet;



int initTrajet(Reseau, Gare, FILE*); //Initialise les chemins qui partent de la gare en parametre à partir de trajets.txt

int initGare(Reseau, FILE*); //Initialise les Gares au reseau à partir du fichier reseau.txt

Reseau initReseau(); //Initialisation a partir des fichiers reseau.txt et trajet.txt

Reseau sauvReseau(Reseau); //Sauvegarder le reseau dans le fichier reseau.txt et trajet.t

void closeReseau(Reseau); //Liberer la memoire

int ajouterUneGare(Reseau, char*); //ajoute une gare au réseau !

int ajouterUnTrajet(Gare, Gare, int); 
/*
ajoute un trajet entre les deux gares
*/

int retirerUneGare(Reseau, Gare); //retire une gare ainsi que ses trajets (DEPART + ARRIVE) du reseau

int retirerUnTrajet(Reseau r, Gare,Gare);  //retire un trajet entre deux gares (dans les deux sens)

#endif