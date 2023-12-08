
let nom = "KUNZE" and prenom = "Tarek" ;;

let p = FAtom("p")
let form1 = FOp(And, p, FNot(FOp(Or, p, FConst(true))))

let rec fm_not f = match f with
  | FNot(a) -> FNot(fm_not a)
  | FAtom(a) -> FNot(FAtom(a))
  | FOp(op, a, b) -> FOp(op, fm_not a, fm_not b)
  | FConst(b) -> FConst(b)
  
let rec eval env form = match form with
  | FNot(a) -> not (eval env a)
  | FAtom(a) -> env a
  | FConst(b) -> b
  | FOp(o, a, b) -> let ea = (eval env a) and eb = (eval env b) in
      match o with
      | And -> ea && eb
      | Or -> ea || eb 
              
let simpl_not form = match form with
  | FNot(FNot(a)) -> a
  | FNot(FConst(a)) -> FConst(not a)
  | _ -> form 
    
let rec simpl_and form = match form with
  | FOp(And, FAtom(a), FAtom(b)) -> 
      if a = b then FAtom(a) 
      else form
  | FOp(And, FAtom(a), FConst(b)) -> 
      if b then FAtom(a) else FConst(false) 
  | FOp(And, FConst(a), FAtom(b)) ->
      if a then FAtom(b) else FConst(false)
  | FOp(op, a, b) -> FOp(op, simpl_and a, simpl_and b)
  | _ -> form
    
let rec simpl_or form = match form with
  | FOp(Or, FAtom(a), FAtom(b)) -> 
      if a = b then FAtom(a) 
      else form
  | FOp(Or, FAtom(a), FConst(b)) -> 
      if b then FConst(true) else FAtom(a)
  | FOp(Or, FConst(a), FAtom(b)) -> 
      if a then FConst(true) else FAtom(b)
  | FOp(op, a, b) -> FOp(op, simpl_and a, simpl_and b)
  | _ -> form
    
    

let rec simplify form = match form with
  | FNot(a) -> simpl_not (FNot(simplify a))
  | FOp(op, a, b) -> (match op with
      | And -> simpl_and (FOp(And, simplify a, simplify b)) 
      | Or -> simpl_or (FOp(Or, simplify a, simplify b)) )
  | _ -> form

    
(* Arbres n-aires *)

let args op f = match f with
  | NOp(iop, lst) -> 
      if iop <> op 
      then f :: []
      else lst
  | _ -> f :: []


(*let rec flatten *)

let is_atom f = match f with
  | NAtom(_) -> true
  | _ -> false


(* let is_not_of p f = match f with *)

let rec is_op_of op p f = match op with
  | And -> (match f with
      | NOp(iop, []) -> true
      | NOp(iop, hd :: tl) -> iop = And && p hd && (is_op_of op p (NOp(iop, tl)))
      | _ -> false
    )
  | Or  -> (match f with
      | NOp(iop, []) -> false
      | NOp(iop, hd :: tl) -> iop = Or && p hd || (is_op_of op p (NOp(iop, tl))) 
      | _ -> false
    ) 
