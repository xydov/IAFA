# Une instance de sac a dos simple à 12 objets numérotés de 0 à 11

param capacite := 20;
set Objets := { 0 to 11 by 1 } ;
param poids[Objets] :=
	<0> 11, <1> 7, <2> 5, <3> 5, <4> 4, <5> 3, <6> 3, <7> 2, <8> 2, <9> 2, <10> 2, <11> 1;
param valeurs[Objets] :=
	<0> 20, <1> 10, <2> 25, <3> 11, <4> 5, <5> 50, <6> 15, <7> 12, <8> 6 , <9> 5, <10> 4, <11> 30;
var x[Objets] binary;

maximize valeur : sum<i> in Objets: valeurs[i] * x[i];
subto poids : sum<i> in Objets: poids[i] * x[i] <= capacite;
# subto domain : forall<i> in Objets : 0 <= x[i] <= 1 ;
