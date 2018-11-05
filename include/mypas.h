/**@mypas.h>::**/
#include <tokens.h>

#pragma once

extern FILE *source_code;

/* The super initial symbol is abstracted as the following
 * procedure: */

void mypas(void);

token_t lookahead;

token_t gettoken(FILE *);

