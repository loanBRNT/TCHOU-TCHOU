#ifndef MENU_H
#define MENU_H
//prototype des fonctions de gestion de chaque menu

//fonction afffichage des differents menus
void afficheMenuPrincipal();
void afficheMenuAdmin();
void afficheMenuControleur();
void afficheMenuClient();
void afficheErreurMenu();
void afficheMessageQuitter();



//fonctions des menus de la partie administrateur
// pre-menu administrateur verifie si la personne a accès au menu administrateur
int menuAdminVerification(Reseau r);
// interface du menu administrateur
int menuAdmin(Reseau r);
/* interface des 3 menus accessibles depuis le menu administrateur 
menuGestionTrajet  est l'interface pour la gestion des trajets
menuExportationJSON est celui pour l'exportation des donnees
et menuGestionAdministration est celui pour gerer les mot de passe des personnes
*/
int menuGestionTrajet(Reseau r);
int menuExportationJSON();
int menuGestionAdministration();
int menuAjouteGare(Reseau r); //saisie sans espace et avec chiffre
int menuSupGare(Reseau r);
int menuAjouteTrajet(Reseau r);
int menuSupTrajet(Reseau r);
int menuChoixModification(int);
int menuModification(int, int);





//fonctions des menus de la partie controleur
// pre-menu controleur verifie si la personne a accès au menu controleur
int menuControleurVerification(Reseau);
// interface du menu Controleur
int menuControleur(int,Reseau);
/* interface des 2 menus accessibles depuis le menu controleur
menuRechercheControleur est l'interface pour la recherche du trajet d'un voyageur avec son numero d'identification
menuAdministrationControleur() est l'interface du menu de gestion des donnees personelle du controleur
*/
int menuRechercheControleur(Reseau);
//fonctions des menus de la partie client





//interface du menu voyageurs
int menuClient(Reseau);
/*interface des 2 menus accessibles depuis le menu client
 menuRechercheEtChoix interface du menu de recherche et de choix de trajet
  menuReservationEtModification interface du menu de reservation et de modification de son trajet.
*/
int menuRechercheEtChoix(Reseau);
int menuReservation(Reseau);
int menuModificationVoyage(Reseau);








#endif