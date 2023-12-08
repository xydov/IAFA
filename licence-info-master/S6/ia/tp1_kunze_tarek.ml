#use "F207.ml"

(*imprime une liste *) 
let rec print_list_string l = match l with  
    [] -> print_string ". " 
    |x::reste -> print_string (" "^x); print_list_string reste;; 

(*imprime une liste contenant des couts*) 
let rec print_list_string_couts l = match l with  
    | [] -> print_string ". " 
    | (n, _, _) :: reste -> print_string (" "^n); print_list_string_couts reste;; 

(* ======================== *) 

(* largeur *)
let rec largeur attente estBut etatsSuivants = match attente with
    []-> failwith "pas de but trouve"
    | x::reste -> 
        if (estBut x) then (print_string "file d'attente:";
        print_list_string attente;
        print_newline (); x)
        else (print_string "file d'attente:"; print_list_string attente; 
        print_newline ();
        largeur (reste @ (etatsSuivants x)) estBut etatsSuivants);;


(* profondeur *)
let rec profondeur attente estBut etatsSuivants = match attente with
    []-> failwith "pas de but trouve"
    | x :: reste -> 
        if (estBut x) then (print_string "file d'attente:";
        print_list_string attente;
        print_newline (); x)
        else (
        print_string "file d'attente:"; print_list_string attente;
        print_newline ();
        profondeur ((etatsSuivants x) @ reste) estBut etatsSuivants)

(* A star *)
(* listes des triplets à insérer dans la file d'attente *)
let creerLesFils etat g_etat opPoss hEtat = 
    let rec aux l = match l with
        | [] -> []
        | (_(*operateur*), cout_op, fils) :: tl -> (fils, g_etat + cout_op, hEtat fils) :: (aux tl)
    in (aux (opPoss etat))
(* insere chaque fils nouvellement «détecté»/«crée» dans a file de priorité *)
let insererLesFils liste_fils attente = 
    let rec insertElem e l = match l with
        | [] -> e :: []
        | hd :: tl -> 
            let (_, g_hd, h_hd) = hd in
            let (_, g_e, h_e) = e in
            if (g_e + h_e) < (g_hd + h_hd) then e :: hd :: tl
            else hd :: insertElem e tl
    in
    let rec parcourFils fils = match fils with
        | [] -> attente
        | h :: tl -> insertElem h (parcourFils tl)
    in
    parcourFils liste_fils

let rec a_star attente initG estBut opPoss hEtat = match attente with
    | [] -> failwith "pas de but trouve"
    | (n, g_n, h_n) :: tl ->
        if estBut n 
        then (  
            print_string "file d'attente:";
            print_list_string_couts tl;
            print_newline ();
            (n, g_n, h_n)
            )
        else
            let g = if initG > g_n then g_n else initG in
            let fils = (creerLesFils n g opPoss hEtat) in
            let ordered_attente = (insererLesFils fils tl) in
            (
            print_string "file d'attente:"; print_list_string_couts ordered_attente;
            print_newline ();
            a_star ordered_attente initG estBut opPoss hEtat
            )


let () = 
    let (n_found, g, h) = (a_star [(initGC, 0, (hEtatGC initGC))] 0 estButGC opPossGC hEtatGC) in
    (* let (n_found, _, _) = (a_star [(initG4, 0, (hEtatG4 initG4))] 0 estButG4 opPossG4 hEtatG4) in *)
    print_string "Sommet trouvé: ";
    print_endline n_found;
    print_int g;
    print_newline ();
    print_int h;


(*  
    add n to taken_path_list
*)