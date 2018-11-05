#!/usr/bin/make -f

indent: interface.h lexer.h mypas.h parser.h
	/usr/bin/indent -orig -nuts -ts4 -nfca $^

clean: mostlyclean

mostlyclean:
	$(RM) *~
