# simple makefile

debug: core/main.c core/pdp.c
	gcc -DDEBUG -o pdpdebug core/main.c core/pdp.c 

ama: core/main.c core/pdp.c
	gcc -DAMA -o pdpama core/main.c core/pdp.c 

compile: core/main.c core/pdp.c
	gcc -o pdp core/main.c core/pdp.c 

clean:
	rm pdp pdpama pdpdebug

cleanascii:
	rm ascii/pdp.obj ascii/pdp.lst
