# simple makefile

debug: core/main.c core/pdp.c
	gcc -DDEBUG -o pdpdebug core/main.c core/pdp.c -w

ama: core/main.c core/pdp.c
	gcc -DAMA -o pdpama core/main.c core/pdp.c -w

compile: core/main.c core/pdp.c
	gcc -o pdp core/main.c core/pdp.c -w

clean:
	rm pdp pdpama pdpdebug 

cleanascii:
	rm ascii/*.obj ascii/*.lst
