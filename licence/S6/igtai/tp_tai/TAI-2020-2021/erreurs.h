#ifndef __erreurs_h_
#define __erreurs_h_


#define DEBUGGING

#ifdef DEBUGGING
#define DEBUG fprintf(stderr,"File %s, line %d\n",__FILE__,__LINE__);
#else
#define DEBUG
#endif

/*
* Fonction a appeler en début de main pour initialiser la gestion des erreurs
 */
extern char *InitMesg(char *argv[]);

/*
* Affichage d'un message formaté sur stderr
 */
extern void Mesg(const char *Msg, ...);

/*
* Affichage de la syntaxe d'appel d'un opérateur sur stderr
 */
extern void Usage(char *Syntaxe);

/*
* Affichage de la description d'un code de retour surn stderr
 */
extern void Code(int ExitStatus, char *Description);


/*
* Affichage d'un message d'erreur sur stderr
 */
extern void Erreur(char *Msg);


#endif /* !__erreurs_h_ */
