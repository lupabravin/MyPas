/**@<lexer.c>::**/
#include <lexer.h>

token_t         iskeyword(const char *symbol);

token_t
skipspaces(FILE * tape)
{
    token_t         head;

  _skipspaces_start:

    while (isspace(head = getc(tape))) {
        if (head == '\n') {
            break;
        }
    }
    /** check the possibility of beginning
        a pascal comment: **/
    if (head == '{') {
        while ((head = getc(tape)) != '}') {
            if (head == EOF)
                return EOF;
        }
        goto _skipspaces_start;
    }
    /** end-check **/
    ungetc(head, tape);
    return 0;
}

char            lexeme[MAXIDLEN + 1];

/*
 * ID = [A-Za-z][_A-Za-z0-9]*
 */
token_t
isID(FILE * tape)
{
    token_t         keyword;
    lexeme[0] = getc(tape);
    if (isalpha(lexeme[0])) {
        int             i;
        for (i = 1; isalnum(lexeme[i] = getc(tape))
             || lexeme[i] == '_'; i++);
        ungetc(lexeme[i], tape);
        lexeme[i] = 0;

        if ((keyword = iskeyword(lexeme)))
            return keyword;

        return ID;
    }
    ungetc(lexeme[0], tape);
    return 0;
}

/*
 * NUM = UINT | FLTP
 * UINT = [1-9][0-9]* | 0
 * FLTP = ( UINT'.'FRAC? | '.'FRAC ) EE? | UINT EE
 *
 */
token_t
isNUM(FILE * tape)
{
    token_t         token = 0;
    int             i;
    if (isdigit(lexeme[0] = getc(tape))) {
        if (lexeme[0] == '0') {
            i = 1;
        } else {
            for (i = 1; isdigit(lexeme[i] = getc(tape)); i++);
            ungetc(lexeme[i], tape);
        }
        token = UINT;
        if ((lexeme[i] = getc(tape)) == '.') {
            token = FLTP;
            i++;
            while (isdigit(lexeme[i] = getc(tape)))
                i++;
            ungetc(lexeme[i], tape);
        } else {
            ungetc(lexeme[i], tape);
        }
    } else if (lexeme[0] == '.') {
        if (isdigit(lexeme[1] = getc(tape))) {
            i = 2;
            token = FLTP;
            while (isdigit(lexeme[i] = getc(tape)))
                i++;
            ungetc(lexeme[i], tape);
        } else {
            ungetc(lexeme[1], tape);
            ungetc('.', tape);
        }
    }
    if (token) {
        /** if we're here we have a NUM **/
        /**  check if scientific notation **/
#ifdef __has_chkEE_implemented__
        int             i0 = i;
        i = chkEE(i, tape);
        if (i > i0 && token == UINT)
            token = FLTP;
#endif
        lexeme[i] = 0;
        return token;
    }

    /*
     * epsilon transition is simulated down here: 
     */
    ungetc(lexeme[0], tape);
    return token;
}
/*******************************
	relop ->    >
		  | >= # GEQ
		  | <
		  | <= # LEQ
		  | <> # NEQ
		  | =
*******************************/
token_t
isRELOP(FILE * tape)
{
    lexeme[2] = 0;
    lexeme[0] = getc(tape);
    switch (lexeme[0]) {
    case '>':
        if ((lexeme[1] = getc(tape)) == '=') {
            return GEQ;
        }
        ungetc(lexeme[1], tape);
        lexeme[1] = 0;
        return '>';
    case '<':
        if ((lexeme[1] = getc(tape)) == '=') {
            return LEQ;
        } else if (lexeme[1] == '>') {
            return NEQ;
        }
        ungetc(lexeme[1], tape);
        lexeme[1] = 0;
        return '<';
    case '=':
        lexeme[1] = 0;
        return '=';
    }
    ungetc(lexeme[0], tape);
    return 0;
}

token_t isASGN(FILE *tape)
{
    if ( (lexeme[0] = getc(tape)) == ':' ) {
	    if ( (lexeme[1] = getc(tape)) == '=' ) {
		    lexeme[2] = 0;
		    return ASGN;
	    }
	    ungetc(lexeme[1], tape);
    }
    ungetc(lexeme[0], tape);
    return 0;
}

token_t
gettoken(FILE * tape)
{
    token_t         token;
    skipspaces(tape);
    if ((token = isID(tape)))
        return token;
    if ((token = isNUM(tape)))
        return token;
    if ((token = isRELOP(tape)))
        return token;
	if ((token = isASGN(tape))) /* Added isASGN to mypas-skeleton version */
		return token;
    return getc(tape);
}
