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

type binop =
	OP_ADD		(** Binary operation: addition. *)
|	OP_SUB		(** Binary operation: subtraction. *)
|	OP_MUL		(** Binary operation: multiplication. *)
|	OP_DIV		(** Binary operation: division. *)
|	OP_MOD		(** Binary operation: modulo. *)

type expr =
|	NONE							(** Null expression. *)
|	CST of int						(** Constant AST: constant value. *)
|	CELL of int * int * int			(** Cell read: (field,dx, dy) *)
|	VAR of int						(** Variable read: register number. *)
|	BINOP of binop * expr * expr	(** Binary operation: (operation, operand1, operand2) *)
|	NEG of expr						(** Negation: operand *)

type comp =
	COMP_EQ		(** Comparison: equal. *)
|	COMP_NE		(** Comparison: not equal. *)
|	COMP_LT		(** Comparison: less than. *)
|	COMP_LE		(** Comparison: less or equal. *)
|	COMP_GT		(** Comparison: greater than. *)
|	COMP_GE		(** Comparison: greater or equal. *)


type cond =
|	NO_COND						(** No condition. *)
|	COMP of comp * expr * expr	(** Comparison: (comparison, left operand, right operand). *)
|	NOT of cond					(** Not operation. *)
|	AND of cond * cond			(** And operation. *)
|	OR of cond * cond				(** Or operation. *)

type stmt =
	NOP							(** Empty statement. *)
|	SET_CELL of int * expr		(** Cell assignment: (field, assigned expression). *)
|	SET_VAR of int * expr		(** Variable assignment: (register number, assigned expression). *)
|	SEQ of stmt * stmt			(** Sequence: (first statrement, second statement). *)
|	IF_THEN of cond * stmt * stmt	(** Selection: (condition, then statement, else statement). *)


(** A program is defined as a collection of fields (identifier, number, range)
	and  a statement. *)
type prog = (string * (int * (int * int))) list * stmt


(** Indent the indentation prefix t.
	@param t	Prefix to indent.
	@return		Result of indentation. *)
let indent t =
	t ^ "    "


(** Print the expression AST using the prefix t.
	@param t	Prefix for printing (indentation)
	@param e	Expression to print. *)
let rec print_expr t e =
	let op_to_string op =
		match op with
		| OP_ADD -> "OP_ADD"
		| OP_SUB -> "OP_SUB"
		| OP_MUL -> "OP_MUL"
		| OP_DIV -> "OP_DIV"
		| OP_MOD -> "OP_MOD" in

	print_string t;
	match e with
	| NONE ->
		print_string "NONE" 
	| CST i ->
		printf "CST(%d)" i
	| CELL (f, x, y) ->
		printf "CELL(%d, %d, %d)" f x y
	| VAR x ->
		printf "VAR(%d)" x
	| NEG e ->
		printf "NEG(\n";
		print_expr (t ^ "  ") e;
		printf "\n%s)" t
	| BINOP(op, e1, e2) ->
		printf "BINOP(%s,\n" (op_to_string op);
		print_expr (indent t) e1;
		printf ",\n";
		print_expr (indent t) e2;
		printf "\n%s)" t

(** Print the statement AST using the prefix t.
	@param t	Prefix for printing (indentation)
	@param s	Statement to print. *)
let rec print_stmt t s =
	print_string t;
	match s with
	| NOP ->
		printf "NOP"
	| SET_CELL(f, e) ->
		printf "SET_CELL(%d,\n" f;
		print_expr (t ^ "  ") e;
		printf "\n%s)" t
	| SET_VAR(x, e) ->
		printf "SET_VAR(%d,\n" x;
		print_expr (t ^ "  ") e;
		printf "\n%s)" t
	| SEQ (s1, s2) ->
		printf "SEQ(\n";
		print_stmt (indent t) s1;
		printf ",\n";
		print_stmt (indent t) s2;
		printf "\n%s)" t
	| IF_THEN (c, s1, s2) ->
		printf "IF_THEN(\n";
		print_cond (indent t) c;
		printf ",\n";
		print_stmt (indent t) s1;
		printf ",\n";
		print_stmt (indent t) s2;
		printf "\n%s)" t

(** Print the condition AST using the prefix t.
	@param t	Prefix for printing (indentation)
	@param c	Condition to print. *)
and print_cond t c =
	let cond_to_string c =
		match c with
		| COMP_EQ -> "COMP_EQ"
		| COMP_NE -> "COMP_NE"
		| COMP_LT -> "COMP_LT"
		| COMP_LE -> "COMP_LE"
		| COMP_GT -> "COMP_GT"
		| COMP_GE -> "COMP_GE" in

	print_string t;
	match c with
	| NO_COND ->
		printf "NO_COND"
	| COMP (c, e1, e2) ->
		printf "COMP(%s,\n" (cond_to_string c);
		print_expr (indent t) e1;
		printf ",\n";
		print_expr (indent t) e2;
		printf "\n%s)" t
	| NOT c ->
		printf "NOT(\n";
		print_cond (indent t) c;
		printf "\n%s)" t
	| AND (c1, c2) ->
		printf "AND(\n";
		print_cond (indent t) c1;
		printf ",\n";
		print_cond (indent t) c2;
		printf "\n%s)" t
	| OR (c1, c2) ->
		printf "OR(\n";
		print_cond (indent t) c1;
		printf ",\n";
		print_cond (indent t) c2;
		printf "\n%s)" t
		
