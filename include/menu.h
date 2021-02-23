#ifndef MENU_H
#define MENU_H
//prototype des fonctions de gestion de chaque menu



// pre-menu administrateur verifie si la personne a accès au menu administrateur
int menuAdminVerification();
// interface du menu administrateur
int menuAdmin();
/* interface des 3 menus accessibles depuis le menu administrateur 
menuGestionTrajet  est l'interface pour la gestion des trajets
menuExportationJSON est celui pour l'exportation des donnees
et menuGestionAdministration est celui pour gerer les mot de passe des personnes
*/
int menuGestionTrajet();
int menuExportationJSON();
int menuGestionAdministration();



// pre-menu controleur verifie si la personne a accès au menu controleur
int menuControleurVerification();
// interface du menu Controleur
int menuControleur();
/* interface des 2 menus accessibles depuis le menu controleur
menuRechercheControleur est l'interface pour la recherche du trajet d'un voyageur avec son numero d'identification
menuAdministrationControleur() est l'interface du menu de gestion des donnees personelle du controleur
*/
int menuRechercheControleur();
int menuAdministrationControleur();



//interface du menu voyageurs
int menuClient();
/*interface des 2 menus accessibles depuis le menu client
 menuRechercheEtChoix interface du menu de recherche et de choix de trajet
  menuReservationEtModification interface du menu de reservation et de modification de son trajet.
*/
int menuRechercheEtChoix();
int menuReservationEtModification();




#endif