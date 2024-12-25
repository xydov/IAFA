{
open Asparser

let ht: token Common.StringHashtbl.t = Common.StringHashtbl.create 17

let _ =
	List.iter
		(fun (k, v) -> Common.StringHashtbl.add ht k v)
		[
			("add",		ADD);
			("sub",		SUB);
			("mul",		MUL);
			("div",		DIV);
			("mod",		MOD);
			("set",		SET);
			("seti",	SETI);
			("goto",	GOTO);
			("goto_eq",	GOTO_EQ);
			("goto_ne", GOTO_NE);
			("goto_lt", GOTO_LT);
			("goto_le", GOTO_LE);
			("goto_gt", GOTO_GT);
			("goto_ge", GOTO_GE);
			("call", 	CALL);
			("return",	RETURN);
			("invoke",	INVOKE);
			("stop",	STOP)
		]

let scan_id id =
	try
		Common.StringHashtbl.find ht (String.lowercase_ascii id)
	with Not_found ->
		LABEL(id)
}

let comment = '@' [^ '\n' '\r']*
let space	= [' ' '\t' '\n' '\r']+
let id		= ['a' - 'z' 'A' - 'Z' '_']['a' - 'z' 'A' - 'Z' '_' '0' - '9']*
let int		= ['0' - '9']+

rule scan =
parse	int	as v				{ INT (int_of_string v) }
|		['r' 'R'] (int as v)	{ REG (int_of_string v) }
|		id as s					{ scan_id s }
|		':'						{ COLON }
|		','						{ COMMA }
|		'#'						{ SHARP }
|		".meta"					{ META }
|		"\""					{ STR (str lexbuf) }
|		eof						{ EOF }
|		space					{ scan lexbuf }
|		comment					{ scan lexbuf }
|		_ as c					{ raise (Common.LexerError (Printf.sprintf "unknown character '%c'" c)) }
and str =
parse	"\\\""					{ (String.make 1 '"') ^ (str lexbuf) }
|		("\\"[^ '"']) as s		{ s ^ (str lexbuf) }
|		'"'						{ "" }
|		[^'"' '\\']+ as s		{ s ^ (str lexbuf) }
|		eof						{ raise (Common.LexerError "EOF in middle of string") }
