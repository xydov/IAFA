
param fichier := "./archive_13/bin-packing-difficile-hard.bpa" ;

param capacite := read fichier as "1n" comment "#" use 1 skip 1;
param No := read fichier as "2n" comment "#" use 1 skip 1;
do print "nbElements : " , No ;

set Objets := {0..(No-1)};
set Boites := {0..(No-1)};

set tmp[<i> in Objets] := {read fichier as "<1n>" skip 2+i use 1};
param poids[<i> in Objets] := ord(tmp[i],1,1) ;
do print "nbElements : " , poids[0] ;


var x[Objets * Boites] binary;
var y[Boites] binary;

minimize valeur : sum<i> in Boites: y[i];
subto poids : forall<j> in Boites: (sum<i> in Objets:  poids[i] * x[i,j]) <= capacite;
subto boite : forall<i> in Objets: (sum<j> in Boites: x[i,j]) == 1;
subto coher_y_x : forall<i> in Objets: forall<j> in Boites: x[i,j] <= y[j];
