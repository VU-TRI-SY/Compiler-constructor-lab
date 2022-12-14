/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum {
  ERR_ENDOFCOMMENT,
  ERR_IDENTTOOLONG,
  ERR_INVALIDCHARCONSTANT,
  ERR_INVALIDSYMBOL,
  ERR_NUMBERTOOLONG,
  ERR_STRINGTOOLONG,
  ERR_ENDOFSTRING
} ErrorCode;


#define ERM_ENDOFCOMMENT "End of comment expected!"
#define ERM_IDENTTOOLONG "Identification too long!"
#define ERM_INVALIDCHARCONSTANT "Invalid const char!"
#define ERM_INVALIDSYMBOL "Invalid symbol!"
#define ERM_NUMBERTOOLONG "Number too long!"
#define ERM_STRINGTOOLONG "String constant too long!"
#define ERM_ENDOFSTRING "End of string expected!"

void error(ErrorCode err, int lineNo, int colNo);

#endif
