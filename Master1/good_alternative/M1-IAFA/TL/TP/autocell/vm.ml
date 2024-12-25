
open Printf
open Quad


type memory = int array								(** (temp, value) list *)
type 'a invoke = 'a -> int -> int -> int -> 'a		(** System call. *)
type vm_state = int * int list * memory				(** pc, stack, memory *)
type 'a state = 'a invoke * 'a 						(** vm_state, karel *)
type prog = quad array


(** Initial number of registers. *)
let init_rnum = 10


(** Increase step when register number is not enough. *)
let rnum_inc = 10


(** Raised if there is an error. *)
exception Error of vm_state * string


(** Create e new VM state.
	@param invoke	Invoke implementation.
	@param state	State for invoke. *)	
let new_state invoke state =
	((0, [], Array.make init_rnum 0), (invoke, state))


(** Calcule la valeur du temporaire dans l'état donné.
	@param state	Etat courant.
	@param temp		Temporaire à consulter.
	@return			Valeur du temporaire. *)
let get state temp =
	let (_, _, mem) = state in
	try
		mem.(temp)
	with Not_found ->
		raise (Error(state, Printf.sprintf "v%d out of register limit" temp))


(** Change la valeur d'un temporaire dans l'état donné.
	@param state	Etat à changer.
	@param temp		Temporaire à changer.
	@param value	Nouvelle valeur du temporaire.
	@return			Nouvel état. *)
let set state temp value =
	let (pc, sp, mem) = state in
	let l = Array.length mem in
	let mem =
		if temp < l then mem else 
		let nmem = Array.make ((temp + rnum_inc) / rnum_inc * rnum_inc) 0 in
		Array.blit mem 0 nmem 0 l; nmem in
	mem.(temp) <- value;
	(pc, sp, mem)


(** Effectue un branchement, c'est-à-dire change le pc avec la cible
	donnée.
	@param state	Etat courant.
	@param target	Adresse du branchement.
	@return			Nouvel état avec branchement effectué. *)
let goto state target =
	let (_, sp, mem) = state in
	(target, sp, mem)


(** Ajoute le PC dans la pile.
	@param state	Etat courant.
	@return			Nouvel état. *)
let push state =
	let (pc, sp, mem) = state in
	(pc, (pc + 1) :: sp, mem)


(** Retire une valeur de la tête de pile.
	@param state	Etat courant.
	@return			(tête de pile, nouvel état) *)
let pop state =
	let (pc, sp, mem) = state in
	match sp with
	| h::t -> (h, (pc, t, mem))
	| _ -> raise (Error ((pc, sp, mem), "too many subprogram returns!"))


(** Passe à l'instruction suivante.
	@param state	Etat à mettre à jour.
	@return			Etat avec PC incrémenté. *)
let next state =
	let (pc, sp, mem) = state in
	(pc + 1, sp, mem)


(** Teste si l'exécution est terminée.
	@param state	Etat courant.
	@return			True si c'est l'exécution est terminée, false sinon. *)
let ended state =
	let ((pc, sp, mem), kar) = state in
	pc < 0


(** Obtiens la valeur du PC.
	@param state	Etat courant.
	@return			Valeur du PC. *)
let get_pc state =
	let ((pc, _, _), _) = state in pc


(** Effectue une action spéciale de Karel.
	@param s	Etat courant.
	@param d	action.
	@param a	1er argument.
	@param b	2ème argument.
	@return		Nouvel état. *)
let invoke s d a b =
	let (vs, (f, is)) = s in
	let (vs, is) = f vs is d a b in
	(vs, (f, is))


(** Get the invoke state from a state.
	@param s	State to look in.
	@return		Invoke state. *)
let get_istate s =
	let (_, (_, s)) = s in s


(** Stop the WM.
	@param state	Current state.
	@return			New state. *)
let stop state =
	let (vs, is) = state in
	(goto vs (-1), is)


(** Execute un quadruplet dans l'état courant.
	@param state	Etat courant.
	@param quad		Quadruplet à exécuter.
	@return			Nouvel état après exécution. *)
let exec_quad state quad =
	let (vs, is) = state in
	match quad with
	| ADD (d, a, b) 	-> (next (set vs d ((get vs a) + (get vs b))), is)
	| SUB (d, a, b) 	-> (next (set vs d ((get vs a) - (get vs b))), is)
	| MUL (d, a, b) 	-> (next (set vs d ((get vs a) * (get vs b))), is)
	| DIV (d, a, b) 	-> (next (set vs d ((get vs a) / (get vs b))), is)
	| MOD (d, a, b) 	-> (next (set vs d ((get vs a) mod (get vs b))), is)
	| SET (d, a)		-> (next (set vs d (get vs a)), is)
	| SETI (d, a)		-> (next (set vs d a), is)
	| GOTO d 			-> (goto vs d, is)
	| GOTO_EQ (d, a, b)	-> ((if (get vs a) =  (get vs b) then goto vs d else next vs), is)
	| GOTO_NE (d, a, b)	-> ((if (get vs a) <> (get vs b) then goto vs d else next vs), is)
	| GOTO_LT (d, a, b)	-> ((if (get vs a) <  (get vs b) then goto vs d else next vs), is)
	| GOTO_LE (d, a, b)	-> ((if (get vs a) <= (get vs b) then goto vs d else next vs), is)
	| GOTO_GT (d, a, b)	-> ((if (get vs a) >  (get vs b) then goto vs d	else next vs), is)
	| GOTO_GE (d, a, b)	-> ((if (get vs a) >= (get vs b) then goto vs d	else next vs), is)
	| STOP				-> stop state
	| CALL d			-> (goto (push vs) d, is)
	| RETURN			-> (let (pc, vs) = pop vs in goto vs pc, is)
	| INVOKE (d, a, b)	-> let vs, is = invoke state d a b in (next vs, is)
	| LABEL _			-> (next vs, is)


(** Effectue un pas d'exécution.
	@param state	Etat courant.
	@param prog		Programme courant.
	@return			Nouvel état. *)
let step state prog =
	let (vstate, _) = state in
	let (pc, _, _) = vstate in
	if pc < 0 then 
		state
	else if pc >= (Array.length prog) then
		raise (Error (vstate, Printf.sprintf "invalid pc at %d" pc))
	else
		exec_quad state prog.(pc)


(** Execute the given program by starting at address 0.
	@param prog		Program to execute.
	@param rnum		Number of registers.
	@param invoke	Function to execute invokes.
	@param state	State of invoke implementation.
	@return			Final state. *)
let execute prog rnum invoke state =
	
	let rec perform state =
		if ended state then state
		else perform (step state prog) in
		
	perform (new_state invoke state)


(** Get the value of a register.
	@param state	Current state.
	@param index	Index of the register.
	@return			Value of the register. *)
let get_reg state index =
	let (vstate, _) = state in
	get vstate index


(** Get the values of the registers. *)
let all_regs s =
	let ((_, _, m), _) = s in m
