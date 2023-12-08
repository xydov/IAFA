#include <stdio.h>
#include <string.h>
#include "limace.h"
#include "erreurs.h"
#include "tai.h"

/* Codes de retour */
#define OK 0
#define HELP 1
#define ERR_NB_PARAM 2
#define ERR_IM_IN 3
#define ERR_IM_TYPE 4
#define ERR_ES_IN 5
#define ERR_IM_OUT 6

void Syntaxe(void)
{
  Usage("ImageEntree.pbm ElementStructurant.mx ImageSortie.pbm\n"
        "-h\n");
}

void Description(void)
{
  Mesg("RÔLE\n");
  Mesg("\tDilatation d'une image binaire\n");
  Mesg("ARGUMENTS\n");
  Mesg("\tImageEntree : nom du fichier en entrée (format PBM)\n");
  Mesg("\tElementStructurant : nom du fichier (format Matrix) contenant des 0 \n"
	     "\tet des 1\n");
  Mesg("\tImageSortie : nom du fichier en sortie (format PBM)\n");
  Mesg("OPTION\n");
  Mesg("\t-h: affiche l'aide\n");
  Mesg("CODES DE RETOUR\n");
  Code(OK,"succès");
  Code(HELP,"aide demandée");
  Code(ERR_NB_PARAM,"nombre d'arguments incorrect");
  Code(ERR_IM_IN,"erreur durant la lecture du fichier image en entrée");
  Code(ERR_IM_TYPE,"mauvais type d'image (doit être binaire)");
  Code(ERR_ES_IN,"erreur durant la lecture de l'élément structurant");
  Code(ERR_IM_OUT,"erreur durant le calcul du résultat");
}

int main(int argc, char *argv[])
{
  Image ImIn=NULL, ImOut=NULL;
  Matrix ElementStructurant=NULL;

  /* Initialisation de la gestion des messages d'erreur */
  InitMesg(argv);
  /* Vérification du nombre d'argument */
  if (argc==1 || argc>4)
  {
    Syntaxe();
    return ERR_NB_PARAM;
  }
  if (argc==2)
  {
    if (!strcmp(argv[1],"-h"))
    {
      Syntaxe();
      Description();
      return HELP;
    }
    else /* un paramètre mais pas -h */
    {
      Syntaxe();
      return ERR_NB_PARAM;
    }
  }
  /* Lecture de l'image en entrée */
  ImIn=ImRead(argv[1]);
  if (ImIn==NULL)
  {
    Erreur("Erreur durant la lecture de l'image en entrée");
    return ERR_IM_IN;
  }
  /* Vérification du type de l'image */
  if (ImType(ImIn)!=BitMap)
  {
    Erreur("L'image doit être de type binaire");
    ImFree(&ImIn);
    return ERR_IM_TYPE;
  }
  /* Lecture de l'élément structurant */
  ElementStructurant=MatReadAsc(argv[2]);
  if (ElementStructurant==NULL)
  {
    Erreur("Erreur durant la lecture de l'élément structurant");
    ImFree(&ImIn);
    return ERR_ES_IN;
  }
  /* Vérification de la validité de l'élément structurant */
  if (InvalideES(ElementStructurant)==ES_NOT_INT)
  {
    Erreur("L'élément structurant doit contenir uniquement des entiers");
    ImFree(&ImIn);
    MatFree(&ElementStructurant);
    return ERR_ES_IN;
  }
  if (InvalideES(ElementStructurant)==ES_NOT_BIN)
  {
    Erreur("L'élément structurant doit contenir uniquement des 0 et des 1");
    ImFree(&ImIn);
    MatFree(&ElementStructurant);
    return ERR_ES_IN;
  }

  /* Dilatation de l'image */
  ImOut=Dilatation(ImIn,ElementStructurant);
  if (ImOut==NULL)
  {
    Erreur("Erreur durant la calcul de l'image résultat");
    ImFree(&ImIn);
    MatFree(&ElementStructurant);
    return ERR_IM_OUT;
  }
  /* Écriture de l'image en sortie */
  ImWrite(ImOut,argv[3]);
  /* Libération de la mémoire occupée par les images et la matrice */
  ImFree(&ImIn);
  ImFree(&ImOut);
  MatFree(&ElementStructurant);
  return OK;
}
