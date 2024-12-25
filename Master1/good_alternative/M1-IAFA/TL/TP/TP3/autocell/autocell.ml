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

module S = Tiny_httpd
module U = Tiny_httpd_util
open Printf
open Common
open Sys

exception BadURL

let asis s _ = output_string stderr s
(*let verbose f = f stderr; flush stderr*)
let verbose m = ()

(** Basic time-out (continue action). *)
let timeout = ref 0.2

(** Current program. *)
let current_program = ref (0, Array.make 1 Quad.STOP)

(** Original map. *)
let original_map = ref Cell.null

(** Current VM. *)
let current_vm = ref (Vm.new_state Cell.invoke !original_map)

(** List of breakpoints *)
let break_points = ref []

(** List of interest points *)
let int_points = ref []


(** Current generation. *)
let gen = ref 0


(** Check if ".." path is passed.
	@param s	Path to test.
	@return		True if a ".." path is used, false else. *)
let contains_dot_dot s =
	try
		String.iteri
			(fun i c ->
				if c='.' && i+1 < String.length s && String.get s (i+1) = '.' then raise Exit)
				s;
			false
	with Exit -> true


(** Run the browser on the served pages. *)
let display _ =
	verbose (asis "DEBUG: running command!\n");
	let url = "http://localhost:4040/index.html" in
	match Sys.os_type with
	| "Unix"
	| "Cygwin"->
		let ic = Unix.open_process_in "uname" in
		let uname = input_line ic in
		close_in ic;
		(match uname with
		| "Darwin" ->
			ignore (Sys.command ("open " ^ url))
		| _ ->
			ignore (Sys.command ("xdg-open " ^ url))
		)
	| "Win32" ->
		ignore (Sys.command ("start \"\" \"" ^ url ^ "\""))
	| _ ->
		printf "Run your browser with URL \"%s\"!" url


(** Bad syntax answer. *)
let bad_syntax _ =
	S.Response.fail ~code:404 "bad syntax"


(** Generate a JSON answer.
	@param t	JSOn text.
	@return		Answer. *)
let answer_json t =
	verbose (fun _ -> sprintf "ANSWER: %s\n" t);
	S.Response.make_string
		~headers:[("Content-Type", "application/json")]
		(Ok t)


(** Get the value of a register.
	@param state	State to look in.
	@param i		Register index.
	@return			Register value or -1. *)
let get_reg state i = 
	try Vm.get_reg state i
	with Vm.Error _ -> -1


(** Build an answer for an execurtion.
	@param status	Status of the execution.
	@param messages	Messages to display. *)
let answer_exec status messages =
	answer_json (json_to_string (
		JRECORD [
			("status", JINT status);
			("pc", JINT (Vm.get_pc !current_vm));
			("messages", JARRAY (fun f -> List.iter (fun m -> f (JSTR m)) messages));
			("gen", JINT !gen);
			("x", JINT (get_reg !current_vm 0));
			("y", JINT (get_reg !current_vm 1))
		]
	))


(** Perform the read action. *)
let do_quit server path req =
	verbose (asis "Quit!\n");
	exit 0


(** Output the list of quads in the program. *)
let do_quads server path req =
	let s = Quad.size !current_program - 1 in
	let qs = Quad.quads !current_program in
	let rec collect i =
		if i >= s
		then
			(sprintf "\"%04d %s\"\n]\n" i (Quad.to_string qs.(i)))
		else
			(sprintf "\"%04d %s\",\n" i (Quad.to_string qs.(i)))
			^ (collect (i + 1)) in
	let t = "[\n" ^ (collect 0) in
	answer_json t


(** Get information about the map. *)
let do_map server path req =
	let t = sprintf "{ \"fields\": %d, \"width\": %d, \"height\": %d }"
		(Cell.fields (Vm.get_istate !current_vm))
		(Cell.width (Vm.get_istate !current_vm))
		(Cell.height (Vm.get_istate !current_vm)) in
	answer_json t


(** Get the current state about the map. *)
let do_state server path req =
	let s = Vm.get_istate !current_vm in
	let w = Cell.width s in
	let h = Cell.height s in
	let get = Cell.get_current s 0 in

	let rec col x y =
		if x >= w - 1
		then (sprintf "%d" (get x y))
		else (sprintf "%d, " (get x y)) ^ (col (x + 1) y) in

	let rec row y =
		if y >= h-1
		then "[" ^ (col 0 y) ^ "]"
		else "[" ^ (col 0 y) ^ "], " ^ (row (y + 1)) in

	let t = ("[" ^  (row 0) ^ "]") in
	answer_json t


(** Move to the next generation. *)
let next_gen state =
	incr gen;
	let s = Cell.switch (Vm.get_istate state) in
	Vm.new_state Cell.invoke s


(** Perform the next step. *)
let do_next server path req =
	let rec run state =
		if Vm.ended state then state else
		run (Vm.step state (Quad.quads !current_program)) in
	try
		current_vm := next_gen (run !current_vm);
		answer_exec 1 []
	with Vm.Error (_, msg) ->
		answer_exec (-1) [msg]


(** Perform an execution step. *)
let do_step server path req =
	current_vm := Vm.step !current_vm (Quad.quads !current_program);
	if not (Vm.ended !current_vm)
	then answer_exec 0 []
	else (
		current_vm := next_gen !current_vm;
		answer_exec 1 []
	)

(** Reset the map. *)
let do_reset server path req =
	current_vm := Vm.new_state Cell.invoke (Cell.copy !original_map);
	gen := 0;
	answer_exec 1 []


(** Enable/disable a breakpoint. *)
let do_bp server args req =
	try
		let bp = int_of_string (List.assoc "num" (S.Request.query req)) in
		let ins = List.mem bp !break_points in
		if ins then
			break_points := List.filter (fun x -> x <> bp) !break_points
		else
			break_points := bp :: !break_points;
		answer_json (json_to_string (JBOOL (not ins)))
	with
	| Not_found
	| Failure _ ->
		bad_syntax ()


(** Enable/disable interest point. *)
let do_ip server path req =
	try
		let x = int_of_string (List.assoc "x" (S.Request.query req)) in
		let y = int_of_string (List.assoc "y" (S.Request.query req)) in
		let ins = List.mem (x, y) !int_points in
		if ins then
			int_points := List.filter (fun ip -> ip <> (x, y)) !int_points
		else
			int_points := (x, y) :: !int_points;			
		answer_json (json_to_string (JBOOL (not ins)))
	with
	| Not_found
	| Failure _ ->
		bad_syntax ()


(** Start a continue action. *)
let do_continue server path req =
	let t0 = Sys.time () in

	let check_bp state =
		List.mem (Vm.get_pc state) !break_points &&
		(
			!int_points = []
			|| List.mem (get_reg state 0, get_reg state 1) !int_points
		) in
		
	let rec run state status =
		if Vm.ended state then (1, next_gen state) else
		if (Sys.time ()) -. t0 >= !timeout then (status, state) else
		let state = Vm.step state (Quad.quads !current_program) in
		if check_bp state then (2, state) else
		run state status in
	try
		let (status, vm) = run !current_vm 0 in
		current_vm := vm;
		answer_exec status []
	with Vm.Error (_, msg) ->
		answer_exec (-1) [msg]


(** Generate register content. *)
let do_regs server path req =
	answer_json (json_to_string (JARRAY
		(fun f -> Array.iter (fun x -> f (JINT x)) (Vm.all_regs !current_vm))
	))


(** Generate the list of colors. *)
let do_colors server path req =
	answer_json (json_to_string (JARRAY
		(fun f -> List.iter
			(fun x -> f (JSTR ("#" ^ x)))
			(Cell.colors (Vm.get_istate !current_vm)))
	))


(** List of commands. *)
let commands = [
	("colors", do_colors);
	("continue", do_continue);
	("bp", do_bp);
	("ip", do_ip);
	("map", do_map);
	("next", do_next);
	("quads", do_quads);
	("quit", do_quit);
	("regs", do_regs);
	("reset", do_reset);
	("state", do_state);
	("step", do_step)
]


(** Serve a file. *)
let serve_file server path req =
	let path = if path = "" then "index.html" else path in
	let path = "pages/" ^ path in
	if contains_dot_dot path then
		S.Response.fail ~code:403 "Path is forbidden"
	else if not (Sys.file_exists path) then
		S.Response.fail ~code:404 "File not found"
	else if Sys.is_directory path then
		S.Response.fail ~code:404 "Cannot serve directory"
	else (
		try
			let ic = open_in path in
			let mime_type = ("Content-Type", "text/html") in
			S.Response.make_raw_stream
				~headers:([mime_type])
				~code:200 (S.Byte_stream.of_chan ic)
		with e ->
			S.Response.fail ~code:500 "error while reading file: %s" (Printexc.to_string e)
	)


(** Serve the page at the given path.
	@param server	Current server.
	@param req		Current request.
	@param path		Current path.*)
let serve_page server path req =
	try
		verbose (fun out ->
			fprintf out "GOT: %s\n" path;
			List.iter (fun (k, v) -> fprintf out "DEBUG: %s=%s\n" k v) (S.Request.query req));
		(List.assoc path commands) server path req		
	with
	| Not_found ->
		serve_file server path req
	| BadURL ->
		bad_syntax ()


(** Run the server. *)
let serve _ =
	let server = S.create
		~addr:"127.0.0.1"
		~port:4040
		~startup: display
		()
	in
	S.add_route_handler
		server ~meth:`GET
		S.Route.rest_of_path_urlencoded
		(serve_page server);
	match S.run server with
	| Ok () 	->
		()
	| Error e	->
		fatal_error (Printexc.to_string e)


(** Load the file. *)
let load prog map =
	try
		current_program := Quad.load prog;
		original_map := Cell.load map;
		current_vm := Vm.new_state Cell.invoke (Cell.copy !original_map)
	with
	| Quad.Error msg
	| Cell.Error msg
		-> fatal_error msg


(** Program entry. *)

let _ =
	let free_args = ref [] in

	Arg.parse
		[]
		(fun f -> free_args := f :: !free_args)
		"autocell FILE.exe FILE.map";

	match !free_args with
	| [map; prog] ->
		load prog map; serve ()
	| _ -> fatal_error "bad number of arguments!"

