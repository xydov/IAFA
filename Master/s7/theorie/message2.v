(************************************************************)
(*                                                          *)
(* This tutorial is for two slots/weeks (i.e., 2 * 2 hours) *)
(*                                                          *)
(************************************************************)

Require Import Lia.
Require Import Strings.String Nat Lists.List.
Import ListNotations.

Local Open Scope string_scope.

Module EXP.

(* We define the inductive type of expressions. An expression is a
   variable, a constant, a sum, a subtraction or a conditional
   expression. *)
Inductive exp : Type :=
  | Var (n : string)
  | Const (c : nat)
  | Add (e1 e2 : exp)
  | Sub (e1 e2 : exp)
  | IfThen (c e1 e2 : exp).

(* Encoding variables a and b as exp. *)
Definition A := Var "a".
Definition B := Var "b".

(* Encoding expression (b - (a + 1)) ? a+b : a+3 *)
Definition exp_example :=
  (IfThen (Sub B (Add A (Const 1)))
          (Add A B)
          (Add A (Const 3))).

(* Give the denotational semantics of expressions. It is defined by an
   'eval' function taking as argument an environment (a function
   mapping name of variables to natural integers) and an expression
   and returning the value of the expression (of type 'nat'). We
   assume, as in exp_example, that an expression is true when it is
   nonzero. We'll use a match to test the condition. *)
Fixpoint eval (env : string -> nat) (e : exp) : nat :=
  match e with
  | Var v => env v
  | Const c => c
  | Add e1 e2 => eval env e1 + eval env e2
  | Sub e1 e2 => eval env e1 - eval env e2
  | IfThen e1 e2 e3 =>
      match eval env e1 with
      | 0 => eval env e3
      | _ => eval env e2
      end
  end.

(* An environment mapping variables a and b to 1 and 2. *)
Definition env_example v :=
  match v with
  | "a" => 1
  | "b" => 2
  | _ => 0
  end.

Eval compute in eval env_example exp_example.

(* Example of expression evaluation. *)
Lemma eval_example : eval env_example exp_example = 4.
Proof.
  reflexivity.
Qed.

(* Let us now compile our expressions to our language asm. *)
Inductive asm : Type :=
  | stop
    (* machine halts *)
  | push (c : nat) (cnt : asm)
    (* we push the value 'c' on the stack
       and proceed with the next instruction 'cnt' *)
  | add (cnt : asm)
    (* we replace the two integers on top of the stack by their sum
       and proceed with the next instruction 'cnt' *)
  | sub (cnt : asm)
    (* we replace the two integers on top of the stack by their
       subtraction and proceed with the next instruction 'cnt' *)
  | ifThen (ift iff : asm).
    (* when the top of the stack is 0, we go to iff, otherwise to
       ift. In both cases, the top of the stack is popped. *)

(* A small step transforms the state of the machine represented by the
   pair (stk,l) into (stk',l') where stk is an integer stack and l is
   the current instruction. *)

(* Fill in the small step semantics below:
   - rule ssPush: when the instruction is a 'push c l', we add c on
     top of the stack and we proceed with l
   - rule ssAdd: when the instruction is a 'add l' and the stack
     contains at least two elements, we replace them by their sum and
     proceed with l
   - rule ssSub: when the instruction is a 'sub l' and the stack
     contains at least two elements, we replace them by their
     subtraction and proceed with l
   - rule ssI: whe the instruction is a 'ifThen l1 l2' and the top of
     the stack is >0, we pop it and proceed with l1, otherwise l2.  We
     can express this rule with two constructors or with a single
     constructor embedding a test (via match ... end) on the value on
     top of the stack. *)
Inductive smallStep : (list nat * asm) -> (list nat * asm) -> Prop :=
  | ssPush : forall c stk l, smallStep (stk, push c l) (c :: stk, l)
  | ssAdd : forall e1 e2 stk l, smallStep (e1 :: e2 :: stk, add l) ((e1 + e2) :: stk, l)
  | ssSub : forall e1 e2 stk l, smallStep (e1 :: e2 :: stk, sub l) ((e1 - e2) :: stk, l)
  | ssItt : forall c stk l1 l2, smallStep (S c :: stk, ifThen l1 l2) (stk, l1)
  | ssIff : forall stk l1 l2, smallStep (0 :: stk, ifThen l1 l2) (stk, l2).

(* A big step transforms the stack stk into stk' after executing the
   code l. It is a sequence of small steps until the machine halts. *)

(* Fill in the big step semantics below:
   - rule bsStop: when the instruction is a stop, the stack is
     unchanged
   - rule bsStep: when a small step transforms (stk, l) into (stk',
     l') and when the big step semantics of stk' and l' is stk'', then
     the big step semantics of stk and l is stk''. *)
Inductive bigStep : list nat -> asm -> list nat -> Prop :=
  | bsStop : forall stk, bigStep stk stop stk
  | bsStep : forall stk l stk' l' stk'',
      smallStep (stk, l) (stk', l') -> bigStep stk' l' stk'' ->
      bigStep stk l stk''.

(* Sidenote: we can prove that the semantics of asm is deterministic
   (although we won't use that property below). *)
Lemma smallStep_determinist stk l stk' l' stk'' l'' :
  smallStep (stk, l) (stk', l') ->
  smallStep (stk, l) (stk'', l'') ->
  (stk' = stk'' /\ l' = l'').
Proof.
  intro H; inversion_clear H; intro H2; inversion_clear H2; auto.
Qed.

Lemma bigStep_determinist stk l stk' stk'' :
  bigStep stk l stk' ->
  bigStep stk l stk'' ->
  stk' = stk''.
Proof.
  intro H; elim H.
  - intros stk0 H0; inversion_clear H0; auto.
    inversion_clear H1.
  - intros stk0 l0 stk'0 l' stk''0 H0 H1 IH H2.
    revert H0; inversion_clear H2; intro H4.
    + inversion_clear H4.
    + specialize (smallStep_determinist _ _ _ _ _ _ H0 H4).
      intros [H5 H6].
      apply IH.
      rewrite <-H5, <-H6; auto.
Qed.

(* Let's now compile our expressions toward our asm language. *)

(* Write the compile_cnt function that compiles the expression e in
   the environment env into an asm code. The execution of this code
   will proceed with cnt. *)
Fixpoint compile_cnt (env : string -> nat) (e : exp) (cnt : asm) : asm :=
  match e with
  | Var v => push (env v) cnt
  | Const c => push c cnt
  | Add e1 e2 => compile_cnt env e2 (compile_cnt env e1 (add cnt))
  | Sub e1 e2 => compile_cnt env e2 (compile_cnt env e1 (sub cnt))
  | IfThen c e1 e2 =>
      compile_cnt
        env c
        (ifThen (compile_cnt env e1 cnt) (compile_cnt env e2 cnt))
  end.

Definition compile env e := compile_cnt env e stop.

(* Example of expression compilation. *)
Lemma compile_example :
  compile env_example exp_example =
    push 1 (push 1 (add (push 2 (sub
    (ifThen
       (push 2 (push 1 (add stop)))
       (push 3 (push 1 (add stop)))))))).
Proof.
  reflexivity.
Qed.

(* Let's now prove that our compilation function is correct.

   We may use the 'specialize (H Ha)' tactic to replace an hypothesis
   H : a -> b with b (provided Ha : a). The tactic 'revert H' that is
   the reverse of intro may also come handy. *)
Lemma compile_cnt_correct : forall env e stk cnt stk',
  bigStep (eval env e :: stk) cnt stk' ->
  bigStep stk (compile_cnt env e cnt) stk'.
Proof.
  induction e; intros stk cnt stk'; simpl.
  - apply bsStep.
    apply ssPush.
  - apply bsStep.
    apply ssPush.
  - intro bscnt.
    apply IHe2.
    apply IHe1.
    revert bscnt.
    apply bsStep.
    apply ssAdd.
  - intro bscnt.
    apply IHe2.
    apply IHe1.
    revert bscnt.
    apply bsStep.
    apply ssSub.
  - intro bscnt.
    apply IHe1.
    destruct (eval env e1).
    + specialize (IHe3 _ _ _ bscnt).
      revert IHe3.
      apply bsStep.
      apply ssIff.
    + specialize (IHe2 _ _ _ bscnt).
      revert IHe2.
      apply bsStep.
      apply ssItt.
Qed.

Lemma compile_correct env e : bigStep [] (compile env e) [eval env e].
Proof.
  apply compile_cnt_correct.
  apply bsStop.
Qed.

(* Let's now define an interpret for asm. *)

Inductive Result :=
  | Value (v : nat)   (* the result is an integer *)
  | StackError.  (* a stack error occured *)

(* Define the asm_interp function for a program l starting from a
   stack stk. During the execution of the stop instruction, we'll
   return the value at the top of the stack. The function will return
   StackError when the stack doesn't contain enough values (for
   instance when we try to apply an 'add' instruction on the empty
   stack). *)
Fixpoint asm_interp (stk : list nat) (l : asm) : Result :=
  match l with
  | stop =>
      match stk with
      | [] => StackError
      | v :: _ => Value v
      end
  | push c l' => asm_interp (c :: stk) l'
  | add l' =>
      match stk with
      | e1 :: e2 :: stk' => asm_interp ((e1 + e2) :: stk') l'
      | _ => StackError
      end
  | sub l' =>
      match stk with
      | e1 :: e2 :: stk' => asm_interp ((e1 - e2) :: stk') l'
      | _ => StackError
      end
  | ifThen l1 l2 =>
      match stk with
      | 0 :: stk' => asm_interp stk' l2
      | _ :: stk' => asm_interp stk' l1
      | _ => StackError
      end
  end.

(* Example of expression compilation. *)
Lemma asm_interp_example :
  asm_interp [] (compile env_example exp_example) = Value 4.
Proof.
  reflexivity.
Qed.

(* Let's now prove that our interpret is correct.

   We can use the 'discriminate' tactic to prove the goals with an
   inconsistent hypothesis, like 'StackError = Value _' for instance.
   The 'injection H' tactic enables to deduce v = v' from an
   hypothesis Value v = Value v'. *)
Lemma asm_interp_correct stk l v : asm_interp stk l = Value v ->
  exists stk', bigStep stk l (v :: stk').
Proof.
  revert stk; elim l; clear l; simpl.
  - intros [|v' stk']; [discriminate|].
    intro H; injection H; clear H; intros ->.
    exists stk'; apply bsStop.
  - intros c l IHl stk H0.
    destruct (IHl _ H0) as [stk' IHl'].
    exists stk'.
    revert IHl'; apply bsStep; apply ssPush.
  - intros l IHl [|e1 [|e2 stk]] H0; [discriminate..|].
    destruct (IHl _ H0) as [stk' IHl'].
    exists stk'.
    revert IHl'; apply bsStep; apply ssAdd.
  - intros l IHl [|e1 [|e2 stk]] H0; [discriminate..|].
    destruct (IHl _ H0) as [stk' IHl'].
    exists stk'.
    revert IHl'; apply bsStep; apply ssSub.
  - intros l1 IHl1 l2 IHl2 [|[|c] stk] H0; [discriminate| |].
    + destruct (IHl2 _ H0) as [stk' IHl2'].
      exists stk'.
      revert IHl2'; apply bsStep; apply ssIff.
    + destruct (IHl1 _ H0) as [stk' IHl1'].
      exists stk'.
      revert IHl1'; apply bsStep; apply ssItt.
Qed.

(* Sidenote: we can also prove the converse. *)
Lemma asm_interp_complete stk l v stk' : bigStep stk l (v :: stk') ->
  asm_interp stk l = Value v.
Proof.
  revert stk v stk'; elim l; clear l; simpl.
  - intros stk v stk'.
    intro H; inversion_clear H; auto.
    inversion_clear H0.
  - intros c l IHl stk v stk'.
    intro H; inversion_clear H.
    revert IHl H1; inversion_clear H0; intro IHl.
    apply IHl.
  - intros l IHl stk v stk'.
    intro H; inversion_clear H.
    revert IHl H1; inversion_clear H0; intro IHl.
    apply IHl.
  - intros l IHl stk v stk'.
    intro H; inversion_clear H.
    revert IHl H1; inversion_clear H0; intro IHl.
    apply IHl.
  - intros l1 IHl1 l2 IHl2 stk v stk'.
    intro H; inversion_clear H.
    revert H0 IHl1 IHl2; destruct stk as [|[|c] stk];
      intro H; inversion_clear H; intros IHl1 IHl2.
    + revert H1; apply IHl2.
    + revert H1; apply IHl1.
Qed.

(* ...which enables to prove the following theorem: *)
Lemma asm_interp_compile_correct env e :
  asm_interp [] (compile env e) = Value (eval env e).
Proof.
  specialize (compile_correct env e).
  apply asm_interp_complete.
Qed.

End EXP.
