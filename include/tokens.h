#pragma once

/**@<tokens.h"::**/

/* Tokens are recognized by the type token_t*/
typedef int token_t;


/************** TOKEN LIST ****************
 *
 *   Factor Tokens: ID (identifier), UINT (INTEGER), FLTP (FLOAT POINT)
 *   Relational Operation Tokens: GEQ (Great Equal Than) , LEQ (Less Equal Than), NEQ (Not Equal Than)
 *   Assignment Operation Tokens: ASGN (Right value assigned to Left VAR)
 *
 ***************************************/
enum {
    ID = 1025,
    UINT,
    FLTP,
    GEQ,
    LEQ,
    NEQ,
    ASGN,
};

