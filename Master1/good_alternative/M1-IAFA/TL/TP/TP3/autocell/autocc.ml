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

open Ast
open Common
open Printf
open Quad

let print_eval s =

	let rec clean s =
		match s with
		| NOP
		| SET_CELL _
		| SET_VAR _ ->
			s
		| IF_THEN (c, s1, s2) ->
			IF_THEN (c, clean s1, clean s2)
		| SEQ (s1, s2) ->
			match (clean s1, clean s2) with
			| (NOP, NOP) 	-> NOP
			| (s1, NOP)		-> s1
			| (NOP, s2)		-> s2
			| (s1, s2)		-> SEQ (s1, s2) in

	let op o =
		match o with
		| OP_ADD -> "ADD"
		| OP_SUB -> "SUB"
		| OP_MUL -> "MUL"
		| OP_DIV -> "DIV"
		| OP_MOD -> "MOD" in

	let cmp c =
		match c with
		| COMP_EQ	-> "EQ"
		| COMP_NE	-> "NE"
		| COMP_LT	-> "LT"
		| COMP_LE	-> "LE"
		| COMP_GT	-> "GT"
		| COMP_GE	-> "GE" in
 
	let rec expr e =
		match e with
		| NONE ->
			printf "NONE\n"
		| CST k ->
			printf "CST(%d)\n" k
		| CELL (f, x, y) ->
			printf "CELL(%d, %d, %d)\n" f x y
		| VAR x ->
			printf "VAR(%d)\n" x
		| NEG e ->
			printf "NEG(\n";
			expr e;
			printf ")\n"
		| BINOP (o, e1, e2) ->
			printf "BINOP(%s,\n" (op o);
			expr e1;
			printf ",\n";
			expr e2;
			printf ")\n" in

	let rec cond c =
		match c with
		| NO_COND ->
			printf "NOCOND\n"
		| COMP (c, e1, e2) ->
			printf "COMP(%s,\n" (cmp c);
			expr e1;
			printf ",\n";
			expr e2;
			printf ")\n"
		| NOT c ->
			printf "NOT(\n";
			cond c;
			printf ")\n"
		| AND (c1, c2) ->
			printf "AND(\n";
			cond c1;
			printf ",\n";
			cond c2;
			printf ")\n"
		| OR (c1, c2) ->
			printf "OR(\n";
			cond c1;
			printf ",\n";
			cond c2;
			printf ")\n" in

	let rec stmt s =
		match s with
		| NOP ->
			printf "NOP\n"
		| SET_CELL (f, e) ->
			printf "SET_CELL(%d, \n" f;
			expr e;
			printf ")\n"
		| SET_VAR (x, e) ->
			printf "SET_VAR(%d, \n" x;
			expr e;
			printf ")\n"
		| SEQ (s1, s2) ->
			stmt s1;
			stmt s2
		| IF_THEN (c, s1, s2) ->
			printf "IF_THEN(\n";
			cond c;
			printf ",\n";
			stmt s1;
			printf ",\n";
			stmt s2;
			printf ")\n" in
	
	stmt (clean s)

let _ =
	let dump_ast = ref false in
	let dump_eval = ref false in
	let one = ref false in

	let make_field f (id, (num, (lo, hi))) =
		f (JRECORD [
			("name", JSTR id);
			("num", JINT num);
			("lo", JINT lo);
			("hi", JINT hi)
		]) in

	let compile lexbuf name =
		try
			let (flds, stmt) = Parser.program Lexer.token lexbuf in
			if !dump_ast then
				(Ast.print_stmt "" stmt; printf "\n"; exit 0)
			else if !dump_eval then
				(print_eval stmt; exit 0)
			else
				let metas = [
					("source", JSTR name);
					("fields", JARRAY (fun f -> 
						List.iter (make_field f) flds
					))
				] in
				(metas, Comp.compile flds stmt)
		with
		| LexerError msg ->
			source_fatal lexbuf name msg
		| Parsing.Parse_error ->
			source_fatal lexbuf name "syntax error"
		| SyntaxError msg ->
			source_fatal lexbuf name msg in

	let rec escape i s =
		let l = String.length s in
		if i >= l then s else
		if s.[i] <> '"' then escape (i+1) s else
		(String.sub s 0 i) ^ "\\\"" ^ (escape 0 (String.sub s (i+1) (l-i-1))) in

	let save metas quads output =
			List.iter (fun (k, v) -> fprintf output "\t.meta %s \"%s\"\n" k (escape 0 (json_to_string v))) metas;
			output_prog output quads in
	
	let compile_path path =
		one := true;
		let (metas, qs) =
			try
				let in_channel = open_in path in
				let (metas, qs) = compile (Lexing.from_channel in_channel) path in
				close_in in_channel;
				(metas, qs)
			with Sys_error msg ->
				fatal_error (sprintf "ERROR: cannot load %s: %s\n" path msg) in
		let out_path = set_suffix path ".auto" ".s" in
		try
			let out_channel = open_out out_path in
			save metas qs out_channel;
			fprintf stderr "Assembly saved to %s\n" out_path;
			close_out out_channel
		with Sys_error msg ->
			fprintf stderr "ERROR: cannot save %s: %s\n" out_path msg in

	Arg.parse
		[
			("-ast", Set dump_ast, "Dump the AST.");
			("-eval", Set dump_eval, "")
		]
		compile_path
		"autocc [<file1>.auto...]";

	if not !one then
		let (metas, quads) = compile (Lexing.from_channel stdin) "<stdin>" in
		save metas quads stdout
