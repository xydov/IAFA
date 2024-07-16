param fichier := "u120_00.bpa" ;


param capacite := read fichier as "1n" comment "#" use 1 skip 1;
param No := read fichier as "2n" comment "#" use 1 skip 1;
set Objets := { 1 to No by 1 } ;
set Boites := { 1 to No by 1 } ;
set tmp [<i> in Objets]:= {read fichier as "<1n>" skip 1+i use 1};
param taille [<i> in Objets] := ord(tmp[i],1,1);

var x[Objets*Boites] binary;
var y[Boites] binary;

minimize valeur : sum<j> in Boites:y[j];
subto c : forall<i> in Boites: forall<j> in Objets: x[i,j] >= 0;
subto cap : forall<j> in Boites : sum<i> in Objets : taille[i] * x[i,j]<= capacite;
subto utb: forall<j> in Boites : forall<i> in Objets : y[j]>= x[i,j] ;
subto ob : forall<i> in Objets : sum<j> in Boites : x[i,j]== 1;


