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

Require Import ZArith.
Require Import Strings.String.

Inductive binop :=
	OP_ADD		(** Binary operation: addition. *)
|	OP_SUB		(** Binary operation: subtraction. *)
|	OP_MUL		(** Binary operation: multiplication. *)
|	OP_DIV		(** Binary operation: division. *)
|	OP_MOD		(** Binary operation: modulo. *)
.

Inductive expr :=
|	NONE				(** Null expression. *)
|	CST (c:Z)			(** Constant AST: constant value. *)
|	CELL (fld:nat) (dx:Z) (dy:Z)	(** Cell read: (field, dx, dy) *)
|	VAR (r:nat)			(** Variable read: register number. *)
|	BINOP (op:binop) (left:expr) (right:expr)	(** Binary operation: (operation, operand1, operand2) *)
|	NEG (arg:expr)			(** Negation: operand *)
.

Inductive comp :=
	COMP_EQ		(** Comparison: equal. *)
|	COMP_NE		(** Comparison: not equal. *)
|	COMP_LT		(** Comparison: less than. *)
|	COMP_LE		(** Comparison: less or equal. *)
|	COMP_GT		(** Comparison: greater than. *)
|	COMP_GE		(** Comparison: greater or equal. *)
.

Inductive cond :=
|	NO_COND				(** No condition. *)
|	COMP (op:comp) (left:expr) (right:expr)	(** Comparison: (comparison, left operand, right operand). *)
|	NOT (arg:cond)			(** Not operation. *)
|	AND (left:cond) (right:cond)	(** And operation. *)
|	OR (left:cond) (right:cond)	(** Or operation. *)
.

Inductive stmt :=
	NOP					(** Empty statement. *)
|	SET_CELL (field:nat) (value:expr)	(** Cell assignment: (field, assigned expression). *)
|	SET_VAR (reg:nat) (value:expr)		(** Variable assignment: (register number, assigned expression). *)
|	SEQ (left:stmt) (right:stmt)		(** Sequence: (first statrement, second statement). *)
|	IF_THEN (cnd:cond) (ift:stmt) (iff:stmt)	(** Selection: (condition, then statement, else statement). *)
.

(** A program is defined as a collection of fields (identifier, number, range)
	and  a statement. *)

Definition prog := (list (string * (nat * (nat * nat))) * stmt)%type.
