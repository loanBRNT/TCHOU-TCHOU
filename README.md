# TCHOU-TCHOU
Projet en Structure de Donnée. Gestion d'une compagnie de chemin de fer.

Les explications du codes sont donnés dans documentation !


# Axes à réaliser & Methode de résolution

## Interface administrateur

L'interface administrateur doit permettre de nombreuses choses. L'accès y est protégé par un mot de passe UNIQUE (chiffré) sans identifiant.

### Gestion des Trajets

L'administrateur doit pouvoir ajouter/enlever une gare. Ajouter ou enlever un trajet entre gare


1. Si le choix du graphe pour les trajets (non orienté) : Dictionnaire à deux dimensions</li>
2. Un ensemble de variable pour chaque gare, représentant chacune un trajet</li>    

### Exportation des Trajets + Passagers

*Se renseigner sur le fichir JSON*

### Administration

Changer le mot de passe Admin, changer le mot de passe d'un controleur *REGARDER COMMENT CHIFFRE LES MDP*

## Interface Contrôleur

L'interface controleur permet un accès modéré à la gestion des trains.

### Recherche

Recherche d'un voyageur à travers son numero

### Administration

Changer son mot de passe et ses informations

## Interface Client

### Recherche et Choix d'un Trajet

Premiere entree : Gare de depart
Deuxieme entree : Gare d'arrivée

Choix parmis les heures de departs disponibles et les trajets possibles

Si entree inconnue on redemande l'entree

### Reservation

Donne un numero d'identification a 6 chiffres + 2 lettres (Initiale du client) exemple : 123456BL

--> Entre le numero dans un fichier sauv voyageurs format : NOM NUM Gare_DEPART Gare_ARRIVEE
--> Entre le numero dans le fichier du trajet ou des trajets correspondants

Bloquer 1 place pour le voyageur dans le ou les trains qu'il prend

### Modifier son trajet

*Pas encore regardé cet aspect*

## Représenter les Gares + trajets

Possibilité de choisir la représentation via un graphe non orienté

Le temps peut servir de pondération pour les arretes

![Schema Gare](img/base_trajet.png "Schema Gare")

## Generer les tickets de trajets

*Pas encore regardé cet aspect*

## Naviguation dans les menus

Basique, sans graphisme (utilisation de SIWTCH)

Un menu où l'utilisateur indique son choix via un numero.

Chaque choix de menu est entété par "###################ADMINISTRATEUR################" par exemple ou bien (CONTROLEUR/CLIENT)

le format doit être le même : 
" 1. choix 1
 2. choix 2 "

En cas d'entrée incorect on repose la question.


## Gestion des Trains

Plusieurs trains à des horaires programmés, chaque Train part de la gare de Gauche va jusqu'au bout, et repars dans l'autre sens : 
T1 -> Premier depart 00:00 (modulo 03:00) (4 trains sur le trajet en simultanée)
T2 -> Premier depart 00:00 (modulo 04:00) (4 trains sur le trajet en simultanée)
T3 -> Premier depart 00:00 (modulo 03:00) (2 trains sur le trajet en simultanée)
T4 -> Premier depart 00:00 (modulo 03:30) (2 trains sur le trajet en simultanée)

## Gestion des mdp et comptes

Faire un fichier nom prenom nom_d_utilisateurs mot_de_passe *REGARDER COMMENT CHIFFRE*
