param fichier := "archive_1/shift-scheduling.zplread" ;
do print fichier ;


####################
# Horizon = nb days

param horizon := read fichier as "2n" comment "#" match "^h";
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
	read fichier as "<2sfichier,3s> 4n" comment "#"  match "c" default 0 ;


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
# do print "Pref Shifts On" ;le nombre de personnes requises pour chaque service
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
# le nombre depersonnes affectées à ce service.
var z[Days*Services] integer >= 0;
var y[Days*Services] integer >= 0;
var workingSched[Personnes*Days] binary;

#1 - 2
subto ecart : forall<s,d> in Services*Days: (sum<p> in Personnes: assigned[p,d,s]) - y[d,s] + z[d,s] == requirement[d,s];
# exo2
subto c21: forall <p,d> in Personnes*Days : (sum <s> in Services : assigned[p,d,s]) <= 1;
subto c22: forall <p ,d ,s > in Personnes*Days*Services : assigned[p,d,s] <= 1-dayOff[p,d];
subto c23: forall <p,s> in Personnes*Services : (sum <d> in Days : assigned[p,d,s]) <= MaxShift[p,s];
subto c241: forall <p> in Personnes : MinTotalMinutes[p] <= (sum <d,s> in Days*Services : duree[s] * assigned[p,d,s]);
subto c242: forall <p> in Personnes : (sum <d,s> in Days*Services : duree[s] * assigned[p,d,s]) <= MaxTotalMinutes[p];

# exo3
subto c31: forall <p,d> in Personnes*Days with d+MaxConsecutiveShifts[p] < horizon : sum <s,j> in Services * {0..MaxConsecutiveShifts[p]} with d+j < horizon : assigned[p,d+j,s] <= MaxConsecutiveShifts[p];
subto c32: forall <p,d,s1,s2> in Personnes*Days*Services*Services with d < horizon-1 : ForbiddenSeq[s1,s2] * (assigned[p,d,s1] + assigned[p,d+1,s2]) <= 1;
#4
subto worksched: forall<p,d> in Personnes*Days: (sum<s> in Services: assigned[p,d,s]) == workingSched[p,d];

#subto minconsdayoff : forall <k> in Personnes: forall<j> in Days with (2 <= MinConsecutiveDaysOff[k]) and (j+MinConsecutiveDaysOff[k]-1 < horizon) : forall <l> in {2..MinConsecutiveDaysOff[k]} with j+l < horizon : vif workingSched[k,j+1] == 0 and workingSched[k,j] == 1 then workingSched[k,j+l] == 0 end ;

#subto minconsshifts : forall<k> in Personnes: forall<j> in {1 to horizon-MinConsecutiveShifts[k]-1} with (2 <= MinConsecutiveShifts[k]): vif workingSched[k,j-1] == 0 and workingSched[k,j] == 1 then sum<d> in {1 to MinConsecutiveShifts[k]-1}: (workingSched[k,j+d]) >= MinConsecutiveShifts[k]-1 end ;

subto minconsshifts: forall <p> in Personnes: 
                        forall <k> in {2..MinConsecutiveShifts[p]}: 
                            forall<j> in{0..(horizon-k-1)}:
                                workingSched[p,j] + workingSched[p,j+k] >= sum<n> in {(j+1)..(j+k-1)}: (workingSched[p,n]) - (k-2);

subto minconsdayoff: forall <p> in Personnes: 
                        forall <k> in {2..MinConsecutiveDaysOff[p]}: 
                            forall<j> in{0..(horizon-k-1)}:
                                (workingSched[p,j] + workingSched[p,j+k] - 1) <= (sum<n> in {(j+1)..(j+k-1)}: workingSched[p,n]);

minimize obj_exo5: (sum <d,s> in Days*Services : (belowCoverPen[d,s] * z[d,s] + aboveCoverPen[d,s] * y[d,s]) ) + ( sum <p,d,s> in Personnes*Days*Services : (prefOff[p,d,s] * assigned[p,d,s] + prefOn[p,d,s] * (1-assigned[p,d,s])) );
#minimize cost : sum<d> in Days: (sum<s> in Services: (z[d,s] + y[d,s]));