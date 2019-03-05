# PDP11_Simulator

## Guidelines
Follow these steps to generate ascii files and simulate.

Move the "macro11" and "obj2ascii" executables to ~/PDP11_Simulator/ascii

 ---Command Line Arguments---
* Compile: 		$ make compile
* Compile for debug:	$ make debug
* Compile for AMA:	$ make ama
* Generate ASCII Files: $ ./pdp obj2ascii filename
* Run Simulator: 	$ ./pdp filename *address of first instruction 

 ---Example---
* $ make compile
* $ ./pdp obj2ascii filename
* $ ./pdp filename *00010


