/*
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
 */

%{

open Common
open Printf
open Quad

let quads = Array.make 1000 Quad.STOP
let cnt = ref 0

let labels: int StringHashtbl.t = StringHashtbl.create 253

let backpatches: (string * int) list ref = ref []

let metas = ref []

(** Add a new quad to the program.
	@param quad		Added quad. *)
let gen quad =
	quads.(!cnt) <- quad;
	incr cnt

(** Get the number of the next quad..
	@return	Next quad number. *)
let nextquad _ =
	!cnt

(** Apply a backpatch on the goto at address g in order to make it
	branch to address a.
	@param g	Address of goto to patch.
	@param a	Branch address. *)
let backpatch g a =
	quads.(g) <-
		match quads.(g) with
		| Quad.GOTO _				-> Quad.GOTO a
		| Quad.GOTO_EQ (_, r, s)	-> Quad.GOTO_EQ (a, r, s)
		| Quad.GOTO_NE (_, r, s)	-> Quad.GOTO_NE (a, r, s)
		| Quad.GOTO_LT (_, r, s)	-> Quad.GOTO_LT (a, r, s)
		| Quad.GOTO_LE (_, r, s)	-> Quad.GOTO_LE (a, r, s)
		| Quad.GOTO_GT (_, r, s)	-> Quad.GOTO_GT (a, r, s)
		| Quad.GOTO_GE (_, r, s)	-> Quad.GOTO_GE (a, r, s)
		| _							-> failwith "Backpatched a non-goto instruction!"

let resolve_label label = 
	try
		StringHashtbl.find labels label
	with Not_found ->
		(backpatches := (label, nextquad ()) :: !backpatches; 0)

let resolve_backpatches _ =
	let rec resolve patches =
		match patches with
		| [] -> ()
		| (l, a)::t -> 
			try
				backpatch a (StringHashtbl.find labels l);
				resolve t
			with Not_found ->
				Printf.fprintf stderr "ERROR: cannot resolve %s" l;
				raise Exit in
	resolve !backpatches

%}

%token ADD
%token SUB
%token MUL
%token DIV
%token MOD
%token SET
%token SETI
%token GOTO
%token GOTO_EQ
%token GOTO_NE
%token GOTO_LT
%token GOTO_LE
%token GOTO_GT
%token GOTO_GE
%token CALL
%token RETURN
%token INVOKE
%token STOP

%token <int> 	REG
%token <int> 	INT
%token <string>	LABEL
%token <string> STR

%token COMMA
%token SHARP
%token COLON
%token META
%token EOF

%type <int * Quad.quad array> listing
%start listing

%%

listing: commands EOF
	{
		gen Quad.STOP;
		resolve_backpatches ();
		(!cnt, quads)
	}
;

commands:
	command
		{ () }
|	command commands
		{ () }
;

command:
	META LABEL STR
		{ metas := ($2, $3)::!metas }
|	LABEL COLON
		{
			if StringHashtbl.mem labels $1
			then raise (SyntaxError (sprintf "label %s already used!" $1))
			else StringHashtbl.add labels $1 (nextquad ())
		}
|	STOP
		{ gen Quad.STOP }
|	ADD REG COMMA REG COMMA REG
		{ gen (Quad.ADD ($2, $4, $6)) }
|	SUB REG COMMA REG COMMA REG
		{ gen (Quad.SUB ($2, $4, $6)) }
|	MUL REG COMMA REG COMMA REG
		{ gen (Quad.MUL ($2, $4, $6)) }
|	DIV REG COMMA REG COMMA REG
		{ gen (Quad.DIV ($2, $4, $6)) }
|	MOD REG COMMA REG COMMA REG
		{ gen (Quad.MOD ($2, $4, $6)) }
|	SET REG COMMA REG
		{ gen (Quad.SET ($2, $4)) }
|	SETI REG COMMA SHARP INT
		{ gen (Quad.SETI ($2, $5)) }
|	GOTO LABEL
		{ gen (Quad.GOTO (resolve_label $2)) }
|	GOTO_EQ LABEL COMMA REG COMMA REG
		{ gen (Quad.GOTO_EQ (resolve_label $2, $4, $6)) }
|	GOTO_NE LABEL COMMA REG COMMA REG
		{ gen (Quad.GOTO_NE (resolve_label $2, $4, $6)) }
|	GOTO_GT LABEL COMMA REG COMMA REG
		{ gen (Quad.GOTO_GT (resolve_label $2, $4, $6)) }
|	GOTO_GE LABEL COMMA REG COMMA REG
		{ gen (Quad.GOTO_GE (resolve_label $2, $4, $6)) }
|	GOTO_LT LABEL COMMA REG COMMA REG
		{ gen (Quad.GOTO_LT (resolve_label $2, $4, $6)) }
|	GOTO_LE LABEL COMMA REG COMMA REG
		{ gen (Quad.GOTO_LE (resolve_label $2, $4, $6)) }
|	CALL LABEL
		{ gen (Quad.CALL (resolve_label $2)) }
|	RETURN
		{ gen Quad.RETURN }
|	INVOKE INT COMMA INT COMMA INT
		{ gen (Quad.INVOKE ($2, $4, $6)) }
;

%%

