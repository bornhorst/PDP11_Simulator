# simple makefile

compile: core/main.c core/pdp.c
	gcc -o pdp core/main.c core/pdp.c 

clean:
	rm pdp 

cleanascii:
	rm ascii/pdp.obj ascii/pdp.lst
