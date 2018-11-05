/**@<parser.c>::**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lexer.h>
#include <tokens.h>
#include <interface.h>
#include <keywords.h>
#include <parser.h>

/*********************************************************************
MyPascal is a name for the academic
project mypas, which is a simplified
and modified Pascal

Syntax::

Initial symbol: mypas

mypas -> PROGRAM ID ';' body .
*/
void mypas(void)
{
    match(PROGRAM);
    match(ID);
	match(';');
    body();
}
/*********************************************************************
body -> declarative blkstmt
*/
void body(void)
{
    declarative();
    blkstmt();
}
/*********************************************************************
declarative -> [ VAR varclause { varclause } ] methods
*/
void
declarative(void)
{
    if (lookahead == VAR) {
        match(VAR);
        varclause();
        while (lookahead == ID) {
            varclause();
        }
    }
    methods();
}
/*********************************************************************
varclause -> varlist ':' typespec ;
*/
void
varclause(void)
{
    varlist();
    match(':');
    typespec();
    match(';');
}
/*********************************************************************
varlist -> varspec { , varspec }
*/
void
varlist(void)
{
    match(ID);
    while (lookahead == ',') {
        match(',');
        match(ID);
    }
}
/*********************************************************************
typespec -> INTEGER | REAL | DOUBLE | BOOLEAN
*/
void
typespec(void)
{
    switch (lookahead) {
    case INTEGER:
    case REAL:
    case DOUBLE:
        match(lookahead);
		break;
    default:
        match(BOOLEAN);
		break;
    }
}
/*********************************************************************
methods -> { procedure | function }
*/
void
methods(void)
{
    while (lookahead == PROCEDURE || lookahead == FUNCTION) {
        switch (lookahead) {
        case PROCEDURE:
            procedure();
            break;
        default:
            function();
        }
    }
}
/*********************************************************************
procedure -> PROCEDURE ID formalparm ';' body ;
*/
void
procedure(void)
{
    match(PROCEDURE);
    match(ID);
    formalparm();
    match(';');
    body();
    match(';');
}
/*********************************************************************

/***********
 * formalparm -> [ '(' argdef {';' argdef } ')' ] 
************/

void formalparm(void){

	if (lookahead == '(') {
		match('(');
		argdef();
		
		while (lookahead == ';') {
			match(';');
			argdef();
			match(')');
		}
		match(')');
	}
}

/***********
 * argdef -> [ VAR  ] ID { ',' ID } ':' typespec  
 *
************/

void argdef(void) {

	if (lookahead == VAR) match(VAR);
	
	match(ID);
	while (lookahead == ',') { match(','); match(ID); }

	match(':');
	typespec();
}


/*
function -> FUNCTION ID formalparm ':' typespec ';' body ;
*/
void
function(void)
{
    match(FUNCTION);
    match(ID);
    formalparm();
    match(':');
    typespec();
    match(';');
    body();
    match(';');
}
/*********************************************************************
stmtlist -> stmt { ';' stmt }
*/
void
stmtlist(void)
{
    stmt();
    while (lookahead == ';') {
        match(';');
        stmt();
    }
}
/*********************************************************************
stmt ->   blkstmt
	| ifstmt
	| whlstmt
	| repstmt
	| factor
	| <empty>
*/
void
stmt(void)
{
    switch (lookahead) {
    case BEGIN:
        blkstmt();
        break;
    case IF:
        ifstmt();
        break;
    case WHILE:
        whlstmt();
        break;
    case REPEAT:
        repstmt();
        break;
    default:
        switch (lookahead) {
        case '-':
        case '+':
        case '(':
        case NOT:
        case UINT:
        case FLTP:
        case FALSE:
        case TRUE:
		case ID:
            factor();
        }
        /*
         * <empty>
         */ ;
    }
}
/*********************************************************************
blkstmt  -> BEGIN stmtlist END
*/
void
blkstmt(void)
{
    match(BEGIN);
    stmtlist();
    match(END);
}
/*********************************************************************
ifstmt   -> IF expr THEN stmt [ ELSE stmt ]
*/
void
ifstmt(void)
{
    match(IF);
    expr();
    match(THEN);
    stmt();
    if (lookahead == ELSE) {
        match(ELSE);
        stmt();
    }
}
/*********************************************************************
whlstmt  -> WHILE expr DO stmt
*/
void whlstmt(void)
{
 match(WHILE);
 expr();
 match(DO);
 stmt();
}
/*********************************************************************
repstmt  -> REPEAT stmtlist UNTIL expr
*/
void repstmt(void)
{
  match(REPEAT);
  stmtlist();
  match(UNTIL);
  expr();
}
/*********************************************************************
smpexpr -> [ + | - | NOT ] term { oplus term }

	oplus   -> + | - | OR

term    -> factor { otimes factor }

	otimes  -> * | / | DIV | MOD | AND

factor  -> variable [ ":=" expr ] | constant | ( expr )

variable -> ID

constant -> UINT | FLT | TRUE | FALSE

expr   -> smpexpr [ relop smpexpr ]

	relop ->    >
		  | >= # GEQ
		  | <
		  | <= # LEQ
		  | <> # NEQ
		  | =
*/
int
isrelop(void)
{
    int             relop = lookahead;
    switch (lookahead) {
    case '>':
    case GEQ:
    case '<':
    case LEQ:
    case NEQ:
    case '=':
        match(lookahead);
        return relop;
    }
    return 0;
}
/****************************************************************
expr   -> smpexpr [ relop smpexpr ]
*/
void
expr(void)
{
    smpexpr();
    if (isrelop()) {
        smpexpr();
    }
}
/****************************************************************

(1) recursive parser for smpexpression using the Wirth's syntatic
  diagram:
 
                     /---<----(+)---<----\
                     |                   |
                     |  /--<--(*)--<--\  |  
                     |  |             |  |
                     |  |   ------    |  |
 smpexpr->--['+''-']--------|fact|---------->---
                            ------
 
 fact ->  ID | UINT | FLT | ( expr )

**********************************************/
void
smpexpr(void)
{
    switch (lookahead) {
    case '+':
        match('+');
        break;
    case '-':
        match('-');
    }

  T_entry:

  F_entry:

    factor();

    if (lookahead == '*' || lookahead == '/') {
        match(lookahead);
        goto F_entry;
    }

    if (lookahead == '+' || lookahead == '-') {
        match(lookahead);
        goto T_entry;
    }

}

void factor(void)
{
    switch (lookahead) {
    case ID:
        match(ID);
        assgn();
        break;
    case UINT:
    case FLTP:
        match(lookahead);
        break;
    default:
        match('(');
        expr();
        match(')');
    }
}

int assgn(void)
{
	
    if (lookahead == ASGN) {
        match(ASGN);
        expr();
    } else {
    }
}
