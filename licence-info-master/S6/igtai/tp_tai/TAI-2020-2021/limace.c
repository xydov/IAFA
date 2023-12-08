/* Copyright (C) 1999-2011 A. Crouzil  LIMaCE release 1.6 (07/06/2012) */
/* Debugging : N. Begue (15/05/2001), G. Jaffre (08/05/2002),
 *             B. Pailhes (02/04/2003), F. Courteille (09/04/2003),
 *             J.-D. Durou (18/08/2005, 08/09/2005), G. Gales (02/03/2011).
 */
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "limace.h"


/* Commutateur d'affichage des messages d'erreurs sur stderr.
 * A chaque appel de la fonction on passe d'un etat a l'autre :
 * - ON : les messages d'erreurs sont affiches sur stdout (par defaut)
 * - OFF : aucun message d'erreur n'est affiche
 * Verbose retourne le nouvel etat (ON ou OFF)
 */
int Verbose(void)
{
  static int Etat=ON;

  Etat=!Etat;
  return Etat;
}



/* Affichage des messages d'erreur
 */
static void LimError(const char *Function, const char *Format, ...)
{
  va_list Params;
  (void)Verbose(); if (!Verbose()) return;
  va_start(Params,Format);
  if (Function != NULL)
    fprintf(stderr, "[LIMaCE] (%s) : ",Function);
  vfprintf(stderr,Format,Params);
  fprintf(stderr, ".\n");
  va_end(Params);
  return;
}


/**************************************************************************/

/* MANIPULATION DE MATRICES
 */

/* Structures de donnees "privees"
 */

typedef union
{
  int **AccesInt;
  double **AccesDouble;
} Data;

struct sMatrix
{
  MatrixType TypeMatrix;
  int NbRow;
  int NbCol;
  Data Info;
};


/* Creation d'une matrice de unsigned char
 * Retourne NULL si probleme
 */
static unsigned char **MatAllocUC(int NbRow, int NbCol, int Init)
{
  unsigned char **Matrice,**pM,**Fin,*pD,*Data;

  if (Init)
    Data=(unsigned char *)calloc(NbRow*NbCol,sizeof(unsigned char));
  else
    Data=(unsigned char *)malloc(NbRow*NbCol*sizeof(unsigned char));
  if (Data==NULL)
    return NULL;
  if ((Matrice=(unsigned char **)malloc(NbRow*sizeof(unsigned char*)))==NULL)
  {
    free(Data);
    return NULL;
  }
  Fin=Matrice+NbRow;
  for (pM=Matrice,pD=Data;pM<Fin;pD+=NbCol) *pM++=pD;
  return(Matrice);
}


/* Liberation complete de l'espace memoire occupe par une matrice de
 * unsigned char
 */
static void MatFreeUC(unsigned char ***pMatrice)
{
  if (*pMatrice != NULL)
  {
    free(*(*pMatrice));
    free(*pMatrice);
    *pMatrice=NULL;
  }
}


/* Lecture dans un fichier binaire d'une matrice de unsigned char
 * Retourne la matrice ou NULL si probleme
 */
static unsigned char **fMatReadUC(FILE *Fid, int NbRow, int NbCol)
{
  unsigned char **I;

  if ((I=MatAllocUC(NbRow,NbCol,0))==NULL) return NULL;
  if (fread(*I,sizeof(unsigned char),NbRow*NbCol,Fid)!=((size_t)NbRow*NbCol))
  {
    MatFreeUC(&I);
    return NULL;
  }
  return I;
}


/* Ecriture du contenu d'une matrice de unsigned char dans un fichier binaire
 * Retourne le nombre de unsigned char effectivement ecrits
 */
static int fMatWriteUC(FILE *Fid, unsigned char **I, int NbRow, int NbCol)
{
  return fwrite(*I,sizeof(unsigned char),NbRow*NbCol,Fid);
}


/* Copie d'une matrice de unsigned char
 * Retourne NULL si probleme
 */
static unsigned char **MatCopyUC(unsigned char **Source, int NbRow, int NbCol)
{
  unsigned char **Dest;

  if ((Dest=MatAllocUC(NbRow,NbCol,0))==NULL) return NULL;
  memcpy(*Dest,*Source,NbRow*NbCol*sizeof(unsigned char));
  return Dest;
}


/* Creation d'une matrice de int
 * Retourne NULL si probleme
 */
static int **MatAllocInt(int NbRow, int NbCol, int Init)
{
  int **Matrice,**pM,**Fin,*pD,*Data;

  if (Init)
    Data=(int *)calloc(NbRow*NbCol,sizeof(int));
  else
    Data=(int *)malloc(NbRow*NbCol*sizeof(int));
  if (Data==NULL)
    return NULL;
  if ((Matrice=(int **)malloc(NbRow*sizeof(int*)))==NULL)
  {
    free(Data);
    return NULL;
  }
  Fin=Matrice+NbRow;
  for (pM=Matrice,pD=Data;pM<Fin;pD+=NbCol) *pM++=pD;
  return(Matrice);
}


/* Liberation complete de l'espace memoire occupe par une matrice de int
 */
static void MatFreeInt(int ***pMatrice)
{
  if (*pMatrice != NULL)
  {
    free(*(*pMatrice));
    free(*pMatrice);
    *pMatrice=NULL;
  }
}


/* Creation d'une matrice de double
 * Retourne NULL si probleme
 */
static double **MatAllocDouble(int NbRow, int NbCol, int Init)
{
  double **Matrice,**pM,**Fin,*pD,*Data,*FinData;

  Data=(double *)malloc(NbRow*NbCol*sizeof(double));
  if (Data==NULL)
    return NULL;
  if ((Matrice=(double **)malloc(NbRow*sizeof(double*)))==NULL)
  {
    free(Data);
    return NULL;
  }
  Fin=Matrice+NbRow;
  for (pM=Matrice,pD=Data;pM<Fin;pD+=NbCol) *pM++=pD;
  FinData=Data+NbRow*NbCol;
  if (Init) for (pD=Data;pD<FinData;*pD++=0.0) ;
  return(Matrice);
}


/* Liberation complete de l'espace memoire occupe par une matrice de double
 */
static void MatFreeDouble(double ***pMatrice)
{
  if (*pMatrice!=NULL)
  {
    free(*(*pMatrice));
    free(*pMatrice);
    *pMatrice=NULL;
  }
}


/* Creation d'une matrice de int ou de double
 * Retourne NULL si probleme
 */
static Matrix MatAllocAux(MatrixType Type, int NbRow, int NbCol, int Init)
{
  Matrix M;

  if ((Type!=Int)&&(Type!=Double))
  {
    LimError("MatAlloc","unknown matrix type");
    return NULL;
  }
  M=(Matrix)malloc(sizeof(struct sMatrix));
  if (M==NULL)
  {
    LimError("MatAlloc","not enough memory");
    return NULL;
  }
  M->TypeMatrix=Type;
  M->NbRow=NbRow;
  M->NbCol=NbCol;
  if (Type==Int)
  {
    M->Info.AccesInt=MatAllocInt(NbRow,NbCol,Init);
    if (M->Info.AccesInt==NULL)
    {
      LimError("MatAlloc","not enough memory");
      free(M);
      return NULL;
    }
  }
  else
  {
    M->Info.AccesDouble=MatAllocDouble(NbRow,NbCol,Init);
    if (M->Info.AccesDouble==NULL)
    {
      LimError("MatAlloc","not enough memory");
      free(M);
      return NULL;
    }
  }
  return(M);
}


/* Creation d'une matrice de int ou de double
 * Retourne NULL si probleme
 */
Matrix MatAlloc(MatrixType Type, int NbRow, int NbCol)
{
  return MatAllocAux(Type,NbRow,NbCol,0);
}


/* Creation d'une matrice de int ou de double initialisee a 0
 * Retourne NULL si probleme
 */
Matrix MatCAlloc(MatrixType Type, int NbRow, int NbCol)
{
  return MatAllocAux(Type,NbRow,NbCol,1);
}


/* Retourne le type d'une matrice (Int, Double)
 */
MatrixType MatType(Matrix Mat)
{
  if (Mat==NULL)
  {
    LimError("MatType","NULL pointer");
    return Int;
  }
  return Mat->TypeMatrix;
}


/* Retourne le nombre de lignes d'une matrice, 0 si probleme
 */
int MatNbRow(Matrix Mat)
{
  if (Mat==NULL)
  {
    LimError("MatNbRow","NULL pointer");
    return 0;
  }
  return Mat->NbRow;
}


/* Retourne le nombre de colonnes d'une matrice, 0 si probleme
 */
int MatNbCol(Matrix Mat)
{
  if (Mat==NULL)
  {
    LimError("MatNbCol","NULL pointer");
    return 0;
  }
  return Mat->NbCol;
}


/* Acces aux elements d'une matrice de int
 * Retourne NULL si probleme (par ex. si type matrice incorrect)
 */
int **MatGetInt(Matrix Mat)
{
  if (MatType(Mat)!=Int)
  {
    LimError("MatGetInt","matrix of int required");
    return NULL;
  }
  else return Mat->Info.AccesInt;
}


/* Acces aux elements d'une matrice de double
 * Retourne NULL si probleme (par ex. si type matrice incorrect)
 */
double **MatGetDouble(Matrix Mat)
{
  if (MatType(Mat)!=Double)
  {
    LimError("MatGetDouble","matrix of double required");
    return NULL;
  }
  else return Mat->Info.AccesDouble;
}


/* Copie d'une matrice de int
 * Retourne NULL si probleme
 */
static int **MatCopyInt(int **Source, int NbRow, int NbCol)
{
  int **Dest;

  if ((Dest=MatAllocInt(NbRow,NbCol,0))==NULL) return NULL;
  memcpy(*Dest,*Source,NbRow*NbCol*sizeof(int));
  return Dest;
}


/* Creation d'une matrice de int a partir d'un acces a une matrice.
 * Retourne NULL si probleme
 */
static Matrix MatInt2Mat(int **aM, MatrixType Type, int NbRow, int NbCol)
{
  Matrix Mat;

  Mat=(Matrix)malloc(sizeof(struct sMatrix));
  if (Mat==NULL) return NULL;
  Mat->TypeMatrix=Type;
  Mat->NbRow=NbRow;
  Mat->NbCol=NbCol;
  Mat->Info.AccesInt=MatCopyInt(aM,NbRow,NbCol);
  if (Mat->Info.AccesInt==NULL)
  {
    free(Mat);
    return NULL;
  }
  return(Mat);
}


/* Copie d'une matrice de double
 * Retourne NULL si probleme
 */
static double **MatCopyDouble(double **Source, int NbRow, int NbCol)
{
  double **Dest;
  if ((Dest=MatAllocDouble(NbRow,NbCol,0))==NULL) return NULL;
  memcpy(*Dest,*Source,NbRow*NbCol*sizeof(double));
  return Dest;
}


/* Creation d'une matrice de double a partir d'un acces a une matrice.
 * Retourne NULL si probleme
 */
static Matrix MatDouble2Mat(double **aM, MatrixType Type, int NbRow, int NbCol)
{
  Matrix Mat;

  Mat=(Matrix)malloc(sizeof(struct sMatrix));
  if (Mat==NULL) return NULL;
  Mat->TypeMatrix=Type;
  Mat->NbRow=NbRow;
  Mat->NbCol=NbCol;
  Mat->Info.AccesDouble=MatCopyDouble(aM,NbRow,NbCol);
  if (Mat->Info.AccesDouble==NULL)
  {
    free(Mat);
    return NULL;
  }
  return(Mat);
}


/* Copie d'une matrice
 * Retourne NULL si probleme
 */
Matrix MatCopy(Matrix Mat)
{
  Matrix Dest;

  if (Mat==NULL)
  {
    LimError("MatCopy","NULL pointer");
    return NULL;
  }
  if ((Mat->TypeMatrix!=Int) && (Mat->TypeMatrix!=Double))
  {
    LimError("MatCopy","unknown matrix type");
    return NULL;
  }
  if (Mat->TypeMatrix==Int)
    Dest=MatInt2Mat(MatGetInt(Mat),Mat->TypeMatrix,Mat->NbRow,Mat->NbCol);
  else
    Dest=MatDouble2Mat(MatGetDouble(Mat),Mat->TypeMatrix,Mat->NbRow,Mat->NbCol);
  if (Dest==NULL) LimError("MatCopy","not enough memory");
  return Dest;
}


/* Lecture d'une chaine de caract�res dans le fichier de descripteur Flux.
 * Les �ventuels s�parateurs au d�but de la cha�ne sont ignor�s.
 * La lecture s'arr�te au premier '\n' rencontr� ou lorsque la fin du fichier
 * est atteinte. Le caract�re '\n' n'est pas stock� dans la cha�ne.
 * Le caract�re '\0' est rajout� en fin de cha�ne. L'allocation dynamique
 * est faite dans la fonction. La lib�ration de la zone m�moire doit �tre
 * r�alis�e par l'appelant. La taille de la zone est ajust�e au nombre de
 * caract�res + 1.
 * La valeur retourn�e est l'adresse du premier caract�re de la cha�ne
 * ou NULL en cas de probl�me (allocation m�moire).
 */
static char *LireLigne(FILE *Flux)
{
  char *Ligne,*NouvelleLigne;
  int Car;
  unsigned long int i=0,Taille=BUFSIZ;

  Ligne=(char *)malloc(BUFSIZ);
  if (Ligne==NULL) return NULL;
  while ((isspace(Car=fgetc(Flux))) && (Car!=EOF)) ;
  while ((Car!='\n') && (Car!=EOF))
  {
    if (i==Taille)
    {
      Taille+=BUFSIZ;
      NouvelleLigne=(char *)realloc(Ligne,Taille);
      if (NouvelleLigne==NULL)
      {
        free(Ligne);
        return NULL;
      }
      Ligne=NouvelleLigne;
    }
    Ligne[i++]=Car;
    Car=fgetc(Flux);
  }
  Ligne=(char *)realloc(Ligne,i+1);
  Ligne[i]='\0';
  return Ligne;
}


/* Lecture d'une matrice de int a partir d'un fichier ASCII
 * de nom FileName. Si FileName="" (chaine vide) alors Fid=stdin et la matrice
 * est lue sur stdin.
 * Retourne la matrice ou NULL si probleme
 */
static Matrix MatReadAscInt(FILE *Fid, const char FileName[])
{
  int NbRow,NbCol=0,NbColCour,First=1,Dim,*pMat,x;
  Matrix Mat;
  char *Buffer,*p;

  NbRow=0;
  while (strcmp(Buffer=LireLigne(Fid),""))
  {
    NbRow++;
    p=Buffer;
    NbColCour=0;
    p=strtok(Buffer," \t\n\r,;:");
    while (p)
    {
      NbColCour++;
      sscanf(p,"%d",&x);
      p=strtok(NULL," \t\n\r,;:");
    }
    if (NbColCour)
    {
      if (First) { NbCol=NbColCour; First=0; }
      else
      {
  if (NbColCour!=NbCol)
  {
    LimError("MatReadAsc for Int","%s, line %d : wrong number of elements",FileName,NbRow);
    return NULL;
  }
      }
    }
    else NbRow--;
    free(Buffer);
  }
  rewind(Fid);
  Mat=MatAlloc(Int,NbRow,NbCol);
  if (Mat==NULL)
  {
    LimError("MatReadAsc for Int","not enough memory");
    return NULL;
  }
  pMat=*(MatGetInt(Mat));
  Dim=NbRow*NbCol;
  while (Dim--) fscanf(Fid,"%d%*[,;:]",pMat++);
  return Mat;
}


/* Lecture d'une matrice de double a partir d'un fichier ASCII
 * de nom FileName. Si FileName="" (chaine vide) alors Fid=stdin et la matrice
 * est lue sur stdin.
 * Retourne la matrice ou NULL si probleme
 */
static Matrix MatReadAscDouble(FILE *Fid, const char FileName[])
{
  int NbRow,NbCol=0,NbColCour,First=1,Dim;
  char *Buffer,*p;
  Matrix Mat;
  double *pMat,x;

  NbRow=0;
  while (strcmp(Buffer=LireLigne(Fid),""))
  {
    NbRow++;
    p=Buffer;
    NbColCour=0;
    p=strtok(Buffer," \t\n\r,;:");
    while (p)
    {
      NbColCour++;
      sscanf(p,"%lf",&x);
      p=strtok(NULL," \t\n\r,;:");
    }
    if (NbColCour)
    {
      if (First) { NbCol=NbColCour; First=0; }
      else
      {
  if (NbColCour!=NbCol)
  {
    LimError("MatReadAsc for Double","%s, line %d : wrong number of elements",FileName,NbRow);
    return NULL;
  }
      }
    }
    else NbRow--;
    free(Buffer);
  }
  rewind(Fid);
  Mat=MatAlloc(Double,NbRow,NbCol);
  if (Mat==NULL)
  {
    LimError("MatReadAsc for Double","not enough memory");
    return NULL;
  }
  pMat=*(MatGetDouble(Mat));
  Dim=NbRow*NbCol;
  while (Dim--) fscanf(Fid,"%lf%*[,;:]",pMat++);
  return Mat;
}


/* Lecture d'une matrice de int ou de double a partir d'un fichier ASCII
 * de descripteur Fid au format "Matrix".
 * Retourne la matrice ou NULL si probleme
 */
static Matrix fMatReadAsc(FILE *Fid)
{
  char *Buffer,Nombre[BUFSIZ+1],Format[13];
  int NbLig,NbCol,Dim,*pMatI;
  double *pMatD;
  Matrix Mat;

  if ((Buffer=LireLigne(Fid))==NULL)
  {
    LimError("MatReadAsc","error while reading");
    return NULL;
  }
  if ((Buffer[0]!='M')||(Buffer[1]!='a')||(Buffer[2]!='t'))
  {
    LimError("MatReadAsc","unknown matrix format, Matrix expected");
    free(Buffer);
    return NULL;
  }
  free(Buffer);
  if (fscanf(Fid,"%d",&NbLig)!=1)
  {
    LimError("MatReadAsc","error while reading matrix size");
    return NULL;
  }
  if (fscanf(Fid,"%d",&NbCol)!=1)
  {
    LimError("MatReadAsc","error while reading matrix size");
    return NULL;
  }
  Dim=NbLig*NbCol;
  sprintf(Format,"%%%ds",BUFSIZ);
  if (fscanf(Fid,Format,Nombre)!=1)
  {
    LimError("MatReadAsc","error while reading matrix elements");
    return NULL;
  }
  if ((strchr(Nombre,'.')==NULL)&&
      (strchr(Nombre,'e')==NULL)&&
      (strchr(Nombre,'E')==NULL))
  {
    if ((Mat=MatAlloc(Int,NbLig,NbCol))==NULL)
    {
      LimError("MatReadAsc","not enough memory");
      return NULL;
    }
    pMatI=*(MatGetInt(Mat));
    *pMatI=(int)strtol(Nombre,NULL,0); pMatI++; Dim--;
    while (Dim--)
      if (fscanf(Fid,"%d",pMatI++)!=1)
      {
  LimError("MatReadAsc","error while reading matrix elements");
  MatFree(&Mat);
  return NULL;
      }
  }
  else
  {
    if ((Mat=MatAlloc(Double,NbLig,NbCol))==NULL)
    {
      LimError("MatReadAsc","not enough memory");
      return NULL;
    }
    pMatD=*(MatGetDouble(Mat));
    *pMatD=strtod(Nombre,NULL); pMatD++; Dim--;
    while (Dim--)
      if (fscanf(Fid,"%lf",pMatD++)!=1)
      {
  LimError("MatReadAsc","error while reading matrix elements");
  MatFree(&Mat);
  return NULL;
      }
  }
  return Mat;
}


/* Lecture d'une matrice de int ou de double a partir d'un fichier disque ASCII
 * de nom FileName.
 * Retourne la matrice ou NULL si probleme
 */
static Matrix dMatReadAsc(const char FileName[])
{
  FILE *Fid;
  Matrix Mat;
  char *Buffer,*p,Nombre[BUFSIZ+1],Format[13];

  if ((Fid=fopen(FileName,"rt"))==NULL)
  {
    LimError("MatReadAsc","unable to open file %s",FileName);
    return NULL;
  }
  if ((Buffer=LireLigne(Fid))==NULL)
  {
    LimError("MatReadAsc","error while reading file %s",FileName);
    fclose(Fid);
    return NULL;
  }
  rewind(Fid);
  if((Buffer[0]=='M')&&(Buffer[1]=='a')&&(Buffer[2]=='t'))
  {
    Mat=fMatReadAsc(Fid);
    free(Buffer);
    fclose(Fid);
    return Mat;
  }
  p=strtok(Buffer," \t\n\r,;:");
  sprintf(Format,"%%%ds",BUFSIZ);
  if (sscanf(p,Format,Nombre)!=1)
  {
    LimError("MatReadAsc","error while reading file %s",FileName);
    free(Buffer);
    fclose(Fid);
    return NULL;
  }
  free(Buffer);
  rewind(Fid);
  if ((strchr(Nombre,'.')==NULL)&&
      (strchr(Nombre,'e')==NULL)&&
      (strchr(Nombre,'E')==NULL))
    Mat=MatReadAscInt(Fid,FileName);
  else
    Mat=MatReadAscDouble(Fid,FileName);
  fclose(Fid);
  return Mat;
}



/* Lecture d'une matrice de int ou de double a partir d'un fichier ASCII
 * de nom FileName.
 * Le fichier peut etre au format "Matrix" ou ASCII de base.
 * Si FileName="" (chaine vide) la matrice est lue sur stdin ; dans ce cas,
 * le format attendu est le format "Matrix".
 * Retourne la matrice ou NULL si probleme
 */
Matrix MatReadAsc(const char FileName[])
{
  if (FileName[0]=='\0')
    return fMatReadAsc(stdin);
  else
    return dMatReadAsc(FileName);
}



/* Liberation complete de l'espace memoire occupe par une matrice
 */
void MatFree(Matrix *pMat)
{
  MatrixType Type;
  Matrix M=*pMat;
  int **MI;
  double **MD;

  Type=MatType(*pMat);
  if (M != NULL)
  {
    if (Type==Int)
    {
      MI=MatGetInt(*pMat);
      MatFreeInt(&MI);
    }
    else
    {
      if (Type==Double)
      {
  MD=MatGetDouble(*pMat);
  MatFreeDouble(&MD);
      }
      else
      {
  LimError("Matfree","unknown matrix type");
  return;
      }
    }
  }
  free(M);
  *pMat=NULL;
  return;
}


/* Ecriture ASCII d'une matrice de int dans un fichier de
 * nom FileName. Si FileName="" (chaine vide) la matrice est ecrite sur stdout.
 */
static void MatWriteAscInt(Matrix Mat, const char FileName[])
{
  FILE *Fid;
  int i,j,NbLig,NbCol;
  int **MM;

  if (Mat==NULL)
  {
    LimError("MatWriteAsc for Int","NULL pointer");
    return;
  }
  if (FileName[0]!='\0')
  {
    Fid=fopen(FileName,"wt");
    if (Fid==NULL)
    {
      LimError("MatWriteAsc for Int","unable to open %s",FileName);
      return;
    }
  }
  else Fid=stdout;

  if ((MM=MatGetInt(Mat))==NULL)
  {
    LimError("MatWriteAsc for Int","memory access problem");
    return;
  }
  NbLig=MatNbRow(Mat);
  NbCol= MatNbCol(Mat);
  fprintf(Fid,"Matrix\n%d %d\n",NbLig,NbCol);
  for (i=0;i<NbLig;i++)
  {
    fprintf(Fid,"%d",MM[i][0]);
    for (j=1;j<NbCol;j++)
      fprintf(Fid," %d",MM[i][j]);
    fprintf(Fid,"\n");
  }
  if (FileName[0]!='\0') fclose(Fid);
  return;
}


/* Ecriture ASCII d'une matrice de double dans un fichier de
 * nom FileName. Si FileName="" (chaine vide) la matrice est ecrite sur stdout.
 */
static void MatWriteAscDouble(Matrix Mat, const char FileName[])
{
  FILE *Fid;
  int i,j,NbLig,NbCol;
  double **MM;

  if (Mat==NULL)
  {
    LimError("MatWriteAsc for Double","NULL pointer");
    return;
  }
  if (FileName[0]!='\0')
  {
    Fid=fopen(FileName,"wt");
    if (Fid==NULL)
    {
      LimError("MatWriteAsc for Double","unable to open %s",FileName);
      return;
    }
  }
  else Fid=stdout;

  if ((MM=MatGetDouble(Mat))==NULL)
  {
    LimError("MatWriteAsc for Double","memory access problem");
    return;
  }
  NbLig=MatNbRow(Mat);
  NbCol= MatNbCol(Mat);
  fprintf(Fid,"Matrix\n%d %d\n",NbLig,NbCol);
  for (i=0;i<NbLig;i++)
  {
    fprintf(Fid,"% .16e",MM[i][0]);
    for (j=1;j<NbCol;j++)
      fprintf(Fid," % .16e",MM[i][j]);
    fprintf(Fid,"\n");
  }
  if (FileName[0]!='\0') fclose(Fid);
  return;
}



/* Ecriture ASCII d'une matrice de int ou de double au format "Matrix" dans un
 * fichier de nom FileName. Si FileName="" (chaine vide) la matrice est ecrite
 * sur stdout.
 */
void MatWriteAsc(Matrix Mat, const char FileName[])
{
  MatrixType Type=MatType(Mat);

  if (Type==Int) MatWriteAscInt(Mat,FileName);
  else
    if (Type==Double) MatWriteAscDouble(Mat,FileName);
    else
      LimError("MatWriteAsc","unknown matrix type");
  return;
}


/**************************************************************************/

/* MANIPULATION D'IMAGES
 */

/* Structures de donnees "privees"
 */

typedef struct
{
  unsigned char **R;
  unsigned char **G;
  unsigned char **B;
} ColImage;

typedef union
{
  unsigned char **I;
  ColImage CI;
} Contenu;

struct sImage
{
  ImageType TypeImage;
  int NbRow;
  int NbCol;
  Contenu Info;
};


/* Creation d'une image. Retourne NULL si probleme.
 */
static Image ImAllocAux(ImageType Type, int NbRow, int NbCol, int Init)
{
  Image Im;
  const char *FctName;

  FctName=Init?"ImCAlloc":"ImAlloc";

  if ((Type!=BitMap)&&(Type!=GrayLevel)&&(Type!=Color))
  {
    LimError(FctName,"unknown image type");
    return NULL;
  }
  Im=(Image)malloc(sizeof(struct sImage));
  if (Im==NULL)
  {
    LimError(FctName,"not enough memory");
    return NULL;
  }
  Im->TypeImage=Type;
  Im->NbRow=NbRow;
  Im->NbCol=NbCol;
  if ((Type==GrayLevel)||(Type==BitMap))
  {
    Im->Info.I=MatAllocUC(NbRow,NbCol,Init);
    if (Im->Info.I==NULL)
    {
      LimError(FctName,"not enough memory");
      free(Im);
      return NULL;
    }
  }
  else
  {
    Im->Info.CI.R=MatAllocUC(NbRow,NbCol,Init);
    if (Im->Info.CI.R==NULL)
    {
      LimError(FctName,"not enough memory");
      free(Im);
      return NULL;
    }
    Im->Info.CI.G=MatAllocUC(NbRow,NbCol,Init);
    if (Im->Info.CI.G==NULL)
    {
      LimError(FctName,"not enough memory");
      MatFreeUC(&(Im->Info.CI.R));
      free(Im);
      return NULL;
    }
    Im->Info.CI.B=MatAllocUC(NbRow,NbCol,Init);
    if (Im->Info.CI.B==NULL)
    {
      LimError(FctName,"not enough memory");
      MatFreeUC(&(Im->Info.CI.R));
      MatFreeUC(&(Im->Info.CI.G));
      free(Im);
      return NULL;
    }
  }
  return(Im);
}



/* Creation d'une image. Retourne NULL si probleme.
 */
Image ImAlloc(ImageType Type, int NbRow, int NbCol)
{
  return ImAllocAux(Type,NbRow,NbCol,0);
}


/* Creation d'une image initialisee a 0. Retourne NULL si probleme.
 */
Image ImCAlloc(ImageType Type, int NbRow, int NbCol)
{
  return ImAllocAux(Type,NbRow,NbCol,1);
}


/* Creation d'une image de niveaux de gris a partir d'une matrice.
 * Retourne NULL si probleme
 */
static Image Mat2Image(unsigned char **I,ImageType Type, int NbRow, int NbCol)
{
  Image Im;

  Im=(Image)malloc(sizeof(struct sImage));
  if (Im==NULL) return NULL;
  Im->TypeImage=Type;
  Im->NbRow=NbRow;
  Im->NbCol=NbCol;
  Im->Info.I=MatCopyUC(I,NbRow,NbCol);
  if (Im->Info.I==NULL)
  {
    free(Im);
    return NULL;
  }
  return(Im);
}


/* Creation d'une image Color a partir de 3 matrices.
 * Retourne NULL si probleme
 */
static Image RGB2Image(unsigned char **R, unsigned char **G, unsigned char **B, int NbRow, int NbCol)
{
  Image Im;

  Im=(Image)malloc(sizeof(struct sImage));
  if (Im==NULL) return NULL;
  Im->TypeImage=Color;
  Im->NbRow=NbRow;
  Im->NbCol=NbCol;
  Im->Info.CI.R=MatCopyUC(R,NbRow,NbCol);
  if (Im->Info.CI.R==NULL)
  {
    free(Im);
    return NULL;
  }
  Im->Info.CI.G=MatCopyUC(G,NbRow,NbCol);
  if (Im->Info.CI.G==NULL)
  {
    MatFreeUC(&(Im->Info.CI.R));
    free(Im);
    return NULL;
  }
  Im->Info.CI.B=MatCopyUC(B,NbRow,NbCol);
  if (Im->Info.CI.B==NULL)
  {
    MatFreeUC(&(Im->Info.CI.R));
    MatFreeUC(&(Im->Info.CI.G));
    free(Im);
    return NULL;
  }
  return(Im);
}


/* Retourne le type d'une image (BitMap, GrayLevel, Color)
 */
ImageType ImType(Image Im)
{
  if (Im==NULL)
  {
    LimError("ImType","NULL pointer");
    return GrayLevel;
  }
  return Im->TypeImage;
}


/* Retourne le nombre de lignes d'une image, 0 si probleme
 */
int ImNbRow(Image Im)
{
  if (Im==NULL)
  {
    LimError("ImNbRow","NULL pointer");
    return 0;
  }
  return Im->NbRow;
}


/* Retourne le nombre de colonnes d'une image, 0 si probleme
 */
int ImNbCol(Image Im)
{
  if (Im==NULL)
  {
    LimError("ImNbCol","NULL pointer");
    return 0;
  }
  return Im->NbCol;
}


/* Acces a la matrice des niveaux de gris d'une image de type GrayLevel ou
 * BitMap
 * Retourne NULL si probleme
 */
unsigned char **ImGetI(Image Im)
{
  if (Im==NULL)
  {
    LimError("ImGetI","NULL pointer");
    return NULL;
  }
  if ((Im->TypeImage!=GrayLevel)&&(Im->TypeImage!=BitMap))
  {
    LimError("ImGetI","wrong image type");
    return NULL;
  }
  return Im->Info.I;
}


/* Acces a la matrice du plan R d'une image de type Color
 * Retourne NULL si probleme
 */
unsigned char **ImGetR(Image Im)
{
  if (Im==NULL)
  {
    LimError("ImGetR","NULL pointer");
    return NULL;
  }
  if (Im->TypeImage!=Color)
  {
    LimError("ImGetR","wrong image type");
    return NULL;
  }
  return Im->Info.CI.R;
}


/* Acces a la matrice du plan G d'une image de type Color
 * Retourne NULL si probleme
 */
unsigned char **ImGetG(Image Im)
{
  if (Im==NULL)
  {
    LimError("ImGetG","NULL pointer");
    return NULL;
  }
  if (Im->TypeImage!=Color)
  {
    LimError("ImGetG","wrong image type");
    return NULL;
  }
  return Im->Info.CI.G;
}


/* Acces a la matrice du plan B d'une image de type Color
 * Retourne NULL si probleme
 */
unsigned char **ImGetB(Image Im)
{
  if (Im==NULL)
  {
    LimError("ImGetB","NULL pointer");
    return NULL;
  }
  if (Im->TypeImage!=Color)
  {
    LimError("ImGetB","wrong image type");
    return NULL;
  }
  return Im->Info.CI.B;
}


/* Copie d'une image
 * Retourne NULL si probleme
 */
Image ImCopy(Image Im)
{
  Image Dest;

  if (Im==NULL)
  {
    LimError("ImCopy","NULL pointer");
    return NULL;
  }
  if ((Im->TypeImage!=BitMap)&&
      (Im->TypeImage!=GrayLevel)&&
      (Im->TypeImage!=Color))
  {
    LimError("ImCopy","unknown image type");
    return NULL;
  }
  if ((Im->TypeImage==GrayLevel)||(Im->TypeImage==BitMap))
    Dest=Mat2Image(ImGetI(Im),Im->TypeImage,Im->NbRow,Im->NbCol);
  else
    Dest=RGB2Image(ImGetR(Im),ImGetG(Im),ImGetB(Im),Im->NbRow,Im->NbCol);
  if (Dest==NULL) LimError("ImCopy","not enough memory");
  return Dest;
}


/* Liberation complete de l'espace memoire occupe par une image
 */
void ImFree(Image *pIm)
{
  Image I=*pIm;

  if (I==NULL)
  {
    LimError("ImFree","NULL pointer");
    return;
  }
  if ((I->TypeImage!=BitMap)&&
      (I->TypeImage!=GrayLevel)&&
      (I->TypeImage!=Color))
  {
    LimError("ImFree","unknown image type");
    return;
  }
  if ((I->TypeImage==GrayLevel)||(I->TypeImage==BitMap))
    MatFreeUC(&(I->Info.I));
  else
  {
    MatFreeUC(&(I->Info.CI.R));
    MatFreeUC(&(I->Info.CI.G));
    MatFreeUC(&(I->Info.CI.B));
  }
  free(I);
  *pIm=NULL;
  return;
}



/* Manipulation des bits d'un octet numerotes 0 1 2 ... 7 */
#define BITGET(Byte,Position) (((Byte)>>(7^(Position)))&1)
#define BITPUT(Byte,Position) ((Byte)=((128>>(Position))|(Byte)))

/* Lit le prochaine caractere dans le flux Fid. Saute les commentaires
 * commencant par le caractere # et se terminant a la fin de la ligne.
 * Retourne 0 si probleme ou si fin de fichier atteinte, 1 sinon.
 */
static int GetC(FILE *Fid, char *pCar)
{
  int i;
  char c;

  i=getc(Fid);
  if (i==EOF) return 0;
  c=(char)i;
  if (c=='#')
  {
    do
    {
      i= getc(Fid);
      if (i==EOF) return 0;
      c=(char)i;
    } while ((c!='\n') && (c!='\r'));
  }
  *pCar=c;
  return 1;
}


/* Lit le prochaine entier (ascii) dans le flux Fid en ignorant les
 * commentaires.
 * Retourne 0 si probleme ou si fin de fichier atteinte, 1 sinon.
 */
static int GetInt(FILE* Fid, int *pInt)
{
  char c;
  int i;

  do
  {
    if (GetC(Fid,&c)==0) return 0;
  } while ((c==' ') || (c=='\t') || (c=='\n') || (c=='\r'));
  if ((c<'0') || (c>'9')) return 0;
  i=0;
  do
  {
    i=i*10+c-'0';
    if (GetC(Fid,&c)==0) return 0;
  } while ((c>='0') && (c<='9'));
  *pInt=i;
  return 1;
}


/* Lit une image dans un fichier deja ouvert de nom FileName et de descripteur
 * *pFid.
 * Le descripteur est passe par adresse car le fichier peut etre ferme et
 * reouvert dans cette fonction alors qu'il doit etre ferme par l'appelant.
 * Si le FileName="" (chaine vide) alors *pFid=stdin et la lecture se fait sur
 * stdin.
 * Retourne l'image ou NULL si probleme.
 */
static Image fImRead(FILE **pFid, const char FileName[])
{
  Image Im=NULL;
  unsigned char Byte=0,**I=NULL,**R=NULL,**G=NULL,**B=NULL;
  char Format;
  int i,j,k,MaxVal=0,Val,NbLig,NbCol;
  long Debut;
  double Coeff;

  if (GetC(*pFid,&Format)==0)
  {
    fclose(*pFid);
    LimError("ImRead","error while reading %s",FileName);
    return NULL;
  }
  if (Format!='P')
  {
    LimError("ImRead","%s not a pnm (pbm, pgm, ppm) file",FileName);
    return NULL;
  }
  if (GetC(*pFid,&Format)==0)
  {
    LimError("ImRead","error while reading %s",FileName);
    return NULL;
  }
  if ((Format<'1')||(Format>'6'))
  {
    LimError("ImRead","%s not a pnm (pbm, pgm, ppm) file",FileName);
    return NULL;
  }
  if (GetInt(*pFid,&NbCol)==0)
  {
    LimError("ImRead","error while reading %s",FileName);
    return NULL;
  }
  if (GetInt(*pFid,&NbLig)==0)
  {
    LimError("ImRead","error while reading %s",FileName);
    return NULL;
  }
  if ((Format!='1')&&(Format!='4'))
  {
    if (GetInt(*pFid,&MaxVal)==0)
    {
      LimError("ImRead","error while reading %s",FileName);
      return NULL;
    }
    if (MaxVal<0)
    {
      LimError("ImRead","bad value for maxval in %s",FileName);
      return NULL;
    }
    if (MaxVal>255)
    {
      LimError("ImRead","%s: maxval > 255 not supported",FileName);
      return NULL;
    }
  }

  switch (Format)
  {
    /* Image de niveaux de gris */
  case '2':
    Im=ImAlloc(GrayLevel,NbLig,NbCol);
    if (Im==NULL)
    {
      LimError("ImRead","error while reading %s",FileName);
      return NULL;
    }
    I=ImGetI(Im);
    for (i=0;i<NbLig;i++)
      for (j=0;j<NbCol;j++)
      {
  if (GetInt(*pFid,&Val)==0)
  {
    LimError("ImRead","error while reading %s",FileName);
    ImFree(&Im);
    return NULL;
  }
  I[i][j]=(unsigned char)Val;
      }
    break;
  case '5':
    /*if (FileName[0]!='\0') 12/12/2009 */
    if (strcmp(FileName,"stdin"))
    {
      Debut=ftell(*pFid);
      fclose(*pFid);
      *pFid=fopen(FileName,"rb");
      if (*pFid==NULL)
      {
  LimError("ImRead","%s: file not found",FileName);
  return NULL;
      }
      fseek(*pFid,Debut,SEEK_SET);
    }
    I=fMatReadUC(*pFid,NbLig,NbCol);
    if (I==NULL)
    {
      LimError("ImRead","error while reading %s",FileName);
      return NULL;
    }
    if ((Im=Mat2Image(I,GrayLevel,NbLig,NbCol))==NULL)
    {
      LimError("ImRead","not enough memory");
      return NULL;
    }
    MatFreeUC(&I);
    break;

    /* Image noir et blanc */
  case '1':
    Im=ImAlloc(BitMap,NbLig,NbCol);
    if (Im==NULL)
    {
      LimError("ImRead","error while reading %s",FileName);
      return NULL;
    }
    I=ImGetI(Im);
    for (i=0;i<NbLig;i++)
      for (j=0;j<NbCol;j++)
      {
  if (GetInt(*pFid,&Val)==0)
  {
    LimError("ImRead","error while reading %s",FileName);
    ImFree(&Im);
    return NULL;
  }
  if ((Val!=0) && (Val!=1))
  {
    LimError("ImRead","%s: value differ from 0 and 1",FileName);
    ImFree(&Im);
    return NULL;
  }
  I[i][j]=(unsigned char)(!Val);
      }
    break;
  case '4':
    Im=ImAlloc(BitMap,NbLig,NbCol);
    if (Im==NULL)
    {
      LimError("ImRead","error while reading %s",FileName);
      return NULL;
    }
    I=ImGetI(Im);
    /*if (FileName[0]!='\0') 23/02/2010 */
    if (strcmp(FileName,"stdin"))
    {
      Debut=ftell(*pFid);
      fclose(*pFid);
      *pFid=fopen(FileName,"rb");
      if (*pFid==NULL)
      {
  LimError("ImRead","%s: file not found",FileName);
  return NULL;
      }
      fseek(*pFid,Debut,SEEK_SET);
    }
    for (i=0;i<NbLig;i++)
    {
      for (j=0,k=8;j<NbCol;j++)
      {
  if (k==8)
  {
    if ((Val=getc(*pFid))==EOF)
    {
      LimError("ImRead","error while reading %s",FileName);
      ImFree(&Im);
      return NULL;
    }
    Byte=(unsigned char)Val;
    k=0;
  }
  I[i][j]=(!(BITGET(Byte,k)));
  k++;
      }
    }
    break;

    /* Image couleur */
  case '3':
    Im=ImAlloc(Color,NbLig,NbCol);
    if (Im==NULL)
    {
      LimError("ImRead","error while reading %s",FileName);
      return NULL;
    }
    R=ImGetR(Im);
    G=ImGetG(Im);
    B=ImGetB(Im);
    for (i=0;i<NbLig;i++)
      for (j=0;j<NbCol;j++)
      {
  if (GetInt(*pFid,&Val)==0)
  {
    LimError("ImRead","error while reading %s",FileName);
    ImFree(&Im);
    return NULL;
  }
  R[i][j]=(unsigned char)Val;
  if (GetInt(*pFid,&Val)==0)
  {
    LimError("ImRead","error while reading %s",FileName);
    ImFree(&Im);
    return NULL;
  }
  G[i][j]=(unsigned char)Val;
  if (GetInt(*pFid,&Val)==0)
  {
    LimError("ImRead","error while reading %s",FileName);
    ImFree(&Im);
    return NULL;
  }
  B[i][j]=(unsigned char)Val;
      }
    break;
  case '6':
    if (FileName[0]!='\0')
    {
      Debut=ftell(*pFid);
      fclose(*pFid);
      *pFid=fopen(FileName,"rb");
      if (*pFid==NULL)
      {
  LimError("ImRead","%s: file not found",FileName);
  return NULL;
      }
      fseek(*pFid,Debut,SEEK_SET);
    }
    Im=ImAlloc(Color,NbLig,NbCol);
    if (Im==NULL)
    {
      LimError("ImRead","error while reading %s",FileName);
      return NULL;
    }
    R=ImGetR(Im);
    G=ImGetG(Im);
    B=ImGetB(Im);
    for (i=0;i<NbLig;i++)
      for (j=0;j<NbCol;j++)
      {
  if ((Val=getc(*pFid))==EOF)
  {
    LimError("ImRead","error while reading %s",FileName);
    ImFree(&Im);
    return NULL;
  }
  R[i][j]=(unsigned char)Val;
  if ((Val=getc(*pFid))==EOF)
  {
    LimError("ImRead","error while reading %s",FileName);
    ImFree(&Im);
    return NULL;
  }
  G[i][j]=(unsigned char)Val;
  if ((Val=getc(*pFid))==EOF)
  {
    LimError("ImRead","error while reading %s",FileName);
    ImFree(&Im);
    return NULL;
  }
  B[i][j]=(unsigned char)Val;
      }
    break;
  }

  if ((MaxVal!=255)&&(MaxVal!=0))
  {
    Coeff=255.0/(double)MaxVal;
    if (ImType(Im)==GrayLevel)
    {
      I=ImGetI(Im);
      for (i=0;i<NbLig;i++)
  for (j=0;j<NbCol;j++)
    I[i][j]=(unsigned char)floor(Coeff*I[i][j]+0.5);
    }
    else
    {
      R=ImGetR(Im);
      for (i=0;i<NbLig;i++)
  for (j=0;j<NbCol;j++)
  {
    R[i][j]=(unsigned char)floor(Coeff*R[i][j]+0.5);
    G[i][j]=(unsigned char)floor(Coeff*G[i][j]+0.5);
    B[i][j]=(unsigned char)floor(Coeff*B[i][j]+0.5);
  }
    }
  }

  return Im;
}



/* Lit une image dans un fichier de nom FileName.
 * Si FileName="" (chaine vide) l'image est lue sur stdin.
 * Retourne NULL si probleme
 */
Image ImRead(const char FileName[])
{
  Image Im;
  FILE *Fid;

  if (FileName[0]=='\0')
  {
    Fid=stdin;
    Im=fImRead(&Fid,"stdin");
  }
  else
  {
    Fid=fopen(FileName,"rb");
    if (Fid==NULL)
    {
      LimError("ImRead","%s: file not found",FileName);
      return NULL;
    }
    Im=fImRead(&Fid,FileName);
    fclose(Fid);
  }
  return Im;
}



/* Ecrit une image dans un fichier au format binaire de nom FileName.
 * Si FileName="" (chaine vide) l'image est erite sur stdout (attention :
 * lors de l'ecriture sur stdout, problemes possibles sous DOS).
 */
void ImWrite(Image Im, const char FileName[])
{
  FILE *Fid;
  ImageType Type;
  int i,j,k,NbEcrits,NbLig,NbCol;
  unsigned char **I,**R,**G,**B,Byte=0;

  if (Im==NULL)
  {
    LimError("ImWrite","NULL pointer");
    return;
  }

  if (FileName[0]=='\0') { Fid=stdout;  FileName="stdout"; }
  else
  {
    Fid=fopen(FileName,"wb");
    if (Fid==NULL)
    {
      LimError("ImWrite","%s: unable to open",FileName);
      return;
    }
  }
  Type=ImType(Im);
  NbLig=ImNbRow(Im);
  NbCol=ImNbCol(Im);
  switch (Type)
  {
  case BitMap:
    NbEcrits=fprintf(Fid,"%s\n%d %d\n",
         "P4",NbCol,NbLig);
    if (NbEcrits<=0)
    {
      LimError("ImWrite","error while writing %s",FileName);
      if (FileName[0]!='\0') fclose(Fid);
      return;
    }
    /*if (FileName[0]!='\0')
      {
      fclose(Fid);
      Fid=fopen(FileName,"ab");
      if (Fid==NULL)
      {
      LimError("ImWrite","error while writing %s",FileName);
      return;
      }
      }*/
    I=ImGetI(Im);
    for (i=0,k=0,Byte=0;i<NbLig;i++)
    {
      for (j=0;j<NbCol;j++)
      {
  if (!I[i][j]) BITPUT(Byte,k);
  k++;
  if (k==8)
  {
    if (putc(Byte,Fid)==EOF)
    {
      LimError("ImWrite","error while writing %s",FileName);
      return;
    }
    k=0;
    Byte=0;
  }
      }
      if (k)
      {
  if (putc(Byte,Fid)==EOF)
  {
    LimError("ImWrite","error while writing %s",FileName);
    return;
  }
  k=0;
  Byte=0;
      }
    }
    break;

  case GrayLevel:
    NbEcrits=fprintf(Fid,"%s\n%d %d\n%d\n",
         "P5",NbCol,NbLig,255);
    if (NbEcrits<=0)
    {
      LimError("ImWrite","error while writing %s",FileName);
      if (FileName[0]!='\0') fclose(Fid);
      return;
    }
    /*if (FileName[0]!='\0')
      {
      fclose(Fid);
      Fid=fopen(FileName,"ab");
      if (Fid==NULL)
      {
      LimError("ImWrite","error while writing %s",FileName);
      return;
      }
      }*/
    NbEcrits=fMatWriteUC(Fid,ImGetI(Im),NbLig,NbCol);
    if (NbEcrits!=(NbLig*NbCol))
    {
      LimError("ImWrite","error while writing %s",FileName);
      if (FileName[0]!='\0') fclose(Fid);
      return;
    }
    break;

  case Color:
    NbEcrits=fprintf(Fid,"%s\n%d %d\n%d\n",
         "P6",NbCol,NbLig,255);
    if (NbEcrits<=0)
    {
      LimError("ImWrite","error while writing %s",FileName);
      if (FileName[0]!='\0') fclose(Fid);
      return;
    }
    /*if (FileName[0]!='\0')
      {
      fclose(Fid);
      Fid=fopen(FileName,"ab");
      if (Fid==NULL)
      {
      LimError("ImWrite","error while writing %s",FileName);
      return;
      }
      }*/
    R=ImGetR(Im);
    G=ImGetG(Im);
    B=ImGetB(Im);
    for (i=0;i<NbLig;i++)
      for (j=0;j<NbCol;j++)
      {
  if (putc(R[i][j],Fid)==EOF)
  {
    LimError("ImWrite","error while writing %s",FileName);
    if (FileName[0]!='\0') fclose(Fid);
    return;
  }
  if (putc(G[i][j],Fid)==EOF)
  {
    LimError("ImWrite","error while writing %s",FileName);
    if (FileName[0]!='\0') fclose(Fid);
    return;
  }
  if (putc(B[i][j],Fid)==EOF)
  {
    LimError("ImWrite","error while writing %s",FileName);
    if (FileName[0]!='\0') fclose(Fid);
    return;
  }
      }
    break;
  }

  if (FileName[0]!='\0') fclose(Fid);
  return;
}


/* Ecrit une image dans un fichier au format ASCII de nom FileName.
 * Si FileName="" (chaine vide) l'image est ecrite sur stdout.
 */
void ImWriteAsc(Image Im, const char FileName[])
{
  FILE *Fid;
  ImageType Type;
  int i,j,NbEcrits,NbLig,NbCol;
  unsigned char **I,**R,**G,**B;

  if (Im==NULL)
  {
    LimError("ImWriteAsc","NULL pointer");
    return;
  }
  if (FileName[0]=='\0') { Fid=stdout; FileName="stdout"; }
  else
  {
    Fid=fopen(FileName,"wb");
    if (Fid==NULL)
    {
      LimError("ImWriteAsc","%s: unable to open",FileName);
      return;
    }
  }
  Type=ImType(Im);
  NbLig=ImNbRow(Im);
  NbCol=ImNbCol(Im);
  switch (Type)
  {
  case BitMap:
    NbEcrits=fprintf(Fid,"%s\n%d %d\n",
         "P1",NbCol,NbLig);
    if (NbEcrits<=0)
    {
      LimError("ImWriteAsc","error while writing %s",FileName);
      if (FileName[0]!='\0') fclose(Fid);
      return;
    }
    I=ImGetI(Im);
    for (i=0;i<NbLig;i++)
      for (j=0;j<NbCol;j++)
  if (fprintf(Fid,"%d ",!I[i][j])<=0)
  {
    LimError("ImWriteAsc","error while writing %s",FileName);
    if (FileName[0]!='\0') fclose(Fid);
    return;
  }
    break;

  case GrayLevel:
    NbEcrits=fprintf(Fid,"%s\n%d %d\n%d\n",
         "P2",NbCol,NbLig,255);
    if (NbEcrits<=0)
    {
      LimError("ImWriteAsc","error while writing %s",FileName);
      if (FileName[0]!='\0') fclose(Fid);
      return;
    }
    I=ImGetI(Im);
    for (i=0;i<NbLig;i++)
      for (j=0;j<NbCol;j++)
  if (fprintf(Fid,"%d ",I[i][j])<=0)
  {
    LimError("ImWriteAsc","error while writing %s",FileName);
    if (FileName[0]!='\0') fclose(Fid);
    return;
  }
    break;

  case Color:
    NbEcrits=fprintf(Fid,"%s\n%d %d\n%d\n",
         "P3",NbCol,NbLig,255);
    if (NbEcrits<=0)
    {
      LimError("ImWriteAsc","error while writing %s",FileName);
      if (FileName[0]!='\0') fclose(Fid);
      return;
    }
    R=ImGetR(Im);
    G=ImGetG(Im);
    B=ImGetB(Im);
    for (i=0;i<NbLig;i++)
      for (j=0;j<NbCol;j++)
  if (fprintf(Fid,"%d %d %d ",R[i][j],G[i][j],B[i][j])<=0)
  {
    LimError("ImWriteAsc","error while writing %s",FileName);
    if (FileName[0]!='\0') fclose(Fid);
    return;
  }
    break;
  }

  if (FileName[0]!='\0') fclose(Fid);
  return;
}


/*****************************************************************************/
/* MANIPULATION DE LISTES
 */

/* Structures de donnees "privees"
 */

/* Cellule */
typedef struct _Cell
{
  void *Data;
  struct _Cell *Previous, *Next;
} Cell;

/* Descripteur de liste */
struct sList
{
  Cell *First, *Last, *Current;
  size_t DataSize;
  int NbElts;
  int (*CompareFct)(void *pElt1, void *pElt2);
};



/* Numerotation des exceptions */
#define MEMORY_ALLOC 1
#define NULL_POINTER 2
#define POSITION 3
#define MODE 4
#define ELT_NOT_FOUND 5
#define NOT_SORTED 6

/* Affichage des messages d'exeptions */
static void ListError(const int Num, const char *Operator)
{
  (void)Verbose(); if (!Verbose()) return;
  switch (Num)
  {
  case MEMORY_ALLOC:
    fprintf(stderr,"[LIMaCE] (%s): Not enough memory !\n",Operator);
    return;
  case NULL_POINTER:
    fprintf(stderr,"[LIMaCE] (%s): NULL pointer passed !\n",Operator);
    return;
  case POSITION:
    fprintf(stderr,"[LIMaCE] (%s): bad position !\n",Operator);
    return;
  case MODE:
    fprintf(stderr,"[LIMaCE] (%s): bad mode !\n",Operator);
    return;
  case ELT_NOT_FOUND:
    fprintf(stderr,"[LIMaCE] (%s): element not found !\n",Operator);
    return;
  case NOT_SORTED:
    fprintf(stderr,"[LIMaCE] (%s): must be a sorted list !\n",Operator);
    return;
  }
}


/*******************
 * FONCTIONS DE BASE
 */

/* Creation d'une liste vide. Renvoie NULL si probleme d'allocation.
 * EltSize : taille de chaque element
 */
List ListCreate(size_t EltSize)
{
  List Lst;

  Lst=(List)malloc(sizeof(struct sList));
  if (Lst!=NULL)
  {
    Lst->NbElts=0;
    Lst->DataSize=EltSize;
    Lst->First=Lst->Last=Lst->Current=NULL;
    Lst->CompareFct=NULL;
  }
  else ListError(MEMORY_ALLOC,"ListCreate");
  return(Lst);
}


/* Nombre d'elements dans une liste
 * Retourne -1 si probleme
 */
int ListCount(List L)
{
  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListCount");
    return -1;
  }
  return L->NbElts;
}


/* Taille d'un element d'une liste
 * Retourne 0 si probleme
 */
size_t ListEltSize(List L)
{
  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListEltSize");
    return 0;
  }
  return L->DataSize;
}


/* Liste vide ?
 * Retourne 1 si liste vide, 0 sinon.
 * Retourne -1 si probleme
 */
int ListIsEmpty(List L)
{
  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListIsEmpty");
    return -1;
  }
  return(L->NbElts==0);
}


/* Retourne l'adresse de la cellule qui se trouve en position Position dans la liste L.
 * Retourne NULL si Position<0 ou Position>=(ListCount(L)-1).
 */
static Cell *ListGetCell(List L, int Position)
{
  Cell *p;
  int Dernier=ListCount(L)-1,i;

  if ((Position<0) || (Position>Dernier)) return NULL;
  if (Position<(Dernier/2))
  {
    p=L->First;
    for (i=0;i<Position;p=p->Next,i++) ;
    return p;
  }
  else
  {
    p=L->Last;
    for (i=Dernier;i>Position;p=p->Previous,i--) ;
    return p;
  }
}


/* Retourne l'adresse de l'element qui se trouve en position
 * Position dans la liste L.
 * - si Position=FIRST : designe le premier element ;
 * - si Position=LAST : designe le dernier element ;
 * - si Position=CURRENT : designe l'element place sous le curseur ;
 * - si 0 <= Position <= (ListCount(L)-1) : designe l'element qui se trouve
 *   en position Position.
 * Retourne NULL si la position specifiee est incorrecte.
 */
void *ListGet(List L, int Position)
{
  Cell *p;

  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListGet");
    return NULL;
  }
  switch (Position)
  {
  case FIRST:
    p=L->First; break;
  case LAST:
    p=L->Last; break;
  case CURRENT:
    p=L->Current; break;
  default:
    p=ListGetCell(L,Position);
    if (p==NULL)
    {
      ListError(POSITION,"ListGet");
      return NULL;
    }
  }
  if (p==NULL) return NULL;
  return p->Data;
}


/* Retourne l'adresse d'une copie de l'element qui se trouve en position
 * Position dans la liste L.
 * - si Position=FIRST : designe le premier element ;
 * - si Position=LAST : designe le dernier element ;
 * - si Position=CURRENT : designe l'element place sous le curseur ;
 * - si 0 <= Position <= (ListCount(L)-1) : designe l'element qui se trouve
 *   en position Position.
 * Retourne NULL si la position specifiee est incorrecte.
 */
void *ListGetCopy(List L, int Position)
{
  Cell *p;
  void *pRes;

  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListGetCopy");
    return NULL;
  }
  switch (Position)
  {
  case FIRST:
    p=L->First; break;
  case LAST:
    p=L->Last; break;
  case CURRENT:
    p=L->Current; break;
  default:
    p=ListGetCell(L,Position);
    if (p==NULL)
    {
      ListError(POSITION,"ListGetCopy");
      return NULL;
    }
  }
  if (p==NULL) return NULL;


  pRes=malloc(L->DataSize);
  if (pRes==NULL)
  {
    ListError(MEMORY_ALLOC,"ListGetCopy");
    return NULL;
  }
  memcpy(pRes,p->Data,L->DataSize);
  return pRes;
}


/* Insertion d'un element d'adresse pElt dans une liste L.
 * Place le nouvel element a l'endroit defini par les parametres Mode et
 * Position.
 *
 * La position est ainsi definie :
 * - Position = FIRST designe le premier element de la liste ;
 * - Position = LAST designe le dernier element de la liste ;
 * - Position = CURRENT designe l'element qui se trouve sous le curseur ;
 * - 0 <= Position <= (ListCount(L)-1) : designe un element de la liste repere
 *   par sa position (0 pour le premier, etc.).
 *
 * Le mode est ainsi defini :
 * - Mode = BEFORE signifie que l'insertion se fera avant la position definie
 *   par Position ;
 * - Mode = AFTER signifie que l'insertion se fera apres la position definie
 *   par Position.
 *
 * Une recopie de l'element a inserer est effectuee.
 * Le curseur de la liste n'est pas modifie (il reste sur le meme element).
 * Si l'on souhaite qu'il soit place sur l'element qui vient d'etre insere,
 * il faut utiliser les fonctions de gestion du curseur.
 *
 * Retourne l'adresse de la copie de l'element placee dans la liste, NULL si
 * probleme (position incorrecte, etc.).
 */
void *ListInsert(List L, void *pElt, int Mode, int Position)
{
  Cell *pNew,*Suiv=NULL;
  int n=ListCount(L);
  enum ActionType { EnTete, EnFin, AuMilieu, ListeVide } Action;

  if ((pElt==NULL)||(L==NULL))
  {
    ListError(NULL_POINTER,"ListInsert");
    return NULL;
  }
  if ((Mode!=BEFORE)&&(Mode!=AFTER))
  {
    ListError(MODE,"ListInsert");
    return NULL;
  }
  if ((Position!=FIRST)&&(Position!=CURRENT)&&(Position!=LAST))
  {
    if ((Position<LAST)||(Position>=n))
    {
      ListError(POSITION,"ListInsert");
      return NULL;
    }
  }
  else
    if ((Position==CURRENT)&&(L->Current==NULL)&&(L->First!=NULL))
    {
      ListError(POSITION,"ListInsert");
      return NULL;
    }
  if (L->First==NULL) Action=ListeVide;
  else
    if (Mode==BEFORE)
      switch (Position)
      {
      case FIRST:
  Action=EnTete; break;
      case LAST:
  if (L->Last->Previous==NULL)
    Action=EnTete;
  else
  {
    Action=AuMilieu;
    Suiv=L->Last;
  }
  break;
      case CURRENT:
  if (L->Current->Previous==NULL) Action=EnTete;
  else
  {
    Action=AuMilieu;
    Suiv=L->Current;
  }
  break;
      default:
  Action=AuMilieu; Suiv=ListGetCell(L,Position);
      }
    else /* AFTER */
      switch (Position)
      {
      case FIRST:
  if (L->First->Next==NULL) Action=EnFin;
  else
  {
    Action=AuMilieu;
    Suiv=L->First->Next;
  }
  break;
      case LAST:
  Action=EnFin; break;
      case CURRENT:
  if (L->Current->Next==NULL) Action=EnFin;
  else
  {
    Action=AuMilieu;
    Suiv=L->Current;
  }
  break;
      default:
  if (Position==(n-1)) Action=EnFin;
  else
  {
    Action=AuMilieu;
    Suiv=ListGetCell(L,Position+1);
  }
      }
  pNew=(Cell *)malloc(sizeof(Cell));
  if (pNew==NULL)
  {
    ListError(MEMORY_ALLOC,"ListInsert");
    return NULL;
  }
  pNew->Data=malloc(L->DataSize);
  if (pNew->Data==NULL)
  {
    ListError(MEMORY_ALLOC,"ListInsert");
    free(pNew);
    return NULL;
  }
  memcpy(pNew->Data,pElt,L->DataSize);
  switch (Action)
  {
  case EnTete:
    pNew->Next=L->First;
    pNew->Previous=NULL;
    L->First=L->First->Previous=pNew;
    break;
  case EnFin:
    pNew->Next=NULL;
    pNew->Previous=L->Last;
    L->Last=L->Last->Next=pNew;
    break;
  case AuMilieu:
    pNew->Next=Suiv;
    pNew->Previous=Suiv->Previous;
    Suiv->Previous=Suiv->Previous->Next=pNew;
    break;
  case ListeVide:
    pNew->Next=pNew->Previous=NULL;
    L->First=L->Last=pNew;
  }
  (L->NbElts)++;
  return(pNew);
}


/* Suppression d'un element de position specifiee dans une liste :
 * - Position=FIRST : suppression du premier element ;
 * - Position=LAST : suppression du dernier element ;
 * - Position=CURRENT : suppression de l'element place sous le curseur ;
 * - 0 <= Position <= (ListCount(L)-1) : suppression de l'element se trouvant
 *   en position Position.
 * Si le curseur se trouve sur l'element  a supprimer, il est avance d'une
 * position, sinon, il n'est pas modifie
 * Aucune modification n'est effectuee si la position specifiee n'existe pas
 */
void ListRemove(List L, int Position)
{
  Cell *p;
  int n=ListCount(L);

  if ((Position<-2)||(Position>(n-1)))
  {
    ListError(POSITION,"ListRemove");
    return;
  }
  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListRemove");
    return;
  }
  switch (Position)
  {
  case FIRST:
    p=L->First; break;
  case LAST:
    p=L->Last; break;
  case CURRENT:
    p=L->Current; break;
  default:
    p=ListGetCell(L,Position);
  }
  (L->NbElts)--;
  if (p==NULL) return;
  if (L->Current==p)
    L->Current=p->Next;
  if (p->Previous==NULL)
    L->First=p->Next;
  else
    p->Previous->Next=p->Next;
  if (p->Next==NULL)
    L->Last=p->Previous;
  else
    p->Next->Previous=p->Previous;
  free(p->Data);
  free(p);
  return;
}



/* Liberation complete de l'espace memoire occupe par une liste
 * Si les elements comportent des pointeurs, la liberation des objets
 * pointes doit etre geree au prealable par l'utilisateur.
 */
void ListFree(List *pL)
{
  Cell *p;
  List Lst=*pL;

  if ((Lst!=NULL)&&(!ListIsEmpty(Lst)))
  {
    for(p=Lst->First;p!=Lst->Last;)
    {
      free(p->Data);
      p=p->Next;
      free(p->Previous);
    }
    free(p->Data);
    free(p);
  }
  free(Lst);
  *pL=NULL;
  return;
}


/* Retourne une copie d'une liste, NULL si probleme
 */
List ListCopy(List Source)
{
  List Dest;
  int i,n=ListCount(Source);

  n=ListCount(Source);
  if (n==-1)
  {
    ListError(NULL_POINTER,"ListCopy");
    return NULL;
  }
  Dest=ListCreate(ListEltSize(Source));
  if (Dest==NULL)
  {
    ListError(MEMORY_ALLOC,"ListCopy");
    return NULL;
  }
  for (i=0;i<n;i++)
    if (ListInsert(Dest,ListGet(Source,i),BEFORE,i)==NULL)
    {
      ListError(MEMORY_ALLOC,"ListCopy");
      ListFree(&Dest);
      return NULL;
    }
  return Dest;
}


/************************
 * UTILISATION DU CURSEUR
 */

/* Place le curseur de la liste L sur le premier element.
 * Retourne NULL si probleme.
 */
void ListInitCur(List L)
{
  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListInitCur");
    return;
  }
  L->Current=L->First;
}


/* Retourne 1 si le curseur se trouve a la fin de la liste L (il n'est place sur aucun element),
 * 0 sinon et -1 en cas de probleme.
 */
int ListEol(List L)
{
  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListEol");
    return -1;
  }
  return L->Current==NULL;
}


/* Avance d'une position le curseur de la liste L.
 * Retourne l'adresse du nouvel element place sous le curseur ou NULL si le curseur est deja
 * a la fin de la liste ou en cas de probleme.
 */
void *ListForward(List L)
{
  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListForward");
    return NULL;
  }
  if (L->Current==NULL) return NULL;
  L->Current=L->Current->Next;
  if (L->Current==NULL) return NULL;
  return L->Current->Data;
}


/* Recule d'une position le curseur de la liste L.
 * Retourne l'adresse du nouvel element place sous le curseur ou NULL si le curseur est deja
 * au debut de la liste ou en cas de probleme.
 */
void *ListBackward(List L)
{
  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListBackward");
    return NULL;
  }
  if (L->Current==NULL) return NULL;
  L->Current=L->Current->Previous;
  if (L->Current==NULL) return NULL;
  return L->Current->Data;
}


/* Retourne la position du curseur de la liste L.
 * Retourne -1 si le curseur est en fin de liste ou en cas de probleme.
 */
int ListTell(List L)
{
  Cell *p;
  int i;

  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListTell");
    return -1;
  }
  for (p=L->First,i=0;(p!=NULL)&&(p!=L->Current);p=p->Next,i++) ;
  if (p==NULL) return -1;
  return i;
}


/* Place le curseur de la liste L sur l'element situe a Offset elements de
 * l'origine definie par RefPos :
 * - RefPos=BEGIN designe le debut de la liste ;
 * - RefPos=CURRENT designe la position actuelle du curseur de la liste ;
 * - RefPos=END designe la fin de la liste.
 * ListSeek retourne 0 si tout s'est bien passe, -1 si la position definie est incorrecte,
 * -2 si le parametre Mode est incorrect et -3 en cas de probleme.
 */
int ListSeek(List L, int Offset, int RefPos)
{
  Cell *p;
  int Dernier=ListCount(L)-1,Position,i,Fin;

  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListSeek");
    return -3;
  }
  switch (RefPos)
  {
  case BEGIN:
    Position=0; p=L->First;
    break;
  case CURRENT:
    Position=ListTell(L); p=L->Current;
    if (L->Current==NULL)
    {
      ListError(POSITION,"ListSeek");
      return -1;
    }
    break;
  case END:
    Position=Dernier; p=L->Last; Offset++;
    break;
  default:
    ListError(MODE,"ListSeek");
    return -2;
  }
  Position+=Offset;
  if ((Position<0)||(Position>Dernier))
  {
    ListError(POSITION,"ListSeek");
    return -1;
  }
  i=0; Fin=(Offset>0?Offset:-Offset);
  if (Offset>0) while (i++<Fin) p=p->Next;
  else while (i++<Fin) p=p->Previous;
  L->Current=p;
  return 0;
}


/* Positionne le curseur de la liste L sur l'element d'adresse pElt.
 * Retourne l'adresse de l'element en question ou NULL si probleme.
 */
void *ListSetCur(List L, void *pElt)
{
  Cell *p;

  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListSetCur");
    return NULL;
  }
  for (p=L->First;((p!=NULL)&&(p->Data!=pElt));p=p->Next) ;
  if (p==NULL)
  {
    ListError(ELT_NOT_FOUND,"ListSetCur");
    return NULL;
  }
  L->Current=p;
  return pElt;
}


/* Retourne l'adresse de l'element place sous le curseur de la liste L ou NULL
 * si probleme. Cette fonction est equivalente a ListGet(L,CURRENT);
 */
void *ListGetCur(List L)
{
  Cell *p;

  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListGetCur");
    return NULL;
  }
  p=L->Current;
  if (p==NULL) return NULL;
  return p->Data;
}


/* Retourne l'adresse d'une copie de l'element place sous le curseur de la
 * liste L ou NULL si probleme. Cette fonction est equivalente a
 * ListGetCopy(L,CURRENT);
 */
void *ListGetCurCopy(List L)
{
  Cell *p;
  void *pRes;

  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListGetCurCopy");
    return NULL;
  }
  p=L->Current;
  if (p==NULL) return NULL;
  pRes=malloc(L->DataSize);
  if (pRes==NULL)
  {
    ListError(MEMORY_ALLOC,"ListGetCurCopy");
    return NULL;
  }
  memcpy(pRes,p->Data,L->DataSize);
  return pRes;
}


/* Suppression de l'element place sous le curseur de la liste L.
 * Le curseur est avance d'une position.
 * Si le curseur est deja en fin de liste ou si un probleme survient, aucune
 * modification n'est effectuee. Cette fonction est equivalente a
 * ListRemove(L,CURRENT);
 */
void ListRemoveCur(List L)
{
  Cell *p;

  if (L==NULL)
  {
    ListError(NULL_POINTER,"ListRemoveCur");
    return;
  }
  p=L->Current;
  if (p==NULL) return;
  L->Current=p->Next;
  if (p->Previous==NULL)
    L->First=p->Next;
  else
    p->Previous->Next=p->Next;
  if (p->Next==NULL)
    L->Last=p->Previous;
  else
    p->Next->Previous=p->Previous;
  free(p->Data);
  free(p);
  return;
}


/********************
 * FONCTIONS AVANCEES
 */

/* Application d'une fonction a tous les elements d'une liste :
 * applique la fonction passe en deuxieme parametre a tous les elements de la liste L.
 * Les eventuels parametres suivants sont passes a la fonction lors de son application.
 */
void ListApply(List L, Function Fct, ...)
{
  va_list Pars;
  Cell *p;

  if ((L==NULL) || (Fct==NULL))
  {
    ListError(NULL_POINTER,"ListApply");
    return;
  }
  va_start(Pars,Fct);
  for (p=L->First;p!=NULL;p=p->Next)
    Fct(p->Data,Pars);
  va_end(Pars);
}


/* Retourne l'adresse du premier element de la liste L pour lequel la fonction passee en
 * parametre retourne une valeur non nulle.
 * Retourne NULL si aucun element ne correspond ou en cas de probleme.
 */
void *ListFirstThat(List L, Function Fct, ...)
{
  va_list Pars;
  Cell *p;

  if ((L==NULL) || (Fct==NULL))
  {
    ListError(NULL_POINTER,"ListFirstThat");
    return NULL;
  }
  va_start(Pars,Fct);
  for (p=L->First;((p!=NULL)&&(!Fct(p->Data,Pars)));p=p->Next) ;
  va_end(Pars);
  if (p==NULL) return NULL;
  /*L->Current=p;*/
  return p->Data;
}


/* Retourne l'adresse du premier element suivant le curseur pour lequel la
 * fonction passee en parametre retourne une valeur non nulle.
 * Retourne NULL si aucun element ne correspond ou en cas de probleme.
 */
void *ListNextThat(List L, Function Fct, ...)
{
  va_list Pars;
  Cell *p;

  if ((L==NULL) || (Fct==NULL))
  {
    ListError(NULL_POINTER,"ListNextThat");
    return NULL;
  }
  va_start(Pars,Fct);
  for (p=L->Current;((p!=NULL)&&(!Fct(p->Data,Pars)));p=p->Next) ;
  va_end(Pars);
  if (p==NULL) return NULL;
  /*L->Current=p;*/
  return p->Data;
}


/* Retourne l'adresse du premier element precedent le curseur pour lequel la
 * fonction passee en parametre retourne une valeur non nulle.
 * Retourne NULL si aucun element ne correspond ou en cas de probleme.
 */
void *ListPreviousThat(List L, Function Fct, ...)
{
  va_list Pars;
  Cell *p;

  if ((L==NULL) || (Fct==NULL))
  {
    ListError(NULL_POINTER,"ListPreviousThat");
    return NULL;
  }
  va_start(Pars,Fct);
  for (p=L->Current;((p!=NULL)&&(!Fct(p->Data,Pars)));p=p->Previous) ;
  va_end(Pars);
  if (p==NULL) return NULL;
  /*L->Current=p;*/
  return p->Data;
}


/* Retourne l'adresse du dernier element de la liste L pour lequel la fonction passee en
 * parametre retourne une valeur non nulle.
 * Retourne NULL si aucun element ne correspond ou en cas de probleme.
 */
void *ListLastThat(List L, Function Fct, ...)
{
  va_list Pars;
  Cell *p;

  if ((L==NULL) || (Fct==NULL))
  {
    ListError(NULL_POINTER,"ListLastThat");
    return NULL;
  }
  va_start(Pars,Fct);
  for (p=L->Last;((p!=NULL)&&(!Fct(p->Data,Pars)));p=p->Previous) ;
  va_end(Pars);
  if (p==NULL) return NULL;
  /*L->Current=p;*/
  return p->Data;
}


/* Retourne une liste composee des elements de la liste L pour lesquels la fonction passee en
 * parametre retourne une valeur non nulle.
 * Retourne NULL en cas de probleme.
 */
List ListAllThat(List L, Function Fct, ...)
{
  va_list Pars;
  Cell *p;
  List Res=NULL;
  List ListCreateSorted(size_t EltSize, int (*Fct)(void *pElt1, void *pElt2));

  if ((L==NULL) || (Fct==NULL))
  {
    ListError(NULL_POINTER,"ListAllThat");
    return NULL;
  }
  if (L->CompareFct!=NULL)
    Res=ListCreateSorted(L->DataSize,L->CompareFct);
  else
    Res=ListCreate(L->DataSize);
  if (Res==NULL)
  {
    ListError(MEMORY_ALLOC,"ListAllThat");
    return NULL;
  }
  va_start(Pars,Fct);
  for (p=L->Last;p!=NULL;p=p->Previous)
    if (Fct(p->Data,Pars))
      if (ListInsert(Res,p->Data,BEFORE,BEGIN)==NULL)
      {
  ListError(MEMORY_ALLOC,"ListAllThat");
  return Res;
      }
  va_end(Pars);
  return Res;
}


/* Supprime de la liste L tous les elements pour lesquels la fonction passee en
 * parametre retourne une valeur non nulle.
 * Le curseur est place sur l'element suivant le dernier element efface.
 */
void ListRemoveAllThat(List L, Function Fct, ...)
{
  va_list Pars;
  Cell *p;
  int Pos;

  if ((L==NULL) || (Fct==NULL))
  {
    ListError(NULL_POINTER,"ListRemoveAllThat");
    return;
  }
  va_start(Pars,Fct);
  for (p=L->First,Pos=0;p!=NULL;p=p->Next,Pos++)
    if (Fct(p->Data,Pars)) ListRemove(L,Pos);
  va_end(Pars);
  return;
}



/*********************************
 * LISTES TRIEES (ordre croissant)
 */


/* Creation d'une liste triee vide. Renvoie NULL si probleme d'allocation.
 * EltSize : taille de chaque element
 * Fct : fonction de comparaison qui doit retourner :
 *       <0 si *pElt1 < *pElt2
 *       =0 si *pElt1 = *pElt2
 *       >0 si *pElt1 > *pElt2
 */
List ListCreateSorted(size_t EltSize, int (*Fct)(void *pElt1, void *pElt2))
{
  List Lst;

  Lst=(List)malloc(sizeof(struct sList));
  if (Lst!=NULL)
  {
    Lst->NbElts=0;
    Lst->DataSize=EltSize;
    Lst->First=Lst->Last=Lst->Current=NULL;
    Lst->CompareFct=Fct;
  }
  else ListError(MEMORY_ALLOC,"ListCreateSorted");
  return Lst;
}


/* Insertion d'un element dans une liste triee.
 * Positionne le nouvel element de telle sorte qu'il se trouve dans la position
 * specifiee (insertion en tete : 0 ; insertion en fin : ListCount(L))
 * L : la liste
 * pElt : adresse de l'element a inserer
 * Une recopie de cet element est effectuee
 * Le curseur n'est pas modifie
 * Retourne l'adresse de la copie de l'element, NULL si probleme.
 */
void *ListInsertSorted(List L, void *pElt)
{
  Cell *pNew,*p;

  if ((pElt==NULL)||(L==NULL))
  {
    ListError(NULL_POINTER,"ListInsertSorted");
    return NULL;
  }
  if (L->CompareFct==NULL)
  {
    ListError(NOT_SORTED,"ListInsertSorted");
    return NULL;
  }
  pNew=(Cell *)malloc(sizeof(Cell));
  if (pNew==NULL)
  {
    ListError(MEMORY_ALLOC,"ListInsertSorted");
    return NULL;
  }
  pNew->Data=malloc(L->DataSize);
  if (pNew->Data==NULL)
  {
    ListError(MEMORY_ALLOC,"ListInsertSorted");
    free(pNew);
    return NULL;
  }
  memcpy(pNew->Data,pElt,L->DataSize);
  if (L->NbElts==0)
  {
    pNew->Previous=pNew->Next=NULL;
    L->First=L->Last=pNew;
  }
  else
  {
    for(p=L->First;
  ((p!=NULL)&&(L->CompareFct(p->Data,pElt)<0));
  p=p->Next) ;
    if (p==NULL)
    {
      pNew->Previous=L->Last;
      pNew->Next=NULL;
      L->Last=L->Last->Next=pNew;
    }
    else
    {
      pNew->Previous=p->Previous;
      pNew->Next=p;
      if (p->Previous==NULL)
  p->Previous=L->First=pNew;
      else
  p->Previous=p->Previous->Next=pNew;
    }
  }
  (L->NbElts)++;
  return(pNew);
}


typedef int (*CompareType)(const void *, const void *);
/* Tri d'une liste.
 * Retourne une nouvelle liste triee (par ordre croissant) ou NULL si probleme.
 * Fct : fonction de comparaison qui doit retourner :
 *       <0 si *pElt1 < *pElt2
 *       =0 si *pElt1 = *pElt2
 *       >0 si *pElt1 > *pElt2
 * ListSort n'est pas optimisee, au niveau temps d'execution.
 */
List ListSort(List L, int (*Fct)(void *pElt1, void *pElt2))
{
  List LRes;
  Cell *p;

  if ((L==NULL)||(Fct==NULL))
  {
    ListError(NULL_POINTER,"ListSort");
    return NULL;
  }
  LRes=ListCreateSorted(ListEltSize(L),Fct);
  if (LRes==NULL)
  {
    ListError(MEMORY_ALLOC,"ListSort");
    return NULL;
  }
  for (p=L->First; p!=NULL; p=p->Next)
    if (ListInsertSorted(LRes,p->Data)==NULL)
    {
      ListError(MEMORY_ALLOC,"ListSort");
      ListFree(&LRes);
      return NULL;
    }
  return LRes;
}
