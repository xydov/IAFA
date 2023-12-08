#ifndef __APPLICATION_H__
#define __APPLICATION_H__

/****************************************
 * Interface avec la couche application *
 ****************************************/

/* =========================================================== */
/* ==================== Mode non connecté ==================== */
/* =========================================================== */

/*
 * Lecture de données émanant de la couche application.
 * Paramètres (en sortie):
 *  - donnees : message devant être envoyé (issu de la couche application)
 *  - taille_msg : nombre d'octets de données à émettre (0 si pas de données)
 */
void de_application(unsigned char *donnees, int *taille_msg);

/*
 * Remise de données à la couche application.
 * Paramètres (en entrée):
 *  - donnees : données à remonter à l'application
 *  - taille_msg : taille des données
 * Renvoie :
 *    -> 1 si le récepteur n'a plus rien à écrire (fichier terminé)
 *    -> 0 sinon
 */
int vers_application(unsigned char *donnees, int taille_msg);


#endif
