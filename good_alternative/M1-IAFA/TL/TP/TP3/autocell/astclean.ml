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

let _ =
	let one = ref false in

	let transfo lexbuf name =
		try
			let p = Parser.program Lexer.token lexbuf in
                        Astpp.pp_prog (Transfo.transfo p)
		with
		| LexerError msg ->
			source_fatal lexbuf name msg
		| Parsing.Parse_error ->
			source_fatal lexbuf name "syntax error"
		| SyntaxError msg ->
			source_fatal lexbuf name msg in

	let transfo_path path =
		one := true;
		let cleaned_prog =
			try
				let in_channel = open_in path in
				let p = transfo (Lexing.from_channel in_channel) path in
				close_in in_channel;
				p
			with Sys_error msg ->
				fatal_error (sprintf "ERROR: cannot load %s: %s\n" path msg) in
		let out_path = set_suffix path ".auto" "-cleaned.auto" in
		try
		  let out_channel = open_out out_path in
                  fprintf out_channel "%s" cleaned_prog;
		  fprintf stderr "Cleaned prog saved to %s\n" out_path;
		  close_out out_channel
		with Sys_error msg ->
		  fprintf stderr "ERROR: cannot save %s: %s\n" out_path msg in

	Arg.parse
		[ ]
		transfo_path
		"astclean [<file1>.auto...]";

	if not !one then
	  fprintf stderr "ERROR: .auto file expected\n"
