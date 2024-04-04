#Spécifier le nom du fichier à partir duquel les paramètres sont lus.
param fichier := "u40_00.bpa" ;
#Lire la capacité à partir du fichier en ignorant la première ligne et en utilisant la première valeur numérique sur la deuxième ligne. Les commentaires commençant par "#" sont ignorés.
param capacite := read fichier as "1n" comment "#" use 1 skip 1;
#Lire le nombre d'éléments (No) à partir du fichier en ignorant la première ligne et en utilisant la première valeur numérique sur la deuxième ligne
param No := read fichier as "2n" comment "#" use 1 skip 1;
do print "nbElements : " , No ;

#Créer un ensemble d'objets allant de 0 à No-1.
set Objets := {0..(No-1)};
#Créer un ensemble de boites allant de 0 à No-1.
set Boites := {0..(No-1)};


#Lire les valeurs du fichier pour chaque objet, en commençant à partir de la 3e ligne. Les valeurs sont stockées dans l'ensemble tmp.
set tmp[<i> in Objets] := {read fichier as "<1n>" skip 2+i use 1};
# Définire le paramètre poids en utilisant la première colonne des valeurs stockées dans tmp pour chaque objet.
param poids[<i> in Objets] := ord(tmp[i],1,1) ;
do print "nbElements : " , poids[0] ;

#l'objet se trouve dans la boite 
var x[Objets * Boites] binary;

#on utilise la boite 
var y[Boites] binary;

#objectif

minimize valeur : sum<i> in Boites: y[i];

#contraintes 

#la somme des tailles des objets ne doit pas dépasser la capacité des boites
subto poids : forall<j> in Boites: (sum<i> in Objets:  poids[i] * x[i,j]) <= capacite;
#chaque objet doit être dans exactement une boit
subto boite : forall<i> in Objets: (sum<j> in Boites: x[i,j]) == 1;
#verifier la coherence , une boite est utilisée ssi elle contient au moins un objet 
subto coher_y_x : forall<i> in Objets: forall<j> in Boites: x[i,j] <= y[j];


#symetrie : 
#on peut ajouter une contrainte pour assurer que la boite i est utilisé que lorsque la boite i-1 est utilisé. (symetrie non traité , trop d'erreurs)
#subto sym : forall <i> in Boites: y[i+1]<=y[i];  



#résultats  : 
#ce programme est testé sur l'ensemble des fichiers de tests fournis 
# U20 : Solving Time (sec) : 0.04  , objective value: 9
# U40 : Solving Time (sec) : 32.31 , objective value: 17
# U60 : / 		   
# U120: / 
# inst60-non-unif_9.bpa: Solving Time (sec) : 1.33 , objective value: 14












