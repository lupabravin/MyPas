/**@<interface.h>::**/

#pragma once

extern FILE *source_code;
int gettoken(FILE *);
extern int lookahead;
void match (int expected_token);
