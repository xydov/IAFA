(* #use "arbres.ml" *)

(* ========================== *)
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

(* =========================== *)

let lst_apply f l = match l with
  | [] -> failwith "[lst_apply] > Empty list not allowed"
  | hd :: tl -> List.fold_left f hd tl


let minimax etatInitial profondeur etatsFils evaluation = 
  let rec aux p e = 
    let fils = (etatsFils e) in
    match fils with
      | [] -> (evaluation e)
      | (_, noeud) :: tl -> 
        if p mod 2 = 0
        then List.fold_left (fun b (_, n) -> max b (aux (p + 1) n)) (aux (p + 1) noeud) tl
        else List.fold_left (fun b (_, n) -> min b (aux (p + 1) n)) (aux (p + 1) noeud) tl
  in aux 0 etatInitial

let recherche profondeurMax etatInitial profondeur etatsFils evaluation = 
		let rec aux p e pm = 
			if pm = 0 then evaluation e else (* /!\ Fixed here *)
			let fils = (etatsFils e) in
			match fils with
				| [] -> (evaluation e)
				| (_, noeud) :: tl -> (* /!\ je dois m'arreter au père et non taper sur les fils, ici je descend-AIS 1 fois de trop *)
						if p mod 2 = 0
						then List.fold_left (fun b (_, n) -> max b (aux (p + 1) n (pm - 1))) (aux (p + 1) noeud (pm - 1)) tl
						else List.fold_left (fun b (_, n) -> min b (aux (p + 1) n (pm - 1))) (aux (p + 1) noeud (pm - 1)) tl
		in aux 0 etatInitial profondeurMax


let meilleurCoup profondeurMax etatInitial profondeur etatsFils evaluation = 
		let rec aux p (e, chem) pm = 
			if pm = 0 then (evaluation e, chem) else
			let fils = (etatsFils e) in
			match fils with
				| [] -> (evaluation e, chem)
				| (arc, noeud) :: tl -> 
						if p mod 2 = 0
						then 
						(* (max b (aux (p + 1) n (pm - 1)), a) *)
						List.fold_left (fun (bv, ba) (a, n) -> let valNode, chemNode = aux (p + 1) (n, a) (pm - 1) in if valNode > bv then (valNode, chemNode) else (bv, ba)) 
													(aux (p + 1) (noeud, arc) (pm - 1)) 
													tl
						else 
							List.fold_left (fun (bv, ba) (a, n) -> let valNode, chemNode = aux (p + 1) (n, a) (pm - 1) in if valNode <= bv then (valNode, chemNode) else (bv, ba)) 
													(aux (p + 1) (noeud, arc) (pm - 1)) 
													tl
		in aux 0 (etatInitial, " ") profondeurMax


(* let meilleurCoup profondeurMax etatInitial profondeur etatsFils evaluation = 
		let rec aux p e pm a = 
			if pm = 0 then (evaluation e, a) else
			let fils = etatsFils e in
			match fils with
				| [] -> (evaluation e, a)
				| (arc, noeud) :: tl -> (* renvoyer (int * 'x) *)
						if p mod 2 = 0
						(* then List.fold_left (fun (bv, ba) (a, n) -> let v = (aux (p + 1) n (pm - 1) arc) in if bv >= v then (bv, ba) else (v, a)) ((aux (p + 1) noeud (pm - 1) arc), arc) tl
						else List.fold_left (fun (bv, ba) (a, n) -> let v = (aux (p + 1) n (pm - 1) arc) in if bv >= v then  (v, a) else (bv, ba)) ((aux (p + 1) noeud (pm - 1) arc), arc) tl *)
		in aux 0 etatInitial profondeurMax  *)


let () = 
	(* let v, chem = meilleurCoup 3 etatInitialA5 0  etatsFilsA5 evaluationA5 in *)
	let v, chem = meilleurCoup 3 etatInitialA1 0  etatsFilsA1 evaluationA1 in
  let va = (recherche 3 etatInitialA5 0  etatsFilsA5 evaluationA5) in
	Printf.printf "%d : %s\n%d\n" v chem va