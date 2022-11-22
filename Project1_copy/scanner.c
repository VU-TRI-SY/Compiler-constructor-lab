/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
// #include <conio.h>
#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"


extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

/***************************************************************/
void skipBlank() {
  // TODO
  while (currentChar != EOF && charCodes[currentChar] == CHAR_SPACE)
  {
    readChar();
  }
}

void skipComment() {
  // TODO
  while (currentChar != EOF)
  {
    if (charCodes[currentChar] == CHAR_TIMES)
    {
      readChar();
      if (currentChar != EOF && charCodes[currentChar] == CHAR_RPAR)
      {
        readChar();
        return;
      }
      continue;
    }
    readChar();
  }
  error(ERR_ENDOFCOMMENT, lineNo, colNo);
}

Token* readIdentKeyword(void) {
  // TODO
  int i = 0;
  Token* token = makeToken(TK_NONE, lineNo, colNo);
  int ln = lineNo;
  int cn = colNo;
  char str[MAX_IDENT_LEN + 1];
  while (currentChar != EOF && charCodes[currentChar] == CHAR_LETTER || charCodes[currentChar] == CHAR_DIGIT)
  {
    if(i >= MAX_IDENT_LEN){
      while (currentChar != EOF && charCodes[currentChar] == CHAR_LETTER || charCodes[currentChar] == CHAR_DIGIT){
        i++;
        readChar();
      }
      error(ERR_IDENTTOOLONG, ln, cn);
      break;
    }
    str[i++] = currentChar;
    readChar();
  }
  str[i] = '\0';
  if (i > MAX_IDENT_LEN)
  {
    return token;
  }
  token->tokenType = (checkKeyword(str) == TK_NONE) ? TK_IDENT : checkKeyword(str);
  strcpy(token->string, str);
  return token;
}

// Token* readNumber(void) {
//   // TODO
//   Token *token = makeToken(TK_NONE, lineNo, colNo);
//   int ln = lineNo;
//   int cn = colNo;
//   int index = 0;
//   char string[11];
//   while(currentChar == '0')
//     readChar();

//   while (currentChar != EOF && charCodes[currentChar] == CHAR_DIGIT)
//   {
//     if (index >= 10)
//     {
//       while (currentChar != EOF && charCodes[currentChar] == CHAR_DIGIT)
//       {
//         index++;
//         readChar();
//       }
//       error(ERR_NUMBERTOOLONG, ln, cn);
//       break;
//     }
//     string[index] = currentChar;
//     index++;
//     readChar();
//   }

//   if (index > 10)
//     return token;

//   if(index == 0){
//     token->tokenType = TK_NUMBER;
//     token->value = 0;
//     token->string[0] = '0';
//     token->string[1] = '\0';
//     return token;
//   }

//   string[index] = '\0';
//   char strNumber[11];
//   sprintf(strNumber, "%d", INT_MAX);
//   if (strlen(string) == strlen(strNumber) && strcmp(string, strNumber) > 0)
//   {
//     error(ERR_NUMBERTOOLONG, ln, cn);
//     return token;
//   }
//   token->tokenType = TK_NUMBER;
//   strcpy(token->string, string);
//   token->value = atoi(string);
//   return token;
// }

Token* readNumber(void){
  Token *token = makeToken(TK_NONE, lineNo, colNo);
  int isFloat = 0;
  char string[1001];
  int index = 0;
  int firstTime = 0;
  while(currentChar == '0'){
    readChar();
  }
  while(currentChar != EOF && (charCodes[currentChar] == CHAR_DIGIT || charCodes[currentChar] == CHAR_PERIOD)){
    if(charCodes[currentChar] == CHAR_DIGIT){
      string[index] = currentChar;
      index++;
    }else{
      if(charCodes[currentChar] == CHAR_PERIOD){
        if(index == 0){
          string[0] = '0';
          string[1] = '.';
          index = 2;
          isFloat = 1;
        }else{
          if(isFloat){
            break;
          }else{
            string[index] = currentChar;
            index++;
            isFloat = 1;
          }
        }
      }
    }
    readChar();
  }
  if(isFloat){
    while(string[index-1] == '0'){
      index--;
    }
    if(string[index-1] == '.'){
      string[index++] = '0';
      string[index] = '\0';
    }else{
      string[index] = '\0';
    }
    token->tokenType = TK_FLOAT;
    token->value = atof(string);
    strcpy(token->string, string);
    return token;
  }else{
    if(index == 0){
      string[0] = '0';
      string[1] = '\0';
    }else{
      string[index] = '\0';
    }
    token->tokenType = TK_NUMBER;
    strcpy(token->string, string);
    token->value = atoi(string);
    return token;
  }
}
Token* readConstChar(void) {
  // TODO
  Token* token = makeToken(TK_NONE, lineNo, colNo);
  readChar();
  if(currentChar != EOF){
    char ct = currentChar;
    readChar();
    if (currentChar != EOF && charCodes[currentChar] == CHAR_SINGLEQUOTE){
      token->string[0] = ct;
      token->string[1] = '\0';
      token->tokenType = TK_CHAR;
      readChar();
      return token;
    }
    else{
      error(ERR_INVALIDCHARCONSTANT, lineNo, colNo);
      return token;
    }
  }else{
    error(ERR_INVALIDCHARCONSTANT, lineNo, colNo);
    return token;
  }
  return token;
}
Token* readConstantString(){
  Token* token = makeToken(TK_NONE, lineNo, colNo);
  int ln = lineNo;
  int cn = colNo;
  char string[MAX_STRING_LEN + 1];
  int i = 0;
  int closed = 0;
  while(currentChar != EOF){
    readChar();
    if(charCodes[currentChar] == CHAR_DOUBLEQUOTE){
      closed = 1;
      break;
    }else{
      if(i < MAX_STRING_LEN)
        string[i] = currentChar;
    }
    i++;
  }
  string[i] = '\0';

  if(i > MAX_STRING_LEN){
    error(ERR_STRINGTOOLONG, ln, cn);
    return token;
  }else{
    if(closed){
      token->tokenType = TK_STRING;
      strcpy(token->string, string);
      readChar();
      return token;
    }else{
      error(ERR_ENDOFSTRING, ln, cn);
      return token;
    }
  }
}

Token* getToken(void) {
  Token *token;
  int ln, cn;

  if (currentChar == EOF) 
    return makeToken(TK_EOF, lineNo, colNo);

  switch (charCodes[currentChar]) {
  case CHAR_SPACE: 
    skipBlank(); 
    return getToken();
  case CHAR_LETTER: 
    return readIdentKeyword(); 
  case CHAR_DIGIT: 
    return readNumber();
  case CHAR_PLUS: 
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_EQ){
      readChar();
      return makeToken(SB_ASSIGN_PLUS, ln, cn);
    }else{
      token = makeToken(SB_PLUS, ln, cn);
    }
    return token;
  case CHAR_MINUS:
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_EQ){
      readChar();
      return makeToken(SB_ASSIGN_SUBTRACT, ln, cn);
    }
    else{
      token = makeToken(SB_MINUS, ln, cn);
    }
    return token;
  case CHAR_TIMES:
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_EQ){
      readChar();
      return makeToken(SB_ASSIGN_TIME, ln, cn);
    }
    else{
      token = makeToken(SB_TIMES, ln, cn);
    }
    return token;
  case CHAR_SLASH: 
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_EQ){
      readChar();
      return makeToken(SB_ASSIGN_DIVIDE, ln, cn);
    }
    else{
      token = makeToken(SB_SLASH, ln, cn);
    }
    return token;
  case CHAR_EQ: 
    token = makeToken(SB_EQ, lineNo, colNo);
    readChar();
    return token;
  case CHAR_COMMA: 
    token = makeToken(SB_COMMA, lineNo, colNo);
    readChar();
    return token;
  case CHAR_SEMICOLON: 
    token = makeToken(SB_SEMICOLON, lineNo, colNo);
    readChar();
    return token;
    case CHAR_GT:
      ln = lineNo;
      cn = colNo;
      readChar();
      if (charCodes[currentChar] == CHAR_EQ)
        return makeToken(SB_GE, ln, cn);
      else
        return makeToken(SB_GT, ln, cn);

    case CHAR_LT:
      ln = lineNo;
      cn = colNo;
      readChar();
      if (charCodes[currentChar] == CHAR_EQ){
        token = makeToken(SB_LE, ln, cn);
        readChar();
      }
      else
        token = makeToken(SB_LT, ln, cn);
      return token;

    case CHAR_PERIOD: 
      ln = lineNo;
      cn = colNo;
      readChar();
      if (charCodes[currentChar] == CHAR_RPAR)
        token = makeToken(SB_RSEL, ln, cn);
      else
        token = makeToken(SB_PERIOD, ln, cn);
      readChar();
      return token;

    case CHAR_COLON: 
      ln = lineNo;
      cn = colNo;
      readChar();
      if(charCodes[currentChar] == CHAR_EQ){
        token = makeToken(SB_ASSIGN, ln, cn);
        readChar();
      }
      else
        token = makeToken(SB_COLON, ln, cn);
      return token;

    case CHAR_EXCLAIMATION:
      ln = lineNo;
      cn = colNo;
      readChar();
      if(charCodes[currentChar] == CHAR_EQ){
        token = makeToken(SB_NEQ, ln, cn);
        readChar();
      }
      else{
          error(ERR_INVALIDSYMBOL, ln, cn);
          token = makeToken(TK_NONE, ln, cn);
      }
      return token;

    case CHAR_SINGLEQUOTE: 
      return readConstChar();

    case CHAR_RPAR: 
      token = makeToken(SB_RPAR, lineNo, colNo);
      readChar();
      return token;

    case CHAR_LPAR: 
      ln = lineNo;
      cn = colNo;
      readChar();
      if (charCodes[currentChar] == CHAR_TIMES)
        skipComment();
      else if (charCodes[currentChar] == CHAR_PERIOD)
        return makeToken(SB_LSEL, ln, cn);
      else
        return makeToken(SB_LPAR, ln, cn);

      return getToken(); //get next token after comment
    case CHAR_MODULO:
      token = makeToken(SB_MODULO, lineNo, colNo);
      readChar();
      return token;
    case CHAR_DOUBLEQUOTE:
      return readConstantString();
    default:
      token = makeToken(TK_NONE, lineNo, colNo);
      error(ERR_INVALIDSYMBOL, lineNo, colNo);
      readChar();
      return token;
  }
}


/******************************************************************/

void printToken(Token *token) {

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType) {
  case TK_NONE: printf("TK_NONE\n"); break;
  case TK_IDENT: printf("TK_IDENT(%s)\n", token->string); break;
  case TK_NUMBER: printf("TK_NUMBER(%s)\n", token->string); break;
  case TK_FLOAT: printf("TK_FLOAT(%s)\n", token->string); break;
  case TK_CHAR: printf("TK_CHAR(\'%s\')\n", token->string); break;
  case TK_EOF: printf("TK_EOF\n"); break;
  case TK_STRING: printf("TK_STRING(\"%s\")\n", token->string); break;

  case KW_PROGRAM: printf("KW_PROGRAM\n"); break;
  case KW_CONST: printf("KW_CONST\n"); break;
  case KW_TYPE: printf("KW_TYPE\n"); break;
  case KW_VAR: printf("KW_VAR\n"); break;
  case KW_INTEGER: printf("KW_INTEGER\n"); break;
  case KW_CHAR: printf("KW_CHAR\n"); break;
  case KW_ARRAY: printf("KW_ARRAY\n"); break;
  case KW_OF: printf("KW_OF\n"); break;
  case KW_FUNCTION: printf("KW_FUNCTION\n"); break;
  case KW_PROCEDURE: printf("KW_PROCEDURE\n"); break;
  case KW_BEGIN: printf("KW_BEGIN\n"); break;
  case KW_END: printf("KW_END\n"); break;
  case KW_CALL: printf("KW_CALL\n"); break;
  case KW_IF: printf("KW_IF\n"); break;
  case KW_THEN: printf("KW_THEN\n"); break;
  case KW_ELSE: printf("KW_ELSE\n"); break;
  case KW_WHILE: printf("KW_WHILE\n"); break;
  case KW_DO: printf("KW_DO\n"); break;
  case KW_FOR: printf("KW_FOR\n"); break;
  case KW_TO: printf("KW_TO\n"); break;

  case SB_SEMICOLON: printf("SB_SEMICOLON\n"); break;
  case SB_COLON: printf("SB_COLON\n"); break;
  case SB_PERIOD: printf("SB_PERIOD\n"); break;
  case SB_COMMA: printf("SB_COMMA\n"); break;
  case SB_ASSIGN: printf("SB_ASSIGN\n"); break;
  case SB_EQ: printf("SB_EQ\n"); break;
  case SB_NEQ: printf("SB_NEQ\n"); break;
  case SB_LT: printf("SB_LT\n"); break;
  case SB_LE: printf("SB_LE\n"); break;
  case SB_GT: printf("SB_GT\n"); break;
  case SB_GE: printf("SB_GE\n"); break;
  case SB_PLUS: printf("SB_PLUS\n"); break;
  case SB_MINUS: printf("SB_MINUS\n"); break;
  case SB_TIMES: printf("SB_TIMES\n"); break;
  case SB_SLASH: printf("SB_SLASH\n"); break;
  case SB_LPAR: printf("SB_LPAR\n"); break;
  case SB_RPAR: printf("SB_RPAR\n"); break;
  case SB_LSEL: printf("SB_LSEL\n"); break;
  case SB_RSEL: printf("SB_RSEL\n"); break;
  case SB_MODULO: printf("SB_MODULO\n"); break;
  case SB_ASSIGN_DIVIDE: printf("SB_ASSIGN_DIVIDE\n"); break;
  case SB_ASSIGN_TIME: printf("SB_ASSIGN_TIME\n"); break;
  case SB_ASSIGN_SUBTRACT: printf("SB_ASSIGN_SUBTRACT\n"); break;
  case SB_ASSIGN_PLUS: printf("SB_ASSIGN_PLUS\n"); break;
  }
}

int scan(char *fileName) {
  Token *token;

  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  token = getToken();
  while (token->tokenType != TK_EOF) {
    printToken(token);
    free(token);
    token = getToken();
  }

  free(token);
  closeInputStream();
  return IO_SUCCESS;
}

/******************************************************************/

/*int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("scanner: no input file.\n");
    return -1;
  }

  if (scan(argv[1]) == IO_ERROR) {
    printf("Can\'t read input file!\n");
    return -1;
  }

  return 0;
}*/

int main()
{
  if (scan("test/example2.kpl") == IO_ERROR)
  {
    printf("Can\'t read input file!\n");
  }
  return 0;
}


