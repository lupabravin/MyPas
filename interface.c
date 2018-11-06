/**@<interface.c>::**/
#include "stdlib.h"
#include "stdio.h"
#include "lexer.h"
extern FILE    *source_code;
int             gettoken(FILE *);

int             lookahead;

void
match(int expected_token)
{
    if (expected_token == lookahead) {
        lookahead = gettoken(source_code);
    } else {
        fprintf(stderr, "token mismatch... exiting\n");
        exit(-2);
    }
}
