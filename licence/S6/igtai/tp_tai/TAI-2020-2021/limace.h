/* Copyright (C) 1999-2011 A. Crouzil  LIMaCE release 1.6 (07/06/2012) */
/* Debugging : N. Begue (15/05/2001), G. Jaffre (08/05/2002),
 *             B. Pailhes (02/04/2003), F. Courteille (09/04/2003),
 *             J.-D. Durou (18/08/2005, 08/09/2005), G. Gales (02/03/2011).
 */
#ifndef __limace_h_
#define __limace_h_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


/*************** GESTION DE L'AFFICHAGE DES MESSAGES D'ERREUR ****************/

#define ON 1
#define OFF 0

/* Commutateur d'affichage des messages d'erreurs sur stderr.
 * A chaque appel de la fonction on passe d'un etat a l'autre :
 * - ON : les messages d'erreurs sont affiches sur stdout (par defaut)
 * - OFF : aucun message d'erreur n'est affiche
 * Verbose retourne le nouvel etat (ON ou OFF)
 */
extern int Verbose(void);


#ifdef __cplusplus
}
#endif


/************************** MANIPULATION D'IMAGES ****************************/

/* Le type "prive" Image
 */
typedef struct sImage *Image;

/* Types d'image
 */
typedef enum
{
 BitMap=0,    /* image noir=0 et blanc=1 [0,1]             */
 GrayLevel=1, /* image de niveaux de gris [0,255]          */
 Color=2      /* image couleur RGB [0,255]x[0,255]x[0,255] */
} ImageType;


#ifdef __cplusplus
extern "C" {
#endif


/* Creation d'une image. Retourne NULL si probleme.
 */
extern Image ImAlloc(ImageType Type, int NbRow, int NbCol);


/* Creation d'une image initialisee a 0. Retourne NULL si probleme.
 */
extern Image ImCAlloc(ImageType Type, int NbRow, int NbCol);


/* Retourne le type d'une image (BitMap, GrayLevel, Color)
 */
extern ImageType ImType(Image Im);


/* Retourne le nombre de lignes d'une image, 0 si probleme
 */
extern int ImNbRow(Image Im);


/* Retourne le nombre de colonnes d'une image, 0 si probleme
 */
extern int ImNbCol(Image Im);


/* Acces a la matrice des niveaux de gris d'une image de type GrayLevel ou
 * BitMap
 * Retourne NULL si probleme
 */
extern unsigned char **ImGetI(Image Im);



/* Acces a la matrice du plan R d'une image de type Color
 * Retourne NULL si probleme
 */
extern unsigned char **ImGetR(Image Im);


/* Acces a la matrice du plan G d'une image de type Color
 * Retourne NULL si probleme
 */
extern unsigned char **ImGetG(Image Im);


/* Acces a la matrice du plan B d'une image de type Color
 * Retourne NULL si probleme
 */
extern unsigned char **ImGetB(Image Im);


/* Copie d'une image
 * Retourne NULL si probleme
 */
extern Image ImCopy(Image Im);


/* Lit une image dans un fichier de nom FileName.
 * Si FileName="" (chaine vide) l'image est lue sur stdin.
 * Retourne NULL si probleme
 */
extern Image ImRead(const char FileName[]);


/* Ecrit une image dans un fichier au format binaire de nom FileName.
 * Si FileName="" (chaine vide) l'image est ecrite sur stdout (attention :
 * lors de l'ecriture sur stdout, problemes possibles sous DOS).
 */
extern void ImWrite(Image Im, const char FileName[]);


/* Ecrit une image dans un fichier au format ASCII de nom FileName.
 * Si FileName="" (chaine vide) l'image est ecrite sur stdout.
 */
extern void ImWriteAsc(Image Im, const char FileName[]);


/* Liberation complete de l'espace memoire occupe par une image
 */
extern void ImFree(Image *pIm);


#ifdef __cplusplus
}
#endif










/************************** MANIPULATION DE MATRICES *************************/

/* Le type "prive" Matrix */
typedef struct sMatrix *Matrix;

/* Types des elements d'une matrice */
typedef enum
{
 Int=3,
 Double=4
} MatrixType;


#ifdef __cplusplus
extern "C" {
#endif


/* Creation d'une matrice de int ou de double
 * Retourne NULL si probleme
 */
extern Matrix MatAlloc(MatrixType Type, int NbRow, int NbCol);


/* Creation d'une matrice de int ou de double initialisee a 0
 * Retourne NULL si probleme
 */
extern Matrix MatCAlloc(MatrixType Type, int NbRow, int NbCol);


/* Retourne le type d'une matrice (Int, Double);
 */
extern MatrixType MatType(Matrix Mat);


/* Retourne le nombre de lignes d'une matrice, 0 si probleme
 */
extern int MatNbRow(Matrix Mat);


/* Retourne le nombre de colonnes d'une matrice, 0 si probleme
 */
extern int MatNbCol(Matrix Mat);


/* Acces aux elements d'une matrice de int
 * Retourne NULL si probleme (par ex. si type matrice incorrect)
 */
extern int **MatGetInt(Matrix Mat);


/* Acces aux elements d'une matrice de double
 * Retourne NULL si probleme (par ex. si type matrice incorrect)
 */
extern double **MatGetDouble(Matrix Mat);


/* Copie d'une matrice
 * Retourne NULL si probleme
 */
extern Matrix MatCopy(Matrix Mat);


/* Lecture d'une matrice de int ou de double a partir d'un fichier ASCII
 * de nom FileName.
 * Le fichier peut etre au format "Matrix" ou ASCII de base.
 * Si FileName="" (chaine vide) la matrice est lue sur stdin ; dans ce cas,
 * le format attendu est le format "Matrix".
 * Retourne la matrice ou NULL si probleme
 */
extern Matrix MatReadAsc(const char FileName[]);


/* Ecriture ASCII d'une matrice de int ou de double au format "Matrix" dans un
 * fichier de nom FileName. Si FileName="" (chaine vide) la matrice est ecrite
 * sur stdout.
 */
extern void MatWriteAsc(Matrix Mat, const char FileName[]);


/* Liberation complete de l'espace memoire occupe par une matrice
 */
extern void MatFree(Matrix *pMat);


#ifdef __cplusplus
}
#endif


/************************** MANIPULATION DE LISTES *************************/

#include <stdarg.h>

#define FIRST 0
#define CURRENT -1
#define LAST -2
#define BEFORE 0
#define AFTER 1
#define BEGIN 0
#define END -3

/* Le type "prive" List */
typedef struct sList *List;

#ifdef __cplusplus
extern "C" {
#endif

/*******************
 * FONCTIONS DE BASE
 */

/* Creation d'une liste vide. Renvoie NULL si probleme d'allocation.
 * EltSize : taille de chaque element
 */
extern List ListCreate(size_t EltSize);


/* Nombre d'elements dans une liste
 * Retourne -1 si probleme
 */
extern int ListCount(List L);


/* Taille d'un element d'une liste
 * Retourne 0 si probleme
 */
extern size_t ListEltSize(List L);


/* Liste vide ?
 * Retourne 1 si liste vide, 0 sinon.
 * Retourne -1 si probleme
 */
extern int ListIsEmpty(List L);


/* Retourne l'adresse de l'element qui se trouve en position
 * Position dans la liste L.
 * - si Position=FIRST : designe le premier element ;
 * - si Position=LAST : designe le dernier element ;
 * - si Position=CURRENT : designe l'element place sous le curseur ;
 * - si 0 <= Position <= (ListCount(L)-1) : designe l'element qui se trouve
 *   en position Position.
 * Retourne NULL si la position specifiee est incorrecte.
 */
extern void *ListGet(List L, int Position);


/* Retourne l'adresse d'une copie de l'element qui se trouve en position
 * Position dans la liste L.
 * - si Position=FIRST : designe le premier element ;
 * - si Position=LAST : designe le dernier element ;
 * - si Position=CURRENT : designe l'element place sous le curseur ;
 * - si 0 <= Position <= (ListCount(L)-1) : designe l'element qui se trouve
 *   en position Position.
 * Retourne NULL si la position specifiee est incorrecte.
 */
extern void *ListGetCopy(List L, int Position);


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
extern void *ListInsert(List L, void *pElt, int Mode, int Position);


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
extern void ListRemove(List L, int Position);


/* Liberation complete de l'espace memoire occupe par une liste
 * Si les elements comportent des pointeurs, la liberation des objets
 * pointes doit etre geree au prealable par l'utilisateur.
 */
extern void ListFree(List *pL);


/* Retourne une copie d'une liste, NULL si probleme
 */
extern List ListCopy(List Source);


/************************
 * UTILISATION DU CURSEUR
 */

/* Place le curseur de la liste L sur le premier element.
 * Retourne NULL si probleme.
 */
extern void ListInitCur(List L);


/* Retourne 1 si le curseur se trouve a la fin de la liste L (il n'est place sur aucun element),
 * 0 sinon et -1 en cas de probleme.
 */
extern int ListEol(List L);


/* Avance d'une position le curseur de la liste L.
 * Retourne l'adresse du nouvel element place sous le curseur ou NULL si le curseur est deja
 * a la fin de la liste ou en cas de probleme.
 */
extern void *ListForward(List L);


/* Recule d'une position le curseur de la liste L.
 * Retourne l'adresse du nouvel element place sous le curseur ou NULL si le curseur est deja
 * au debut de la liste ou en cas de probleme.
 */
extern void *ListBackward(List L);


/* Retourne la position du curseur de la liste L.
 * Retourne -1 si le curseur est en fin de liste ou en cas de probleme.
 */
extern int ListTell(List L);


/* Place le curseur de la liste L sur l'element situe a Offset elements de
 * l'origine definie par RefPos :
 * - RefPos=BEGIN designe le debut de la liste ;
 * - RefPos=CURRENT designe la position actuelle du curseur de la liste ;
 * - RefPos=END designe la fin de la liste.
 * ListSeek retourne 0 si tout s'est bien passe, -1 si la position definie est incorrecte,
 * -2 si le parametre Mode est incorrect et -3 en cas de probleme.
 */
extern int ListSeek(List L, int Offset, int RefPos);


/* Positionne le curseur de la liste L sur l'element d'adresse pElt.
 * Retourne l'adresse de l'element en question ou NULL si probleme.
 */
extern void *ListSetCur(List L, void *pElt);


/* Retourne l'adresse de l'element place sous le curseur de la liste L ou NULL
 * si probleme. Cette fonction est equivalente a ListGet(L,CURRENT);
 */
extern void *ListGetCur(List L);


/* Retourne l'adresse d'une copie de l'element place sous le curseur de la
 * liste L ou NULL si probleme. Cette fonction est equivalente a
 * ListGetCopy(L,CURRENT);
 */
extern void *ListGetCurCopy(List L);


/* Suppression de l'element place sous le curseur de la liste L.
 * Le curseur est avance d'une position.
 * Si le curseur est deja en fin de liste ou si un probleme survient, aucune
 * modification n'est effectuee. Cette fonction est equivalente a
 * ListRemove(L,CURRENT);
 */
extern void ListRemoveCur(List L);


/********************
 * FONCTIONS AVANCEES
 */

/* Type des fonctions que l'utilisateur pourra definir.
 * Elles doivent :
 * - retourner un int (ignore pour ListApply)
 * - avoir comme premier parametre un void * qui doit etre l'adresse d'un
 *   element de la liste
 * Elles peuvent avoir d'autres parametres formels ; les parametres effectifs
 * correspondants seront passes comme derniers parametres effectifs de la
 * fonction avancee (ListApply, etc.).
 * Remarque : pour eviter un warning, il est conseille de forcer au type
 * Function la fonction passee en parametre effectif de la fonction avancee.
 * Par exemple :
 * Definition de MaFonction :
 * int MaFonction(void *pElt, va_list Params)
 * {
 *  MonTypeElement *pElement=pElt;
 *  FILE *Fid=var_arg(Params, FILE*);
 *  . . .
 * }
 * . . .
 * List MaListe;
 * FILE *MonParamSupplementaire;
 * . . .
 * ListApply(MaListe, (Function)MaFonction, MonParamSupplementaire);
 * applique la fonction MaFonction a tous les elements de la liste MaListe
 */
typedef int (*Function)(void *pElt, va_list Params);

/* Application d'une fonction a tous les elements d'une liste :
 * applique la fonction passe en deuxieme parametre a tous les elements de la liste L.
 * Les eventuels parametres suivants sont passes a la fonction lors de son application.
 */
extern void ListApply(List L, Function Fct, ...);


/* Retourne l'adresse du premier element de la liste L pour lequel la fonction passee en
 * parametre retourne une valeur non nulle.
 * Retourne NULL si aucun element ne correspond ou en cas de probleme.
 */
extern void *ListFirstThat(List L,  Function Fct, ...);


/* Retourne l'adresse du premier element suivant le curseur pour lequel la
 * fonction passee en parametre retourne une valeur non nulle.
 * Retourne NULL si aucun element ne correspond ou en cas de probleme.
 */
extern void *ListNextThat(List L, Function Fct, ...);


/* Retourne l'adresse du premier element precedent le curseur pour lequel la
 * fonction passee en parametre retourne une valeur non nulle.
 * Retourne NULL si aucun element ne correspond ou en cas de probleme.
 */
extern void *ListPreviousThat(List L, Function Fct, ...);


/* Retourne l'adresse du dernier element de la liste L pour lequel la fonction passee en
 * parametre retourne une valeur non nulle.
 * Retourne NULL si aucun element ne correspond ou en cas de probleme.
 */
extern void *ListLastThat(List L, Function Fct, ...);


/* Retourne une liste composee des elements de la liste L pour lesquels la fonction passee en
 * parametre retourne une valeur non nulle.
 * Retourne NULL en cas de probleme.
 */
extern List ListAllThat(List L, Function Fct, ...);


/* Supprime de la liste L tous les elements pour lesquels la fonction passee en
 * parametre retourne une valeur non nulle.
 * Le curseur est place sur l'element suivant le dernier element efface.
 */
extern void ListRemoveAllThat(List L, Function Fct, ...);


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
extern List ListCreateSorted(size_t EltSize, int (*Fct)(void *pElt1, void *pElt2));


/* Insertion d'un element dans une liste triee.
 * Positionne le nouvel element de telle sorte qu'il se trouve dans la position
 * specifiee (insertion en tete : 0 ; insertion en fin : ListCount(L))
 * L : la liste
 * pElt : adresse de l'element a inserer
 * Une recopie de cet element est effectuee
 * Le curseur n'est pas modifie
 * Retourne l'adresse de la copie de l'element, NULL si probleme.
 */
extern void *ListInsertSorted(List L, void *pElt);


/* Tri d'une liste.
 * Retourne une nouvelle liste triee (par ordre croissant) ou NULL si probleme.
 * Fct : fonction de comparaison qui doit retourner :
 *       <0 si *pElt1 < *pElt2
 *       =0 si *pElt1 = *pElt2
 *       >0 si *pElt1 > *pElt2
 * ListSort n'est pas optimisee, au niveau temps d'execution.
 */
extern List ListSort(List L, int (*Fct)(void *pElt1, void *pElt2));



/*********************************
 * GESTION D'UNE PILE (LIFO)
 */

#define StackCreate(EltSize)   ListCreate(EltSize)
#define StackIsEmpty(S)   ListIsEmpty(S)
#define StackPush(S,pElt)  ListInsert(S,pElt,BEFORE,FIRST)
#define StackGet(S)          ListGet(S,FIRST)
#define StackPop(S)    ListRemove(S,FIRST)
#define StackFree(pS)    ListFree(pS)


/*********************************
 * GESTION D'UNE FILE (FIFO)
 */

#define QueueCreate(EltSize)   ListCreate(EltSize)
#define QueueIsEmpty(Q)   ListIsEmpty(Q)
#define QueuePush(Q,pElt)  ListInsert(Q,pElt,AFTER,LAST)
#define QueueGet(Q)    ListGet(Q,FIRST)
#define QueuePop(Q)    ListRemove(Q,FIRST)
#define QueueFree(pQ)    ListFree(pQ)




#ifdef __cplusplus
}
#endif


#endif /* !__limace_h_ */
