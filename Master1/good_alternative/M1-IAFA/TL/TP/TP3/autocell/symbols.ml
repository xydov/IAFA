open Common

(* globals -- ugly but make things easier *)
let reg_cnt = ref 5
let lab_cnt = ref 0


(** Map of variables. *)
let var_map : int Stdlib__hashtbl.Make(Common.StringHash).t = StringHashtbl.create 255


(** List of fields. *)
let fields: (string*(int*(int*int))) list ref = ref []


(** Generate a new register.
	@return	New register. *)	
let new_reg _ =
	let x = !reg_cnt in
	incr reg_cnt;
	x

(** Generate a new label.
	@return	New variable. *)	
let new_lab _ =
	let x = !lab_cnt in
	incr lab_cnt;
	x

(** reverse access from field index to field name *)
let get_field_id n =
  let rec lookup = function
      [] -> failwith ("field not found: "^(string_of_int n))
    | (f,(m,_))::l when n=m -> f
    | _::l -> lookup l
  in lookup !fields

(** reverse access from var index to var name *)
let get_var_id n =
  let id = StringHashtbl.fold (fun id m r -> if m=n then id else r) var_map "" in
  if id="" then failwith "var not found" else id

(** Get the field number from the field identifier.
	@param id	Field identifier.
	@return		Field number or -1if the field does not exist. *)
let get_field id =
	try
		let (n, _) = List.assoc id !fields in n
	with Not_found ->
		-1


(** Set the list of fields.
	@param fs	Parsed list of fields. *)
let set_fields fs =
	let i = ref (-1) in
	fields := List.map (fun (id, r) -> incr i; (id, (!i, r))) (List.rev fs);
	!fields

(** Get the number for the register number
	for the given variable.
	@param id	Variable identifier.
	@return		Variable register or -1 (if variable does not exists). *)
let get_var id =
	try
		StringHashtbl.find var_map id
	with Not_found ->
		-1

(** Declare a new variable.
	@param id	Variable identifier.
	@return		Register for the variable. *)
let declare_var id =
	let num = new_reg () in
	StringHashtbl.add var_map id num;
	num

