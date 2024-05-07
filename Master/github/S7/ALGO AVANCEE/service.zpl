param fichier := "shift-scheduling-5.zplread" ;
do print fichier ;


####################
# Horizon = nb days

param horizon := read fichier as "2n" comment "#" match "^h" ;
do print "horizon : ", horizon, " jours" ;


############################################
# Sets of days, week-ends, services, staff :

set Days := {0..horizon-1} ;
# All instances start on a Monday
# planning horizon is always a whole number of weeks (h mod 7 = 0)
set WeekEnds := {1..horizon/7} ;
do print card(WeekEnds), " week-ends :" ;
do print WeekEnds ;

set Services := { read fichier as "<2s>" comment "#" match "^d" } ;
do print card(Services), " services" ;

set Personnes := { read fichier as "<2s>" comment "#" match "^s" } ;
do print card(Personnes) , " personnels" ;


############
# Parameters

param duree[Services] := read fichier as "<2s> 3n" comment "#" match "^d";
# do forall <t> in Services  do print "durée ", t, " : ", duree[t] ;

param ForbiddenSeq[Services*Services] :=
	read fichier as "<2s,3s> 4n" comment "#"  match "c" default 0 ;


param MaxTotalMinutes[Personnes] :=
  read fichier as "<2s> 3n" comment "#" match "^s"  ;
param MinTotalMinutes[Personnes] :=
  read fichier as "<2s> 4n" comment "#" match "^s"  ;
param MaxConsecutiveShifts[Personnes] :=
  read fichier as "<2s> 5n" comment "#" match "^s"  ;
param MinConsecutiveShifts[Personnes] :=
  read fichier as "<2s> 6n" comment "#" match "^s"  ;
param MinConsecutiveDaysOff[Personnes] :=
  read fichier as "<2s> 7n" comment "#" match "^s"  ;
param MaxWeekends[Personnes] :=
  read fichier as "<2s> 8n" comment "#" match "^s"  ;

param MaxShift[Personnes*Services] :=
  read fichier as "<2s,3s> 4n" comment "#" match "^m" default 0 ;

param requirement[Days*Services] :=
  read fichier as "<2n,3s> 4n" comment "#" match "^r" ;

param belowCoverPen[Days*Services] :=
  read fichier as "<2n,3s> 5n" comment "#" match "^r" ;

param aboveCoverPen[Days*Services] :=
  read fichier as "<2n,3s> 6n" comment "#" match "^r" ;

param dayOff[Personnes*Days] :=
  read fichier as "<2s,3n> 4n" comment "#" match "^f" default 0 ;

# penalité si jour "pas off" = "on"
param prefOff[Personnes*Days*Services] :=
  read fichier as "<2s,3n,4s> 5n" comment "#" match "^n" default 0 ;

# penalité si jour "pas on" = "off"
param prefOn[Personnes*Days*Services] :=
  read fichier as "<2s,3n,4s> 5n" comment "#" match "^y" default 0 ;

# do print "Services" ;
# do forall <s> in Services do print s, duree[s] ;
# do forall <s1,s2> in Services*Services with ForbiddenSeq[s1,s2] == 1
#   do print s1, s2, ForbiddenSeq[s1,s2] ;
# do print "Staff" ;
# do forall <p> in Personnes
#   do print p, MaxTotalMinutes[p], MinTotalMinutes[p],
#     MaxConsecutiveShifts[p], MinConsecutiveShifts[p],
#     MinConsecutiveDaysOff[p], MaxWeekends[p] ;
# do print "Days Off" ;
# do forall<p,d> in Personnes * Days with dayOff[p,d] == 1 do print p,d,dayOff[p,d] ;
# do print "Pref Shifts On" ;
# do forall<p,d,s> in Personnes * Days * Services
#   with prefOn[p,d,s] >= 1 do print p,d,s,prefOn[p,d,s] ;
# do print "Pref Shifts Off" ;
# do forall<p,d,s> in Personnes * Days * Services
#   with prefOff[p,d,s] >= 1 do print p,d,s,prefOff[p,d,s] ;
# do print "Cover" ;
# do forall<d,s> in Days * Services
#   do print d,s,requirement[d,s], belowCoverPen[d,s], aboveCoverPen[d,s] ;



###########
# Variables
var assigned[Personnes*Days*Services] binary ;
var work[Personnes*Days] binary ;

# Question 1.1.
#7-y+z=5 => y=2+z => y-z=2
#2-y+z=5 => y=-3+z => y-z=-3
#y+1 est exactement l'ecart entre x et n.

#Question 1.2.
#min somme(jours) somme(services) (nbpersonneRequise - affectees)
#min somme(jours) somme(service) y+z
#sous la contrainte
#somme(personnes) assigned(p,d,s)-y+z = requirements(d,s) pour tout jour et pour tout services

var y[Days*Services] integer >= 0;
var z[Days*Services] integer >= 0;

minimize planif : sum<d> in Days : sum<s> in Services: (y[d,s] + z[d,s]);

subto contrainte: forall<d,s> in Days*Services: (sum<p> in Personnes: assigned[p,d,s])-y[d,s]+z[d,s] == requirement[d,s];

#Question 2.1.
subto servjour: forall<p,d> in Personnes*Days: (sum<s> in Services : assigned[p,d,s]) <= 1;
#Question 2.2
subto jour_off : forall<p,d> in Personnes*Days : sum<s> in Services: assigned[p,d,s] + dayOff[p,d] <= 1;
#Question 2.3
subto maxServicePeriode : forall<p,s> in Personnes*Services: sum<d> in Days: assigned[p,d,s] <= MaxShift[p,s] ;
#Question 2.4
subto dureeMinTotaleService : forall<p> in Personnes: MinTotalMinutes[p] <= sum<d,s> in Days*Services: duree[s]*assigned[p,d,s] ;
subto dureeMaxTotaleService : forall<p> in Personnes: MaxTotalMinutes[p] >= sum<d,s> in Days*Services: duree[s]*assigned[p,d,s] ;
#Question 3.1
subto jourServiceConsecutifs : forall<p,d> in Personnes*Days with d <= horizon-1-MaxConsecutiveShifts[p]: MaxConsecutiveShifts[p] >= sum<i> in {d..d+MaxConsecutiveShifts[p]}: work[p,i];
#Question 3.2
subto serviceInterdit : forall<p,s1,s2> in Personnes*Services*Services with ForbiddenSeq[s1,s2] == 1 : forall<d> in Days with d < horizon-2 : assigned[p,d,s1] + assigned[p,d+1,s2] <= 2;
#Question 4.1.1
subto joursMinConsOff: forall<p> in Personnes: forall<d> in Days with d <= horizon-MinConsecutiveDaysOff[p] and d > 0: vif work[p, d-1] == 1 and work[p, d] == 0 then (sum<i> in {d..(d+MinConsecutiveDaysOff[p]-1)}: work[p, i]) == 0 end;
#Question 4.1.2
subto jourMinConsOn : forall<p> in Personnes:forall<d> in Days with d <= horizon-MinConsecutiveDaysOff[p] and d>0: vif work[p, d-1] == 0 and work[p,d] == 1then sum<i> in {d..(d+MinConsecutiveShifts[p]-1)}: work[p,i] >= MinConsecutiveShifts[p] end;
