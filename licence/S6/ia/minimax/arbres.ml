 
(* ==================================================================================== *)
(* ARBRE DE L'EXEMPLE : DESCRIPTION A COMPLETER --------------------------------------- *)
(* etatInitial de type ‘a : l’état initial                                              *)
(* etatsFils de type 'a -> ('b * 'a) list : fonction qui associe à chaque état la liste *)
(* des doublets (coup possible, état fils obtenu)                                       *)

let etatInitialA1 = "0";;

let etatsFilsA1
(e : 'a)
: ('b * 'a) list =
match e with
	"0" -> [("p","a");("v","b");("q","c")]
	|"a" -> [("u","a1");("r","a2")]
	|"a1" -> [("s","a1a");("q","a1b")]
  |"b" -> [("q","b1");("t","b2");("u","b3")]
  |"c" -> [("x","c1");("r","c2")]
	| _  -> [];;

(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let evaluationA1
(e : 'a)
: int =
match e with
  |"a1a" -> -7
  |"a1b" -> -9
	|"a2" -> -2
	|"b1" -> 2
  |"b2" -> 9
	|"b3" -> -1
	|"c1" -> -7
  |"c2" -> -9
	| _  -> failwith "Erreur : evaluation : etat non terminal";;

(* ------------------------------------------------------------------------------------ *)
(* RESULTATS ATTENDUS pour ce premier arbre - APRÈS L'AVOIR COMPLÉTÉ                    *)
(* "minimax" renvoie le minimax de l'arbre                                              *)
(* "recherche" renvoie le minimax en fixant une profondeur max à l'arbre (ici 3)        *)
(* "meilleurCoup" renvoie le couple (minimax, meilleurCoup) de l'arbre                  *)
minimax etatInitialA1 0  etatsFilsA1 evaluationA1;;
(* - : int = -1                                                                         *)
recherche 3 etatInitialA1 0  etatsFilsA1 evaluationA1;;
(* - : int = -1                                                                         *)
meilleurCoup 3 etatInitialA1 0  etatsFilsA1 evaluationA1;;
(* - : int * string = (-1, "v")                                                         *)
(* ==================================================================================== *)



(* ==================================================================================== *)
(* Un autre arbre                                                                       *)
(* etatInitial de type ‘a : l’état initial                                              *)
(* etatsFils de type 'a -> ('b * 'a) list : fonction qui associe à chaque état la liste *)
(* des doublets (coup possible, état fils obtenu)                                       *)

let etatInitialA2 = "0";;

let etatsFilsA2
(e : 'a)
: ('b * 'a) list =
match e with
	"0"    -> [("p","a");("v","b");("q","c");("r","d")]
	|"a"  -> [("u","a1");("r","a2");("t","a3")]
	|"b"  -> [("q","b1");("u","b2")]
	|"d"  -> [("x","d1");("y","d2");("g","d3")]
	|"a2" -> [("s","a2a");("q","a2b")]
	|"d3" -> [("u","d3a");("s","d3b");("j","d3c")]
	| _   -> [];;

(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let evaluationA2
(e : 'a)
: int =
match e with
	|"a1" -> -1
	|"a2a"  -> 4
	|"a2b"  -> 8
	|"a3" -> -2
	|"b1"  -> 7
	|"b2"  -> -4
	|"c"  -> 0
	|"d1"  -> 12
	|"d2"  -> 4
	|"d3a"  -> 8
	|"d3b"  -> -7
	|"d3c"  -> 2
	| _    -> failwith "Erreur : evaluation : etat non terminal";;

(* ------------------------------------------------------------------------------------ *)
(* RESULTATS ATTENDUS pour cet arbre                                                    *)
(* "minimax" renvoie le minimax de l'arbre                                              *)
(* "recherche" renvoie le minimax en fixant une profondeur max à l'arbre (ici 3)        *)
(* "meilleurCoup" renvoie le couple (minimax, meilleurCoup) de l'arbre                  *)
minimax etatInitialA2 0  etatsFilsA2 evaluationA2;;
(* - : int = 4                                                                          *)
recherche 3 etatInitialA2 0  etatsFilsA2 evaluationA2;;
(* - : int = 4                                                                          *)
meilleurCoup 3 etatInitialA2 0  etatsFilsA2 evaluationA2;;
(* - : int * string = (4, "r")                                                          *)
(* ==================================================================================== *)



(* ==================================================================================== *)
(* Un autre arbre : profondeur 5 à tester avec Minimax en imposant une profondeur max   *)
(* ayant les valeurs successives 1, 2, 3, 4                                             *)
(* etatInitial de type ‘a : l’état initial                                              *)
(* etatsFils de type 'a -> ('b * 'a) list : fonction qui associe à chaque état la liste *)
(* des doublets (coup possible, état fils obtenu)                                       *)
(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let etatInitialA3 = "a";;

let etatsFilsA3
(e : string) =
match e with
	"a"    -> [("v","a1");("b","a2");("c","a3");("d","a4");("e","a5")]
	|"a1"  -> [("b","a1a");("c","a1b")]
	|"a2"  -> [("d","a2a");("b","a2b");("f","a2c");("v","a2d")]
	|"a3"  -> [("g","a3a");("c","a3b")]
	|"a4"  -> []
	|"a5"  -> [("f","a5a");("g","a5b");("b","a5c")]
	|"a1a" -> [("g","a1a1");("c","a1a2");("f","a1a3")]
	|"a1b" -> []
	|"a2a" -> []
	|"a2b" -> [("h","a2b1");("i","a2b2")]
	|"a2c" -> []
	|"a2d" -> []
	|"a3a" -> []
	|"a3b" -> [("m","a3b1");("n","a3b2");("j","a3b3")]
	|"a5a" -> []
	|"a5b" -> []
	|"a5c" -> []
	|"a1a1" -> []
	|"a1a2" -> []
	|"a1a3" -> []
	|"a2b1" -> []
	|"a2b2" -> [("k","a2b2a");("v","a2b2b")]
	|"a3b1" -> []
	|"a3b2" -> []
	|"a3b3" -> []
	|"a2b2a" -> []
	|"a2b2b" -> [("l","a2b2b1")]
	|"a2b2b1" -> []
	| _    -> failwith "Erreur : etatsFils : etat inconnu";;

(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let evaluationA3
(e : string) =
match e with
	"a"    -> 5
	|"a1"  -> 6
	|"a2"  -> -2
	|"a3"  -> -4
	|"a4"  -> 2
	|"a5"  -> -12
	|"a1a" -> 0
	|"a1b" -> 18
	|"a2a" -> 5
	|"a2b" -> -1
	|"a2c" -> -4
	|"a2d" -> 9
	|"a3a" -> 12
	|"a3b" -> -11
	|"a5a" -> 15
	|"a5b" -> -7
	|"a5c" -> -3
	|"a1a1" -> 0
	|"a1a2" -> -4
	|"a1a3" -> -3
	|"a2b1" -> 7
	|"a2b2" -> 19
	|"a3b1" -> -15
	|"a3b2" -> 4
	|"a3b3" -> 1
	|"a2b2a" -> -8
	|"a2b2b" -> 9
	|"a2b2b1" -> -19
	| _     -> failwith "Erreur : evaluation : etat inconnu";;

(* ------------------------------------------------------------------------------------ *)
(* RESULTATS ATTENDUS pour cet arbre                                                    *)
(* "minimax" renvoie le minimax de l'arbre                                              *)
(* "recherche" renvoie le minimax en fixant une profondeur max à l'arbre (ici 3)        *)
(* "meilleurCoup" renvoie le couple (minimax, meilleurCoup) de l'arbre                  *)

minimax etatInitialA3 0  etatsFilsA3 evaluationA3;;
(* - : int = 4                                                                          *)

recherche 0 etatInitialA3 0  etatsFilsA3 evaluationA3;;
(* - : int = 5                                                                          *)
recherche 1 etatInitialA3 0  etatsFilsA3 evaluationA3;;
(* - : int = 6                                                                          *)
recherche 2 etatInitialA3 0  etatsFilsA3 evaluationA3;;
(* - : int = 2                                                                          *)
recherche 3 etatInitialA3 0  etatsFilsA3 evaluationA3;;
(* - : int = 4                                                                          *)
recherche 4 etatInitialA3 0  etatsFilsA3 evaluationA3;;
(* - : int = 4                                                                          *)

meilleurCoup 3 etatInitialA3 0  etatsFilsA3 evaluationA3;;
(* - : int * string = (4, "c")                                                          *)
(* ==================================================================================== *)



(* ==================================================================================== *)
(* Un autre arbre : profondeur 5 à tester avec Minimax en imposant une profondeur max   *)
(* ayant les valeurs successives 1, 2, 3, 4                                             *)
(* etatInitial de type ‘a : l’état initial                                              *)
(* etatsFils de type 'a -> ('b * 'a) list : fonction qui associe à chaque état la liste *)
(* des doublets (coup possible, état fils obtenu)                                       *)
(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let etatInitialA5 = "a";;

let etatsFilsA5
(e : string) =
match e with
	"a"    -> [("b","a1");("d","a2");("i","a3");("d","a4");("z","a5")]
	|"a1"  -> [("z","a1a");("m","a1b")]
	|"a2"  -> [("g","a2a");("c","a2b");("z","a2c");("f","a2d")]
	|"a3"  -> []
	|"a4"  -> [("l","a4a");("n","a4b")]
	|"a5"  -> [("z","a5a");("b","a5b");("g","a5c");("h","a5d")]
	|"a1a" -> [("h","a1a1");("i","a1a2");("k","a1a3")]
	|"a1b" -> []
	|"a2a" -> []
	|"a2b" -> [("i","a2b1");("b","a2b2")]
	|"a2c" -> []
	|"a2d" -> []
	|"a4a" -> []
	|"a4b" -> [("n","a4b1");("m","a4b2");("e","a4b3")]
	|"a5a" -> []
	|"a5b" -> []
	|"a5c" -> []
	|"a5d" -> [("e","a5d1");("g","a5d2");("f","a5d3")]
	|"a1a1" -> []
	|"a1a2" -> []
	|"a1a3" -> []
	|"a2b1" -> []
	|"a2b2" -> [("o","a2b2a");("p","a2b2b")]
	|"a4b1" -> []
	|"a4b2" -> []
	|"a4b3" -> []
	|"a5d1" -> []
	|"a5d2" -> []
	|"a5d3" -> []
	|"a2b2a" -> [("e","a2b2a1");("q","a2b2a2")]
	|"a2b2b" -> []
	|"a2b2a1" -> []
	|"a2b2a2" -> []
	| _    -> failwith "Erreur : etatsFils : etat inconnu";;

(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let evaluationA5
(e : string) =
match e with
	"a"    -> -8
	|"a1"  -> 14
	|"a2"  -> 0
	|"a3"  -> -13
	|"a4"  -> 1
	|"a5"  -> -12
	|"a1a" -> 2
	|"a1b" -> 13
	|"a2a" -> -19
	|"a2b" -> -6
	|"a2c" -> 0
	|"a2d" -> 17
	|"a4a" -> -15
	|"a4b" -> -12
	|"a5a" -> -3
	|"a5b" -> 16
	|"a5c" -> -9
	|"a5d" -> 6
	|"a1a1" -> 0
	|"a1a2" -> 19
	|"a1a3" -> 18
	|"a2b1" -> -11
	|"a2b2" -> -8
	|"a4b1" -> -3
	|"a4b2" -> 16
	|"a4b3" -> -4
	|"a5d1" -> -14
	|"a5d2" -> -7
	|"a5d3" -> 16
	|"a2b2a" -> -20
	|"a2b2b" -> 9
	|"a2b2a1" -> 7
	|"a2b2a2" -> -16
	| _     -> failwith "Erreur : evaluation : etat inconnu";;

(* ------------------------------------------------------------------------------------ *)
(* RESULTATS ATTENDUS pour cet arbre                                                    *)
(* "minimax" renvoie le minimax de l'arbre                                              *)
(* "recherche" renvoie le minimax en fixant une profondeur max à l'arbre (ici 3)        *)
(* "meilleurCoup" renvoie le couple (minimax, meilleurCoup) de l'arbre                  *)

minimax etatInitialA5 0  etatsFilsA5 evaluationA5;;
(* - : int = 13                                                                         *)

recherche 0 etatInitialA5 0  etatsFilsA5 evaluationA5;;
(* - : int = -8                                                                         *)
recherche 1 etatInitialA5 0  etatsFilsA5 evaluationA5;;
(* - : int = 14                                                                         *)
recherche 2 etatInitialA5 0  etatsFilsA5 evaluationA5;;
(* - : int = 2                                                                          *)
recherche 3 etatInitialA5 0  etatsFilsA5 evaluationA5;;
(* - : int = 13                                                                         *)
recherche 4 etatInitialA5 0  etatsFilsA5 evaluationA5;;
(* - : int = 13                                                                         *)

meilleurCoup 3 etatInitialA5 0  etatsFilsA5 evaluationA5;;
(* - : int * string = (13, "b")                                                         *)
(* ==================================================================================== *)


