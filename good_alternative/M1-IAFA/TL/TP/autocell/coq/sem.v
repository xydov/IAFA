Require Import ZArith.
Require Import Coq.ZArith.BinIntDef.
Require Import Coq.ZArith.Zdiv.
Require Import Coq.ZArith.Zcompare.
Require Import ast.

(*
  the type cdom is the semantics domain for the cell array: functions taking as parameters coordinates, the field number and returning a value. Coordinates may be negative as they are relative to the current cell position.
*)
Definition cdom := Z->Z->nat->Z.

(*
  the type rdom is the semantic domain for registers: functions taking as parameter a register number and returning a value.
*)
Definition rdom := nat->Z.

(*
  osem returns the binary function over ints corresponding to each operator
*)
Definition osem o: Z -> Z -> Z :=
  match o with
    OP_ADD => Z.add
  | OP_SUB => Z.sub
  | OP_MUL => Z.mul
  | OP_DIV => Z.div
  | OP_MOD => Z.modulo
  end.

(*
  esem defines the semantics of expressions as a function taking 3 parameters:
- cd: the current contents of the cell array
- rd: the current contents of registers
- e: an expression
It returns the value of the expression:
- the value of a CELL is given by the parameter 'cd'
- the value of a VAR is given by the parameter 'rd'
- the value of a BINOP uses 'osem op'
- the value of NEG e is 1 if the value of e is 0 and conversely. (x ?= y)%Z can be used to compare two integers. e%Z means that the expression e should be parsed as an integer expression. 
 *)

Fixpoint esem (cd: cdom) (rd: rdom) (e:expr): Z :=
  match e with
  | CST c => c
  | NONE => 0%Z
  | todo => 0%Z 
  end.

(*
  bsem defines the semantics of a comparator: a function from ints to bool.
*)
Definition bsem o (x y: Z): bool :=
  match o with
    COMP_EQ => Z.eqb x y
  | COMP_NE => negb (Z.eqb x y)
  | COMP_LT => Z.ltb x y
  | COMP_LE => Z.leb x y
  | COMP_GT => Z.gtb x y
  | COMP_GE => Z.geb x y
  end.

(*
  csem defines the semantics of conditions as a function taking 3 parameters:
- cd: the current contents of the cell array
- rd: the current contents of registers
- c: a condition
It returns the value of the expression:
- the value of COMP o ...  uses 'bsem o'
- the value of NOT a uses 'negb: bool->bool'
- the value of AND ...  uses '&&'
- the value of OR ... uses '||'
 *)

Fixpoint csem (cd: cdom) (rd: rdom) (c:cond): bool :=
  match c with
  | NO_COND  => false
  | todo => false                  
  end.

(*
setr is used to update register values. It takes 3 parameters:
- rd: current register-value map
- r: a register number
- v: a value
It returns the new register-value map. '=?' ca be used to compare register numbers
*)
Definition setr (rd: rdom) (r:nat) (v:Z) : rdom :=
  fun r' => if r =? r' then v else rd r'.

(*
  registers other than the modified one are left unchanged.
'destruct (r =? r') eqn:ne' can be used to make a case distinction.
The lemma 'Nat.eqb_eq' can be applied to use the semantics of '=?'.
*)
Lemma setr_ne: forall rv r r' v, r <> r' ->  setr rv r v r' = rv r'.
Proof.
Admitted.

(* 
   the value of the modified register is the expected value .
uses 'Nat.eqb_neq'
*)
Lemma setr_eq: forall rv r v, setr rv r v r = v.
Proof.
Admitted.

(*
the semantics of statements is defined by two function. ssem_r defined the update of registers while ssem_c defines the updates of the cell array.
*)

(*
  ssem_r is a function taking 3 arguments:
- cd: the current contents of the cell array
- rd: the current contents of the register array
- s : the statement
It returns the updated register array obtained after executing s:
- for SET_VAR, call 'setr' to update register r in rd
- for SEQ, chain two recursive calls
- for IF_THEN, use 'csem' to check the condition, then call recursively 'sem_r' on the corresponding branch.
*)
Fixpoint ssem_r (cd : cdom) (rd: rdom) (s:stmt): rdom :=
  match s with
    NOP => rd
  | SET_CELL f v => rd (* registers are not modified *)
  | todo => rd 
  end.

(*
  ssem_c is a function taking 3 arguments:
- cd: the original contents of the cell array
- ncd: the current contents of fields of the current cell
- rd: the current contents of the register array
- s : the statement
It returns the new contents of the fields of the current cell.
Note that only one cell is updated and that the updated cell is never read: reaing the current cell (at offset 0,0) returns its original value.
- for SET_CELL, use 'setr' to update field f of ncd
- SET_VAR does not change cell fields
- SEQ needs to compute the effect of the first statement on registers (using ssem_r) and on the current cell fields (through a recursive call) before computing the effect of the second statement on current cell fields.
- IF_THEN uses 'csem' to compute the value of the condition, then make a recursive call on the corresponding branch.
*)
Fixpoint ssem_c (cd : cdom) (ncd: nat->Z) (rd: rdom) (s:stmt): (nat->Z) :=
  match s with
    NOP => ncd
  | todo => ncd 
  end.

(*
  if the cell valuations ncd and ncd' agree on field f then valuations still
  agree after the execution of statement s.
  proof by induction on s.
  uses 'eq_nat_dec' to make two cases depending on the value of f
  uses lemmas 'setr_eq' or 'setr_ne'.
*)
Lemma ssem_c_eq: forall s cd ncd ncd' rd f,
    ncd f = ncd' f -> ssem_c cd ncd rd s f = ssem_c cd ncd' rd s f.
Proof.
Admitted.

(* The semantics of a program is a function taking as parameters
   the values of a cell array, the values of registers, the program
   and returning the value of of the fields of the current cell 
*)
Definition psem (cd: cdom) (rd: rdom) (p: prog): nat->Z :=
  ssem_c cd (cd 0%Z 0%Z) rd (snd p).
