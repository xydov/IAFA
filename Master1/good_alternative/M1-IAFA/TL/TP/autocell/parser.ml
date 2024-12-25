type token =
  | EOF
  | DIMENSIONS
  | END
  | OF
  | ASSIGN
  | COMMA
  | LBRACKET
  | RBRACKET
  | LPARENTHS
  | RPARENTHS
  | DOT_DOT
  | DOT
  | ADDITION
  | SOUSTRACTION
  | MULTIPLICATION
  | DIVISION
  | MODULO
  | GE
  | LE
  | NE
  | LT
  | GR
  | EQ
  | IF
  | THEN
  | ELSE
  | ELSEIF
  | ID of (string)
  | INT of (int)

open Parsing;;
let _ = parse_error;;
# 17 "parser.mly"

open Common
open Ast
open Printf
open Symbols

(** Raise a syntax error with the given message.
	@param msg	Message of the error. *)
let error msg =
	raise (SyntaxError msg)


(** Restructure the when assignment into selections.
	@param f	Function to build the assignment.
	@param v	Initial values.
	@param ws	Sequence of (condition, expression).
	@return		Built statement. *)
let rec make_when f v ws =
	match ws with
	| [] ->	f v
	| (c, nv)::t ->
		IF_THEN(c, f v, make_when f nv t)

# 59 "parser.ml"
let yytransl_const = [|
    0 (* EOF *);
  257 (* DIMENSIONS *);
  258 (* END *);
  259 (* OF *);
  260 (* ASSIGN *);
  261 (* COMMA *);
  262 (* LBRACKET *);
  263 (* RBRACKET *);
  264 (* LPARENTHS *);
  265 (* RPARENTHS *);
  266 (* DOT_DOT *);
  267 (* DOT *);
  268 (* ADDITION *);
  269 (* SOUSTRACTION *);
  270 (* MULTIPLICATION *);
  271 (* DIVISION *);
  272 (* MODULO *);
  273 (* GE *);
  274 (* LE *);
  275 (* NE *);
  276 (* LT *);
  277 (* GR *);
  278 (* EQ *);
  279 (* IF *);
  280 (* THEN *);
  281 (* ELSE *);
  282 (* ELSEIF *);
    0|]

let yytransl_block = [|
  283 (* ID *);
  284 (* INT *);
    0|]

let yylhs = "\255\255\
\001\000\002\000\002\000\004\000\004\000\005\000\003\000\003\000\
\006\000\006\000\006\000\010\000\010\000\010\000\011\000\007\000\
\009\000\009\000\009\000\009\000\009\000\009\000\009\000\008\000\
\008\000\013\000\013\000\012\000\012\000\012\000\014\000\014\000\
\014\000\014\000\015\000\015\000\015\000\015\000\000\000"

let yylen = "\002\000\
\007\000\003\000\001\000\001\000\003\000\005\000\002\000\000\000\
\003\000\003\000\006\000\002\000\005\000\000\000\001\000\005\000\
\003\000\003\000\003\000\003\000\003\000\003\000\000\000\001\000\
\001\000\002\000\002\000\003\000\003\000\001\000\003\000\003\000\
\003\000\001\000\001\000\001\000\001\000\003\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\000\000\039\000\000\000\000\000\000\000\000\000\
\000\000\000\000\004\000\000\000\000\000\000\000\000\000\000\000\
\002\000\000\000\000\000\000\000\000\000\000\000\000\000\005\000\
\000\000\000\000\000\000\000\000\000\000\037\000\036\000\035\000\
\000\000\000\000\000\000\025\000\000\000\034\000\000\000\001\000\
\007\000\000\000\006\000\000\000\000\000\026\000\027\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\010\000\009\000\000\000\038\000\017\000\
\018\000\019\000\020\000\021\000\022\000\000\000\000\000\000\000\
\031\000\032\000\033\000\016\000\000\000\000\000\000\000\012\000\
\000\000\011\000\000\000\000\000\015\000\013\000"

let yydgoto = "\002\000\
\004\000\009\000\021\000\010\000\011\000\022\000\032\000\033\000\
\034\000\079\000\086\000\035\000\036\000\037\000\038\000"

let yysindex = "\017\000\
\013\255\000\000\041\255\000\000\045\255\235\254\046\255\040\255\
\050\255\055\255\000\000\033\255\034\255\024\255\038\255\054\255\
\000\000\039\255\016\255\062\255\068\000\024\255\066\255\000\000\
\043\255\067\255\016\255\016\255\016\255\000\000\000\000\000\000\
\037\255\049\255\253\254\000\000\245\254\000\000\016\255\000\000\
\000\000\016\255\000\000\047\255\065\255\000\000\000\000\016\255\
\016\255\016\255\016\255\016\255\016\255\024\255\011\255\011\255\
\011\255\011\255\011\255\000\000\000\000\069\255\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\251\254\245\254\245\254\
\000\000\000\000\000\000\000\000\024\255\016\255\075\255\000\000\
\056\255\000\000\024\255\251\254\000\000\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\076\255\000\000\000\000\000\000\081\000\000\000\000\000\
\000\000\000\000\058\255\000\000\000\000\081\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\079\000\000\000\001\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\050\255\027\000\053\000\
\000\000\000\000\000\000\000\000\000\000\058\255\000\000\000\000\
\000\000\000\000\000\000\050\255\000\000\000\000"

let yygindex = "\000\000\
\000\000\000\000\061\000\000\000\069\000\204\255\242\255\240\255\
\007\000\002\000\000\000\000\000\000\000\246\255\213\255"

let yytablesize = 362
let yytable = "\023\000\
\030\000\070\000\057\000\058\000\059\000\007\000\008\000\023\000\
\055\000\056\000\045\000\046\000\047\000\073\000\074\000\075\000\
\018\000\001\000\027\000\077\000\078\000\018\000\060\000\027\000\
\080\000\061\000\028\000\028\000\029\000\018\000\084\000\064\000\
\065\000\066\000\067\000\068\000\069\000\030\000\031\000\023\000\
\003\000\005\000\030\000\031\000\071\000\072\000\019\000\006\000\
\012\000\013\000\020\000\014\000\029\000\048\000\049\000\050\000\
\051\000\052\000\053\000\015\000\016\000\017\000\023\000\025\000\
\007\000\039\000\026\000\040\000\023\000\042\000\043\000\044\000\
\054\000\063\000\062\000\076\000\082\000\003\000\024\000\083\000\
\008\000\023\000\041\000\024\000\081\000\085\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\030\000\000\000\000\000\000\000\030\000\000\000\
\000\000\030\000\000\000\000\000\030\000\030\000\000\000\000\000\
\000\000\030\000\030\000\030\000\030\000\030\000\030\000\030\000\
\030\000\030\000\030\000\030\000\028\000\000\000\000\000\000\000\
\028\000\000\000\000\000\028\000\000\000\000\000\028\000\028\000\
\000\000\000\000\000\000\028\000\028\000\028\000\028\000\028\000\
\028\000\028\000\028\000\028\000\028\000\028\000\029\000\000\000\
\000\000\000\000\029\000\000\000\000\000\029\000\000\000\000\000\
\029\000\029\000\000\000\000\000\000\000\029\000\029\000\029\000\
\029\000\029\000\029\000\029\000\029\000\029\000\029\000\029\000\
\024\000\000\000\000\000\000\000\024\000\000\000\000\000\024\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\024\000\
\024\000\024\000\024\000\024\000\024\000\024\000\024\000\024\000\
\024\000\024\000"

let yycheck = "\014\000\
\000\000\054\000\014\001\015\001\016\001\027\001\028\001\022\000\
\012\001\013\001\027\000\028\000\029\000\057\000\058\000\059\000\
\006\001\001\000\008\001\025\001\026\001\006\001\039\000\008\001\
\077\000\042\000\000\000\012\001\013\001\006\001\083\000\048\000\
\049\000\050\000\051\000\052\000\053\000\027\001\028\001\054\000\
\028\001\001\001\027\001\028\001\055\000\056\000\023\001\003\001\
\003\001\010\001\027\001\002\001\000\000\017\001\018\001\019\001\
\020\001\021\001\022\001\005\001\028\001\028\001\077\000\010\001\
\027\001\004\001\028\001\000\000\083\000\004\001\028\001\005\001\
\024\001\009\001\028\001\007\001\002\001\002\001\000\000\024\001\
\000\000\024\001\022\000\015\000\078\000\084\000\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\002\001\255\255\255\255\255\255\006\001\255\255\
\255\255\009\001\255\255\255\255\012\001\013\001\255\255\255\255\
\255\255\017\001\018\001\019\001\020\001\021\001\022\001\023\001\
\024\001\025\001\026\001\027\001\002\001\255\255\255\255\255\255\
\006\001\255\255\255\255\009\001\255\255\255\255\012\001\013\001\
\255\255\255\255\255\255\017\001\018\001\019\001\020\001\021\001\
\022\001\023\001\024\001\025\001\026\001\027\001\002\001\255\255\
\255\255\255\255\006\001\255\255\255\255\009\001\255\255\255\255\
\012\001\013\001\255\255\255\255\255\255\017\001\018\001\019\001\
\020\001\021\001\022\001\023\001\024\001\025\001\026\001\027\001\
\002\001\255\255\255\255\255\255\006\001\255\255\255\255\009\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\017\001\
\018\001\019\001\020\001\021\001\022\001\023\001\024\001\025\001\
\026\001\027\001"

let yynames_const = "\
  EOF\000\
  DIMENSIONS\000\
  END\000\
  OF\000\
  ASSIGN\000\
  COMMA\000\
  LBRACKET\000\
  RBRACKET\000\
  LPARENTHS\000\
  RPARENTHS\000\
  DOT_DOT\000\
  DOT\000\
  ADDITION\000\
  SOUSTRACTION\000\
  MULTIPLICATION\000\
  DIVISION\000\
  MODULO\000\
  GE\000\
  LE\000\
  NE\000\
  LT\000\
  GR\000\
  EQ\000\
  IF\000\
  THEN\000\
  ELSE\000\
  ELSEIF\000\
  "

let yynames_block = "\
  ID\000\
  INT\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : 'config) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : 'opt_statements) in
    Obj.repr(
# 86 "parser.mly"
 (
		if _1 != 2 then error "only 2 dimension accepted";
		(_4, _6)
	)
# 300 "parser.ml"
               : Ast.prog))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 94 "parser.mly"
  (
			if _1 >= _3 then error "illegal field values";
			[("", (0, (_1, _3)))]
		)
# 311 "parser.ml"
               : 'config))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'fields) in
    Obj.repr(
# 99 "parser.mly"
  ( set_fields _1 )
# 318 "parser.ml"
               : 'config))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'field) in
    Obj.repr(
# 104 "parser.mly"
  ( [_1] )
# 325 "parser.ml"
               : 'fields))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'fields) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'field) in
    Obj.repr(
# 106 "parser.mly"
  (_3 :: _1 )
# 333 "parser.ml"
               : 'fields))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 111 "parser.mly"
  (
			if _3 >= _5 then error "illegal field values";
			(_1, (_3, _5))
		)
# 345 "parser.ml"
               : 'field))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'statement) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'opt_statements) in
    Obj.repr(
# 120 "parser.mly"
  ( if (_2 = NOP) then _1 else SEQ (_1, _2) )
# 353 "parser.ml"
               : 'opt_statements))
; (fun __caml_parser_env ->
    Obj.repr(
# 123 "parser.mly"
  (NOP)
# 359 "parser.ml"
               : 'opt_statements))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'cell) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 129 "parser.mly"
  (
			if (fst _1) != 0 then error "assigned x must be 0";
			if (snd _1) != 0 then error "assigned Y must be 0";
			SET_CELL (0, _3)
		)
# 371 "parser.ml"
               : 'statement))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 135 "parser.mly"
  (
			if ((get_var _1)) = -1 then SET_VAR (declare_var _1, _3)
			else SET_VAR (get_var _1, _3)
		)
# 382 "parser.ml"
               : 'statement))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : 'condition) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'statement) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : 'elseStatement) in
    Obj.repr(
# 140 "parser.mly"
  (IF_THEN(_2, _4, _5))
# 391 "parser.ml"
               : 'statement))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'statement) in
    Obj.repr(
# 145 "parser.mly"
  (_2)
# 398 "parser.ml"
               : 'elseStatement))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 3 : 'condition) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : 'statement) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'elseStatement_T) in
    Obj.repr(
# 147 "parser.mly"
  (IF_THEN(_2, _4, _5))
# 407 "parser.ml"
               : 'elseStatement))
; (fun __caml_parser_env ->
    Obj.repr(
# 148 "parser.mly"
  (NOP)
# 413 "parser.ml"
               : 'elseStatement))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'elseStatement) in
    Obj.repr(
# 153 "parser.mly"
  (_1)
# 420 "parser.ml"
               : 'elseStatement_T))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 3 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : int) in
    Obj.repr(
# 159 "parser.mly"
  (
			if (_2 < -1) || (_2 > 1) then error "x out of range";
			if (_4 < -1) || (_4 > 1) then error "x out of range";
			(_2, _4)
		)
# 432 "parser.ml"
               : 'cell))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expression) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 168 "parser.mly"
  (COMP(COMP_GE, _1, _3))
# 440 "parser.ml"
               : 'condition))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expression) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 170 "parser.mly"
  (COMP(COMP_LE, _1, _3))
# 448 "parser.ml"
               : 'condition))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expression) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 172 "parser.mly"
  (COMP(COMP_NE, _1, _3))
# 456 "parser.ml"
               : 'condition))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expression) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 174 "parser.mly"
  (COMP(COMP_LT, _1, _3))
# 464 "parser.ml"
               : 'condition))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expression) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 176 "parser.mly"
  (COMP(COMP_GT, _1, _3))
# 472 "parser.ml"
               : 'condition))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expression) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 178 "parser.mly"
  (COMP(COMP_EQ, _1, _3))
# 480 "parser.ml"
               : 'condition))
; (fun __caml_parser_env ->
    Obj.repr(
# 179 "parser.mly"
  ( error "Wrong condition for an if statement")
# 486 "parser.ml"
               : 'condition))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expressionARTH) in
    Obj.repr(
# 184 "parser.mly"
  (_1)
# 493 "parser.ml"
               : 'expression))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expressionUNR) in
    Obj.repr(
# 186 "parser.mly"
  (_1)
# 500 "parser.ml"
               : 'expression))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 191 "parser.mly"
  (_2)
# 507 "parser.ml"
               : 'expressionUNR))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expression) in
    Obj.repr(
# 193 "parser.mly"
  (NEG (_2))
# 514 "parser.ml"
               : 'expressionUNR))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expressionARTH) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expressionT) in
    Obj.repr(
# 199 "parser.mly"
  ( BINOP (OP_ADD, _1, _3) )
# 522 "parser.ml"
               : 'expressionARTH))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expressionARTH) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expressionT) in
    Obj.repr(
# 201 "parser.mly"
  ( BINOP (OP_SUB, _1, _3) )
# 530 "parser.ml"
               : 'expressionARTH))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expressionT) in
    Obj.repr(
# 203 "parser.mly"
  ( _1 )
# 537 "parser.ml"
               : 'expressionARTH))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expressionT) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'factor) in
    Obj.repr(
# 208 "parser.mly"
  ( BINOP (OP_MUL, _1, _3) )
# 545 "parser.ml"
               : 'expressionT))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expressionT) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'factor) in
    Obj.repr(
# 210 "parser.mly"
  ( BINOP (OP_DIV, _1, _3) )
# 553 "parser.ml"
               : 'expressionT))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expressionT) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'factor) in
    Obj.repr(
# 212 "parser.mly"
  ( BINOP (OP_MOD, _1, _3) )
# 561 "parser.ml"
               : 'expressionT))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'factor) in
    Obj.repr(
# 214 "parser.mly"
  ( _1 )
# 568 "parser.ml"
               : 'expressionT))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cell) in
    Obj.repr(
# 220 "parser.mly"
  ( CELL (0, fst _1, snd _1)
		)
# 576 "parser.ml"
               : 'factor))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 224 "parser.mly"
  ( 
			CST _1
		)
# 585 "parser.ml"
               : 'factor))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 229 "parser.mly"
  ( 
			if ((get_var _1) = -1) then error (Printf.sprintf "undeclared variable %s" _1)
			else VAR (get_var _1)
		)
# 595 "parser.ml"
               : 'factor))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expression) in
    Obj.repr(
# 234 "parser.mly"
  ( _2 )
# 602 "parser.ml"
               : 'factor))
(* Entry program *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let program (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Ast.prog)
