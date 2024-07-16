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

exception LexerError of string
exception SyntaxError of string

(** Hash module for strings. *)
module StringHash = struct
	type t = string
	let equal s1 s2 = s1 = s2
	let hash s = Hashtbl.hash s
end

(** Hash table using strings as keys *)
module StringHashtbl = Hashtbl.Make(StringHash)


(** Change the suffix of a file name.
	@param name		File change to change suffix of.
	@param old_suff	Old suffix to replace.
	@param new_suff	Suffix to replace with.
	@return			File name with suffix changed. *)
let set_suffix name old_suff new_suff =
	let nl = String.length name in
	let sl = String.length old_suff in
	if sl >= nl then name ^ new_suff else
	(String.sub name 0 (nl - sl)) ^ new_suff


(** Get the line containing the given offset.
	@param path		Path of the source file.
	@param offset	Offset to select the content.
	@return			Corresponding line. *)
let line_at path offset =
	let file = open_in path in
	let rec next n sum =
		try
			let size = String.length (input_line file) + 1 in
			if sum + size > offset then (n, offset - sum + 1)
			else next (n + 1) (sum + size)
		with End_of_file ->
			(n, 0) in
	next 1 0
		

(** Print an error in the source.
	@param lexbuf	Current lexbuf.
	@param src		Source to look in.
	@param msg		Error message. *)	
let source_error lexbuf src msg =
	let (line, col) = line_at src (Lexing.lexeme_start lexbuf) in
	printf "ERROR:%d:%d: %s\n" line col msg

(** Print an error in the source and stop the compiler.
	@param lexbuf	Current lexbuf.
	@param src		Source to look in.
	@param msg		Error message. *)	
let source_fatal lexbuf prog msg =
	source_error lexbuf prog msg;
	exit 1

(** Raise a fatal error which message is displayed
	and the application stops.
	@param msg	Message to display. *)
let fatal_error msg =
	fprintf stderr "ERROR: %s\n" msg;
	exit 1


(** Json formatting. *)
type json =
	| JNONE
	| JBOOL of bool
	| JINT of int
	| JSTR of string
	| JRECORD of (string * json) list
	| JARRAY of ((json -> unit) -> unit)


(** Convert a JSON expression to a string.
	@param j	JSON expression to convert.
	@return		Srting outcome of the conversion. *)
let json_to_string j =

	let buf = Buffer.create 256 in
	let add = Buffer.add_string buf in
	let addc = Buffer.add_char buf in
	let com f = if !f then f := false else add ", " in

	let rec item f j = com f; trans j

	and field f (k, j) =
		com f; addc '"'; add k; add "\": "; trans j

	and trans j =
		match j with
		| JNONE ->
			failwith "common: json_to_string: JNONE"
		| JBOOL false ->
			add "false"
		| JBOOL true ->
			add "true"
		| JINT x ->
			add (string_of_int x)
		| JSTR x ->
			addc '"'; add x; addc '"'
		| JARRAY f ->
			addc '['; f (item (ref true)); addc ']'
		| JRECORD rs ->
			add "{ "; List.iter (field (ref true)) rs; add " }" in
	trans j;
	Buffer.contents buf



