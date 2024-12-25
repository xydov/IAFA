/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 TAD de gestion d'éléments syntaxique pour les expressions arithmétiques
 
 */
/*-----------------------------------------------------------------*/
#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdio.h>
#include <stdbool.h>

/** Opaque definition of type Token and ptrToken*/
typedef struct s_Token Token;
typedef Token *ptrToken;

/** Create a Token from the string designed by s, taking only the lg first chars of the string */
Token *createTokenFromString(const char *s, int lg);

Token *createTokenFromValue(float v);

/** dDlete the give token.
 Free the memory used by the token and set the pointer to NULL.
*/
void deleteToken(ptrToken *t);

/** Test if a token represents a number.
 @param t : the token to test
 @return true if the given token represent a number, else false
 */
bool tokenIsNumber(Token *t);

/** Test if a token represents a binary operator.
 @param t : the token to test
 @return true if the given token represent a binary operator, else false
 @note Currently supported binary operators are +,-,*,/,^.
 */
bool tokenIsOperator(Token *t);

/** Test if a token represents a parenthesis.
 @param t : the token to test
 @return true if the given token represent a '(' or ')', else false
 */
bool tokenIsParenthesis(Token *t);

/** get the value of a number token.
 @param t : the token to examine
 @return the value stored in the token
 @pre tokenIsNumber(t) == true
*/
float tokenGetValue(Token *t);

/** Get the operator symbol of a binary operator token.
 @param t : the token to examine
 @return the operator symbol (@see tokenIsOperator)
 @pre tokenIsOperator(t) == true
 */
char tokenGetOperatorSymbol(Token *t);

/** Get the parenthesis symbol of a  token.
 @param t : the token to examine
 @return the parenthesis symbol
 @pre tokenIsParenthesis(t) == true
 */
char tokenGetParenthesisSymbol(Token *t);

/** Get the priority of a binaray operator token.
 @param t : the token to examine
 @return 1 if operator is + or -, 2 if operator is * or /, 3 if operator is ^.
 @pre tokenIsOperator(t) == true
 @see tokenIsOperator
 */
int tokenGetOperatorPriority(Token *t);

/** Is the operator left associative.
 @param t : the token to examine
 @return true if operator is left associative.
 @pre tokenIsOperator(t) == true
 @see tokenIsOperator
 */
bool tokenOperatorIsLeftAssociative(Token *t);

/** Dump the token to the given file */
void tokenDump(FILE *f, Token *t);
#endif
