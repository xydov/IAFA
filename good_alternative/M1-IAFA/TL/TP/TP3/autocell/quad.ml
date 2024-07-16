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

type quad =
		| ADD of int * int * int
		| SUB of int * int * int
		| MUL of int * int * int
		| DIV of int * int * int
		| MOD of int * int * int
		| SET of int * int
		| SETI of int * int
		| GOTO of int
		| GOTO_EQ of int * int * int
		| GOTO_NE of int * int * int
		| GOTO_LT of int * int * int
		| GOTO_LE of int * int * int
		| GOTO_GT of int * int * int
		| GOTO_GE of int * int * int
		| LABEL of int
		| INVOKE of int * int * int
		| CALL of int
		| RETURN
		| STOP


(** Type of programs in quads. *)
type prog = int * quad array


(** Convertit un quadruplet en chaîne de caractère.
	@param q	Quadruplet à convertir.
	@return		Chaîne de caractère. *)
let to_string q =
	match q with
	| ADD (d, a, b) 	-> Printf.sprintf "add r%d, r%d, r%d" d a b
	| SUB (d, a, b) 	-> Printf.sprintf "sub r%d, r%d, r%d" d a b
	| MUL (d, a, b) 	-> Printf.sprintf "mul r%d, r%d, r%d" d a b
	| DIV (d, a, b) 	-> Printf.sprintf "div r%d, r%d, r%d" d a b
	| MOD (d, a, b) 	-> Printf.sprintf "mod r%d, r%d, r%d" d a b
	| SET (d, a)		-> Printf.sprintf "set r%d, r%d" d a
	| SETI (d, a) 		-> Printf.sprintf "seti r%d, #%d" d a
	| GOTO d 			-> Printf.sprintf "goto L%d" d
	| GOTO_EQ (d, a, b) -> Printf.sprintf "goto_eq L%d, r%d, r%d" d a b
	| GOTO_NE (d, a, b) -> Printf.sprintf "goto_ne L%d, r%d, r%d" d a b
	| GOTO_LT (d, a, b) -> Printf.sprintf "goto_lt L%d, r%d, r%d" d a b
	| GOTO_LE (d, a, b) -> Printf.sprintf "goto_le L%d, r%d, r%d" d a b
	| GOTO_GT (d, a, b) -> Printf.sprintf "goto_gt L%d, r%d, r%d" d a b
	| GOTO_GE (d, a, b) -> Printf.sprintf "goto_ge L%d, r%d, r%d" d a b
	| INVOKE (d, a, b)	-> Printf.sprintf "invoke %d, %d, %d" d a b
	| STOP				-> Printf.sprintf "stop"
	| LABEL l			-> Printf.sprintf "L%d:" l

	| CALL d			-> Printf.sprintf "call %d" d
	| RETURN			-> Printf.sprintf "return"



(** Print a quad on the given output.
	@param out	Output to print to.
	@param q	Quad to display. *)
let output out q =
	match q with
	| LABEL _ -> 
		fprintf out "%s\n" (to_string q)
	| _ ->
		fprintf out "\t%s\n" (to_string q)


(** Print a program on the given output.
	@param out	Output to print to.
	@param prog	Program to output. *)
let output_prog out prog =
	List.iter (output out) prog


(** Print a quad on the standard output.
	@param q	Quad to display. *)
let print q =
	output stdout q


(** Print a program on the standard output.
	@param prog	Program to output. *)
let print_prog prog =
	output_prog stdout prog


(** Get the size of a program. *)
let size prog =
	let (s, _) = prog in
	s


(** Get the quadruplets of a progam. *)
let quads prog =
	let (_, q) = prog in
	q


(** Build a program. *)
let make size quads =
	(size, quads)


(** Load a quad program. *)
let load path =
	let error msg = raise (Error msg) in
	try
		let inp = open_in path in
		let (p: prog) = Marshal.from_channel inp in
		close_in inp;
		p
	with
	| Failure msg ->
		error (sprintf "cannot load the program '%s': %s" path msg)
	| Sys_error msg ->
		error (sprintf "reading program: %s" msg)


(** Save a quad program.
	@param prog		Program to save.
	@param path		Path to save to. *)
let save (p: prog) path =
	try
		let out = open_out path in
		Marshal.to_channel out p [];
		close_out out
	with Sys_error msg ->
		raise (Error msg)
