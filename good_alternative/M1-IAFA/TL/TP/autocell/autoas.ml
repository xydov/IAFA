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

open Common
open Printf

let source = ref ""
let target = ref ""

let opts = [
	("-o", Arg.Set_string target, "Use the given file as output.")
]
let  doc = "AutoCell Assembler"

let free_arg s =
	if !source <> ""
	then raise (Arg.Bad "Too many source files specified.")
	else source := s

let _ =
	Arg.parse opts free_arg doc;
	let path, file =
		if !source = ""
		then ("<stdin>", stdin)
		else (!source, open_in !source) in
	let lexbuf = Lexing.from_channel file in
	try
		let (cnt, quads) = Asparser.listing Aslexer.scan lexbuf in
		let out_path =
			if !target <> "" then !target
			else if !source = "" then "a.out"
			else Common.set_suffix !source ".s" ".exe" in
		Quad.save (Quad.make cnt quads) out_path;
		fprintf stderr "Saved to %s!\n" out_path
	with
	|	Parsing.Parse_error ->
			source_fatal lexbuf path "syntax error"
	|	Common.LexerError msg ->
			source_fatal lexbuf path msg
	|	Common.SyntaxError msg ->
			source_fatal lexbuf path msg
	|	Quad.Error msg -> 
			fatal_error msg
