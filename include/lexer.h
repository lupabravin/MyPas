/**@<lexer.h>::**/

#pragma once

#include <ctype.h>
#include <stdio.h>
#include <tokens.h>

#define 	MAXIDLEN	63

extern char lexeme[MAXIDLEN+1];

int chkEE( int, FILE *);

