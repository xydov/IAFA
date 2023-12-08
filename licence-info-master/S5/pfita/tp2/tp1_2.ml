(*
(1,false) ;;
- : int * bool = (1, false)

(2., 1+4, 1=1, "salut") ;;
- : float * int * bool * string = (2., 5, 1=1, "salut") 

(('a', 1), ('b', 2), ('c', 3)) ;;
- : (char * int) * (char * int) * (char * int) = (('a', 1), ('b', 2), ('c', 3))

(1, 2, 3) ;;
- : int * int * int = (1, 2, 3)

(1, (2, 3)) ;;
- : int * (int * int) = (1, (2, 3))

(1, (2, 3)) ;;
- : (int * int) * int = (1, (2, 3)) ;;

(1, 2, 3) = (2, 1, 3) ;;
- : bool = false

(1, (2, 3)) = (1, 2, 3) ;;
This expression has type 'a * 'b * 'c
       but an expression was expected of type int * (int * int)
*) 

let quadruplet = (true, (2, 3), (fun a -> 2. *. a), "stringeling") 

(* Exercice 3 *)
let imp a b = match a, b with
  | true, true -> true
  | true, false -> false
  | false, true -> true
  | false, false -> true 
    
let xor a b = match a, b with
  | true, true -> false
  | true, false -> true
  | false, true -> true
  | false, false -> false 
    
let bissextile annee = (annee mod 4 = 0) && ((annee mod 100) <> 0) || (annee mod 400) = 0 

let nbjour mois annee = 
  match mois with
  | 1 | 3 | 5 | 7 | 8 | 10 | 12 -> 31
  | 2 -> if bissextile annee then 29 else 28
  | 4 | 6 | 9 | 11 -> 30
  | _ -> failwith "nbjour";;
      
(*Does not take february in account*)
let valide (jour, mois, annee) =
  match jour <= 31 && jour >= 0 , mois >= 1 && mois <= 12, annee with
  | true, true, _ -> true
  | _, _, _ -> false
    
(*
let lendemain (jour, mois, annee) = 
  match jour, mois, annee with
  | _, _, _ -> if
  *)  
(* Exercice 4 *)
