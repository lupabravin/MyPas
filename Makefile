#!/usr/bin/make -f

includepath=./include/

CFLAGS=-g -I$(includepath)

objlist=interface.o lexer.o mypas.o parser.o keywords.o

exec=mypas

$(exec): $(objlist) 
	$(CC) -o $@ $^

clean:
	$(RM) *.o

mostlyclean: clean
	$(RM) *~
	(cd $(includepath); make $@)

indent: interface.c lexer.c mypas.c parser.c
	/usr/bin/indent -orig -nuts -ts4 -nfca $^
