
(* ================================== *)

(* Un petit graphe en extension : *)

(* let g1 = ["WA","NA" ; "WA","SA" ; "NA","SA" ; "NA","Q" ; "SA","Q" ; "SA","V" ; "SA","NSW" ; "Q","NSW" ; "NSW","V" ]

let g2 = ["A","B" ; "A","E" ; "B","C" ; "B","D" ; "B","E" ; "C","D" ; "D","E"]

let g7 = [("h","a");("h","d");("h","g");("b","c");("b","e");("b","f");("b","a");("c","f");("d","e");("d","a");("d","g");("e","g");("f","i")] *)

(* ================================== *)

(* Checks if two vertices s1 and s2 are adjacent *)
let sont_adjacents (g : ('a * 'a) list) (s1 : 'a) (s2 : 'a) : bool = 
  List.exists (fun (is1, is2) -> ((is1 = s1) && (is2 = s2)) || ((is1 = s2) && (is2 = s1))) g

(* Creates the list of the graphs vertices *)
let liste_sommets g =
  let la, lb = List.split g in 
  List.sort_uniq compare (la @ lb)

(* Creates the list of all adjacent vertices of a given vertice *)
let sommets_adjacents g s = 
  let rec aux lst = match lst with
  | [], [] -> []
  | h1 :: tl1, h2 :: tl2 -> 
    if h1 = s then h2 :: (aux (tl1, tl2)) else 
    if h2 = s then h1 :: (aux (tl1, tl2)) else (aux (tl1, tl2))
  | _, _ -> failwith "List sizes does not match"
  in List.sort_uniq compare (aux (List.split g))

(* === UTIL === *)

let next_color l = 
  let il = List.sort (fun a b -> if a = b then 0 else if a < b then -1 else 1) l in
  let rec aux l e = match l with
    | [] -> e
    | hd :: tl -> if hd = e then aux tl (e + 1) else e
  in aux il 1

let couleurs_utilisees coloration_partielle s_adjacents = 
  let rec aux col_partielle = match col_partielle with
  | [] -> []
  | (sommet, couleur) :: tl -> 
    if List.mem sommet s_adjacents = true 
    then couleur :: (aux tl)
    else aux tl
  in List.sort_uniq compare (aux coloration_partielle)

let ordre_degre_decroissant g = 
  let s_ponderees = (List.map (fun sommet -> List.length (sommets_adjacents g sommet), sommet) (liste_sommets g)) in
  let _, sommets = List.split (List.sort (fun (d_a, _) (d_b, _) -> - compare d_a d_b) s_ponderees) in sommets

let dsat s g coloration_partielle = 
  List.length (couleurs_utilisees coloration_partielle (sommets_adjacents g s))

let nb_vois_non_coloriee coloration_partielle s_adjacents = 
  let sommets_colorer, _ = List.split coloration_partielle in
  let rec aux s_adjacents =
    match s_adjacents with
    | [] -> 0
    | s :: tl -> if not (List.mem s sommets_colorer) then 1 + aux tl else aux tl
  in aux s_adjacents

let rec dsat_max_ordered_list (l_sommets : 'a list) g coloration_partielle = 
    let dsat_ordered_list =
      List.sort 
      (fun (dsat_a, s_a) (dsat_b, s_b) -> 
        if dsat_a = dsat_b 
        then 
          let test = - compare (nb_vois_non_coloriee coloration_partielle (sommets_adjacents g s_a)) (nb_vois_non_coloriee coloration_partielle (sommets_adjacents g s_b)) in
          if test = 0 then compare s_a s_b else test
        else - compare dsat_a dsat_b) 
      (List.map (fun s -> (dsat s g coloration_partielle), s) l_sommets) in 
      let _, s_list = List.split dsat_ordered_list in s_list

  (* === UTIL === *)

(* Algo glouton sans heuristique, ordre de coloriage des sommets indifférents *)
let gloutonSansH g = 
  let sommets = liste_sommets g in
  let rec glout l_sommets colo_partielle = match l_sommets with
    | [] -> colo_partielle
    | s :: tl ->
      let v = couleurs_utilisees colo_partielle (sommets_adjacents g s) in
      let c = next_color v in 
      glout tl ((s, c) :: colo_partielle)
  in 
  let coloration_partielle = glout sommets [] in
  let cmax = List.fold_left (fun b e -> max b e) 0 (snd (List.split coloration_partielle)) 
  in coloration_partielle, cmax, sommets

(* Algo glouton avec heuristique statique, coloration par ordre de degré décroissant puis alpha *)
let gloutonDeg g = 
  let sommets = ordre_degre_decroissant g in
    let rec glout l_sommets colo_partielle = match l_sommets with
    | [] -> colo_partielle
    | s :: tl ->
      let v = couleurs_utilisees colo_partielle (sommets_adjacents g s) in
      let c = next_color v in 
      glout tl ((s, c) :: colo_partielle)
  in 
  let coloration_partielle = glout sommets [] in
  let cmax = List.fold_left (fun b e -> max b e) 0 (snd (List.split coloration_partielle)) 
  in coloration_partielle, cmax, sommets


let gloutonDSat g =
  let sommets = ordre_degre_decroissant g in
  let rec glout l_sommets colo_partielle = match dsat_max_ordered_list l_sommets g colo_partielle with
    | [] -> colo_partielle
    | s :: tl ->
      let v = couleurs_utilisees colo_partielle (sommets_adjacents g s) in
      let c = next_color v in 
      glout tl ((s, c) :: colo_partielle)
  in 
  let coloration_partielle = glout sommets [] in
  let cmax = List.fold_left (fun b e -> max b e) 0 (snd (List.split coloration_partielle)) 
  in coloration_partielle, cmax, List.rev (fst (List.split coloration_partielle))
