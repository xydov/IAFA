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

(* Execution of a VM program *)

exception Exit

open Common
open Printf



(* option processing *)
let dis = ref false
let verbose = ref false
let step_count = ref 10
let last = ref false

let opts = [
	("-d", Arg.Set dis, "disassemble instructions");
	("-v", Arg.Set verbose, "display the intermediaite states");
	("-s", Arg.Set_int step_count, "number of steps to perform");
	("-l", Arg.Set last, "display map at end")
]
let  doc = "AutoCell execution"


(** Execute the given program.
	@param prog		Program to execute.
	@param world	State to execute in. *)
let process (prog: Quad.prog) map =
	let prog = Quad.quads prog in

	let rec run state =
		if Vm.ended state then state else
		(*if !dis then
			let pc = Vm.get_pc state in
			Printf.printf "\t%04d %s\n" pc (Quad.to_string prog.(pc));*)
		run (Vm.step state prog) in

	let rec iter map step =
		if step >= !step_count then () else
		(
			ignore (run (Vm.new_state Cell.invoke map));
			let map = Cell.switch map in
			if !verbose then (
				printf "\nStep %d\n" step;
				Cell.print map 0
			);
			iter map (step + 1)
		) in

	try
		if !verbose then Cell.print map 0;
		iter map 0
	with
	| Vm.Error (_, m) ->
		fprintf stderr "ERROR: VM: %s\n" m
	

(** Scan the arguments, load the program and the map and start the
	execution
	@param args		Free arguments *)
let scan args =

	try
		match args with
		| [ world; prog]	->
			let map = (Cell.load world) in
			process (Quad.load prog) map;
			Cell.print map 0
		| _					->
			Arg.usage opts "ERROR: syntax: game program [map]"
	with
	| Quad.Error msg
	| Cell.Error msg ->
			fatal_error msg


(* Démarrage. *)
let _ = 
	let free_args = ref [] in
	Arg.parse opts (fun arg -> free_args := arg :: !free_args) doc;
	scan !free_args


