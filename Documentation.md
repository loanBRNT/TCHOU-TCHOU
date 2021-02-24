# DOCUMENTATION DU PROJET TCHOU-TCHOU
Projet et documentation entièrement rédigé par Bernat Loan et Gaudillat Eliott

# Sommaire

1. [Introduction et présentation générale](#intro)
2. [Representation du reseau en memoire](#reseau)
    1. [reseau.h](#re)
    2. [reseauAcesseur.h](#reAc)
3. [Naviguation dans le menu](#menu)








## Introduction et présentation générale <a name="intro"></a>

## Representation du reseau routier <a name="reseau"></a>

Nous avons choisis de representer le réseau avec un graphe **non orienté**. Une gare représente un sommet, un "chemin" entre deux gares représente une arrête.
Nous n'avons pas tenu compte des "4 trajets initiaux", ils nous ont servis pour relier les villes entre elles et tenir compte de la ponderation. **Par la suite, nous appèlerons "trajets" une arrête entre deux gares.**
![Schema Gare](img/base_trajet.png "Schema Gare")

Pour représenter ce graphe en mémoire, nous avons utilisés une liste doublement chainée, où chaque élement de cette liste est une gare et possède une liste chainée d'éléments (correspondants aux chemins de la gare). Pour ce faire nous utilisons 3 structures :
1. struct s_reseau
2. struct s_gare
3. struct s_trajet

### Fonction de Gestion du reseau <a name="re"></a>

### Accesseurs sur les structures du reseau<a name="reAc"></a>

## Naviguation dans le menu <a name="menu"></a>
