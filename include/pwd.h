#ifndef PWD_H
#define PWD_H
/* fichier .h des fonctions en lien avec la gestion des accès sécurisé par mot de passe (pwd) et identifiant(login)
*/
//fonction de verification des identifiant de connexion de mot l admin
int verifierPwdAdmin();
//fonction verification d'un controleur par son identifiant et son mot de passe
int verifierLogControleur();
//fonction similiaire a fgets qui remplace le \n par \0 afin de comparer une ligne avec une chaine de caractere
int lire(char*,int,FILE*);
// fonction dérivée de lire afin de lire un long
long lireLong();

void modiferDonnee(char*,int,char*);


#endif