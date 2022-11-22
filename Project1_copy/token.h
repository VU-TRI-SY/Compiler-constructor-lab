/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __TOKEN_H__
#define __TOKEN_H__

#define MAX_IDENT_LEN 15
#define MAX_STRING_LEN 50
#define KEYWORDS_COUNT 20

typedef enum {
  TK_NONE, TK_IDENT, TK_NUMBER, TK_FLOAT, TK_CHAR, TK_EOF,

  KW_PROGRAM, KW_CONST, KW_TYPE, KW_VAR, TK_STRING, KW_FLOAT,
  KW_INTEGER, KW_CHAR, KW_ARRAY, KW_OF, 
  KW_FUNCTION, KW_PROCEDURE,
  KW_BEGIN, KW_END, KW_CALL,
  KW_IF, KW_THEN, KW_ELSE,
  KW_WHILE, KW_DO, KW_FOR, KW_TO,

  SB_SEMICOLON, SB_COLON, SB_PERIOD, SB_COMMA, SB_MODULO, 
  SB_ASSIGN_PLUS, SB_ASSIGN_SUBTRACT, SB_ASSIGN_TIME, 
  SB_ASSIGN_DIVIDE, SB_ASSIGN, SB_EQ, SB_NEQ, SB_LT, SB_LE, 
  SB_GT, SB_GE, SB_PLUS, SB_MINUS, SB_TIMES, SB_SLASH,
  SB_LPAR, SB_RPAR, SB_LSEL, SB_RSEL
} TokenType; 

typedef struct {
  char string[MAX_IDENT_LEN + 1];
  int lineNo, colNo;
  TokenType tokenType;
  int value;
} Token;

TokenType checkKeyword(char *string);
Token* makeToken(TokenType tokenType, int lineNo, int colNo);


#endif
