#include "stdio.h"
#include "mypas.h"

FILE           *source_code;

int
main(int argc, const char *argv[])
{
    source_code = stdin;

	/* Opens and reads source file */
    if (argc > 1) {
        source_code = fopen(argv[1], "r");
    }

	/* Gets the first token */
    lookahead = gettoken(source_code);

	/* Begin the parsing process */
    mypas();

    return 0;
}
