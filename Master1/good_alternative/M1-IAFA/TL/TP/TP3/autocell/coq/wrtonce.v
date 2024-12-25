Require Import ZArith.
Require Import ast.
Require Import sem.
Require Import listSet.

(*
  This module removes multiple writes to a field of the current cell. Only the last write is kept.
*)

(* returns (a subset of) the set of field numbers that are always written by s.
- SET_CELL writes a single field
- SET_VAR writes no field
- SEQ: uses set_union
- IF_THEN: uses set_inter. We do not take into account the condition on which a field is written.
Note that 'set_union' and 'set_inter' take as first parameter 'eq_nat_dec' to compare set elements.
*)
Fixpoint written (s:stmt) : set nat :=
  match s with
    NOP => empty_set
  | todo => empty_set 
  end.

(*
  removes double writes to some field given that fields of lf will be written later
  => the last write is kept, others are replaced by NOP
- SET_CELL: if f is in lf, it will be written later => remove. Otherwise keep it
- SET_VAR: keep it
- SEQ l r: call wonce on r then on l, given that fields written after l are those written after r or written by r
- IF_THEN: transform each branch
*)
Fixpoint wonce (s:stmt) (lf: list nat): stmt :=
  match s with
    NOP => NOP
  | todo => NOP 
  end.

(*
  register values are unchanged by the wonce transformation
Proof by induction on s. Uses 'set_In_dec Nat.eq_dec'
*)
Lemma wonce_r: forall s cd rd lf,
    ssem_r cd rd s = ssem_r cd rd (wonce s lf).
Proof.
Admitted.

Require Import FunctionalExtensionality.

(* the set of written fields is unchanged by the wonce transformation 
Proof by induction on s. 
Uses 'set_In_dec Nat.eq_dec', 'set_inter_iff', 'set_union_iff'.
*)

Lemma written_wonce: forall s f lf, 
    set_In f (written (wonce s lf)) -> set_In f (written s).
Proof.
Admitted.

(* the value of fields written by s does not depend on previous writes.
Proof by induction on s.
Uses 'setr_eq', 'ssem_c_eq', 'set_inter_iff', 'set_union_iff'.
*)
Lemma ssem_c_w: forall s cd ncd ncd' rd f,
    set_In f (written s) -> ssem_c cd ncd rd s f = ssem_c cd ncd' rd s f.
Proof.
Admitted.

(* if updates of fields not written by s coincide, the value of all the fields
   of the current cell are identical after the execution of s.
Proof by induction on s.
Do case distinction on field numbers using seq_nat_dec
Uses 'setr_eq', 'setr_ne', 'set_inter_iff', 'set_union_iff'.
Uses 'set_In_dec eq_nat_dec' to make case distinction on membership.
*)
Lemma ssem_c_nw: forall s cd ncd ncd' rd,
    (forall f, not (set_In f (written s)) -> ncd f = ncd' f) ->
    forall f, ssem_c cd ncd rd s f = ssem_c cd ncd' rd s f.
Proof.
Admitted.

(*
  the wonce transformation does not change the value of fields outside lf.
  Proof by induction on s after reverting all hypotheses..
Uses 'set_In_dec Nat.eq_dec' to make case distinction on membership
Uses 'ssem_c_w', 'written_wonce', 'wonce_r', 'ssem_c_eq', 'set_union_iff'.
*)
Lemma wonce_c: forall cd rd ncd s lf f,
    not (set_In f lf) -> ssem_c cd ncd rd s f = ssem_c cd ncd rd (wonce s lf) f.
Proof.
Admitted.

(* the wonce transformation on programs *)
Definition elim_w2 (p:prog): prog := (fst p, wonce (snd p) []).

(* correctness of the transformation *)
Theorem wonce_OK: forall cd rd p, psem cd rd p = psem cd rd (elim_w2 p).
Proof.
  intros.
  destruct p as [d p]; unfold psem; simpl.
  extensionality f.
  apply wonce_c.
  simpl; auto.
Qed.
