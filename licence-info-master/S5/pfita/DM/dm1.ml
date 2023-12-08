let nom = "KUNZE" and prenom = "Tarek"

type comment_id = int
type user_id = int
type text = string
type comment = comment_id * user_id * text * (user_id list)
type comments = int * (comment list)
let score (_, _, _, list_votes) =
  let rec length l = match l with
    | [] -> 0
    | _ :: l -> 1 + length l
  in length list_votes;;

(* Q 3.1 *)
let rec add_once e l = match l with 
  | [] -> e :: []
  | hd :: tl -> if e = hd then failwith "already" else hd :: (add_once e tl)

(* Q 3.2 *)
let rec remove_if p l = match l with
  | [] -> []
  | hd :: tl -> if (p hd) = true then remove_if p tl else hd :: (remove_if p tl)


(* procédures auxiliaire *)
let fst (f, s) = f
let snd (f, s) = s

(* Q 4 *)
let init_comments : comments = (0, [])

(* Q 4.1 *)
let add_comment author text comments : comments = 
  let rec ac c = match c with
    | [] -> ((fst comments) + 1, author, text, []) :: []
    | hd :: tl -> hd :: (ac tl)
  in
  if text = "" then failwith "no comment"
  else
    (fst comments + 1, ac (snd comments))

(* Q 4.2 *)
let rec vote_comment user_id comment_id (comments : comments) : comments = match comments with
  | (n, []) -> failwith "no comment" 
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      let is_the_comment = (c_id = comment_id)
      in
      if (user_id = u_id) && is_the_comment
      then failwith "autovote"
      else
      if is_the_comment
      then (n, (c_id, u_id, txt, (add_once user_id u_id_l)) :: tl)
      else (n, (c_id, u_id, txt, u_id_l) :: (snd (vote_comment user_id comment_id (n, tl))))

(* Q 4.3 *)
let rec get_comment comment_id (comments : comments) : text = match comments with
  | (n, []) -> failwith "not found"
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      if comment_id = c_id 
      then txt 
      else get_comment comment_id (n, tl)

(* Q 4.4 *)
let rec get_comments author_id (comments : comments) = match comments with
  | (n, []) -> []
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      if author_id = u_id 
      then txt :: get_comments author_id (n, tl)
      else get_comments author_id (n, tl)


(* fnc that checks if voted for a comment in a comments *)
let rec has_voted user_id (u_id_l : user_id list) = match u_id_l with
  | [] -> false
  | hd :: tl -> hd = user_id || has_voted user_id tl

(* Q 4.5 *)     
let rec get_voted_comments user_id (comments : comments) = match comments with
  | (n, []) -> []
  | (n, (c_id, u_id, txt, u_id_l) :: tl) ->
      if has_voted user_id u_id_l
      then txt :: get_voted_comments user_id (n, tl)
      else get_voted_comments user_id (n, tl)


(* Q 4.6 *)
(* when we remove an element, we do not update (fst comments)
  because it remembers the amount of comments created from the beginning
*)
let rec remove_comment comment_id (comments : comments) : comments = match comments with
  | (n, []) -> failwith "not found"
  | (n, (c_id, u_id, txt, u_id_l) :: tl) ->
      if comment_id = c_id 
      then (n, tl)
      else (n, (c_id, u_id, txt, u_id_l) :: (snd (remove_comment comment_id (n, tl))))


(* Q 4.7 *)
let rec remove_comments user_id (comments : comments) : comments = match comments with
  | (n, []) -> (n, [])
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      if user_id = u_id 
      then (n, snd (remove_comments user_id (n, tl)))
      else (n, (c_id, u_id, txt, u_id_l) :: (snd (remove_comments user_id (n, tl))))


(* Q 4.8 *)
let rec update_comment user_id comment_id f comments : comments = match comments with
  | (n, []) -> failwith "not found"
  | (n, (c_id, u_id, txt, u_id_l) :: tl) -> 
      if (comment_id = c_id) && (user_id <> u_id)
      then failwith "author"
      else if (comment_id = c_id) && (user_id = u_id)
      then (n, (c_id, u_id, f txt, u_id_l) :: tl)
      else (n, (c_id, u_id, txt, u_id_l) :: (snd (update_comment user_id comment_id f (n, tl))))


(* aux *)               
let better_score c1 c2 = score c1 >= score c2 
                           
let older (c_id1, _, _, _) (c_id2, _, _, _) = c_id1 < c_id2
                                              
let rec insert p e l = match l with
  | [] -> e :: []
  | hd :: tl -> 
      if p e hd 
      then (e :: hd :: tl) 
      else hd :: (insert p e tl)

let rec insertion_sort p l = match l with
  | [] -> []
  | hd :: tl -> insert p hd (insertion_sort p tl)

let top_three (comments : comments) : comment list =
  let c_list = snd comments
  in
  let ordered_list = insertion_sort better_score c_list
  in 
  match ordered_list with 
  | f :: s :: t :: tl -> insertion_sort older (f :: s :: t :: [])
  | _ -> ordered_list 

  (*
(* ======================================================== *)
(* insert at *)
let insert_at k e lst =
  let rec at l i = match l, i = 0 with
    | [], false -> failwith "out of bound"
    | [], true -> e :: []
    | hd :: tl, false -> hd :: at tl (i - 1)
    | hd :: tl, true -> e :: hd :: tl
  in
  at lst (k - 1)
   
(* len of a list *)
let rec len l = match l with
  | [] -> 0
  | hd :: tl -> 1 + len tl

(* Q 4.9 *)

let top_three (comments : comments) : comment list = 
  let rec tt c_lst f s t nl = match c_lst with
    | [] -> nl
    | hd :: tl -> 
        let sc = score(hd) in
        if sc > f then tt tl sc f s (insert_at 1 hd nl)
        else if sc > s then tt tl f sc s (insert_at 2 hd nl)
        else if sc > t then tt tl f s sc (insert_at 3 hd nl)
        else tt tl f s t nl
  in 
  let base_snd = (snd comments)
  in
  if (len base_snd) <= 3
  then base_snd
  else tt base_snd -1 -1 -1 []
(* ======================================================== *)
*)