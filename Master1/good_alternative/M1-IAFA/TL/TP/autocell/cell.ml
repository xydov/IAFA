(*
 * autocell - AutoCell compiler and viewer
 * Copyright (C) 2021  University of Toulouse, France <casse@irit.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *)

open Printf

exception Error of string

(* commands *)
let cSIZE = 1		(** d = 1, R[a] <- width, R[b] <- height *)
let cFIELD = 2
let cMOVE = 3		(** d = 3, R[a] = x, R[b] = y *)
let cSET = 4		(** d = 4, R[a] = value, b = field number *)
let cGET = 5		(** d = cGET + field, M[a] <- value, b = position *)
let cGETV = 1005	(** d = cGET + field, M[a] <- value, R[b] = position *)

(* cell position *)
let pCENTER = 0
let pNORTH = 1
let pNORTHWEST = 2
let pWEST = 3
let pSOUTHWEST = 4
let pSOUTH = 5
let pSOUTHEAST = 6
let pEAST = 7
let pNORTHEAST = 8

type map = int array array array
type point = int * int
type dim = int * int * int
type look = string list
type state = point * dim * map * map * look

let null_matrix = Array.make 0 (Array.make 0 (Array.make 0 0))

(** Null map. *)
let null: state = ((0, 0), (0, 0, 0), null_matrix, null_matrix, [])


(** Create a map.
	@param f	Number of fields.
	@param w	Map width.
	@param h	Map height. *)
let create_map f w h =
	let line _ = Array.make h 0 in
	let matrix _ = Array.init w (fun _ -> line ()) in
	Array.init f (fun _ -> matrix ())


(** Create a state with the given dimensions.
	@param f	Number of fields.
	@param w	Map width.
	@param h	Map height.
	@param cs	List of colors. *)
let create f w h cs =
	((0, 0), (f, w, h), create_map f w h, create_map f w h, cs)


(** Get the size of the map.
	@param state	State of the machine.
	@return			(width, height). *)
let size state =
	let (_, (_, w, h), _, _, _) = state in
	(w, h)


(** Get the number of fields.
	@param state	State of the machine.
	@return			Number of fields. *)
let field state =
	let (_, (f, _, _), _, _, _) = state in
	f


(** Move the current cell to the given position.
	@param state	State to process.
	@param x		New x position.
	@param y		New y position. *)
let move state x y =
	let (_, (f, w, h), c, n, cs) = state in
	if (x < 0) || (x >= w) || (y < 0) || (y >= h)
	then raise (Error (sprintf "bad move %d, %d" x y));
	((x, y), (f, w, h), c, n, cs)


(** Compute (x, y) position in the given state.
	@param state	Current state.
	@param pos		Looked position.
	@return			(x, y) corresponding to position. *)
let compute_xy state pos =
	let ((x, y), (_, w, h), _, _, _) = state in
	let x, y = 
		match pos with
		| 0 -> (x, y)		(* center *)
		| 1 -> (x, y-1)		(* north *)
		| 2 -> (x-1, y-1)	(* north west *)
		| 3 -> (x-1, y)		(* west *)
		| 4 -> (x-1, y+1)	(* south west *)
		| 5 -> (x, y+1)		(* south *)
		| 6 -> (x+1, y+1)	(* south east *)
		| 7 -> (x+1, y)		(* east *)
		| 8 -> (x+1, y-1)	(* north east *)
		| _ -> raise (Error (sprintf "bad get direction: %d" pos)) in
	(
		(if x < 0 then w-1 else if x >= w then 0 else x),
		(if y < 0 then h-1 else if y >= h then 0 else y)
	)


(** Get the value around the current cell in the current map.
	@param state	Current state.
	@param pos		Looked position.
	@param fld		Field to look to.
	@return			Value at the given position. *)
let get state pos fld =
	let ((x, y), _, c, _, _) = state in
	let (x, y) = compute_xy state pos in
	c.(fld).(x).(y)


(** Set the value of the current cell in the new map.
	@param state	Current state.
	@param value	Set value.
	@param fld		Field to look to. *)
let set state value fld =
	let ((x, y), _, _, n, _) = state in
	n.(fld).(x).(y) <- value;
	state


(** Set the value of the current state.
	@param state	State to set in.
	@param fld		Field to set.
	@param x		x coordinate.
	@param y		y coordinate.
	@param value	Value to set. *)
let set_current state fld x y value = 
	let (_, _, c, n, _) = state in
	c.(fld).(x).(y) <- value;
	n.(fld).(x).(y) <- value;
	state


(** Let the value of the current at (x, y).
	@param state	State.
	@param fld		Field.
	@param x		X coordinate.
	@param y		Y coordinate.
	@return			Value. *)
let get_current state fld x y =
	let (_, _, c, _, _) = state in
	c.(fld).(x).(y)


(** Implements the invokation to the application from the VM.
	@param vm		VM state.
	@param state	Current state.
	@param d		Command.
	@param a		First argument.
	@param b		Second argument.
	@return			(VM state, new state). *)
let invoke vm state d a b =

	match d with

	| 1 ->		(* size *)
		let (w, h) = size state in
		let vm = Vm.set vm a w in
		let vm = Vm.set vm b h in
		(vm, state)

	| 2	->		(* field *)
		(Vm.set vm a (field state), state)

	| 3 ->		(* move *)
		(vm, move state (Vm.get vm a) (Vm.get vm b))
	
	| 4	->	(* set *)
		(vm, set state (Vm.get vm a) b)

	| f when f < cGETV -> (* get *)
		(Vm.set vm a (get state b (f - cGET)), state)
	| f ->		(* getv *)
		(Vm.set vm a (get state (Vm.get vm b) (f - cGETV)), state)



(** Switch current state and new state.
	@param state	State to change.
	@return			New switched state. *)
let switch state =
	let (p, d, c, n, cs) = state in
	Array.iteri
		(fun f m -> Array.iteri
			(fun x t -> Array.blit n.(f).(x) 0 t 0 (Array.length t))
			m)
		c;
	(p, d, c, n, cs)


(** Iterate function in ranges (0 to h-1) x (0 to w -1).
	@param f	Function to call.
	@param w	Width.
	@param h	Height. *)
let iter f g w h =
	let rec run x y =
		if y >= h then () else
		if x >= w then (
			g ();
			run 0 (y + 1)
		)
		else (
			f x y;
			run (x + 1) y
		) in
	run 0 0


(** Output the current field in the given state.
	@param out		Channel to output to.
	@param state	State to output.
	@param fld		Field to output. *)
let output out state fld =
	let ((x, y), (_, w, h), c, _, _) = state in
	iter
		(fun x y -> fprintf out "%d" c.(fld).(x).(y))
		(fun _ -> output_char out '\n')
		w h


(** Print the given field to the standard output.
	@param state	State to print.
	@param fld		Field to print. *)
let print state fld =
	output stdout state fld


(** Duplicate the given map.
	@param map	Map to duplicate.
	@return		Duplciated map. *)	
let duplicate map =
	Array.map (fun f -> Array.map (fun r -> Array.copy r) f ) map



(** Load a map from a file.
	@param path		Path to the world file.
	@return			Loaded world. *)	
let load path =
	let num = ref 1 in

	let rec next file =
		let l = input_line file in
		incr num;
		let l = String.trim
			(try String.sub l 0 (String.index l '#')
			with Not_found -> l) in
		if l = "" then next file else l in
		
	try

		let file = open_in path in
		let f = int_of_string (next file) in
		let w = int_of_string (next file) in
		let h = int_of_string (next file) in
		let cs = String.split_on_char ',' (next file) in

		let rec scan_fields map i =
			if i = f then map else
			scan_fields (scan_rows map i 0) (i + 1)

		and scan_rows map fld y =
			if y = h then map else
			scan_rows (scan_cols map fld y 0 (next file)) fld (y + 1)

		and scan_cols map fld y x l =
			if x = w then map else
			let v = (int_of_char l.[x]) - (int_of_char '0') in
			scan_cols (set_current map fld x y v) fld y (x + 1) l in

		let map = scan_fields (create f w h cs) 0 in
		close_in file;
		map

	with
	| End_of_file
	| Failure _ ->
		raise (Error (sprintf "%d: bad map format" !num))
	| Sys_error msg ->
		raise (Error (sprintf "reading program: %s" msg))


(** Get the number of fields in the map.
	@param map	Map to look in.
	@return		Number of fields. *)
let fields map =
	let (_, (f, _, _), _, _, _) = map in
	f


(** Get the width of the map.
	@param map	Map to look in.
	@return		Width. *)
let width map =
	let (_, (_, w, _), _, _, _) = map in
	w


(** Get the height of the map.
	@param map	Map to look in.
	@return		Height. *)
let height map =
	let (_, (_, _, h), _, _, _) = map in
	h


(** Perform a copy of the map.
	@param map	Map to copy.
	@return		Copied version. *)
let copy map =

	let (p, d, c, n, l) = map in
	(p, d, duplicate c, duplicate n, l)


(** Get the colors of the map.
	@param map	Map to look in.
	@return		Colors of the graph. *)
let colors map =
	let (_, _, _, _, cs) = map in
	cs
