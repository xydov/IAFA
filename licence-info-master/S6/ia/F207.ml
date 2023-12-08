(* Ce fichier contient des graphes sur lesquels tester un *)
(* algorithme de recherche dans un graphe d etat *)

let initGA = "U" ;;
let opPossGA = ( function
	"V" -> [ 'l',140,"X" ; 'x',80,"Y" ]
|	"B" -> [ 'w',20,"Z" ]
|	"U" -> [ 'g',20,"W" ; 'x',80,"V" ; 'l',300,"D" ]
|	"W" -> [ 'g',20,"Z" ; 'h',60,"X" ; 'l',120,"B" ]
|	"Y" -> [ 'l',80,"C" ; 'h',60,"D" ]
|	"Z" -> [ 'x',60,"A" ; 'z',20,"B" ]
|	"X" -> [ 'x',120,"C" ]
|	 _ -> [] );;
let hEtatGA = ( function
	"V" -> 60
|	"B" -> 100
|	"A" -> 20
|	"U" -> 140
|	"W" -> 100
|	"Y" -> 60
|	"Z" -> 40
|	"X" -> 80
|	 _ -> 0 );;
let estButGA = ( function "C" | "D" -> true | _ -> false ) ;;


let initGB = "U" ;;
let opPossGB = ( function
	"V" -> [ 'h',120,"X" ; 'x',400,"Z" ]
|	"A" -> [ 'x',40,"B" ]
|	"U" -> [ 'g',140,"V" ; 'l',80,"W" ]
|	"W" -> [ 'h',100,"Y" ; 'l',60,"X" ]
|	"Y" -> [ 'h',240,"A" ; 'l',220,"Z" ; 'g',280,"B" ]
|	"Z" -> [ 'g',200,"A" ; 'l',160,"B" ]
|	"X" -> [ 'h',300,"Z" ]
|	 _ -> [] );;
let hEtatGB = ( function
	"V" -> 360
|	"U" -> 380
|	"A" -> 60
|	"Y" -> 200
|	"W" -> 240
|	"X" -> 160
|	 _ -> 0 );;
let estButGB = ( function "Z"|"A" | "B" -> true | _ -> false ) ;;


let initGC = "U" ;;
let opPossGC = ( function
	"V" -> [ 'l',140,"X" ; 'x',80,"Y" ]
|	"B" -> []
|	"U" -> [ 'g',20,"W" ; 'x',80,"V" ; 'l',300,"D" ]
|	"W" -> [ 'g',20,"Z" ; 'h',60,"X" ; 'l',120,"B" ]
|	"Y" -> [ 'l',80,"C" ; 'h',60,"D" ]
|	"Z" -> [ 'x',60,"A" ; 'z',20,"B" ]
|	"X" -> [ 'x',120,"C" ]
|	 _ -> [] );;
let hEtatGC = ( function
	"V" -> 60
|	"B" -> 60
|	"A" -> 40
|	"U" -> 140
|	"W" -> 100
|	"Y" -> 60
|	"Z" -> 40
|	"X" -> 80
|	 _ -> 0 );;
let estButGC = ( function  _ -> false ) ;;

