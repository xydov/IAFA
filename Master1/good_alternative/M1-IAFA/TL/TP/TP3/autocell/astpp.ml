open Ast
open Symbols
let pp_binop = function
    OP_ADD -> "+"
   | OP_SUB -> "-"
   | OP_MUL -> "*"
   | OP_DIV -> "/"
   | OP_MOD -> "%"

let rec pp_expr = function
  | NONE -> failwith "NONE"
  | CST i -> string_of_int i
  | CELL(f,dx,dy) ->
     let c = "["^(string_of_int dx)^","^(string_of_int dy)^"]" in
     if f = 0 then c else (c^"."^(get_field_id f))
  | VAR i -> get_var_id i
  | BINOP(op,e1,e2) -> "("^pp_expr e1 ^" "^pp_binop op^" "^pp_expr e2^")"
  | NEG e -> "(-"^" "^(pp_expr e)^")"

let pp_comp = function
    COMP_EQ -> "="
   | COMP_NE -> "!="
   | COMP_LT -> "<"
   | COMP_LE -> "<="
   | COMP_GT -> ">"
   | COMP_GE -> ">="

let rec pp_cond = function
  | NO_COND -> failwith "NO_COND"
  | COMP(op,e1,e2) -> pp_expr e1^" "^(pp_comp op)^" "^ pp_expr e2
  | NOT c -> "!("^pp_cond c^")"
  | AND (c1,c2) -> pp_cond c1 ^" && "^pp_cond c2
  | OR (c1,c2) -> "("^pp_cond c1 ^" || "^pp_cond c2^")"

let rec pp_stmt = function
    NOP -> ""
   | SET_CELL(f,e) -> "[0,0]"^(if f=0 then "" else ("."^(get_field_id f)))^ " := " ^ (pp_expr e)
   | SET_VAR (i,e) -> (get_var_id i) ^" := "^ (pp_expr e)
   | SEQ(s1,s2) -> pp_stmt s1 ^"\n"^ pp_stmt s2
   | IF_THEN (c,s1,NOP) -> "if "^(pp_cond c) ^ " then " ^ (pp_stmt s1) ^" end"
   | IF_THEN (c,s1,s2) ->
      "if "^(pp_cond c) ^ " then " ^ (pp_stmt s1) ^
        " else " ^ (pp_stmt s2) ^
        " end"

let pp_prog (dl,b) =
  let dcl =
    String.concat ","
      (List.map (fun (id, (i, (min,max))) ->
           (if id="" then ""
            else id^" of ") ^
             string_of_int min ^".."^string_of_int max) dl) in
  "2 dimensions of "^dcl^" end\n"^
    (pp_stmt b)

