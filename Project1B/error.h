/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum {
  ERR_INVALIDSYMBOL,
  ERR_NUMBERTOOLONG,
  ERR_STRINGTOOLONG,
  ERR_INVALIDSTRING
} ErrorCode;

#define ERM_INVALIDSYMBOL "Invalid symbol!"
#define ERM_NUMBERTOOLONG "Number too long!"
#define ERM_STRINGTOOLONG "String constant too long!"
#define ERM_INVALIDSTRING "Invalid string constant!"
void error(ErrorCode err, int lineNo, int colNo);

#endif
