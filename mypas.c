#include "stdio.h"
#include "mypas.h"

FILE           *source_code;

int
main(int argc, const char *argv[])
{
    source_code = stdin;

    if (argc > 1) {
        source_code = fopen(argv[1], "r");
    }

    lookahead = gettoken(source_code);


    mypas();

    return 0;
}
