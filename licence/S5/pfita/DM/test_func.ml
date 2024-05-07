let a = vote_comment 5 1 (add_comment 1 "non mais stop la"(add_comment 2 "mdeir"(add_comment 1 "le petit com la" init_comments)))
(*
- : comments =
(3,
 [(1, 1, "le petit com la", [5; 3]); (2, 2, "mdeir", []);
  (3, 1, "non mais stop la", [])])
  *)


vote_comment 1 3 a
(*Exception: Failure "autovote".*)


get_voted_comments 5 (vote_comment 5 3 a) ;;
(*
- : text list = ["le petit com la"; "non mais stop la"]
*)

get_voted_comments 5 init_comments ;;
(*
- : text list = ["le petit com la"; "non mais stop la"]
*)

(*----------------------------------------------------------------*)

let base = add_comment 11 "meme apres l'avoir revue ca reste nul" (vote_comment 12 1 (vote_comment 11 3 (vote_comment 10 3 (add_comment 12 "racite!!" (add_comment 11 "j'aime vraiment pas tout ca" (add_comment 10 "Pas fou la video" init_comments))))))
(*
val base : comments =
  (3,
   [(1, 10, "Pas fou la video", []);
    (2, 11, "j'aime vraiment pas tout ca", []);
    (3, 12, "racite!!", [10; 11])])
*)

remove_comment 2 init_comment
(*
Exception: Failure "not found".
*)

remove_comments 11 base
(*
- : comments =
(4, [(1, 10, "Pas fou la video", [12]); (3, 12, "racite!!", [10; 11])])
*)

update_comment 12 3 (fun a -> "CHANGED TEXT LOL") base ;;
(*

*)








