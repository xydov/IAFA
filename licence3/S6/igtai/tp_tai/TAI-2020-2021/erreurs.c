#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "erreurs.h"


/*
 * Fonction a appeler en début de main pour initialiser la gestion des erreurs
 */
char *InitMesg(char *argv[])
{
  static char *Prog=NULL;

  if (Prog==NULL)
  {
    if ((Prog=strrchr(argv[0],'/')))
      Prog++;
    else
      Prog=argv[0];
  }
  return Prog;
}

/*
 * Affichage d'un message formaté sur stderr
 */
void Mesg(const char *Msg, ...)
{
  va_list Params;

  va_start(Params, Msg);
  vfprintf(stderr, Msg, Params);
  va_end(Params);
}

/*
 * Affichage de la syntaxe d'appel d'un opérateur sur stderr
 */
void Usage(char *Syntaxe)
{
  char *Ligne, *Copie;

  Copie=malloc(strlen(Syntaxe)+1);
  strcpy(Copie,Syntaxe);
  Mesg("SYNTAXE\n");
  Ligne=strtok(Copie,"\n");
  while (Ligne!=NULL)
  {
    Mesg("\t%s %s\n",InitMesg(NULL),Ligne);
    Ligne=strtok(NULL,"\n");
  }
  free(Copie);
}

/*
 * Affichage de la description d'un code de retour surn stderr
 */
void Code(int ExitStatus, char *Description)
{
  Mesg("\t%d : %s\n",ExitStatus,Description);
}

/*
 * Affichage d'un message d'erreur sur stderr
 */
void Erreur(char *Msg)
{
  Mesg("[%s] %s\n",InitMesg(NULL),Msg);
}
