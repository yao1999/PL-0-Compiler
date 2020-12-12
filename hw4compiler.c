// Zefeng Yao
// Alexandra French
// System Software
// HW3
// Modified for HW4

#include "header.h"
#include "lexicalAnalyzer.h"
#include "parser.h"
#include "virtual_machine.h"

FILE *input;
// removes all the old files at start
void remove_start()
{
	remove("screenOutput.txt");
	remove("finalOutput.txt");
}

// run the main compiler program
int main(int argc, char **argv)
{
	// removes any old files before running the new code. Clean slate.
	remove_start();

	FILE *screenOutput;
	int currInput = 0;

	// Open input and ensure exists
	input = fopen(argv[1], "r");
	if (input == NULL)
	{
		printf("%s\n", error_messages[0]);
		return 1;
	}

	// read in all the options
	while (currInput < argc)
	{
		// see if print lexeme list and symbollic representation
		if (strcmp(argv[currInput], "-l") == 0)
		{
			printLex = 1;
		}
		// see if print out the codegen assembly code
		if (strcmp(argv[currInput], "-a") == 0)
		{
			printParser = 1;
		}
		// see if print virtual machine execution trace
		if (strcmp(argv[currInput], "-v") == 0)
		{
			printVm = 1;
		}
		currInput++;
	}

	// once all options obtained, open the overarching output files
	screenOutput = fopen("screenOutput.txt", "w");
	finalOutput = fopen("finalOutput.txt", "w");

	// If no compiler directives, print in
	if (printLex == 0 && printParser == 0 && printVm == 0)
	{
		printf("in\n");
	}
	// run lexer, parser, and vm
	lexicalAnalyzer(input, screenOutput);
	//fclose(input);
	parser(screenOutput);
	vitual_machine(screenOutput);

	// if no compiler directives, print out
	if (printLex == 0 && printParser == 0 && printVm == 0)
	{
		printf("out\n");
	}

	remove_end(DEBUG);

	// return 0 for successul execution
	return 0;
}
