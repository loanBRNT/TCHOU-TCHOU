# DOCUMENTATION DU PROJET TCHOU-TCHOU
Projet et documentation entièrement rédigé par Bernat Loan et Gaudillat Eliott

# Sommaire

1. [Introduction et présentation générale](#intro)
2. [Representation du reseau en memoire](#reseau)
    1. [reseau.h](#re)
    2. [reseauAcesseur.h](#reAc)
3. [Naviguation dans le menu](#menu)
4. [L'algorithme de recherche du plus court chemin](#recherche)




## Introduction et présentation générale <a name="intro"></a>

A la manière d'une javadoc, ce document recense la totalité des fonctions déclarées et utilisées du programme TCHOU-TCHOU. Nous vous conseillons d'utiliser `CTRL + F` pour taper la fonction que vous recherchez. Pour le fonctionnement INTERNE des fonctions, se référrer aux codes sources directement ! Le document explique uniquement : "Pourquoi ? Avec quoi ? Pour donner quoi ?" de chaque fonction. Si besoin, chaque partie est légerement expliqué en introduction de ces dernières (structures, fonctions particulière...).

**Bonne lecture !**

## Representation du reseau routier <a name="reseau"></a>

Nous avons choisis de representer le réseau avec un graphe **non orienté**. Une gare représente un sommet, un "chemin" entre deux gares représente une arrête.
Nous n'avons pas tenu compte des "4 trajets initiaux", ils nous ont servis pour relier les villes entre elles et tenir compte de la ponderation. **Par la suite, nous appèlerons "trajets" une arrête entre deux gares.**
![Schema Gare](img/base_trajet.png "Schema Gare")

Pour représenter ce graphe en mémoire, nous avons utilisés **une liste doublement chainée**, où chaque élement de cette liste est une gare et possède **une liste chainée** d'éléments (correspondants aux chemins de la gare). Pour ce faire nous utilisons 3 structures :
1. struct s_reseau
2. struct s_gare
3. struct s_trajet

![Schema Reseau](img/explicationReseau.png "Schema Reseau")

Pour sauvegarder et récupérer le réseau entre chaque utilisation du programme, nous utilisons deux fichiers : _reseau.txt_ et _trajet.txt_ dans lesquels nous ecrivons respectivement le nom de l'ensemble des gares du réseau, et l'ensemble des trajets de chaque gare séparé par un '/'.

### Fonction et structure de Gestion du reseau <a name="re"></a>

**----- Reseau -----** `typedef struct s_reseau* Reseau`

C'est un pointeur sur la structure s_reseau, il va nous permettre d'utiliser de manière dynamique notre réseau !

**----- Gare -----** `typedef struct s_gare* Gare`

C'est un pointeur sur la structure s_gare. Il nous permet de gérer nos gares de manière dynamique.

**----- Trajet -----** `typedef struct s_trajet* Trajet`

C'est un pointeur sur la structure s_trajet. Il nous permet de gérer l'ensemble des trajets de chaque gare de manière dynamique.

**----- initReseau -----** `Reseau initReseau()`

Implémente en mémoire le réseau routier **complet** (avec les gares et les trajets initialisé) à partir de deux fichiers texte.

***Parametre*** : AUCUN

***Retour*** : _Reseau_ un pointeur vers l'emplacement du reseau en mémoire

**----- initGare -----** `int initGare(Reseau, FILE*)`

Implémente en mémoire une gare dans le réseau routier à partir d'un fichier texte (sauvegarde précédente).

***Parametre*** : _Reseau_ un pointeur vers l'emplacement du reseau en mémoire, _FILE*_ un pointeur vers le fichier reseau.txt

***Retour*** : 0 si la gare a pu être stockée en mémoire, 1 sinon.


**----- initTrajet -----** `int initTrajet(Gare, FILE*)`

Implémente en mémoire le(s) trajet(s) d'une gare donné en paramètre à partir d'un fichier texte (sauvegarde précédente).

***Parametre*** : _GARE_ La gare à qui appartient le trajet que l'on va entrer en mémoire, _FILE*_ un pointeur vers le fichier trajet.txt

***Retour*** : 0 si le trajet a pu être stocké en mémoire, 1 sinon.

**----- sauvReseau -----** `Reseau sauvReseau(Reseau)`

Sauvegarde dans les fichiers trajet.txt et reseau.txt le réseau routier.

***Parametre*** : _Reseau_ un pointeur vers l'emplacement du reseau en mémoire

***Retour*** : _Reseau_ un pointeur vers l'emplacement du reseau en mémoire

**----- closeReseau -----** `void closeReseau(Reseau)`

libère la mémoire prise par le réseau.

***Parametre*** : _Reseau_ un pointeur vers l'emplacement du reseau en mémoire

___Retour___ : _void_

**----- ajouterUneGare -----** `(int ajouterUneGare(Reseau, char*)`

Ajoute une gare, dont le nom est passé en parametre, au réseau routier.

***Parametre*** : _Reseau_ un pointeur vers l'emplacement du reseau en memoire, _char*_ le nom de la gare a ajouté

***Retour*** :  0 si la gare a été ajouté avec succès, 1 sinon

**----- ajouterUnTrajet -----** `int ajouterUnTrajet(Gare, Gare, int)`

Ajoute un trajet entre deux gares (aller-retour) avec un temps donné dans le réseau routier.

***Parametre*** : _Gare_ Un pointeur vers une des deux gares du trajet,  _Gare_ Un pointeur vers la seconde gare du trajet, _int_ le temps en minute de trajet entre les deux gares

***Retour*** : 0 si le trajet a pu être implémenté au réseau, 1 sinon

### Accesseurs sur les structures du reseau<a name="reAc"></a>

Afin de pouvoir accéder aux paramètres des 3 structures s_gare, s_reseau et s_trajets dans tous le programme, nous avons besoin d'utiliser des accesseurs sur ces paramètres.

**----- gareHead -----** `Gare gareHead(Reseau)`

***Parametre*** : _Reseau_ un pointeur vers l'emplacement du reseau en memoire

***Retour*** : _Gare_ un pointeur vers la Gare en tête de la liste doublement chainée de gare du réseau

**----- gareTail -----** `Gare gareHead(Reseau)`

***Parametre*** : _Reseau_ un pointeur vers l'emplacement du reseau en memoire

***Retour*** : _Gare_ un pointeur vers la Gare en queue de la liste doublement chainée de gare du réseau

**----- tailleReseau -----** `int tailleReseau(Reseau)`

***Parametre*** : _Reseau_ un pointeur vers l'emplacement du reseau en memoire

***Retour*** : _int_ le nombre de gare dans le réseau.

**----- nomDeGare -----** `char* nomDeGare(Gare)`

***Parametre*** :  _Gare_ un pointeur vers une Gare du reseau

***Retour*** : _char*_ le nom de la gare passé en parametre

**----- nnTrajetDeLaGare -----** `int nbTrajetDeLaGare(Gare)`

***Parametre*** :  _Gare_ un pointeur vers une Gare du reseau

***Retour*** : _int_ le nombre de trajets amenant à la Gare passé en parametre (son nombre de "voisin")

**----- trajetHeadDeLaGare -----** `Trajet trajetHeadDeLaGare(Gare)`

***Parametre*** :  _Gare_ un pointeur vers une Gare du reseau

***Retour*** : _Trajet_ Un pointeur vers l'emplacement du trajet en tête de la liste chainée des trajets de la Gare

**----- trajetTailDeLaGare -----** `Trajet trajetTailDeLaGare(Gare)`

***Parametre*** :  _Gare_ un pointeur vers une Gare du reseau

***Retour*** : _Trajet_ un pointeur vers l'emplacement du trajet en queue de la liste chainée des trajets de la Gare

**----- gareNext -----** `Gare gareNext(Gare)`

***Parametre*** :  _Gare_ un pointeur vers une Gare du reseau

***Retour*** : _Gare_ un pointeur vers la Gare suivante du réseau (suivante au sens de la liste chainée, pas de lien avec les itinireraires, trajets, chemin entre les gares)

**----- garePrevious -----** `Gare garePrevious(Gare)`

***Parametre*** :  _Gare_ un pointeur vers une Gare du reseau

***Retour*** : _Gare_ un pointeur vers la Gare précédente du réseau (précédente au sens de la liste chainée, pas de lien avec les itinireraires, trajets, chemin entre les gares)

**----- tempsDuTrajet -----** `int tempsDuTrajet(Trajet tr);`

***Parametre*** :  _Trajet_ un pointeur vers l'emplacement d'un trajet entre deux gares en mémoire.

***Retour*** : _int_ le temps de trajet en minute du trajet passé en paramètre

**----- gareArvDuTrajet -----** `Gare gareArvDuTrajet(Trajet tr);`

***Parametre*** :  _Trajet_ un pointeur vers l'emplacement d'un trajet entre deux gares en mémoire.

***Retour*** : _Gare_ un pointeur vers la gare d'arrivee du trajet donne en parametre

**----- trajetNext -----** `Trajet trajetNext(Trajet tr);`

***Parametre*** :  _Trajet_ un pointeur vers l'emplacement d'un trajet entre deux gares en mémoire.

***Retour*** : __Trajet__ un pointeur vers l'emplacement du trajet suivant en mémoire de la Gare (suivante au sens de la liste chainée)

## Naviguation dans le menu <a name="menu"></a>


## L'algorithme de recherche du plus court chemin <a name="recherche"></a>

Notre algorithme de recherche du plus court chemin est fondé autour de l'algorithme de Dijkstra.

![SchemaDijkstra](https://upload.wikimedia.org/wikipedia/commons/5/57/Dijkstra_Animation.gif)
