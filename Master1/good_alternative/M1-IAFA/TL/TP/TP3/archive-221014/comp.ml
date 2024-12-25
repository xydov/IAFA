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
open Cell
open Quad
open Symbols

(** Variable containing the current x position. *)
let x = 0

(** Variable containing the current y position. *)
let y = 1

(** Variable containing the width of the array. *)
let w = 2

(** Variable containing the height of the array. *)
let h = 3

(** Variable containing 1! *)
let one = 4

(** Compute the position from the relative offset.
	@param x	X offset.
	@param y	Y offset.
	@return		Corresponding position. *)
let pos x y =
	match (x, y) with
	| (0, 0)	-> pCENTER
	| (0, -1)	-> pNORTH
	| (-1, -1)	-> pNORTHWEST
	| (-1, 0)	-> pWEST
	| (-1, +1)	-> pSOUTHWEST
	| (0, +1)	-> pSOUTH
	| (+1, +1)	-> pSOUTHEAST
	| (+1, 0)	-> pEAST
	| (+1, -1)	-> pNORTHEAST
	| _			-> failwith "bad offsets"
	


(** Compile an expression.
	@param e	Expression to compile.
	@return		(register containing the result, quads producing the result). *)
let rec comp_expr e =


	match e with
	| NONE ->
		(0, [])
	| CELL (f, x, y) ->
		let v = new_reg () in 
		(v, [
			INVOKE (cGET + f, v, pos x y)
		])
	|	CST(i) -> let v = new_reg () in
		(v,[SETI (v,i)])
	| VAR(v) -> (v, [])
	| NEG(e) -> let v = new_reg () in
		let aff = [SETI (v, 0)] in 
		(v, aff @ (snd (comp_expr e)) @ [SUB (v, v, fst (comp_expr e))])
		| BINOP (operation, e1, e2) -> 
		let op1 = (comp_expr e1) in 
		let op2 = (comp_expr e2) in 
		let v = match e1, e2 with
			|	VAR(_), VAR(_) -> new_reg()
			| _ , VAR(_) -> fst op1
			| VAR(_), _ -> fst op2
			| _, _ -> fst op1 
		in
		match operation with
			OP_ADD -> (v, (snd op1) @ (snd op2) @ [ADD (v, fst op1, fst op2)])
		| OP_SUB -> (v, (snd op1) @ (snd op2) @ [SUB (v, fst op1, fst op2)])
		| OP_DIV -> (v, (snd op1) @ (snd op2) @ [DIV (v, fst op1, fst op2)])
		| OP_MUL -> (v, (snd op1) @ (snd op2) @ [MUL (v, fst op1, fst op2)])
		| OP_MOD -> (v, (snd op1) @ (snd op2) @ [MOD (v, fst op1, fst op2)])


(** Compile a condition.
	@param c		Condition to compile.
	@param l_then	Label to branch to when the condition is true.
	@param l_else	Label to branch to when the condition is false.
	@return			Quads implementing the condition. *)
let rec comp_cond c l_then l_else =


	match c with

	| _ ->
		failwith "bad condition"


(** Compile a statement.
	@param s	Statement to compile.
	@return		Quads implementing the statement. *)
let rec comp_stmt s =
	match s with
	| NOP ->
		[]
	| SEQ (s1, s2) ->
		(comp_stmt s1) @ (comp_stmt s2)
	| SET_CELL (f, e) ->
		let (v, q) = comp_expr e in
		q @ [
			INVOKE (cSET, v, f)
		]
	| SET_VAR (f, e) ->
		let (v, q) = comp_expr e in
		q @ [
			SET (f, v)
		]
	| _ ->
		failwith "bad instruction"

(** Compile the given application.
	@param flds		List of fields.
	@param stmt		Instructions.
	@return			List of quadss. *)	
let compile flds stmt =
	let x_lab = new_lab () in
	let y_lab = new_lab () in
	[
		INVOKE(cSIZE, w, h);
		SETI(one, 1);

		SETI(x, 0);
		LABEL x_lab;

		SETI(y, 0);
		LABEL y_lab;
		INVOKE(cMOVE, x, y)
	]
	@
	(comp_stmt stmt)
	@
	[
		ADD(y, y, one);
		GOTO_LT(y_lab, y, h);

		ADD(x, x, one);
		GOTO_LT(x_lab, x, w);
		STOP
	]
