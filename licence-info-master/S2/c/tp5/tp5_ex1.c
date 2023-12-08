#include <stdio.h>

#define MAX 10 //80

/* Lecture d'une ligne de texte tapee au clavier
 * ch : adresse du premier caractere de la chaine
 * NbCarMax : nombre maximal de caracteres lus (pour eviter les 
 *   debordements en memoire)
 * Valeur de retour : nombre de caracteres lus
 */
int Lecture(char *ch, int NbCarMax)
{
    int i = 0; // on veut tester le 1er elem scannee
    scanf("%c", &ch[0]); // on scanne le premier element

    while((i < NbCarMax) && (ch[i] != '\n'))
    {
        i ++;
        scanf("%c", &ch[i]);
    }
    ch[i] = '\0';
    
    return i; //int    
}



/* Longueur d'une chaine de caracteres
 * ch : adresse du premier caractere de la chaine
 * Valeur de retour : nombre de caracteres de la chaine
 */
int Longueur(char *ch)
{
    int nbCar = 0;
    while((nbCar < MAX)&&(ch[nbCar] != '\0')){
        nbCar ++;
    }
    return nbCar;
}


/* Copie d'une chaine dans une autre
 * Destination : adresse du premiere caractere de la chaine destination
 * Source : adresse du premiere caractere de la chaine source
 */
void Copie(char *Destination, char *Source)
{
    int tailleSource = Longueur(Source);
    int i;
    for(i = 0; i < tailleSource; i++)
    {
        Destination[i] = Source[i];
    }
    Destination[i] = '\0';
}



/* Comparaison de deux chaines de caracteres
 * ch1 : adresse du premiere caractere de la premiere chaine
 * ch2 : adresse du premiere caractere de la seconde chaine
 * Valeur de retour : 1 si les chaines contiennent des caracteres differents,
 * 0 sinon
 */
int Differentes(char *ch1, char *ch2)
{
    int lgCh1 = Longueur(ch1);

    if (lgCh1 != Longueur(ch2))
    {
        return 1;
    } else
    {
        for(int i= 0; i < lgCh1; i++)
        {
            if (ch1[i] != ch2[i])
            {
                return 1;
            }
        }
        return 0;        
    }
}


/* Ajout (concatenation) d'une chaine de caractere a la fin d'une autre chaine
 * Destination : adresse du premiere caractere de la chaine destination
 * Source : adresse du premiere caractere de la chaine a ajouter
 */
void Ajout(char *Destination, char *Source)
{
  int longDestination = Longueur(Destination);
  int j = 0;
  for(int i = longDestination; i < longDestination + Longueur(Source); i++)
  { 
    Destination[i] = Source[j];
    j ++;
  }
}



/* Fonction principale */
int main(void)
{
  char ch1[MAX+1],ch2[2*MAX+1],ch3[MAX+1]="o";
  int n;
  
  printf("Test de Lecture\n---------------\n");
  printf("Tapez une chaine d'au plus %d caracteres : ",MAX);
  n = Lecture(ch1,MAX);
  printf("La chaine \"%s\" a ete lue ; elle contient %d caracteres.\n",ch1,n);

  printf("\nTest de Longueur\n----------------\n");
  printf("La chaine \"%s\" contient %d caracteres.\n",ch1,Longueur(ch1));

  printf("\nTest de copie\n-------------\n");
  Copie(ch2,ch1);
  printf("ch1=\"%s\", ch2=\"%s\"\n",ch1,ch2);

  printf("\nTest de Differentes\n-------------------\n");
  while (Differentes(ch3,"n"))
  {
    printf("Tapez une premiere chaine : ");
    Lecture(ch1,MAX);
    printf("Tapez une seconde chaine : ");
    Lecture(ch2,MAX);
    if (Differentes(ch1,ch2))
      printf("%s et %s ne contiennent pas les mêmes caracteres.\n",ch1,ch2);
    else
      printf("%s et %s contiennent les memes caracteres.\n",ch1,ch2);
    printf("Voulez-vous continuer le test de Differentes "
           "(tapez n pour arreter) : ");
    Lecture(ch3,1);
  }

  printf("\nTest de Ajout\n-------------\n");
  Copie(ch3,"o");
  while (Differentes(ch3,"n"))
  {
    printf("Tapez une premiere chaine : ");
    Lecture(ch1,MAX);
    printf("Tapez une seconde chaine : ");
    Lecture(ch2,MAX);
    printf("Ajout de la premiere chaine a la seconde :\n");
    Ajout(ch2,ch1);
    printf("ch1=\"%s\", ch2=\"%s\"\n",ch1,ch2);
    printf("Voulez-vous continuer le test de Ajout (tapez n pour arreter) : ");
    Lecture(ch3,1);
  }

  return 0;
}


