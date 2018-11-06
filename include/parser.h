#pragma once

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "lexer.h"
#include "tokens.h"
#include "interface.h"
#include "keywords.h"

/* parser components */
void body(void);
void declarative(void); 
void varclause(void);
void varlist(void);
void typespec(void);
void varspec(void); 
void methods(void);
void procedure(void);
void formalparm(void);
void argdef(void);
void function(void);
void stmt(void);
void blkstmt(void);
void ifstmt(void);
void whlstmt(void);
void repstmt(void);
void factor(void);
void stmtblk(void);
void expr(void);
void smpexpr(void);
int assgn(void);
/* main code input/output buffer declaration */
extern FILE *source_code;
extern FILE *object_code;
