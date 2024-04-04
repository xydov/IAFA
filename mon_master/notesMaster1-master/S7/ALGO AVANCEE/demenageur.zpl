# Résolution d'une instance demenageur lue dans un fichier
param fichier := "u40_00.bpa" ;
#recuperer le parametre capacite
param capacite :=  read fichier as "1n" comment "#" use 1 skip 1;
do print "capacite : " , capacite ;
#recuperer le nombre d'Objet
param nbObjet :=  read fichier as "2n" comment "#" use 1 skip 1;
do print "Le nombre d'objets est : " , nbObjet ;

set Objets := {1 to nbObjet by 1} ;
set Boites := {1 to nbObjet by 1} ;

#l'objet se trouve dans la boite 
var x[Objets*Boites] binary ;

#on utilise la boite 
var y[Boites] binary ;

set tmp [ <i > in Objets ] := { read fichier as " <1n >" skip 1+ i use 1} ;

param taille [ <i > in Objets ] := ord ( tmp [ i ] ,1 ,1);

minimize nbBoite : sum<j> in Boites : y[j] ;
#chaque objet doit être dans exactement une boite 
subto boiteObjet : forall <i> in Objets : sum<j> in Boites : x[i,j] == 1 ;
#une boite est utilisée (yj = 1 > 0) si et seulement si elle contient au moins un objet 
subto utilise : forall <i> in Objets : forall <j> in Boites : x[i,j] <= y[j] ;
#ans chaque boite, la somme des tailles des objets ne doit pas dépasser la capacité
subto c : forall <j> in Boites : sum<i> in Objets : taille[i]*x[i,j] <= capacite ;