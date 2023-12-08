(* Partie A - Fonctions et n-uplets *)
let e1 = ((6, true), 67)
         
let e2 = ((fun x -> x ), 'z')
      
         
let f1 x y = match x, y with 
  | 1, true -> (1, false)
  | _, _ -> (0, false)
    (*
let f1 x y = match x, y with
| 1, true -> (0, false)
| 0, false -> (1, true)
| _, _ -> failwith "erreur"*)
              
let f2 a = true
  
let f3 a b = if a = b then 6 else 7
  
let f4 (a, b) = (b, a) 
  

let f5 = fun f -> fun g -> fun h -> fun i -> fun j -> h (g (fst (f i)) (snd (f j)) , true)
    
let f6 = fun f -> fun g -> fun h -> g h (f h)
    
let f7 (a, b, c) = b (c, a c)
  
let f8 a b c d = if (a = b) && (d = c) then (a, c) else (b, d)
(*
      let f8 a b c d = match a = b, b = a, c = d, d = c with
        | true, true, true, true -> (a, c)
| _, _, _, _ -> failwith "not defined"
                *) 

let cube e = e * e * e

let quad a = a * 4
             
let estPair n = n mod 2 = 0
                
let max3 a b c = max (max a b) c 
    
let discriminant a b c = b * b - 4 * a *c
                                 
let estImpair a = estPair a = false
                  
let choix x = match estPair x with 
  | true -> cube x
  | false -> quad x
               
let nbRac a b c =  
  let n = discriminant a b c in 
  if n > 0 then 2
  else if n = 0 then 1
  else 0
    
let xor a b = match a, b with
  | false, false -> false
  | false, true -> true
  | true, false -> true
  | true, true -> false
  
let nor a b = match a, b with
  | false, false -> true
  | false, true -> false
  | true, false -> false
  | true, true -> false
  
  
let nand a b = match a, b with
  | false, false -> true
  | false, true -> true
  | true, false -> true
  | true, true -> false
    
(* Partie B - Récursion *) 


let sommeChiffres n =
  let rec somme k = match k with
    | 0 -> 0
    | _ -> k mod 10 + somme (k / 10)
  in
  if n < 0 then failwith "valeurs negatives non permises"
  else somme n
      
      
(*--------------------------*)
      
let sommeIteree n =
  let rec si k = 
    let somme = sommeChiffres k 
    in
    if somme < 10 then somme
    else sommeChiffres somme
  in
  si n
(*--------------------------*)



let dernierCh n = n mod 10
                  
let toutSaufDer n = n / 10
                    
let premierCh n = 
  let rec premCh i = 
    if i < 10 then i
    else premCh (i / 10)
  in
  premCh n
    
let toutSaufPrem n = 
  let rec tsp i =
    if i < 10 then 0
    else tsp (i / 10) * 10 + dernierCh i
  in
  tsp n
  
  
let rec estPalindrome n = match n < 10 with
  | true -> true
  | false -> (premierCh n) = (dernierCh n) && estPalindrome (toutSaufDer (toutSaufPrem n)) 
    
let rec nbOcc n c = 
  if c <= 10 then 
    if c = n then 1
    else 0
  else if dernierCh c = n then 1 + nbOcc n (c / 10)
  else nbOcc n (c / 10)
      
      
let rec nbOccsPM n c = match n, c < 10 with
  | _, true -> if c = n then 1 else 0
  | _, _ -> if dernierCh c = n then 1 + nbOccsPM n (c / 10) else nbOccsPM n (c / 10)
          
let rec iterer n f x = match n, f, x with
  | 0, _, _ -> x
  | _, _, _ -> f (iterer (n - 1) f x)
                 
let id z = z
  
let compose x y z = x (y z)

    
let rec iterer2 n f = 
  if n = 0 then id 
  else compose f (iterer2 (n - 1) f)
      
let rec itererBis f p x =
  if p x = true then x
  else itererBis f p (f x)

let sommeIteree2 n = itererBis (fun x -> sommeChiffres x) (fun x -> x < 10) n

let qqsoit n p = 
  let rec qqs i f =
    if i = 1 then f i
    else qqs (i - 1) f && f i
  in
  if n < 1 then failwith "No negative numbers"
  else 
    qqs n p

let ack (m, n) = 
  let rec a (x, y) = match x, y with
    | 0, _ -> y + 1
    | _, 0 -> a (x - 1, 1)
    | _, _ -> a (x - 1, a (x ,y - 1))
  in
  if (m < 0) || (n < 0) 
  then failwith "error m, n should be positive numbers"
  else a (m, n)
