/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(ErrorCode err, int lineNo, int colNo) {
  switch (err) {
  case ERR_INVALIDSYMBOL:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDSYMBOL);
    break;
  case ERR_NUMBERTOOLONG:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_NUMBERTOOLONG);
    break;
  case ERR_STRINGTOOLONG:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_STRINGTOOLONG);
    break;
  case ERR_INVALIDSTRING:
    printf("%d-%d:%s\n", lineNo, colNo, ERM_INVALIDSTRING);
    break;

  }
  // exit(-1);
}

