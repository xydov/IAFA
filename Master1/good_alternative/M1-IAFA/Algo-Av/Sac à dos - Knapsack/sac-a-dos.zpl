# Résolution d'une instance de sac a dos lue dans un fichier
# Suppose que les commentaires commencent par #, que la capacité est sur la première ligne non commentée, et que les autres lignes décrivent les objets : 1 par ligne, d'abord une id puis le poids puis la valeur

param fichier := "../../benchmarks/sac-a-dos/sac-a-dos-100.txt" ;

param capacite :=  read fichier as "1n" comment "#" use 1 ;
do print "capacite : " , capacite ;
set Objets := { read fichier as "<1s>" comment "#" skip 1 } ;
do print "nb objets : " , card(Objets) ;
param poids[Objets] := read fichier as "<1s> 2n" comment "#" skip 1 ;
param valeurs[Objets] := read fichier as "<1s> 3n" comment "#" skip 1 ;
do forall <i> in Objets: print "objet " , i, " : poids = ", poids[i] , " valeurs = " , valeurs[i] ;
var x[Objets] binary;

maximize valeur : sum<i> in Objets: valeurs[i] * x[i];
subto poids : sum<i> in Objets: poids[i] * x[i] <= capacite;
