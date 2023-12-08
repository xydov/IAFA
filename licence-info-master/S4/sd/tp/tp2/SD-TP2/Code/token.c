#include "token.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


/* Enum type that defines the token type */
typedef enum t_Token {number, binary_operator, parenthesis} TokenType;

struct s_Token {
	TokenType type;
	union {
		float number;
		char symbol;
	} value;
};

Token *createTokenFromString(const char *s, int lg) {
	(void)lg;
	Token *t = malloc(sizeof(Token));
	if (isdigit(*s) || *s == '.') {
		t->type = number;
		t->value.number = strtof(s, NULL);
	} else if (*s == '(' || *s == ')') {
		t->type = parenthesis;
		t->value.symbol = *s;
	} else {
		t->type = binary_operator;
		t->value.symbol = *s;
	}
	return t;
}

Token *createTokenFromValue(float v) {
	Token *t = malloc(sizeof(Token));
	t->type = number;
	t->value.number = v;
	return t;
}

void deleteToken(ptrToken *t) {
	free (*t);
	*t = NULL;
}

bool tokenIsNumber(Token *t) {
	return t->type == number;
}

bool tokenIsOperator(Token *t) {
	return t->type == binary_operator;
}

bool tokenIsParenthesis(Token *t) {
	return t->type == parenthesis;
}

float tokenGetValue(Token *t) {
	assert( tokenIsNumber(t) );
	return t->value.number;
}

char tokenGetOperatorSymbol(Token *t) {
	assert(tokenIsOperator(t) );
	return t->value.symbol;
}

char tokenGetParenthesisSymbol(Token *t) {
	assert( tokenIsParenthesis(t) );
	return t->value.symbol;
}

int tokenGetOperatorPriority(Token *t){
	assert( tokenIsOperator(t) );
	switch( t->value.symbol ) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
		default:
			return -1;
	}
}

bool tokenOperatorIsLeftAssociative(Token *t){
	assert( tokenIsOperator(t) );
	switch( t->value.symbol ) {
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
		case '^':
			return false;
		default:
			return false;
	}
}

void tokenDump(FILE *f, Token *t) {
	if (t->type == number)
		fprintf(f, "%f ", t->value.number);
	else
		fprintf(f, "%c ", t->value.symbol);
}
