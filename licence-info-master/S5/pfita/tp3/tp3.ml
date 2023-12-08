(* Partie A  *)

let rec filter p l = match l with 
  | [] -> []
  | hd :: tl -> 
      if (p hd) = true then hd :: (filter p tl)
      else filter p tl
                
let rec forall p l = match l with
  | [] -> true
  | hd :: tl -> (p hd) && (forall p tl)
                          
let rec exists p l = match l with
  | [] -> false
  | hd :: tl -> (p hd) || (exists p tl)
  
let fst (c1, c2) = c1
let snd (c1, c2) = c2
(*
let rec estFonction l = match l with
  | [] -> true
  | hd :: hd2 :: tl -> ( fst hd <> fst hd2) && (estFonction (hd2 :: tl))
  | hd :: [] -> true
  
let estFonction l =
  let rec fst_elements il = match il with
    | [] -> [] 
    | hd :: tl -> (fst hd) :: (fst_elements tl)
  in
  let first_elements = fst_elements l
  in
  let rec fst_diff iil = match iil with
    | [] -> true
    | hd :: tl -> (hd + 1 - 1) <> fst_diff tl
  in
  fst_diff first_elements
  
  *)  
                  (*val estFonction : ('a * 'b) list -> bool*)

let rec image e l = match l with
  | [] -> failwith "inexistant"
  | hd :: tl -> if fst hd = e then snd hd else image e tl
          
let rec imageEns le lc = match le with
  | [] -> []
  | hd :: tl -> image hd  lc :: imageEns tl lc
                  
let rec estInjectif lc = match lc with
  | [] -> failwith "b"
  | hd :: tl -> (snd hd) <> (estInjectif tl)
  
(* Partie B  *)

let liste1v1 = 10 :: 20 :: 30 :: []
let liste1v2 = [10; 20; 30]
               
let rec head l = match l with
  | [] -> failwith "Cannot access head element of empty list" 
  | hd :: _ -> hd
    
let rec tail l = match l with
  | [] -> failwith "Cannot remove head element of empty list" 
  | _ :: tl -> tl
    
let third l = head (tail (tail l))

let rec consCpleDouble n = match n > 0 with
  | false -> []
  | true ->  (n, 2*n) :: consCpleDouble (n - 1)
            
let rec consCpleF f n = match n > 0 with
  | false -> []
  | _ -> (n, f n) :: consCpleF f (n - 1) 
    
(* Partie C  *)

let rec last l = match l with
  | le :: [] -> le
  | [] -> failwith "could not get last element of empty list" 
  | hd :: tl -> last tl
                  
let rec sum l = match l with
  | [] -> 0
  | hd :: tl -> hd + sum tl
                  
let rec append l fl = match l with
  | [] -> fl
  | hd :: tl -> hd :: (append tl fl)

let rec reverse l = match l with
  | [] -> []
  | hd :: tl -> append (reverse tl) (hd :: [])
                  
let nbOcc e l = 
  let rec n ie il a = match il with
    | [] -> a
    | hd :: tl -> if ie = hd then n ie tl (a + 1) else n ie tl a 
  in
  n e l 0
  
let rec elimFirst e l = match l with
  | [] -> []
  | hd :: tl -> if e = hd then tl else hd :: (elimFirst e tl)
    
let elimLast2 e l = reverse (elimFirst e (reverse l))
    
let rec elim e l = match l with 
  | [] -> []
  | hd :: tl -> if hd = e then elim e tl else elim e (hd :: tl)
          
let rec substitute x y l = match l with 
  | [] -> []
  | hd :: tl -> if hd = x then y :: (substitute x y tl) else hd :: (substitute x y tl)
    
let rec hanoi n (source, temp, dest) = 5
    
    