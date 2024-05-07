(* 
Exercice 1 || #use "tp1.ml"
*)

let estZero_v1 x = match x with
  | 0 -> "zero"

let estZero_v2 x = match x with
  | 0 -> "zero"
  | _ -> "nonZero"

let voyelle v = match v with
  | 'a' | 'e' | 'i' | 'o' | 'u' | 'y' -> true
  | _ -> false

(*
Exercice 2
  1:
  *)
let rang d = match d with
  | "lundi" -> 1
  | "mardi" -> 2
  | "mercredi" -> 3
  | "jeudi" -> 4
  | "vendredi" -> 5
  | "samedi" -> 6
  | "dimanche" -> 7
  | _ -> 0

(* 2: *)
let inf d1 d2 = let a = (rang d1 + 1 ) mod 8 in 
  if a  = 0 then 1 = (rang d2)
  else a = (rang d2)

(* 3: *)
let jsem n = match n with
  | 1 -> "lundi"
  | 2 -> "mardi"
  | 3 -> "mercredi"
  | 4 -> "jeudi"
  | 5 -> "vendredi"
  | 6 -> "samedi"
  | 7 -> "dimanche"
  | _ -> "jour inconnu"

(* 4: Successeur de jour *)
let jourSucc1 jour = match jour with
  | "lundi" -> "mardi"
  | "mardi" -> "mercredi"
  | "mercredi" -> "jeudi"
  | "jeudi" -> "vendredi"
  | "vendredi" -> "samedi"
  | "samedi" -> "dimanche"
  | "dimanche" -> "lundi"
  | _ -> "jour inconnu"

let jourSucc2 jour = 
  let rj = rang jour in
  if rj = 0 then jsem 0 
  else if rj = 7 then jsem 1
  else jsem (rj + 1) 

let jourSucc3 jour = 
  let rj = rang jour in 
  if rj = 0 then jsem 0
  else jsem (rj mod 7 + 1)

(* 5: Prédécesseur de jour *)
let jourPred1 jour = match jour with
  | "lundi" -> "dimanche"
  | "mardi" -> "lundi"
  | "mercredi" -> "mardi"
  | "jeudi" -> "mercredi"
  | "vendredi" -> "jeudi"
  | "samedi" -> "vendredi"
  | "dimanche" -> "samedi"
  | _ -> "jour inconnu"

let jourPred2 jour = let rJour = rang jour in if rJour = 1 then jsem 7 else jsem (rJour - 1)

let jourPred3 j =
  let rj = rang j in
  if rj = 0 then jsem 0
  else jsem ((rj - 8) mod 7 + 7);;



(* 6: *)
let bissextile annee = (annee mod 4 = 0) && ((annee mod 100) <> 0) || (annee mod 400) = 0 

(* 7: *)
let nbjour mois annee = match mois, bissextile annee with 
  | 1, _ -> 31
  | 2, false -> 28
  | 2, true -> 29
  | 3, _ -> 31
  | 4, _ -> 30
  | 5, _ -> 31
  | 6, _ -> 30
  | 7, _ -> 31
  | 8, _ -> 31
  | 9, _ -> 30
  | 10, _ -> 31
  | 11, _ -> 30
  | 12, _ -> 31
  | _, _ -> 0


(*
Alternative synthax
*)
let test = fun i -> match i with
  | 1 -> "one"
  | 2 -> "two"
  | 3 -> "three"
  | _ -> "! unmatched"


(* Main function *)
  let main () =
  print_endline (jourPred3 "lundi")

let _ = main ()