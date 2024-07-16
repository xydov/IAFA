Require Import ZArith.

Require Import ast.
Require Import sem.
Require Import listSet.

(*
 The goal of this module is to suppress unused statements when computing the
 value to be assigned to a register.
*)

(*
  returns the set of registers read by the expression e
*)
Fixpoint eused (e: expr) : set nat :=
  match e with
  | NONE => empty_set
  | todo => empty_set 
  end.

(*
  returns the set of registers read by the condition c
*)
Fixpoint cused (c:cond) : set nat :=
  match c with
  | NO_COND => empty_set
  | todo => empty_set 
  end.

(* registers that are used to compute the value of registers in rl or to
   update the current cell
*)

Fixpoint usedFor (s:stmt) (rl: list nat): set nat :=
  match s with
    NOP => rl
  | todo => rl 
  end.

(*
  replaces useless assignments in s by NOP
 *)

Fixpoint clean (s:stmt) (rl: list nat) :=
  match s with
    NOP => NOP
  | todo => NOP 
  end.

(* if rl is a subset of rl', usedFor s rl is a subset of usedFor s rl' *)
Lemma usedFor_mono: forall s rl rl' r,
    (forall r, set_In r rl -> set_In r rl') ->
    set_In r (usedFor s rl) -> set_In r (usedFor s rl').
Proof.
Admitted.

(* if r is used by s, r is also used by clean s rl *)
Lemma usedFor_clean: forall s rl r,
    set_In r (usedFor s rl) -> set_In r (usedFor (clean s rl) rl).
Proof.
Admitted.

(* The value of expression e does not depend on the value of registers unused 
   by e
*)
Lemma usedFor_esem_r: forall e cd rd rd',
    (forall r, set_In r (eused e) -> rd r = rd' r) ->
    esem cd rd e = esem cd rd' e.
Proof.
Admitted.

(* the value of condition c does not depend on registers unused by c *)
Lemma usedFor_csem_r: forall c cd rd rd',
    (forall r, set_In r (cused c) -> rd r = rd' r) ->
    csem cd rd c = csem cd rd' c.
Proof.
Admitted.

(* the value of registers of rl after the execution of s does not depend 
   on unused registers *) 
Lemma usedFor_ssem_r: forall s cd rd rd' rl r,
    (forall r, set_In r (usedFor s rl) -> rd r = rd' r) ->
    set_In r rl -> ssem_r cd rd s r = ssem_r cd rd' s r.
Proof.
Admitted.

(* the value of registers in rl is unchanged by the clean transformation *)
Lemma clean_ssem_r: forall s cd rd rl r,
    set_In  r rl ->
    ssem_r cd rd (clean s rl) r = ssem_r cd rd s r.
Proof.
Admitted.

(* the cell contents after the execution s does not depend on the
value of unused registers
*)
Lemma ssem_c_eqr: forall s cd ncd rd rd' rl,
    (forall r, set_In r (usedFor s rl) -> rd r = rd' r) ->
    forall f, ssem_c cd ncd rd s f = ssem_c cd ncd rd' s f.
Proof.
Admitted.

(* the cell contents is unchanged by the clean transformation *)

Lemma clean_sem_c: forall s cd ncd rd rl f,
    ssem_c cd ncd rd (clean s rl) f = ssem_c cd ncd rd s f.
Proof.
Admitted.

(* clean transformation on programs *)
Definition clean_p (p: prog): prog := (fst p, clean (snd p) []).

(* the clean transformation is correct *)
Theorem clean_p_OK: forall cd rd p f,
    psem cd rd (clean_p p) f = psem cd rd p f.
Proof.
  intros.
  destruct p as [d s]; unfold clean_p; simpl.
  apply clean_sem_c.
Qed.
