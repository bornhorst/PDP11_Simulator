# PDP11_Simulator

## Guidelines
Follow these steps to generate ascii files and simulate.

Move the "macro11" and "obj2ascii" executables to ~/PDP11_Simulator/ascii

 ---Command Line Arguments---
* Compile: 		$ make compile
* Generate ASCII Files: $ ./pdp obj2ascii 
* Run Simulator: 	$ ./pdp pdp.ascii *address of first instruction 

 ---Example---
* $ make compile
* $ ./pdp obj2ascii
* $ ./pdp pdp.ascii *00012


