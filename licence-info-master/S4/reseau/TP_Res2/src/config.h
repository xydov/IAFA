/****************************************************************
 *  Lecture de variables de configuration à partir d'un fichier *
 *                                                              *
 * E. Lavinal - Université de Toulouse III - Paul Sabatier      *
 ****************************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define FICHIER_CONF "../config.txt"

#define FICHIER_IN "FICHIER_IN"
#define FICHIER_OUT "FICHIER_OUT"
#define PROBA_PERTE_E "PROBA_PERTE_E"
#define PROBA_PERTE_R "PROBA_PERTE_R"
#define PROBA_ERREUR_E "PROBA_ERREUR_E"
#define PROBA_ERREUR_R "PROBA_ERREUR_R"

void conf_fichier_emission(char * fichier_emission);

void conf_fichier_reception(char * fichier_reception);

float conf_proba_perte(int role);

float conf_proba_erreur(int role);

#endif
