type token =
  | ADD
  | SUB
  | MUL
  | DIV
  | MOD
  | SET
  | SETI
  | GOTO
  | GOTO_EQ
  | GOTO_NE
  | GOTO_LT
  | GOTO_LE
  | GOTO_GT
  | GOTO_GE
  | CALL
  | RETURN
  | INVOKE
  | STOP
  | REG of (int)
  | INT of (int)
  | LABEL of (string)
  | STR of (string)
  | COMMA
  | SHARP
  | COLON
  | META
  | EOF

open Parsing;;
let _ = parse_error;;
# 17 "asparser.mly"

open Common
open Printf
open Quad

let quads = Array.make 1000 Quad.STOP
let cnt = ref 0

let labels: int StringHashtbl.t = StringHashtbl.create 253

let backpatches: (string * int) list ref = ref []

let metas = ref []

(** Add a new quad to the program.
	@param quad		Added quad. *)
let gen quad =
	quads.(!cnt) <- quad;
	incr cnt

(** Get the number of the next quad..
	@return	Next quad number. *)
let nextquad _ =
	!cnt

(** Apply a backpatch on the goto at address g in order to make it
	branch to address a.
	@param g	Address of goto to patch.
	@param a	Branch address. *)
let backpatch g a =
	quads.(g) <-
		match quads.(g) with
		| Quad.GOTO _				-> Quad.GOTO a
		| Quad.GOTO_EQ (_, r, s)	-> Quad.GOTO_EQ (a, r, s)
		| Quad.GOTO_NE (_, r, s)	-> Quad.GOTO_NE (a, r, s)
		| Quad.GOTO_LT (_, r, s)	-> Quad.GOTO_LT (a, r, s)
		| Quad.GOTO_LE (_, r, s)	-> Quad.GOTO_LE (a, r, s)
		| Quad.GOTO_GT (_, r, s)	-> Quad.GOTO_GT (a, r, s)
		| Quad.GOTO_GE (_, r, s)	-> Quad.GOTO_GE (a, r, s)
		| _							-> failwith "Backpatched a non-goto instruction!"

let resolve_label label = 
	try
		StringHashtbl.find labels label
	with Not_found ->
		(backpatches := (label, nextquad ()) :: !backpatches; 0)

let resolve_backpatches _ =
	let rec resolve patches =
		match patches with
		| [] -> ()
		| (l, a)::t -> 
			try
				backpatch a (StringHashtbl.find labels l);
				resolve t
			with Not_found ->
				Printf.fprintf stderr "ERROR: cannot resolve %s" l;
				raise Exit in
	resolve !backpatches

# 94 "asparser.ml"
let yytransl_const = [|
  257 (* ADD *);
  258 (* SUB *);
  259 (* MUL *);
  260 (* DIV *);
  261 (* MOD *);
  262 (* SET *);
  263 (* SETI *);
  264 (* GOTO *);
  265 (* GOTO_EQ *);
  266 (* GOTO_NE *);
  267 (* GOTO_LT *);
  268 (* GOTO_LE *);
  269 (* GOTO_GT *);
  270 (* GOTO_GE *);
  271 (* CALL *);
  272 (* RETURN *);
  273 (* INVOKE *);
  274 (* STOP *);
  279 (* COMMA *);
  280 (* SHARP *);
  281 (* COLON *);
  282 (* META *);
    0 (* EOF *);
    0|]

let yytransl_block = [|
  275 (* REG *);
  276 (* INT *);
  277 (* LABEL *);
  278 (* STR *);
    0|]

let yylhs = "\255\255\
\001\000\002\000\002\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\003\000\003\000\003\000\003\000\003\000\000\000"

let yylen = "\002\000\
\002\000\001\000\002\000\003\000\002\000\001\000\006\000\006\000\
\006\000\006\000\006\000\004\000\005\000\002\000\006\000\006\000\
\006\000\006\000\006\000\006\000\002\000\001\000\006\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\022\000\000\000\006\000\000\000\000\000\024\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\014\000\000\000\000\000\000\000\000\000\000\000\000\000\021\000\
\000\000\005\000\000\000\001\000\003\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\004\000\000\000\000\000\000\000\000\000\
\000\000\012\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\013\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\007\000\
\008\000\009\000\010\000\011\000\015\000\016\000\019\000\020\000\
\017\000\018\000\023\000"

let yydgoto = "\002\000\
\023\000\024\000\025\000"

let yysindex = "\017\000\
\255\254\000\000\000\255\002\255\003\255\004\255\005\255\007\255\
\008\255\009\255\010\255\011\255\012\255\013\255\014\255\015\255\
\016\255\000\000\018\255\000\000\017\255\019\255\000\000\028\000\
\255\254\006\255\020\255\021\255\022\255\023\255\024\255\025\255\
\000\000\026\255\027\255\028\255\029\255\030\255\031\255\000\000\
\032\255\000\000\034\255\000\000\000\000\038\255\039\255\040\255\
\041\255\042\255\043\255\044\255\045\255\046\255\047\255\048\255\
\050\255\051\255\052\255\000\000\053\255\054\255\055\255\056\255\
\057\255\000\000\061\255\059\255\060\255\062\255\063\255\064\255\
\065\255\066\255\071\255\072\255\073\255\074\255\075\255\000\000\
\076\255\077\255\078\255\079\255\080\255\081\255\082\255\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\039\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000"

let yygindex = "\000\000\
\000\000\016\000\000\000"

let yytablesize = 102
let yytable = "\003\000\
\004\000\005\000\006\000\007\000\008\000\009\000\010\000\011\000\
\012\000\013\000\014\000\015\000\016\000\017\000\018\000\019\000\
\020\000\001\000\026\000\021\000\027\000\028\000\029\000\030\000\
\022\000\031\000\032\000\044\000\046\000\033\000\034\000\035\000\
\036\000\037\000\038\000\039\000\040\000\041\000\002\000\043\000\
\045\000\042\000\047\000\048\000\049\000\050\000\051\000\052\000\
\053\000\054\000\055\000\056\000\057\000\058\000\059\000\060\000\
\061\000\062\000\063\000\064\000\065\000\066\000\000\000\068\000\
\069\000\070\000\071\000\067\000\072\000\073\000\000\000\074\000\
\000\000\000\000\000\000\075\000\076\000\077\000\078\000\079\000\
\080\000\081\000\082\000\000\000\083\000\084\000\085\000\086\000\
\087\000\088\000\089\000\090\000\091\000\092\000\093\000\094\000\
\095\000\096\000\097\000\098\000\000\000\099\000"

let yycheck = "\001\001\
\002\001\003\001\004\001\005\001\006\001\007\001\008\001\009\001\
\010\001\011\001\012\001\013\001\014\001\015\001\016\001\017\001\
\018\001\001\000\019\001\021\001\019\001\019\001\019\001\019\001\
\026\001\019\001\019\001\000\000\023\001\021\001\021\001\021\001\
\021\001\021\001\021\001\021\001\021\001\020\001\000\000\021\001\
\025\000\025\001\023\001\023\001\023\001\023\001\023\001\023\001\
\023\001\023\001\023\001\023\001\023\001\023\001\023\001\022\001\
\019\001\019\001\019\001\019\001\019\001\019\001\255\255\019\001\
\019\001\019\001\019\001\024\001\019\001\019\001\255\255\020\001\
\255\255\255\255\255\255\023\001\023\001\023\001\023\001\023\001\
\020\001\023\001\023\001\255\255\023\001\023\001\023\001\023\001\
\023\001\019\001\019\001\019\001\019\001\019\001\019\001\019\001\
\019\001\019\001\019\001\019\001\255\255\020\001"

let yynames_const = "\
  ADD\000\
  SUB\000\
  MUL\000\
  DIV\000\
  MOD\000\
  SET\000\
  SETI\000\
  GOTO\000\
  GOTO_EQ\000\
  GOTO_NE\000\
  GOTO_LT\000\
  GOTO_LE\000\
  GOTO_GT\000\
  GOTO_GE\000\
  CALL\000\
  RETURN\000\
  INVOKE\000\
  STOP\000\
  COMMA\000\
  SHARP\000\
  COLON\000\
  META\000\
  EOF\000\
  "

let yynames_block = "\
  REG\000\
  INT\000\
  LABEL\000\
  STR\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'commands) in
    Obj.repr(
# 115 "asparser.mly"
 (
		gen Quad.STOP;
		resolve_backpatches ();
		(!cnt, quads)
	)
# 264 "asparser.ml"
               : int * Quad.quad array))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'command) in
    Obj.repr(
# 124 "asparser.mly"
  ( () )
# 271 "asparser.ml"
               : 'commands))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'command) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'commands) in
    Obj.repr(
# 126 "asparser.mly"
  ( () )
# 279 "asparser.ml"
               : 'commands))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 131 "asparser.mly"
  ( metas := (_2, _3)::!metas )
# 287 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : string) in
    Obj.repr(
# 133 "asparser.mly"
  (
			if StringHashtbl.mem labels _1
			then raise (SyntaxError (sprintf "label %s already used!" _1))
			else StringHashtbl.add labels _1 (nextquad ())
		)
# 298 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    Obj.repr(
# 139 "asparser.mly"
  ( gen Quad.STOP )
# 304 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 141 "asparser.mly"
  ( gen (Quad.ADD (_2, _4, _6)) )
# 313 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 143 "asparser.mly"
  ( gen (Quad.SUB (_2, _4, _6)) )
# 322 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 145 "asparser.mly"
  ( gen (Quad.MUL (_2, _4, _6)) )
# 331 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 147 "asparser.mly"
  ( gen (Quad.DIV (_2, _4, _6)) )
# 340 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 149 "asparser.mly"
  ( gen (Quad.MOD (_2, _4, _6)) )
# 349 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 151 "asparser.mly"
  ( gen (Quad.SET (_2, _4)) )
# 357 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 3 : int) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 153 "asparser.mly"
  ( gen (Quad.SETI (_2, _5)) )
# 365 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 155 "asparser.mly"
  ( gen (Quad.GOTO (resolve_label _2)) )
# 372 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 157 "asparser.mly"
  ( gen (Quad.GOTO_EQ (resolve_label _2, _4, _6)) )
# 381 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 159 "asparser.mly"
  ( gen (Quad.GOTO_NE (resolve_label _2, _4, _6)) )
# 390 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 161 "asparser.mly"
  ( gen (Quad.GOTO_GT (resolve_label _2, _4, _6)) )
# 399 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 163 "asparser.mly"
  ( gen (Quad.GOTO_GE (resolve_label _2, _4, _6)) )
# 408 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 165 "asparser.mly"
  ( gen (Quad.GOTO_LT (resolve_label _2, _4, _6)) )
# 417 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 167 "asparser.mly"
  ( gen (Quad.GOTO_LE (resolve_label _2, _4, _6)) )
# 426 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 169 "asparser.mly"
  ( gen (Quad.CALL (resolve_label _2)) )
# 433 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    Obj.repr(
# 171 "asparser.mly"
  ( gen Quad.RETURN )
# 439 "asparser.ml"
               : 'command))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 4 : int) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : int) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 173 "asparser.mly"
  ( gen (Quad.INVOKE (_2, _4, _6)) )
# 448 "asparser.ml"
               : 'command))
(* Entry listing *)
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
let listing (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : int * Quad.quad array)
;;
# 177 "asparser.mly"

# 475 "asparser.ml"
