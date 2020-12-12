// Zefeng Yao
// Alexandra French
// System Software
// HW1 - pm0 VM
// Modified for hw3
// Modified for HW4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_STACK_HEIGHT 40
#define MAX_CODE_LENGTH 300
#define MAX_LEXI_LEVELS 3

// Instruction container
typedef struct instruction
{
  int op; // opcode
  int r; // register
  int l; // Lexographical level
  int m; // M
} instruction;

typedef struct record
{
  int *array; // opcode
  int size;
  int capacity;
} record;

// Globals
int numLines, line = 0, sp = 0, pc = 0, bp = 1, ir = 0;
int registers[8];
int stack[MAX_DATA_STACK_HEIGHT + 1];

// Prototypes
instruction *readData(FILE *input);
void printInstructions(FILE *output, FILE *screenOutput, instruction *instr, instruction *instrReg);
void printExecution(FILE *output, FILE *screenOutput, record *sparray, instruction instr, int halt);
void printExecType(FILE *output, FILE *screenOutput, instruction instr, int option);
int fetchAndRun(FILE *output, FILE *screenOutput, record *sparray, instruction *instr, instruction *instrReg, int halt);
int base(int l, int base);

// Reads the inputfile.txt and save all the opcode in a Instruction(structure) array. Returns it.
instruction *readData(FILE *input)
{
	int i = 0;
	instruction *instr = calloc(MAX_CODE_LENGTH, sizeof(instruction));

	// While not end of file, scan in each line and check for errors.
	while (!feof(input))
	{
    	fscanf(input, "%d %d %d %d", &instr[i].op, &instr[i].r, &instr[i].l, &instr[i].m);
  		i++;
	}
	numLines = i;

	return instr;
}

// create an erray of records
record *createArray(int total_size)
{
  record *arr = malloc(sizeof(record));
  arr->array = malloc(sizeof(int)*total_size);
  arr->size = 0;
  arr->capacity = total_size;
  return arr;
}

// Prints each instruction execution
void printInstructions(FILE *output, FILE *screenOutput, instruction *instr, instruction *instrReg)
{
	int i;

	// prints to final output and its own file (debug)
	fprintf(output, "Line\tOP\tR\tL\tM\n");
	fprintf(finalOutput, "\n\nLine\tOP\tR\tL\tM\n");
	for (i = 0; i < numLines; i++)
	{
		if (i < 10)
		{
			// Formatting
			fprintf(output, " ");
			fprintf(finalOutput, " ");
		}
		// Printings out the lines, instruction type, r, l, and m
		fprintf(output, "%d\t", i);
		fprintf(finalOutput, "%d\t", i);

		printExecType(output, screenOutput, instr[i], 0);

		fprintf(output, "\t%d\t%d\t%d\n", instr[i].r, instr[i].l, instr[i].m);
		fprintf(finalOutput, "\t%d\t%d\t%d\n", instr[i].r, instr[i].l, instr[i].m);
	}
}

// Prints out the type of instruction
void printExecType(FILE *output, FILE *screenOutput, instruction instr, int option)
{
	switch(instr.op)
	{
		case 1:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("lit");
				fprintf(screenOutput, "lit");
			}
			fprintf(finalOutput, "lit");
			fprintf(output, "lit");
			break;
		case 2:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("rtn");
				fprintf(screenOutput, "rtn");
			}
			fprintf(finalOutput, "rtn");
			fprintf(output, "rtn");
			break;
		case 3:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("lod");
				fprintf(screenOutput, "lod");
			}
			fprintf(finalOutput, "lod");
			fprintf(output, "lod");
			break;
		case 4:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("sto");
				fprintf(screenOutput, "sto");
			}
			fprintf(finalOutput, "sto");
			fprintf(output, "sto");
			break;
		case 5:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("cal");
				fprintf(screenOutput, "cal");
			}
			fprintf(finalOutput, "cal");
			fprintf(output, "cal");
      break;
		case 6:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("inc");
				fprintf(screenOutput, "inc");
			}
			fprintf(finalOutput, "inc");
			fprintf(output, "inc");
			break;
		case 7:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("jmp");
				fprintf(screenOutput, "jmp");
			}
			fprintf(finalOutput, "jmp");
			fprintf(output, "jmp");
			break;
		case 8:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("jpc");
				fprintf(screenOutput, "jpc");
			}
			fprintf(finalOutput, "jpc");
			fprintf(output, "jpc");
			break;
		case 9:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("sio");
				fprintf(screenOutput, "sio");
			}
			fprintf(finalOutput, "sio");
			fprintf(output, "sio");
			break;
		case 10:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("sio");
				fprintf(screenOutput, "sio");
			}
			fprintf(finalOutput, "sio");
			fprintf(output, "sio");
			break;
		case 11:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("sio");
				fprintf(screenOutput, "sio");
			}
			fprintf(finalOutput, "sio");
			fprintf(output, "sio");
			break;
		case 12:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("neg");
				fprintf(screenOutput, "neg");
			}
			fprintf(finalOutput, "neg");
			fprintf(output, "neg");
			break;
		case 13:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("add");
				fprintf(screenOutput, "add");
			}
			fprintf(finalOutput, "add");
			fprintf(output, "add");
			break;
		case 14:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("sub");
				fprintf(screenOutput, "sub");
			}
			fprintf(finalOutput, "sub");
			fprintf(output, "sub");
			break;
		case 15:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("mul");
				fprintf(screenOutput, "mul");
			}
			fprintf(finalOutput, "mul");
			fprintf(output, "mul");
			break;
		case 16:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("div");
				fprintf(screenOutput, "div");
			}
			fprintf(finalOutput, "div");
			fprintf(output, "div");
			break;
		case 17:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("odd");
				fprintf(screenOutput, "odd");
			}
			fprintf(finalOutput, "odd");
			fprintf(output, "odd");
			break;
		case 18:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("mod");
				fprintf(screenOutput, "mod");
			}
			fprintf(finalOutput, "mod");
			fprintf(output, "mod");
			break;
		case 19:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("eql");
				fprintf(screenOutput, "eql");
			}
			fprintf(finalOutput, "eql");
			fprintf(output, "eql");
			break;
		case 20:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("neq");
				fprintf(screenOutput, "neq");
			}
			fprintf(finalOutput, "neq");
			fprintf(output, "neq");
			break;
		case 21:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("lss");
				fprintf(screenOutput, "lss");
			}
			fprintf(finalOutput, "lss");
			fprintf(output, "lss");
			break;
		case 22:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("leq");
				fprintf(screenOutput, "leq");
			}
			fprintf(finalOutput, "leq");
			fprintf(output, "leq");
			break;
		case 23:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("gtr");
				fprintf(screenOutput, "gtr");
			}
			fprintf(finalOutput, "gtr");
			fprintf(output, "gtr");
			break;
		case 24:
			// prints to screen if selected
			if (printVm == 1 && option == 1)
			{
				printf("geq");
				fprintf(screenOutput, "geq");
			}
			fprintf(finalOutput, "geq");
			fprintf(output, "geq");
			break;
	}
}

// expand the array capacity
void expandArr(record *sparray)
{
  int capacity = 2 * sparray->capacity + 1;
  int *new_array = realloc(sparray->array, sizeof(int) * capacity);
  sparray->capacity = capacity;
  sparray->array = new_array;
}

// insert into the array
void insertArr(record *sparray, int data)
{
	// if needed, expand array capacity
  if(sparray->size >= sparray->capacity)
  {
    expandArr(sparray);
  }
  sparray->array[sparray->size] = data;
  sparray->size++;
  sparray->array[sparray->size] = '\0';
}

// Performs the fetch and execute functions
int fetchAndRun(FILE *output, FILE *screenOutput, record *sparray, instruction *instr, instruction *instrReg, int halt)
{
	int j;
	halt = 0;

	// if print == 1, print out the virtual machine execution trace
	if (printVm == 1)
	{
		if (printParser == 1 || printLex == 1)
		{
			printf("\n");
		}
		printf("VM Execution Trace:\n");
		fprintf(screenOutput, "\n");
		fprintf(screenOutput, "VM Execution Trace:\n");
	}
	fprintf(finalOutput, "\n");
	fprintf(finalOutput, "VM Execution Trace:\n");

	// Prints out initial values
	// prints to screen if selected
	if (printVm == 1)
	{
		printf("\t\t\t\tpc\tbp\tsp\tregisters\n");
		printf("Initial values");
		printf("\t\t\t %d\t %d\t %d\t", pc, bp, sp);
		printf("%d %d %d %d", registers[0], registers[1], registers[2], registers[3]);
		printf(" %d %d %d %d\n", registers[4], registers[5], registers[6], registers[7]);
		printf("Stack: ");
		fprintf(screenOutput, "\t\t\t\tpc\tbp\tsp\tregisters\n");
		fprintf(screenOutput, "Initial values");
		fprintf(screenOutput, "\t\t\t %d\t %d\t %d\t", pc, bp, sp);
		fprintf(screenOutput, "%d %d %d %d", registers[0], registers[1], registers[2], registers[3]);
		fprintf(screenOutput, " %d %d %d %d\n", registers[4], registers[5], registers[6], registers[7]);
		fprintf(screenOutput, "Stack: ");
	}
	fprintf(finalOutput, "\t\t\t\tpc\tbp\tsp\tregisters\n");
	fprintf(finalOutput, "Initial values");
	fprintf(finalOutput, "\t\t\t %d\t %d\t %d\t", pc, bp, sp);
	fprintf(finalOutput, "%d %d %d %d", registers[0], registers[1], registers[2], registers[3]);
	fprintf(finalOutput, " %d %d %d %d\n", registers[4], registers[5], registers[6], registers[7]);
	fprintf(finalOutput, "Stack: ");

	fprintf(output, "\t\t\t\tpc\tbp\tsp\tregisters\n");
	fprintf(output, "Initial values");
	fprintf(output, "\t\t\t %d\t %d\t %d\t", pc, bp, sp);
	fprintf(output, "%d %d %d %d", registers[0], registers[1], registers[2], registers[3]);
	fprintf(output, " %d %d %d %d\n", registers[4], registers[5], registers[6], registers[7]);
	fprintf(output, "Stack: ");

	// print stack
	for (j = 0; j < MAX_DATA_STACK_HEIGHT; j++)
	{
		if (j == MAX_DATA_STACK_HEIGHT-1)
		{
			// prints to screen if selected
			if (printVm == 1)
			{
				printf("%d", stack[j+1]);
				fprintf(screenOutput, "%d", stack[j+1]);
			}
			fprintf(finalOutput, "%d", stack[j+1]);
			fprintf(output, "%d", stack[j+1]);
		}
		else
		{
			// prints to screen if selected
			if (printVm == 1)
			{
				printf("%d ", stack[j+1]);
				fprintf(screenOutput, "%d ", stack[j+1]);
			}
			fprintf(finalOutput, "%d ", stack[j+1]);
			fprintf(output, "%d ", stack[j+1]);
		}
	}
	// prints to screen if selected
	if (printVm == 1)
	{
		printf("\n\n");
		fprintf(screenOutput, "\n\n");
	}
	fprintf(finalOutput, "\n\n");
	fprintf(output, "\n\n");

	// While not halted, fetch, execute, and print the code
	while (halt != 1){
		// Prints the line, type of execution, r, l, and m values
		if (pc < 10)
		{
			// prints to screen if selected
			if (printVm == 1)
			{
				printf(" %d ", pc);
				fprintf(screenOutput, " %d ", pc);
			}
			fprintf(finalOutput, " %d ", pc);
			fprintf(output, " %d ", pc);
		}
		else
		{
			// prints to screen if selected
			if (printVm == 1)
			{
				printf("%d ", pc);
				fprintf(screenOutput, "%d ", pc);
			}
			fprintf(finalOutput, "%d ", pc);
			fprintf(output, "%d ", pc);
		}

		// print the execution type
		printExecType(output, screenOutput, instr[pc], 1);

		// prints to screen if selected
		if (printVm == 1)
		{
			printf(" %d %d %d", instr[pc].r, instr[pc].l, instr[pc].m);
			printf("\t\t");
			fprintf(screenOutput, " %d %d %d", instr[pc].r, instr[pc].l, instr[pc].m);
			fprintf(screenOutput, "\t\t");
		}
		fprintf(finalOutput, " %d %d %d", instr[pc].r, instr[pc].l, instr[pc].m);
		fprintf(finalOutput, "\t\t");
		fprintf(output, " %d %d %d", instr[pc].r, instr[pc].l, instr[pc].m);
		fprintf(output, "\t\t");

		// FETCH CYCLE
		// Fetch from instr into instrReg
		instrReg->op = instr[pc].op;
		instrReg->r = instr[pc].r;
		instrReg->l = instr[pc].l;
		instrReg->m = instr[pc].m;
		// Increment pc after each fetch
		pc = pc + 1;

		// EXECUTE CYCLE
		// Switch for each possible instruction op
		switch(instrReg->op)
		{
			// LIT
			case 1:
				registers[instrReg->r] = instrReg->m;
				break;
			// RTN
			case 2:
       			insertArr(sparray, sp);
				sp = bp - 1;
				bp = stack[sp + 3];
				pc = stack[sp + 4];
				break;
			// LOD
			case 3:
				registers[instrReg->r] = stack[base(instrReg->l, bp)+instrReg->m];
				break;
			// STO
			case 4:
				stack[base(instrReg->l, bp) + instrReg->m] = registers[instrReg->r];
				break;
			// CAL
			case 5:
				stack[sp + 1] = 0;
				stack[sp + 2] = base(instrReg->l, bp); // static link (sl)
				stack[sp + 3] = bp; //dynamic link (dl)
				stack[sp + 4] = pc;
				bp = sp + 1;
				pc = instrReg->m;
				break;
			// INC
			case 6:
     		  	insertArr(sparray, sp);
				sp = sp + instrReg->m;
				break;
			// JMP
			case 7:
				pc = instrReg->m;
				line = instrReg->m;
				break;
			// JPC
			case 8:
				if (registers[instrReg->r] == 0)
				{
					pc = instrReg->m;
				}
				break;
			// SIO (1)
			case 9:
				printf("\n\n%d\n\n", registers[instrReg->r]);
				fprintf(screenOutput, "\n\n%d\n", registers[instrReg->r]);
				fprintf(finalOutput, "\n\n%d\n", registers[instrReg->r]);
				break;
			// SIO (2)
			case 10:
				printf("\n\nPlease enter the number:\n");
				scanf("%d", &registers[instrReg->r]);
				break;
			// SIO (3)
			case 11:
				halt = 1;
				break;
			// NEG
			case 12:
				registers[instrReg->r] = -(registers[instrReg->l]);
				break;
			// ADD
			case 13:
				registers[instrReg->r] = (registers[instrReg->l] + registers[instrReg->m]);
				break;
			// SUB
			case 14:
				registers[instrReg->r] = (registers[instrReg->l] - registers[instrReg->m]);
				break;
			// MUL
			case 15:
				registers[instrReg->r] = (registers[instrReg->l] * registers[instrReg->m]);
				break;
			// DIV
			case 16:
				registers[instrReg->r] = (registers[instrReg->l] / registers[instrReg->m]);
				break;
			// ODD
			case 17:
				registers[instrReg->r] = registers[instrReg->l]%2;
				break;
			// MOD
			case 18:
				registers[instrReg->r] = registers[instrReg->l] % registers[instrReg->m];
				break;
			// EQL
			case 19:
				registers[instrReg->r] = (registers[instrReg->l] == registers[instrReg->m]);
				break;
			// NEQ
			case 20:
				registers[instrReg->r] = (registers[instrReg->l] != registers[instrReg->m]);
				break;
			// LSS
			case 21:
				registers[instrReg->r] = (registers[instrReg->l] < registers[instrReg->m]);
				break;
			// LEQ
			case 22:
				registers[instrReg->r] = (registers[instrReg->l] <= registers[instrReg->m]);
				break;
			// GTR
			case 23:
				registers[instrReg->r] = (registers[instrReg->l] > registers[instrReg->m]);
				break;
			// GEQ
			case 24:
				registers[instrReg->r] = (registers[instrReg->l] >= registers[instrReg->m]);
				break;
			default:
				printf("\nERROR! Invalid value.\n");
				fprintf(screenOutput, "\nERROR! Invalid value.\n");
				fprintf(finalOutput, "\nERROR! Invalid value.\n");
				halt = 1;
				break;
		}
		// Print execution values (pc, bp, sp, registers, stack)
		printExecution(output, screenOutput, sparray, instr[pc], halt);
	}
}

// Prints out the execution task
void printExecution(FILE *output, FILE *screenOutput, record *sparray, instruction instr, int halt)
{
	int check, i, j;
	
	// prints out pc, bp, sp, and registers (with space formatting)
	if (pc < 10)
	{
		// prints to screen if selected
		if (printVm == 1)
		{
			printf("\t %d\t", pc);
			fprintf(screenOutput, "\t %d\t", pc);
		}
		fprintf(finalOutput, "\t %d\t", pc);
		fprintf(output, "\t %d\t", pc);
	}
	else
	{
		// prints to screen if selected
		if (printVm == 1)
		{
			printf("\t%d\t", pc);
			fprintf(screenOutput, "\t%d\t", pc);
		}
		fprintf(finalOutput, "\t%d\t", pc);
		fprintf(output, "\t%d\t", pc);
	}
	if (bp < 10)
	{
		// prints to screen if selected
		if (printVm == 1)
		{
			printf(" %d\t", bp);
			fprintf(screenOutput, " %d\t", bp);
		}
		fprintf(finalOutput, " %d\t", bp);
		fprintf(output, " %d\t", bp);
	}
	else
	{
		// prints to screen if selected
		if (printVm == 1)
		{
			printf("%d\t", bp);
			fprintf(screenOutput, "%d\t", bp);
		}
		fprintf(finalOutput, "%d\t", bp);
		fprintf(output, "%d\t", bp);
	}
	if (sp < 10)
	{
		// prints to screen if selected
		if (printVm == 1)
		{
			printf(" %d\t", sp);
			fprintf(screenOutput, " %d\t", sp);
		}
		fprintf(finalOutput, " %d\t", sp);
		fprintf(output, " %d\t", sp);
	}
	else
	{
		// prints to screen if selected
		if (printVm == 1)
		{
			printf("%d\t", sp);
			fprintf(screenOutput, "%d\t", sp);
		}
		fprintf(finalOutput, "%d\t", sp);
		fprintf(output, "%d\t", sp);
	}

	// prints the registers
	// prints to screen if selected
	if (printVm == 1)
	{
		printf("%d %d %d %d", registers[0], registers[1], registers[2], registers[3]);
		printf(" %d %d %d %d\n", registers[4], registers[5], registers[6], registers[7]);
		fprintf(screenOutput, "%d %d %d %d", registers[0], registers[1], registers[2], registers[3]);
		fprintf(screenOutput, " %d %d %d %d\n", registers[4], registers[5], registers[6], registers[7]);
	}
	fprintf(finalOutput, "%d %d %d %d", registers[0], registers[1], registers[2], registers[3]);
	fprintf(finalOutput, " %d %d %d %d\n", registers[4], registers[5], registers[6], registers[7]);
	fprintf(output, "%d %d %d %d", registers[0], registers[1], registers[2], registers[3]);
	fprintf(output, " %d %d %d %d\n", registers[4], registers[5], registers[6], registers[7]);

	// prints stack, with adjustment for if no stack
	if (sp > 1)
	{
		// prints to screen if selected
		if (printVm == 1)
		{
			printf("Stack: ");
			fprintf(screenOutput, "Stack: ");
		}
		fprintf(finalOutput, "Stack: ");
		fprintf(output, "Stack: ");
	}
	else
	{
		// prints to screen if selected
		if (printVm == 1)
		{
			printf("Stack");
			fprintf(screenOutput, "Stack");
		}
		fprintf(finalOutput, "Stack");
		fprintf(output, "Stack");
	}

	i;
	j = 0;
    check;

	// prints out the stack contents
	for (i = 1; i <= sp; i++)
	{
		// Separates each activation record
	    check=sparray->array[j];
	    if(check == 0)
	    {
	      j++;
	    }
	    if (i == (check+1) && check != 0)
	    {
	    	if (printVm == 1)
			  {
  				printf("| ");
  				fprintf(screenOutput, "| ");
			  }
			fprintf(finalOutput, "| ");
	    	fprintf(output, "| ");
	    	j++;
	    }

		if (i == sp)
		{
			// prints to screen if selected
			if (printVm == 1)
			{
				printf("%d", stack[i]);
				fprintf(screenOutput, "%d", stack[i]);
			}
			fprintf(finalOutput, "%d", stack[i]);
			fprintf(output, "%d", stack[i]);
		}
		else
		{
			// prints to screen if selected
			if (printVm == 1)
			{
				printf("%d ", stack[i]);
				fprintf(screenOutput, "%d ", stack[i]);
			}
			fprintf(finalOutput, "%d ", stack[i]);
			fprintf(output, "%d ", stack[i]);
		}
	}
	// formatting of new lines
	if (halt != 1)
	{
		if (printVm == 1)
		{
			printf("\n\n");
			fprintf(screenOutput, "\n\n");
		}
		fprintf(output, "\n\n");
		fprintf(finalOutput, "\n\n");
	}

	// formatting for end of program
	if (printVm == 1)
	{
		printf("\n");
		fprintf(screenOutput, "\n");
	}
}

// Given function, by Dr. Euripides Montagne at UCF.
// Finds lexographical level
int base(int l, int base)
{
	int b1; // find base L levels down
	b1 = base;
	while (l > 0)
	{
		b1 = stack[b1 + 1];
		l--;
	}
	return b1;
}

// run the full virtual machine program
void vitual_machine(FILE *screenOutput)
{
	int halt = 0;
	instruction *instr = NULL;
	instruction instrReg;

	// Open file, check if null
	// FILE *filename = fopen(argv[1], "r"); // for input file
	FILE *filename = fopen("machineCode.txt", "r");
	if(filename == NULL)
	{
		return;
	}
	// FILE *output = fopen(argv[2], "w"); // for output file
	FILE *output = fopen("vmOutput.txt", "w");
	record *sparray=createArray(10);
	// Read in the instruction data into instr
	instr = readData(filename);

	// Prints all of the instructions
	printInstructions(output, screenOutput, instr, &instrReg);
	fprintf(output, "\n");

	// Perform the fetch and execution cycles.
	fetchAndRun(output, screenOutput, sparray, instr, &instrReg, halt);

	// Close the file and free pointers
	fclose(filename);
	fclose(output);
	free(instr);
}
