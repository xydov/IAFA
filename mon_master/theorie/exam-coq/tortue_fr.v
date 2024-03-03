(* Important que tout le code compile jusqu'au bout
   une preuve non terminée peut comporter des admits et se terminer par Admitted.
   toute avancée significative dans une preuve sera prise en compte dans la notation *)

(* Aucune restriction sur l'usage des tactiques *)

(*
  Le but de ce TP est de définir un petit langage inspiré du langage LOGO qui
  commande une "tortue" possédant un crayon et se déplaçant sur une feuille de
  papier. Si le crayon est baissé, la tortue va pouvoir écrire et par exemple
  dessiner une figure géométrique (un carré dans le TP).
  
*)

Require Import Arith.
Require Import Bool.
Require Import List.
Import ListNotations.

Inductive type_action: Type :=
| Avancer
| Tourner
| Ecriture (b: bool)
| Sequence (a1 a2: type_action)
| Repeter (n: nat) (a: type_action)
.

Inductive type_direction: Type :=
  Nord | Sud | Est | Ouest.

Definition turn d :=
  match d with
  | Nord => Ouest
  | Ouest => Sud
  | Sud => Est
  | Est => Nord
  end.

(*
Définir la fonction move prenant en argument une position (x,y) et une
direction et renvoyant la nouvelle position après un pas dans la direction
donnée.
- Est incrémente x, Ouest décrémente x (sans effet en 0)
- Nord incrémente y, Sud décrémente y (sans effet en 0)
On utilisera la fonction pred: nat->nat.
 *)

Definition move (pos: nat * nat) (d: type_direction) := match d with 
|Nord => (fst pos  , snd pos +1)
|Sud => (fst pos , snd pos -1) 
|Est => (fst pos +1 , snd pos) 
|Ouest => (fst pos -1 , snd pos ) 
end.

Lemma move_example: move (1, 2) Nord = (1, 3).
Proof.
simpl; auto.
Qed.

Definition type_sheet := nat * nat -> bool.

Definition eq2 (xy: nat * nat) (zt: nat * nat): bool :=
  let (x, y) := xy in
  let (z, t) := zt in
  (x =? z) && (y =? t).

Definition write (pos: nat * nat) (f: type_sheet): type_sheet :=
  fun xy => eq2 xy pos || f xy.

(*
  Un état de la machine est un quadruplet comportant le feuille de papier,
la hauteur du crayon, la position de la tortue et sa direction. Il sera
possible d'accéder aux informations contenues dans l'état via les accesseurs
en lecture sheet, pencil, position et direction. Un état peut être construit en appelant la fonction State sur les 4 données composant l'état.
*)
Record type_state: Type := State {
    sheet: type_sheet ;
    pencil: bool ;
    position: nat * nat ;
    direction: type_direction ;
  }.
Unset Printing Records. (* Avoid verbose syntax {| ... ; ... |} *)

(* renvoie le record où l'état du crayon a été modifié *)
Definition st_set_pencil (st: type_state) b: type_state :=
  State
    (sheet st)
    b
    (position st)
    (direction st).

(* renvoie le record où la position et le contenu de la feuille ont été
 modifiés *)
Definition st_move (st: type_state): type_state :=
  State
    (if pencil st then write (position st) (sheet st) else sheet st)
    (pencil st)
    (move (position st) (direction st))
    (direction st).

(* cette fonction modifie l'état pour déplacer la direction d'1/4 de tour
   vers la gauche en laissant les autres champs inchangés *)
Definition st_turn (st: type_state): type_state :=
  State
    (sheet st)
    (pencil st)
    (position st)
    (turn (direction st)).

(* Définir la fonction récursive terminale power appliquant n fois la
   fonction f sur l'argument x
*)
Fixpoint power (T: Type) (n: nat) (f: T -> T) (x: T): T := match n with 
|0 => x
|S n => power (T)(n)(f)(f x)
end.



(* Démontrer SANS UTILISER L'INDUCTION le théorème suivant *)
Lemma power_example: forall n: nat, power nat (S n) (fun n => n + 2) 5 = power nat n (fun n => n + 2) 7.
Proof.
simpl.

auto.
(*lia.*)
Admitted.


(* Définir la fonction récursive exec renvoyant l'état obtenu en exécutant
   l'action à partie de l'état st.
   On utilisera les fonctions st_* ainsi que la fonction power définies
   précédemment.
*)



Fixpoint exec (a: type_action) (st: type_state): type_state := 
match a with 
|Avancer  => st_move(st)
|Tourner  => st_turn(st) 
|Ecriture (e) => st_set_pencil(st) e 
|Sequence a1 a2 => exec(a2)((exec a1) (st)) 
|Repeter n a => power (type_state)(n) (exec a) (st) 

end.


(* État initial pour tester votre programme *)
Definition init := State (fun pos => false) false (0, 0) Est.

Lemma exec_test: position (exec (Repeter 3 Avancer) init) = (3,0).
Proof.
simpl;reflexivity.
Qed.

(*
  Définir la fonction carre prenant en argument un entier n et renvoyant
  l'action permettant de dessiner un carré de coté n.
  On suppose que la place est suffisante sur le papier.
*)
Definition carre (n: nat): type_action := 
(*peter (4) (Sequence Repeter (n) (Sequence(Tourner)..*)

(* vérifie qu'une ligne de longueur n est présente depuis pos *)


Fixpoint test_line (n: nat) (f: type_sheet) (pos: nat * nat): bool :=
  match n with
  | O => true
  | S p => f pos && test_line p f (let (x, y) := pos in (S x, y))
  end.

(* vérifie qu'une colonne de longeur n est présente depuis pos *)
Fixpoint test_col (n: nat) (f: type_sheet) (pos: nat * nat): bool :=
  match n with
  | O => true
  | S p => f pos && test_col p f (let (x, y) := pos in (x, S y))
  end.

(* vérifie qu'un carré est présent sur la feuille *)
Definition test_carre (n: nat) (f: type_sheet) (pos: nat * nat): bool :=
  test_line n f pos
  && test_line n f (let (x, y) := pos in (x, y + n))
  && test_col n f pos
  && test_col n f (let (x, y) := pos in (x + n, y)).

(* vérifie que la définition de carre est correct *)
Lemma verif_carre: test_carre 4 (sheet (exec (carre 4) init)) (0, 0) = true.
Proof.
simpl;reflexivity.
Admitted. (* TODO *)

(* On commence par s'intéresser à la sémantique à grand pas,
qui spécifie les états finaux accessibles après exécution d'une action à
partir d'un état initial.
Les régles ci-dessous décrivent l'effet des différentes actions selon la
sémantique à grands pas. Il s'agira d'écrire ces régles sous forme d'un
type inductif Coq.


    -------------------------------- (bs_Avancer)
    st -[Avancer]-> (st_move st)

    ---------------------------------------- (bs_Ecriture))
    st -[Ecriture b]-> (st_set_pencil st b)

    -------------------------------- (bs_Tourner)
    st -[Tourner]-> (st_turn st)

  -------------------------------------------- (bs_Repeter0)
      st -[Repeter 0 a]-> st

    st -[a]-> st'    st' -[Repeter n a]-> st''
  -------------------------------------------- (bs_RepeterS)
      st -[Repeter (S n) a]-> st''

    st -[a1]-> st'    st' -[a2]-> st''
  -------------------------------------------- (bs_Sequence)
      st -[Sequence a1 a2]-> st''

 *)
Inductive big_step: type_state -> type_action -> type_state -> Prop :=
  bs_Avancer: forall st, big_step st Avancer (st_move st).
(* TODO - ajouter les autres règles *)

(*
preuve par induction sur n.

en cas d'Error: Unable to find an instance for the variable ... il faut indiquer la valeur du/des paramètre(s) manquant(s) en écrivant apply ... with p1 ...;

 *)
Lemma big_step_Repeter: forall f (a: type_action) (n: nat),
    (forall st, big_step st a (f st)) -> forall st, big_step st (Repeter n a) (power type_state n f st).
Proof. (* TODO *)
Admitted.

(* induction sur a; même remarque sur apply
   utiliser big_step_Repeter *)
Theorem big_exec: forall a st, big_step st a (exec a st).
Proof. (* TODO *)
Admitted.

(*

pour rappel, la sémantique à petit pas définit les transformations élémentaires
de l'état du système, qu'on peut ici représenter par un couple
(st: type_state, al: list type_action)

Dans les règles ci-dessous, la syntaxe (st, al) --> (st', al')
sera formalisée en Coq par la relation à 4 arguments
   small_step st al st' al'

   ss_Avancer:   (st, (Avancer::cnt)) ---> ((st_move st), cnt)
   ss_Tourner:   (st, (Tourner::cnt)) --->  ((st_turn st), cnt)
   ss_Ecriture:  (st, (Ecriture b::cnt)) --> ((st_set_pencil st b), cnt)
   ss_Repeter0:  (st, (Repeter 0 a::cnt)) --> (st, cnt)
   ss_RepeterS:  (st, (Repeter (S n), a::cnt) --> (st, (a::Repeter n a::cnt))
   ss_Sequence:  (st, (Sequence a1 a2::cnt)) --> (st, (a1::a2::cnt))
*)

Inductive small_step: type_state -> list type_action -> type_state -> list type_action -> Prop :=
  ss_Avancer: forall st cnt, small_step st (Avancer::cnt) (st_move st) cnt
| ss_Tourner: forall st cnt, small_step st (Tourner::cnt)  (st_turn st) cnt
| ss_Ecriture: forall st b cnt, small_step st (Ecriture b::cnt) (st_set_pencil st b) cnt
| ss_Repeter0: forall st cnt a, small_step st (Repeter 0 a::cnt) st cnt
| ss_RepeterS: forall st cnt n a, small_step st (Repeter (S n) a::cnt) st (a::Repeter n a::cnt)
| ss_Sequence: forall st cnt a1 a2, small_step st (Sequence a1 a2::cnt) st (a1::a2::cnt).

(* L'inductif suivant est une version alternative de big_step,
   définie à partir de small_step
   (lors du TP non noté, bigStep avait d'ailleurs cette forme)
   on s'attachera à prouver que les deux prédicats inductifs steps et big_step sont liés *)
Inductive steps (st: type_state): list type_action -> type_state -> Prop :=
  stp0: steps st [] st
| stpS: forall al al' st' st'', small_step st al st' al' -> steps st' al' st'' -> steps st al st''.

(* On transforme une liste d'actions en action unique *)
Fixpoint l2s (l: list type_action): type_action :=
  match l with
    [] => Repeter 0 Avancer (* l'action (Repeter 0 a) n'a aucun effet sur l'état courant *)
  | a::al => Sequence a (l2s al)
  end.

Lemma steps_nil: forall st1 st2, steps st1 [] st2 -> st1=st2.
Proof.
  intros.
  inversion H; subst; auto.
  inversion H0.
Qed.

(*
  On procèdera par induction sur l'hypothèse de type (steps st al st').

  On utilisera "apply bs_... with ..." en choisissant le bon constructeur
    pour prouver une relation (big_step ...).
  Dans les cas particuliers de la séquence et de la répétition, il faudra
    aussi indiquer l'état intermédiaire: "apply bs_... with ...".
  On utilisera "destruct H" pour traiter une hypothèse de la forme
     H: small_step st (t :: al) st' al'
  On utilisera "inversion_clear H" pour traiter une hypothèse de la forme
     H: steps at (a :: ...) st'
  ou H: big_step st (Sequence ... ) st'
 *)

Theorem small_big: forall al st st', steps st al st' -> big_step st (l2s al) st'.
Proof.
Admitted.
