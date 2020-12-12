Compiling
------------------------------------------------------------------------
To compile the compiler, enter the following program in your command prompt or terminal:
gcc -o compile hw4compiler.c


Running
------------------------------------------------------------------------
To run the compiler, enter the following command in your command prompt or terminal:
./compile input1.txt -compilerDirective

Input1.txt is your input file. Replace ‘input1’ if the input filename is different from input1, and ‘.txt’ if the extension is different from a text file.
-compilerDirective: There are three possible compiler directives.
	-l	print the list of lexemes/tokens
	-a	print the generated assembly code
	-v	print the virtual machine execution trace
* It is possible to use one, two, all, or none of these objectives. 
* Order of the compiler objectives is not important, so long as they come after: ./compile input1.txt

 
Screen Output
------------------------------------------------------------------------
Depending on the compiler objectives, this program will output to the screen each objective.
If there are no objectives, the program will only output “in” on starting, any read/write output, and then finally “out” upon ending the program.
If there are any errors, then the program will stop upon reaching any errors.


File Output
------------------------------------------------------------------------
Final Output w/ Compiler Directives
To view the final output of this program in file form, determinant on compiler objectives much like screen output, view the screenOutput.txt file. This output file also includes the input file. 
If any errors have occurred, the error will write to the screen and the program will terminate immediately. The output file will only print up until termination point.

All Possible Output
A file containing all possible output is also created for debugging purposes, finalOutput.txt. This file includes:
*	Source program
*	Lexeme table
*	Lexeme list
*	Symbolic lexeme representation
*	Any errors / lack of errors
*	Symbol Table
*	Generated assembly code
*	Interpreted assembly code
*	Virtual machine execution trace
*	Any screen printing from the virtual machine execution


File Deletion on Rerun
------------------------------------------------------------------------
The compiler deletes all files in the folder at the start of each run. If re-running the code but wanting to keep a file, store it elsewhere before rerunning.
 

Viewing an Output File on Screen
------------------------------------------------------------------------
If you wish to view the output in the command prompt or terminal, you can use the following command:
cat outputFile.txt
 


