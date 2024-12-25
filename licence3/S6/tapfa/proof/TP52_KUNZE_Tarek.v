(* Auteur(s) du devoir maison :
   NOM: Kunze
   Prénom: Tarek
 *)

(* UPS - L3 Info - UE TAPFA - DM Coq

Ce sujet a pour but de définir et vérifier deux optimisations simples
qui pourraient être effectuée dans une chaîne de compilation.

Le fichier est long, mais une bonne partie de la solution est fournie,
et seules les 10 premières preuves font partie du travail requis, les
autres "Admitted" étant laissés en bonus.

Ce devoir est à rendre sur Moodle avant le dimanche 2 mai 23h59.

Il doit s’effectuer en monôme ou en binôme.

Vous devrez déposer votre code Coq sous la forme d’un fichier texte
nommé

TPXY_NOM.v ou TPXY_NOM1_NOM2.v

(c'est-à-dire TPXY dans le cas où le premier auteur est dans le groupe
de TP X.Y + nom de famille de l'auteur ou des auteurs du devoir +
extension de fichier .v)

Dans le cas d'un binôme, un seul dépôt devra être fait.

Tout *échange de code* entre différents monômes/binômes est interdit
et sera sanctionné. Lors de la correction, des outils de mesure de
similarité de code seront utilisés.

Votre fichier devra commencer par un commentaire entre (* ... *)
précisant le NOM et le Prénom de l’auteur ou des auteurs du DM.

En cas de question sur le DM, vous privilégieriez l'utilisation du
salon Discord #tapfa-tp-général à l'envoi d'un e-mail à votre
enseignant de TP.

Avant de déposer votre fichier, veuillez remplir dès que possible le
formulaire de déclaration d'équipe dont le lien est situé juste
au-dessus du dépôt sur la page Moodle.

Remarque 1 : Tout commentaire utile (concernant les difficultés
rencontrées ou expliquant la solution) pourra être inséré entre (*
... *) à proximité de la fonction ou de la preuve.

Remarque 2 : l'intégralité du fichier .v doit être accepté par Coq
(coloré en bleu en utilisant le raccourci ProofGeneral "C-c C-b") !
l'évaluation s'arrêtera à la première erreur rencontrée (mais
l'utilisation de commentaires est bien sûr possible pour masquer les
parties qui ne compileraient pas).

Remarque 3 : vous avez le droit d'utiliser toutes les tactiques vues
en Cours, en TP (ou dans la doc. de Coq) mais ne devez pas ajouter
d'axiomes.

Remarque 4 : les zones à compléter sont signalées par un TODO

Remarque 5 : pour toutes les preuves terminées, vous remplacerez
Admitted.  par Qed.  *)

From Coq Require Import Lia.
From Coq Require Import Arith.
From Coq Require Import String.

(* On introduit la signature tIDENT contenant la déclaration du type
   Ident servant à nommer les variables contenues dans les
   expressions. On l'instanciera en général avec le type String. Le
   paramètre id_eq indique que l'égalité doit êtrte décidable sur ce
   type, ce qui permet de définir le test d'égalité ieq. Un
   environnement est une fonction associant à chaque identifiant une
   valeur entière. *)
Module Type tIDENT.
  Parameter Ident : Type.
  Parameter id_eq : forall i1 i2 : Ident, {i1=i2}+{i1<>i2}.
  Definition ieq i1 i2 := if id_eq i1 i2 then true else false.
  Definition Env := Ident -> nat.
End tIDENT.

Module ID <: tIDENT.
  Definition Ident := String.string.
  Definition Env := Ident -> nat.
  Definition id_eq := String.string_dec.
  Definition ieq s1 s2 := if id_eq s1 s2 then true else false.
End ID.

(* La signature tEXP est paramétrée par un tIDENT. Elle définit le
   type Exp des expressions. Une expression peut être évaluée dans un
   environnement. Parmi les expressions, on distigue les expressions
   constantes et on peut déterminer si une variable est libre, cad si
   elle apparait dans une expression. Ces fonctions sont caractérisées
   par 2 propriétés importantes :
   - l'évaluation d'une expression dans deux environnements associant
   les mêmes valeurs aux variables libres donne le même résultat
   - l'évaluation d'une expression constante donne la même valeur
   quelque soit l'environnement.  *)
Module Type tEXP (ID : tIDENT).
  Parameter Exp : Type.
  Parameter eval : ID.Env -> Exp -> nat.
  Parameter isConst : Exp -> bool.
  Parameter free_var : ID.Ident -> Exp -> bool.
  Axiom eval_free : forall exp env1 env2,
      (forall i, free_var i exp = true -> env1 i = env2 i) ->
      eval env1 exp = eval env2 exp.
  Axiom eval_const :
    forall e env1 env2, isConst e = true -> eval env1 e = eval env2 e.
End tEXP.

(* La signature eTRANSFO introduit la notion de transformation
   d'expressions. Une transformation est correcte si l'évaluation
   d'une expression et de sa transformée donnent le même résultat dans
   tout environnement. *)
Module Type eTRANSFO (ID : tIDENT) (E : tEXP ID).
  Parameter tr : E.Exp -> E.Exp.
  Definition etrans_OK tr := forall env e, E.eval env e = E.eval env (tr e).
  Axiom tr_OK : etrans_OK tr.
End eTRANSFO.

(* Définir le module EXP (ID) respectant la signature tEXP ID sachant
   qu'une expression est soit une variable (prenant un ident en
   paramètre), soit une constante (prenant un nat en paramètre), soit
   la somme de 2 expressions, soit la comparaison (par $\le$) de 2
   expressions. *)
Module EXP(ID : tIDENT) <: tEXP ID.
  Definition Env := ID.Env.
  Inductive _Exp :=
    | Const (c : nat)
    | Var (x : ID.Ident)
    | Add (e1 : _Exp) (e2 : _Exp)
    | Le (e1 : _Exp) (e2 : _Exp).
  Definition Exp := _Exp.

  (* Définir la fonction isConst renvoyant true ssi l'expression ne
     contient pas de variables *)
  Fixpoint isConst (e : Exp) : bool :=
    match e with
      | Const _ => true
      | Var _ => false
      | Add a b => isConst a && isConst b
      | Le a b => isConst a && isConst b
    end.

  (* Définir la fonction eval. On utilisera <=? : nat->nat->bool pour
     comparer des entiers (l'évaluation de la comparaison de exp1 et
     exp2 doit retourner 1 si exp1 s'évalue à une valeur inférieure
     ou égale à exp2 et 0 sinon). *)
  Fixpoint eval (env : ID.Env) (e : Exp) : nat :=
    match e with
      | Const n => n
      | Var x => env x
      | Add a b => eval env a + eval env b
      |Le a b => if eval env a <=? eval env b then 1 else 0
    end.

  (* Démontrer le lemme suivant :
     - on procédera par induction sur e.
     - après simplifications, on utilisera Bool.andb_true_iff
     - discriminate permet de prouver un but lorsqu'une hypothèse
       contient une égalité entre 2 constructeurs différents
     - destruct permet de casser une conjonction en hypothèse.
     - quand on tente de réécrire H et qu'on obtient une erreur du type
         Error : Unable to find an instance for the variable env2.
       on peut préciser les paramètres avec rewrite H with param1 param2
       ou simplement rewrite (H param1 param2) *)
  Lemma eval_const :
    forall e env1 env2, isConst e = true -> eval env1 e = eval env2 e.
  Proof.
    (* -intros .. -intros -intros ... *)
    induction e; intros.
    - simpl. reflexivity.
    - discriminate H. (* Hypothese trivialement fausse / jamais atteinte *) (* inversion H. *)
    - simpl in *. (* ANCHOR *)
      rewrite Bool.andb_true_iff in H.
      destruct H as [H1 H2].
      rewrite (IHe1 env1 env2 H1).
      rewrite (IHe2 env1 env2 H2).
      reflexivity.
    - simpl in *.
      rewrite Bool.andb_true_iff in H.
      destruct H as [H1 H2].
      rewrite (IHe1 env1 env2 H1).
      rewrite (IHe2 env1 env2 H2).
      reflexivity.
  Qed.

  (* Définir la fonction mkAdd prenant en argument 2 expressions et
     renvoyant l'expression somme sauf si l'un des argument est la
     constante 0. Dans ce cas, l'autre expression est renvoyée. *)
  Definition mkAdd (e1 e2 : Exp) : Exp :=
    match e1,e2 with
      | Const 0, _ => e2
      | _, Const 0 => e1
      | _, _ => Add e1 e2
    end.

  (* Définir la fonction mkLe prenant en argument deux expressions e1
     et e2 et renvoyant l'expression Le e1 e2 sauf si le résultat peut
     être simplifié (les 2 arguments sont constants ou l'argument de
     gauche est Const 0). *)
  Definition mkLe (e1 e2 : Exp) : Exp :=
    match e1,e2 with
      | Const 0, _ => Const 1
      | Const a, Const b => if a <=? b then Const 1
        else Const 0
      | _, _ => Le e1 e2
    end.

  (* Démontrer le lemme ci-dessous :
     - on fera une preuve par cas (destruct) sur e1 et e2.
     - on fera une preuve par cas pour traiter les constantes (c) *)
  Lemma eval_mkAadd : forall env e1 e2,
      eval env (mkAdd e1 e2) = eval env e1 + eval env e2.
  Proof.
    (* intros. destruct e1, e2. (; auto.) *) 
    (* intros. destruct e1, e2; auto.
    - destruct c, c0; simpl; auto.
    - destruct c. simpl. auto. reflexivity.
    - destruct c. simpl. auto. reflexivity.
    - destruct c. simpl; auto. *)
    intros. destruct e1, e2; auto; destruct c; simpl; auto.
    destruct c, c0; simpl; auto.
  Qed.

  (* Définir la fonction free_var indiquant si la variable x apparait
     dans l'expression e. On utilisera ID.ieq pour comparer les
     identificateurs. On utilisera le OU boléen noté ||. *)
  Fixpoint free_var (x : ID.Ident) (e : Exp) : bool :=
    match e with
      | Const _ => false
      | Var y => ID.ieq y x
      | Add e1 e2 => free_var x e1 || free_var x e2
      | Le e1 e2 => free_var x e1 || free_var x e2
    end.

  (* Démontrer par induction sur exp le lemme suivant (nettement plus
     compliqué que les précédents). *)
  Lemma eval_free : forall exp env1 env2,
      (forall i, free_var i exp = true -> env1 i = env2 i) ->
      eval env1 exp = eval env2 exp.
  Proof.
    intros. induction exp.
    - simpl. reflexivity.
    - simpl. apply H. simpl.
      unfold ID.ieq.
      destruct ID.id_eq. reflexivity. contradiction.
    - simpl.
      rewrite IHexp1, IHexp2.
      reflexivity.
      + intros.
        apply H.
        simpl.
        rewrite Bool.orb_true_iff.
        right. assumption.
      + intros.
        apply H.
        simpl.
        rewrite Bool.orb_true_iff.
        left. assumption.
    - simpl.
      rewrite IHexp1, IHexp2.
      reflexivity.
      + intros.
        apply H.
        simpl.
        rewrite Bool.orb_true_iff.
        right. assumption.
      + intros.
        apply H.
        simpl.
        rewrite Bool.orb_true_iff.
        left. assumption.
  Qed.

End EXP.

(* 1ere transformation : on combine les constantes apparaissant
   dans une addition : 1+x+2+y ==> 3+(x+y) *)
Module MergeCsts (ID : tIDENT).
  Include EXP ID.

  (* définir la fonction getConst renvoyant la somme des constantes
     présentes dans une expression. On renvoie 0 pour une variable ou
     une comparaison. *)
  Fixpoint getConst (e : Exp) : nat :=
    match e with
      | Const n => n
      | Var _ => 0
      | Add e1 e2 => getConst e1 + getConst e2
      | Le e1 e2 => 0
    end.

  (* Définir la fonction remConst remplaçant toutes les constantes
     d'une expression par 0. On appellera mkAdd pour former les sommes
     afin d'éviter de créer des ajouts de 0. Les comparaisons et les
     variables sont inchangées. *)
  Fixpoint remConst (e : Exp) : Exp :=
    match e with
      | Const n => Const 0
      | Var _ => e
      | Add e1 e2 => mkAdd (remConst e1) (remConst e2)
      | Le _ _ => e
    end.

  (* Démontrer par induction sur e le lemme suivant : *)
  Lemma eval_get_rem :
    forall env e, getConst e + eval env (remConst e) = eval env e.
  Proof.
    induction e; auto. 
    simpl. 
    rewrite <- IHe1, <- IHe2, eval_mkAadd.
    lia.
  Qed.

  Definition normalize e := mkAdd (Const (getConst e)) (remConst e).

  Definition tr := normalize.

  Definition etrans_OK tr := forall env e, eval env e = eval env (tr e).

  (* Démontrer le lemme suivant par disjonction de cas sur e.
     On utilisera eval_mkAdd, eval_get_rem et lia *)
  Lemma tr_OK : etrans_OK tr.
  Proof.
    unfold etrans_OK.
    intros.
    induction e; auto.
    - simpl. unfold tr, normalize.
      simpl.
      destruct c.
      + simpl. reflexivity.
      + simpl.  reflexivity.
    - unfold tr. unfold normalize.
      rewrite eval_mkAadd.
      simpl.
      rewrite eval_mkAadd.
      replace (getConst e1 + getConst e2 + 
        (eval env (remConst e1) + eval env (remConst e2))) 
        with ((getConst e1 + eval env (remConst e1)) + (getConst e2 + eval env (remConst e2)))  by lia.
        rewrite eval_get_rem, eval_get_rem.
        reflexivity.
  Qed.

End MergeCsts.

Module Test1.
  Include ID.
  Module Import T_MC := MergeCsts ID.

  Open Scope string_scope.

  (* On définit quelques notations pour pouvoir écrire des expressions
     plus facilement *)
  Existing Class _Exp.
  Coercion Const : nat >-> _Exp.
  (* Dans les lignes ci dessous, remplacer :
     - Var par le nom de votre constructeur pour les variables
     - Le par votre constructeur pour les expression <=
     - Add par votre constructeur pour la somme *)
  Coercion Var : ID.Ident >-> _Exp.
  Notation "e1 #<= e2" := (Le e1 e2) (at level 18, no associativity).
  Notation "e1 #+ e2" := (Add e1 e2) (at level 17, left associativity).

  Definition x := "x" : ID.Ident.
  Definition u := "u" : ID.Ident.
  Definition v := "v" : ID.Ident.
  Definition s := "s" : ID.Ident.

  Definition exp1 := 1 #+ x #+ 2.
  (* équivalent à :
       Definition exp1' := Add (Add (Const 1) (Var "x")) (Const 2). *)

  (* on teste que notre transformation fonctionne correctement *)
  Eval compute in T_MC.tr exp1.

End Test1.

(* Le module paramétré tINST introduit les instructions. Une
   instruction est une affectation, une séquence ou une boucle
   do-while *)
Module Type tINST (ID : tIDENT) (E : tEXP ID).

  Inductive Inst :=
    Assign (id : ID.Ident) (e : E.Exp)
  | Seq (i1 : Inst) (i2:Inst)
  | doWhile (body : Inst) (cnd : E.Exp).

  (* Une instruction établit une relation entre deux environnements
     que l'on note env1 -[inst]-> env2 : l'exécution de inst à partir
     de env1 conduit, si elle se termine, à env2. Elle est définie
     par 4 règles :

              (forall i, i <> id -> env2 i = env1 i)    env2 id = E.eval env1 e
    s_Assign  =================================================================
                                env1 -[Assign id e]-> env2

                 env1 -[e1]-> env   env -[e2]-> env2
    s_Seq        ===================================
                     env1 -[Seq e1 e2]-> env2

       env1 -[bdy]-> env   E.eval env cnd <> 0   env -[doWhile bdy cnd]-> env2
    WT =======================================================================
                   env1 -[doWhile bdy cnd]-> env2

       env1 -[bdy]-> env2   E.eval env2 cnd = 0
    WF ==========================================
             env1 -[doWhile bdy cnd]-> env2

    Cette relation est définie par le prédicat inductif sem ci-dessous. *)
  Inductive sem : Inst -> ID.Env -> ID.Env -> Prop :=
    s_Assign : forall env1 env2 id e,
      (forall i, i <> id -> env2 i = env1 i) -> env2 id = E.eval env1 e ->
      sem (Assign id e) env1 env2
  | s_Seq : forall env1 env env2 e1 e2,
      sem e1 env1 env -> sem e2 env env2 -> sem (Seq e1 e2) env1 env2
  | s_doWhileT : forall env1 env env2 cnd bdy,
      sem bdy env1 env -> E.eval env cnd <> 0 -> sem (doWhile bdy cnd) env env2 ->
      sem (doWhile bdy cnd) env1 env2
  | s_doWhileF : forall env1 env env2 cnd bdy,
      sem bdy env1 env -> E.eval env cnd = 0 -> (forall i, env i = env2 i) ->
      sem (doWhile bdy cnd) env1 env2.

  (* Une transformation est correcte si elle préserve la sémantique de
     l'instruction transformée.  *)
  Definition itrans_OK tr := forall i env1 env2, sem i env1 env2 <-> sem (tr i) env1 env2.

End tINST.

(* Le module INST satisfait la spécification tINST en reprenant
   exactement les mêmes définitions. *)
Module INST (ID : tIDENT) (E : tEXP ID).
  Inductive Inst :=
    Assign (id : ID.Ident) (e : E.Exp)
  | Seq (i1 : Inst) (i2:Inst)
  | doWhile (body : Inst) (cnd : E.Exp).

  Inductive sem : Inst -> ID.Env -> ID.Env -> Prop :=
    s_Assign : forall env1 env2 id e,
      (forall i, i <> id -> env2 i = env1 i) -> env2 id = E.eval env1 e ->
      sem (Assign id e) env1 env2
  | s_Seq : forall env1 env env2 e1 e2,
      sem e1 env1 env -> sem e2 env env2 -> sem (Seq e1 e2) env1 env2
  | s_doWhileT : forall env1 env env2 cnd bdy,
      sem bdy env1 env -> E.eval env cnd <> 0 -> sem (doWhile bdy cnd) env env2 ->
      sem (doWhile bdy cnd) env1 env2
  | s_doWhileF : forall env1 env env2 cnd bdy,
      sem bdy env1 env -> E.eval env cnd = 0 -> (forall i, env i = env2 i) ->
      sem (doWhile bdy cnd) env1 env2.

  Definition itrans_OK tr := forall i env1 env2, sem i env1 env2 <-> sem (tr i) env1 env2.

End INST.

(* Ce module paramétré définit une 2eme transformation consistant à
   extraire des boucles les affectations par des constantes dans
   certains cas. Par exemple :
     do x := 1; y := y+x; while y < 10
   devient
     x := 1; do y := y+x; while y < 10 *)

Module EXTRACT_CONST (ID : tIDENT) (E : tEXP ID) (INS : tINST ID E).
  Include INS.

  (* Définir la fonction assigned_var indiquant si la variable x
     apparait ç gauche d'une affectation dans l'instruction i. On
     utilisera ID.ieq pour comparer les identificateurs. On utilisera
     le OU boléen noté || .  *)
  Fixpoint assigned_var (x : ID.Ident) (i : Inst) : bool :=
    match i with
      | Assign y _ => ID.ieq y x
      | Seq p1 p2 => assigned_var x p1 || assigned_var x p2
      | doWhile p _ => assigned_var x p
    end.

  (* Définir la fonction free_or_assigned_var indiquant si la variable
     x apparait dans l'instruction i. On utilisera ID.ieq pour
     comparer les identificateurs. On utilisera le OU boléen noté || .*)
  Fixpoint free_or_assigned_var (x : ID.Ident) (i : Inst) : bool :=
    match i with
      | Assign y b => ID.ieq y x || E.free_var x b
      | Seq p1 p2 => free_or_assigned_var x p1 || free_or_assigned_var x p2
      | doWhile p c => free_or_assigned_var x p || E.free_var x c
    end.

 (* Cela permet de définir une transformation de programme permettant
    de faire sortir les affectations d constantes des boucles.
    Par exemple, le programme suivant
      x := 0;
      s := 0;
      do
        u := 1 #+ 1;
        s := s #+ x;
        x := u #+ x
      while x #<= 10.
    sera transformé en
      u := 1 #+ 1;
      x := 0;
      s := 0;
      do
        s := s #+ x;
        x := u #+ x
      while x #<= 10 *)
  Fixpoint extract_const (i : Inst) :=
    match i with
      Assign _ _ => i
    | Seq i1 i2 =>
      match extract_const i2 with
        Seq (Assign y e) i2' =>
        if E.isConst e then
          if free_or_assigned_var y i1 then i
          else Seq (Assign y e) (Seq i1 i2')
        else
          match extract_const i1 with
            Seq i1 i1' => Seq i1 (Seq i1' i2)
          | _ => i
          end
      | _ =>
        match extract_const i1 with
          Seq i1 i1' => Seq i1 (Seq i1' i2)
        | _ => i
        end
      end
    | doWhile body cnd =>
      match extract_const body with
        Seq (Assign x e) body' =>
        if (E.free_var x cnd || assigned_var x body' || negb (E.isConst e))%bool then i
        else Seq (Assign x e) (doWhile body' cnd)
      | _ => i
      end
    end.

  (* montrer par induction sur i *)
  Lemma assigned_free_or_assigned : forall x i,
      assigned_var x i = true -> free_or_assigned_var x i = true.
  Proof.
    induction i; intros.
    - simpl.
      apply Bool.orb_true_iff.
      left. exact H.
    - simpl. rewrite Bool.orb_true_iff.
      simpl in H. rewrite Bool.orb_true_iff in H.
      destruct H.
      + auto. (* left. apply (IHi1 H) *)
      + auto.
    - simpl. rewrite Bool.orb_true_iff.
      left. apply IHi. exact H.
  Qed.

  (* On peut montrer que la mise en séquence est associative.
     - Pour prouver un but de la forme "prop1 <-> prop2", on utilisera
       la tactique "split."
     - Pour détruire les hypothèses de la forme
         H : sem ... env1 env2
       on pourra utiliser la tactique "inversion_clear H." *)
  Lemma Seq_assoc : forall i1 i2 i3 env1 env2,
      sem (Seq i1 (Seq i2 i3)) env1 env2 <-> sem (Seq (Seq i1 i2) i3) env1 env2.
  Proof.
    intros; split; intros.
    (* - inversion H. subst. *)
    - inversion_clear H.
      inversion_clear H1.
      apply (s_Seq _ env3 _).
      + apply (s_Seq _ env _). apply H0. apply H.
      + apply H2.
    - inversion_clear H.
      inversion_clear H0.
      apply (s_Seq _ env3 _).
      + apply H.
      + apply (s_Seq _ env _).
        apply H2.
        apply H1.
        
  Qed.

  Lemma Seq_compat_l : forall i1 i2,
      (forall env1 env2, sem i1 env1 env2 <-> sem i2 env1 env2) ->
      forall i3 env1 env2,
        sem (Seq i1 i3) env1 env2 <-> sem (Seq i2 i3) env1 env2.
  Proof.
    intros; split; intros.
    - inversion_clear H0.
      apply (s_Seq _ env).
      + rewrite <- H. apply H1.
      + apply H2.
    - inversion_clear H0.
      apply (s_Seq _ env).
      + rewrite H. apply H1.
      + apply H2.
  Qed.

  Lemma Seq_compat_r : forall i1 i2,
      (forall env1 env2, sem i1 env1 env2 <-> sem i2 env1 env2) ->
      forall i3 env1 env2,
        sem (Seq i3 i1) env1 env2 <-> sem (Seq i3 i2) env1 env2.
  Proof.
    intros; split; intros.
    - inversion_clear H0.
      apply (s_Seq _ env).
      + apply H1.
      + rewrite <- H. apply H2.
    - inversion_clear H0.
      apply (s_Seq _ env).
      + apply H1.
      + rewrite H. apply H2.
  Qed.

  (* On peut dupliquer une affectation de constante. *)
  Lemma Assign_dupl_const : forall x e env1 env2, E.isConst e = true ->
      sem (Assign x e) env1 env2 <->
      sem (Seq (Assign x e) (Assign x e)) env1 env2.
  Proof.
    intros; split; intros.
    - apply (s_Seq _ env2).
      + apply H0.
      + apply s_Assign.
        reflexivity.
        inversion_clear H0. 
        rewrite (E.eval_const _ env2 env1). apply H2. apply H. 
    - apply s_Assign.
      + inversion_clear H0.
        inversion_clear H1.
        inversion_clear H2.
        intros.
        rewrite (H1 i H2).
        apply (H0 i H2).
      + inversion_clear H0.
        inversion_clear H2.
        rewrite (E.eval_const _ env1 env2); auto.
        rewrite (E.eval_const _ env2 env); auto.
  Qed.

(**********************************************************************)
(* Fin de la partie attendue,                                         *)
(* les lemmes suivant constituent des questiosn bonus.                *)
(**********************************************************************)

  (* Question bonus. On procédera par induction sur l'hypothèse
     (sem i env1 env2). *)
  Lemma not_assigned : forall i env1 env2,
      sem i env1 env2 ->
      forall id, assigned_var id i = false -> env2 id = env1 id.
  Proof.
    (* TODO *)
  Admitted.

  (* Les trois preuves suivantes sont plus longue, on les donne. *)
  Lemma sem_free_or_assigned : forall env1 env2 env1' env2' i,
      (forall x, free_or_assigned_var x i = true -> env1 x = env1' x) ->
      (forall x, assigned_var x i = true -> env2' x = env2 x) ->
      (forall x, assigned_var x i = false -> env2' x = env1' x) ->
      sem i env1 env2 -> sem i env1' env2'.
  Proof.
    intros env1 env2 env1' env2' i H1 H2 H3 H4.
    revert env1' env2' H1 H2 H3.
    induction H4; intros env1' env2'; simpl; intros H1 H2 H3.
    - apply s_Assign.
      + intros x Hx.
        rewrite H3; auto.
        unfold ID.ieq; destruct (ID.id_eq x id); auto; tauto.
      + rewrite H2.
        * rewrite H0.
          apply E.eval_free.
          intros x Hx.
          apply H1.
          rewrite Hx.
          now rewrite Bool.orb_comm.
        * unfold ID.ieq; destruct (ID.id_eq id id); auto; tauto.
    - apply (s_Seq _ (fun x => if assigned_var x e1 then env x else env1' x)).
      + apply IHsem1; intros x Hx.
        * apply H1.
          now rewrite Hx.
        * now rewrite Hx.
        * now rewrite Hx.
      + apply IHsem2; intros x Hx.
        * case_eq (assigned_var x e1); intros Hx'; auto.
          rewrite (not_assigned _ _ _ H4_ _ Hx').
          apply H1.
          rewrite Hx.
          now rewrite Bool.orb_comm.
        * apply H2.
          rewrite Hx.
          now rewrite Bool.orb_comm.
        * case_eq (assigned_var x e1); intros Hx'.
          -- rewrite <-(not_assigned _ _ _ H4_0 _ Hx).
             apply H2.
             now rewrite Hx'.
          -- apply H3.
             rewrite Hx.
             now rewrite Hx'.
    - apply (s_doWhileT _ (fun x => if assigned_var x bdy then env x else env1' x)).
      + apply IHsem1; intros x Hx.
        * apply H1.
          now rewrite Hx.
        * now rewrite Hx.
        * now rewrite Hx.
      + rewrite (E.eval_free _ _ env); auto; intros x Hx.
        case_eq (assigned_var x bdy); intro Hx'; auto.
        rewrite (not_assigned _ _ _ H4_ _ Hx').
        rewrite H1; auto.
        rewrite Hx.
        now rewrite Bool.orb_comm.
      + apply IHsem2; simpl; intros x Hx.
        * case_eq (assigned_var x bdy); auto; intro Hx'.
          rewrite (not_assigned _ _ _ H4_ _ Hx').
          now rewrite (H1 _ Hx).
        * now apply H2.
        * rewrite Hx.
          now apply H3.
    - apply s_doWhileF with (env:=env2').
      + apply IHsem; intros x Hx; auto.
        * apply H1.
          now rewrite Hx.
        * apply H2 in Hx.
          rewrite Hx.
          symmetry; now apply H0.
      + rewrite (E.eval_free _ _ env); auto; intros x Hx.
        case_eq (assigned_var x bdy); intro Hx'.
        -- apply H2 in Hx'.
           rewrite H0; now symmetry.
        -- rewrite H3; auto.
           rewrite (not_assigned _ _ _ H4 _ Hx').
           rewrite <-H1; auto.
           rewrite Hx.
           now rewrite Bool.orb_comm.
      + intro; symmetry.
        reflexivity.
  Qed.

  Lemma Seq_perm : forall i x e,
      free_or_assigned_var x i = false -> E.isConst e = true ->
      forall env1 env2,
        sem (Seq i (Assign x e)) env1 env2 <->
        sem (Seq (Assign x e) i) env1 env2.
  Proof.
    intros i x e Hx He env1 env2; split; intro H; inversion_clear H.
    - apply (s_Seq _ (fun y => if ID.ieq y x then E.eval env1 e else env1 y)).
      + apply s_Assign.
        * intros y.
          unfold ID.ieq; destruct (ID.id_eq y x); intro; auto; try tauto.
        * unfold ID.ieq; destruct (ID.id_eq x x); auto; try tauto.
      + inversion_clear H1.
        apply (sem_free_or_assigned env1 env); auto.
        * intros y.
          unfold ID.ieq; destruct (ID.id_eq y x); intro; auto; try tauto.
          subst y.
          rewrite Hx in H1; discriminate.
        * intros y Hy.
          case (ID.id_eq y x).
          -- intros Hyx.
             rewrite Hyx in Hy.
             rewrite (assigned_free_or_assigned _ _ Hy) in Hx.
             discriminate.
          -- apply H.
        * intros y Hy.
          unfold ID.ieq; destruct (ID.id_eq y x); auto; try tauto.
          -- subst y.
             rewrite H2.
             now apply E.eval_const.
          -- rewrite H; auto.
             apply (not_assigned _ _ _ H0 _ Hy).
    - apply (s_Seq _ (fun y => if ID.ieq y x then env1 x else env2 y)).
      + inversion_clear H0.
        apply (sem_free_or_assigned env env2); auto.
        * intros y.
          case (ID.id_eq y x); auto.
          intros Hyx.
          rewrite Hyx.
          rewrite Hx.
          discriminate.
        * intros y Hy.
          unfold ID.ieq; destruct (ID.id_eq y x); auto; try tauto.
          subst y.
          rewrite (assigned_free_or_assigned _ _ Hy) in Hx.
          discriminate.
        * intros y Hy.
          unfold ID.ieq; destruct (ID.id_eq y x); auto; try tauto.
          -- now subst y.
          -- rewrite (not_assigned _ _ _ H1 _ Hy).
             now apply H.
      + apply s_Assign.
        * intros y Hy.
          unfold ID.ieq; destruct (ID.id_eq y x); auto; try tauto.
        * simpl.
          inversion_clear H0.
          rewrite E.eval_const with (env2:=env1); auto.
          rewrite <-H2.
          revert Hx.
          intros Hx.
          apply (not_assigned i); auto.
          case_eq (assigned_var x i); auto.
          intros Ha.
          now rewrite <-(assigned_free_or_assigned _ _ Ha).
  Qed.

  Lemma DoWhile_extract : forall x e bdy bdy' cnd,
      E.isConst e = true ->
      E.free_var x cnd = false ->
      assigned_var x bdy' = false ->
      (forall env1 env2 : ID.Env,
          sem bdy env1 env2 <-> sem (Seq (Assign x e) bdy') env1 env2) ->
      forall env1 env2,
        sem (doWhile bdy cnd) env1 env2 <->
        sem (Seq (Assign x e) (doWhile bdy' cnd)) env1 env2.
  Proof.
    intros x e bdy bdy' cnd He Hx Hx' Hbdy env1 env2.
    split.
    - intro H.
      cut (match doWhile bdy cnd, doWhile bdy' cnd with
           | doWhile bdy1 cnd1, doWhile bdy2 cnd2 =>
             cnd1 = cnd2 /\ E.free_var x cnd2 = false
             /\ assigned_var x bdy2 = false
             /\ forall env1 env2, sem bdy1 env1 env2
                                  <-> sem (Seq (Assign x e) bdy2) env1 env2
           | _, _ => False
           end); [|simpl; do 2 split; auto].
      clear Hx Hx' Hbdy.
      revert H.
      set (w := doWhile bdy cnd).
      set (w' := doWhile bdy' cnd).
      clearbody w w'.
      clear bdy bdy' cnd.
      intros H.
      revert w'.
      induction H; intros w'; try now intros H'; destruct H'.
      + destruct w'; try now intros H'; destruct H'.
        intros H2.
        specialize (IHsem2 (doWhile w' cnd0) H2).
        destruct H2 as [H3 [H4 [H5 H6]]].
        subst cnd0.
        inversion_clear IHsem2.
        clear IHsem1.
        apply H6 in H; clear H6.
        assert (H' : sem (Seq (Assign x e) w') env1 env3).
        { refine (sem_free_or_assigned _ _ env1 env3 _ _ _ _ H);
            intros y Hy; auto.
          2:{ transitivity (env y).
              2:{ now revert Hy; apply not_assigned. }
              apply (not_assigned _ _ _ H2).
              simpl in Hy |- *.
              apply (Bool.orb_false_elim _ _ Hy). }
          case_eq (assigned_var y (Assign x e)).
          2:{ now intros Hy'; apply (not_assigned _ _ _ H2). }
          simpl; unfold ID.ieq.
          case ID.id_eq; intros Hyx Hb; try discriminate.
          rewrite Hyx.
          inversion_clear H2.
          rewrite H7.
          inversion_clear H.
          rewrite (not_assigned _ _ _ H8 _ H5).
          inversion_clear H2.
          rewrite H9.
          now apply E.eval_const. }
        inversion_clear H'.
        apply (s_Seq _ env4); auto.
        apply (s_doWhileT _ env3); auto.
        assert (H_env3_env : forall i : ID.Ident, E.free_var i cnd = true ->
                                                  env3 i = env i).
        { intros y _.
          inversion_clear H2.
          case (ID.id_eq y x); intros Hyx; auto.
          rewrite Hyx.
          rewrite H9.
          inversion_clear H.
          rewrite (not_assigned _ _ _ H10 _ H5).
          inversion_clear H2.
          rewrite H11.
          now apply E.eval_const. }
        now rewrite (E.eval_free _ _ _ H_env3_env).
      + destruct w'; try now intros H'; destruct H'.
        intros H2.
        destruct H2 as [H3 [H4 [H5 H6]]].
        subst cnd0.
        clear IHsem.
        apply H6 in H; clear H6.
        inversion_clear H.
        apply (s_Seq _ env3); auto.
        apply s_doWhileF with (env:=env); now auto.
    - intros H.
      inversion_clear H.
      revert H0.
      cut (match doWhile bdy' cnd, doWhile bdy cnd with
           | doWhile bdy2 cnd2, doWhile bdy1 cnd1 =>
             cnd1 = cnd2 /\ E.free_var x cnd2 = false
             /\ assigned_var x bdy2 = false
             /\ forall env1 env2, sem bdy1 env1 env2
                                  <-> sem (Seq (Assign x e) bdy2) env1 env2
           | _, _ => False
           end); [|simpl; do 2 split; auto].
      clear Hx Hx' Hbdy.
      revert H1.
      set (w := doWhile bdy cnd).
      set (w' := doWhile bdy' cnd).
      clearbody w w'.
      clear bdy bdy' cnd.
      intros H.
      revert w env1.
      induction H; intros; try tauto; try now intros H'; destruct H'.
      + destruct w; try tauto; try now intros H'; destruct H'.
        specialize (IHsem2 (doWhile w cnd0)).
        simpl in IHsem2.
        assert (Hs := fun env1 => IHsem2 env1 H2).
        clear IHsem2 IHsem1.
        destruct H2 as [H4 [H5 [H6 H7]]].
        subst cnd0.
        apply (s_doWhileT _ env); auto.
        * apply H7; clear H7.
          now apply (s_Seq _ env1).
        * apply Hs.
          apply s_Assign; auto.
          simpl.
          inversion_clear H3.
          rewrite E.eval_const with (env2:=env) in H4; auto; rewrite <-H4.
          apply (not_assigned bdy _ _ H x).
          destruct (assigned_var x bdy); auto.
      + destruct w; try tauto; try now intros H'; destruct H'.
        destruct H2 as [H4 [H5 [H6 H7]]].
        subst cnd0.
        apply s_doWhileF with (env:=env); auto.
        apply H7; clear H7.
        apply s_Seq with (env:=env1); now auto.
  Qed.

  (* Équipés de ces lemmes, on devrait maintenant pouvoir prouver la
     correction de notre transformation. *)
  (* (Question bonus) *)
  Theorem extract_const_correct : itrans_OK extract_const.
  Proof.
    unfold itrans_OK.
    (* TODO *)
  Admitted.

End EXTRACT_CONST.

Module Test2.
  Include Test1.
  Module T_INST := INST ID T_MC.
  Module T_EXTR := EXTRACT_CONST ID T_MC T_INST.
  Include T_INST.

  Notation "i1 ; i2" := (Seq i1 i2) (at level 21, left associativity).
  Notation "v ':=' e" := (Assign v e) (at level 20, no associativity).
  Notation "'do' i 'while' c" := (doWhile i c) (at level 19, no associativity).

  Definition prog1 :=
    x := 0;
    s := 0;
    do
      u := 1 #+ 1;
      s := s #+ x;
      x := u #+ x
    while x #<= 10.

  (* On peut enfin tester. *)
  Eval compute in T_EXTR.extract_const prog1.
End Test2.

(* Le module iTRANSFO applique une simplification d'expressions
   définie dans son paramètre TR à toutes les expressions présentes
   dans une instruction. *)
Module iTRANSFO(ID : tIDENT) (E : tEXP ID) (TR : eTRANSFO ID E) (INS : tINST ID E).
  Include INS.

  (* Définir la fonction apply_etr appliquant la simplification TR.tr
     à toutes les expressions présentes dans i. *)
  Fixpoint apply_etr (i : Inst) : Inst :=
    match i with
      (* TODO a compléter *)
    end.

  (* Démontrer le lemme apply_OK.
     Le squelette de la preuve est donné.
     Supprimer le admit (et changer le Admitted final en Qed). *)
  Lemma apply_OK : itrans_OK apply_etr.
  Proof.
  unfold TR.etrans_OK, itrans_OK; intros.
  split; intro.
  - induction H; simpl; intros; auto.
    * apply s_Assign; auto.
      admit.    (* TODO *)
    * apply s_Seq with (env:=env); auto.
    * apply s_doWhileT with (env:=env); auto.
      admit.    (* TODO *)
    * apply s_doWhileF with (env:=env); auto.
      admit.    (* TODO *)
  - revert H; set (i1 := apply_etr i); intro.
    assert (i1 = apply_etr i) by reflexivity; clearbody i1.
    revert i H0; induction H; simpl; intros; auto.
    * destruct i; try discriminate.
      simpl in H1.
      injection H1; clear H1; intros; subst.
      admit.    (* TODO *)
    * destruct i; try discriminate.
      simpl in H1.
      injection H1; clear H1; intros; subst.
      apply s_Seq with (env:=env); auto.
    * destruct i; try discriminate.
      simpl in H2.
      injection H2; clear H2; intros; subst.
      apply s_doWhileT with (env:=env); auto.
      admit.    (* TODO *)
    * destruct i; try discriminate.
      simpl in H2.
      injection H2; clear H2; intros; subst.
      apply s_doWhileF with (env:=env); auto.
      admit.    (* TODO *)
  Admitted.

End iTRANSFO.

Module Test3.
  Include Test2.
  Module T_ITR := iTRANSFO ID T_MC T_MC T_INST.

  Theorem apply_norm_OK : T_ITR.itrans_OK T_ITR.apply_etr.
  Proof.
    apply T_ITR.apply_OK.
  Qed.

  (* on peut tester *)
  Eval compute in T_ITR.apply_etr prog1.
End Test3.
