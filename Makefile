# simple makefile

compile: main.c pdp.c
	gcc -o pdp main.c pdp.c 

clean:
	rm pdp
