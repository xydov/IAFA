#include <stdio.h>
#include <string.h>
#include "limace.h"
#include "erreurs.h"
#include "tai.h"

/* Codes de retour */
#define IDENTIQUES 0
#define HELP 1
#define ERR_NB_PARAM 2
#define ERR_IN1 3
#define ERR_IN2 4
#define IM_TYPE 5
#define MAT_TYPE 6
#define IM_SIZE 7
#define MAT_SIZE 8
#define IM_PIX 9
#define MAT_ELT 10

void Syntaxe(void)
{
  Usage("Ficher1 Fichier2\n"
        "-h\n");
}

void Description(void)
{
  Mesg("RÔLE\n");
  Mesg("\tComparaison de deux images ou de deux matrices\n");
  Mesg("ARGUMENTS\n");
  Mesg("\tFichier1 : image (PBM, PGM ou PPM) ou matrice (Matrix)\n");
  Mesg("\tFichier2 : image (PBM, PGM ou PPM) ou matrice (Matrix)\n");
  Mesg("OPTION\n");
  Mesg("\t-h: affiche l'aide\n");
  Mesg("CODES DE RETOUR\n");
  Code(IDENTIQUES,"images ou matrices identiques");
  Code(HELP,"aide demandée");
  Code(ERR_NB_PARAM,"nombre d'arguments incorrect");
  Code(ERR_IN1,"le premier argument n'est ni une image ni une matrice");
  Code(ERR_IN2,"le second argument n'est ni une image ni une matrice");
  Code(IM_TYPE,"les deux images ne sont pas du même type");
  Code(MAT_TYPE,"les deux matrices ne sont pas du même type");
  Code(IM_SIZE,"les images ne sont pas de même taille");
  Code(MAT_SIZE,"les matrices ne sont pas de même taille");
  Code(IM_PIX,"des pixels n'ont pas la même valeur");
  Code(MAT_ELT,"des éléments n'ont pas la même valeur");
}

int main(int argc, char *argv[])
{
  Image Im1=NULL,Im2=NULL;
  Matrix Mat1=NULL,Mat2=NULL;
  int i,j,l,c;
  unsigned char **UC1,**UC2,**R1,**G1,**B1,**R2,**G2,**B2;
  int **I1,**I2;
  double **D1,**D2;

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
  /* Tentative de lecture d'une image */
  Im1=ImRead(argv[1]);
  if (Im1==NULL)
  {
    /* Tentative de lecture d'une matrice */
    Mat1=MatReadAsc(argv[1]);
    if (Mat1==NULL)
    {
      Erreur("Le premier argument doit être une image ou une matrice");
      return ERR_IN1;
    }
    Mat2=MatReadAsc(argv[2]);
    if (Mat2==NULL)
    {
      Erreur("Le second argument doit être une matrice, comme le premier");
      MatFree(&Mat1);
      return ERR_IN2;
    }
    if (MatType(Mat1)!=MatType(Mat2))
    {
      Mesg("Les matrices ne sont pas du même type\n");
      MatFree(&Mat1);
      MatFree(&Mat2);
      return MAT_TYPE;
    }
    l=MatNbRow(Mat1);
    c=MatNbCol(Mat1);
    if (l!=MatNbRow(Mat2) || c!=MatNbCol(Mat2))
    {
      Mesg("Les matrices ne sont pas de la même taille\n");
      MatFree(&Mat1);
      MatFree(&Mat2);
      return MAT_SIZE;
    }
    if (MatType(Mat1)==Int)
    {
      I1=MatGetInt(Mat1);
      I2=MatGetInt(Mat2);
      for (i=0;i<l;i++)
        for (j=0;j<c;j++)
          if (I1[i][j]!=I2[i][j])
          {
            Mesg("Contenus différents : \n"
						     "l'élément (%d,%d) de la première matrice vaut %d "
                 "alors que l'élément (%d,%d) de la seconde matrice vaut %d\n",
                  i,j,I1[i][j],i,j,I2[i][j]);
            MatFree(&Mat1);
            MatFree(&Mat2);
            return MAT_ELT;
          }
    }
    else
    {
      D1=MatGetDouble(Mat1);
      D2=MatGetDouble(Mat2);
      for (i=0;i<l;i++)
        for (j=0;j<c;j++)
          if (D1[i][j]!=D2[i][j])
          {
            Mesg("Contenus différents : \n"
						     "l'élément (%d,%d) de la première matrice vaut %f "
                 " alors que l'élément (%d,%d) de la seconde matrice vaut %f\n",
                  i,j,D1[i][j],i,j,D2[i][j]);
            MatFree(&Mat1);
            MatFree(&Mat2);
            return MAT_ELT;
          }
    }
		Mesg("Les deux matrices sont identiques\n");
    MatFree(&Mat1);
    MatFree(&Mat2);
    return IDENTIQUES;
  }
  else /* Le premier argument est une image */
  {
    Im2=ImRead(argv[2]);
    if (Im2==NULL)
    {
      Erreur("Le second argument doit être une image, comme le premier");
      ImFree(&Im1);
      return ERR_IN2;
    }
    if (ImType(Im1)!=ImType(Im2))
    {
      Mesg("Les images ne sont pas du même type\n");
      ImFree(&Im1);
      ImFree(&Im2);
      return IM_TYPE;
    }
    l=ImNbRow(Im1);
    c=ImNbCol(Im1);
    if (l!=ImNbRow(Im2) || c!=ImNbCol(Im2))
    {
      Mesg("Les images ne sont pas de la même taille\n");
      ImFree(&Im1);
      ImFree(&Im2);
      return IM_SIZE;
    }
    if (ImType(Im1)==BitMap || ImType(Im1)==GrayLevel)
    {
      UC1=ImGetI(Im1);
      UC2=ImGetI(Im2);
      for (i=0;i<l;i++)
        for (j=0;j<c;j++)
          if (UC1[i][j]!=UC2[i][j])
          {
            Mesg("Contenus différents : \n"
						     "le pixel (%d,%d) de la première image vaut %d "
                 "alors que le pixel (%d,%d) de la seconde image vaut %d\n",
                  i,j,UC1[i][j],i,j,UC2[i][j]);
            ImFree(&Im1);
            ImFree(&Im2);
            return IM_PIX;
          }
    }
    else /* Image couleur */
    {
      R1=ImGetR(Im1);
      G1=ImGetG(Im1);
      B1=ImGetB(Im1);
      R2=ImGetR(Im2);
      G2=ImGetG(Im2);
      B2=ImGetB(Im2);
      for (i=0;i<l;i++)
        for (j=0;j<c;j++)
          if (R1[i][j]!=R2[i][j] || G1[i][j]!=G2[i][j] || B1[i][j]!=B2[i][j])
          {
            Mesg("Contenus différents : \n"
						     "le pixel (%d,%d) de la première matrice vaut (%d,%d,%d) "
                 "alors que le pixel (%d,%d) de la seconde matrice vaut (%d,%d,%d)\n",
                  i,j,R1[i][j],G1[i][j],B1[i][j],i,j,R2[i][j],G2[i][j],B2[i][j]);
            ImFree(&Im1);
            ImFree(&Im2);
            return IM_PIX;
          }
    }
		Mesg("Les deux images sont identiques\n");
    ImFree(&Im1);
    ImFree(&Im2);
    return IDENTIQUES;
  }
}
