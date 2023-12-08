taille dynamique = à déclaré dans le tas le "heap"

else {
	à déclarer dans la pile "stack"
}

### Alloc dynamique a l'exec

* malloc (nbrOctet)
	// int *a = NULL;
	// a = malloc(10 * sizeof(int));
* free(a);
	// Libère la mémoire
* realloc()
	// modifie taille de la mémoire


MAJ entré, minuscule sortie

POINTEUR !! [X]

Calculabilité:

## 16/09/19

problème calculabe s'il existe une fct calculable par machine de turing


* /!\ Recusion Primitive
3+3 successeur de 3+2 etc...

réécriture pour redéfinir l'addition

**il n'existe pas d'algo qui rep par oui ou non si une fct REC est primitve REC**

fonction est dite **Terminale** si l'appel récursif est la dernière instruction de la fonction

permet de transformer un terminale en itératif

## 17/09/19

palindrome à refaire /!\ à l'algo de cours

* knuth

triplet de Hoare:

1. Précondition
2. abstraction du programme
3. Postcondition

contrat: P

si la précondition est satisfaisante alors c(e,s) se termine en satisfiant la postconditionion

# 23/09/2019

pas de il n'existe pas mais non il existe




### Specification du programme

#### Ceci est un contrat /!\

```
/* Précondition */
Action(E, s)  // ajout de &s en C
/* Postcondition */
```

* La précondition exprime a l'aide d'une formule logique, les propriétés que doivent satisfaires les données fournies par l'utilisatieur du programme
* Action(), représente une abstraction de l'algorithme
* la postcondition exprime, à l'aide de formule logique, les propriétés satisfaites par les variables du programme à la fin de l'exécution de celui-ci



