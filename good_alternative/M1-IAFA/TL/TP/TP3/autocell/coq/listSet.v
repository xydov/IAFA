Definition set := list.
Require Import List.
Include ListNotations.
Section SETS.

Context {T: Type}.
Variable eq_dec: forall (x y:T), {x=y}+{x<>y}.

Definition empty_set := @nil T.

Definition set_sing (x: T) := [x].

Fixpoint set_In x (l: set T) := 
match l with
  [] => False
| y::l' => x=y \/ set_In x l'
end.

Lemma set_In_dec x (l: list T): {set_In x l}+{not (set_In x l)}.
Proof.
  induction l; simpl; intros; auto.
  destruct IHl; auto.
  destruct (eq_dec x a); auto.
  right; intro.
  destruct H; auto.
Defined.

Fixpoint set_union (l1 l2: set T): set T :=
  match l1 with
    [] => l2
  |x::l => if set_In_dec x l2 then set_union l l2 else x::set_union l l2
  end.

Lemma set_union_iff x l1 l2: set_In x (set_union l1 l2) <-> set_In x l1 \/ set_In x l2.
Proof.
  induction l1; simpl; intros; auto; try tauto.
  destruct (set_In_dec a l2).
  rewrite IHl1; clear IHl1.
  destruct (eq_dec x a); subst; auto; try tauto.
  simpl.
  rewrite IHl1; clear IHl1.
  tauto.
Qed.

Fixpoint set_inter (l1 l2: set T): set T :=
  match l1 with
    [] => []
  |x::l => if set_In_dec x l2 then x::set_inter l l2 else set_inter l l2
  end.

Lemma set_inter_iff x l1 l2: set_In x (set_inter l1 l2) <-> set_In x l1 /\ set_In x l2.
Proof.
  induction l1; simpl; intros; auto; try tauto.
  destruct (set_In_dec a l2); simpl; rewrite IHl1; clear IHl1.
  destruct (eq_dec x a); subst; auto; try tauto.
  destruct (eq_dec x a); subst; auto; try tauto.
Qed.

Fixpoint remove x (l: set T): set T :=
  match l with
    [] => []
  |y::l' => if eq_dec x y then remove x l' else y::remove x l'
  end.

Lemma in_remove (l : set T) x y: set_In x (remove  y l) -> set_In x l /\ x <> y.
Proof.
  induction l; simpl; intros; auto.
  destruct (eq_dec y a).
  apply IHl in H.
  tauto.
  simpl in H; destruct H.
  subst x.
  split; now auto.
  apply IHl in H; tauto.
Qed.

Lemma in_in_remove (l : list T) x y: x <> y -> set_In x l -> set_In x (remove y l).
Proof.
  induction l; simpl; intros; auto.
  destruct (eq_dec y a).
  apply IHl.
  tauto.
  subst y.
  destruct H0; auto; tauto.
  simpl.
  destruct H0; auto.
Qed.

End SETS.
