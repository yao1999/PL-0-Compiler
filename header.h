// Zefeng Yao
// Alexandra French
// System Software
// HW3
// Modified for HW4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#ifndef header
#define header


// LEXER FUNCTIONS
typedef struct arrays
{
  int capacity;
  int capacity_xy;
  int capacity_only_num;
  int *array_num;
  char **array_only_num;
  char **array_xy;
  int num_size;
  int only_num_size;
  int xy_size;
}arrays;

arrays *createArrays(int capacity);
arrays *destroy(arrays *arr);
void expand(arrays *all_array);
void expand_only_num(arrays *all_array);
void expand_xy(arrays *all_array);
void format(char *str, int token, FILE *output);
void insert(arrays *all_array, char *str, int token, FILE *output);
void insert_xy(arrays *all_array, char *str);
char *reset(char *str, int size);
void forspace(char *str);
void fornextline(char *str);
void fortab(char *str);
void forcarriagereturn(char *str);
void for_left_right(char *str);
void only_useful(char *str);
void lexical_conventions(arrays *all_array, char *str, int *str_size, FILE *output);
void printdata(arrays *all_array, FILE *output, FILE *screenOutput);
void readData_only_for_output(FILE *input, FILE *output);
int for_comments(char *line);
void readData_lexeme_table(arrays *all_array, FILE *input);
int check_valid(char *str);
int error3(char *str, FILE *screenOutput);
int error2(char *str, FILE *screenOutput);
int error4(char *str, FILE *screenOutput);
int run_four_time(char *str, int *str_size, FILE *screenOutput);
int error1(char *str, FILE *screenOutput);
int check_the_error1(char *line, FILE *screenOutput);
int HQ(FILE *input, FILE *screenOutput);
void lexicalAnalyzer(FILE *input, FILE *screenOutput);


// PARSER FUNCTIONS
typedef struct token_list {
	int tokenTypeInt;
	int lexemeNumber;
	char lexemeName[11];
	char lexemeType[12];
} token_list;

void error(int error_num, FILE *screenOutput);
void populateArray(FILE *input);
void getToken(FILE *ifp);
void printLexemeNames(FILE *output);
void insert_symbol_table(int kind, char *name, int val, int address, int level);
int search(char *name, FILE *screenOutput, int level);
int invalidate(int level);
int rel_op(int token_type);
void term(FILE *ifp, FILE *screenOutput);
void expression(FILE *ifp, FILE *screenOutput);
void condition(FILE *ifp, FILE *screenOutput);
void statement(FILE *ifp, FILE *screenOutput);
void block_const(FILE *ifp, FILE *screenOutput);
int block_var(FILE *ifp, int currM, FILE *screenOutput);
void block(FILE *ifp, FILE *screenOutput);
void program(FILE *ifp, FILE *screenOutput);
void printall();
void parser(FILE *screenOutput);
void factor(FILE *ifp, FILE *screenOutput);
void printemit(FILE *screenOutput);
void emit(int newOp, int newM, int newL, int newR);


// GLOBAL FUNCTIONS / USAGES

// global file pointer for overall file.
FILE *finalOutput;

// to debug (not remove), set = 0
#define DEBUG 1
#define DEBUGFAIL 1

// removes all the old files at end
void remove_end(int debug)
{
	if (debug == 0)
	{
		return;
	}
	remove("initialInput.txt");
	remove("lexemeList.txt");
	remove("symbolicLexemes.txt");
	remove("lexemeTable.txt");
	remove("machineCode.txt");
	remove("vmOutput.txt");
	remove("symbolTable.txt");
}

// adds error messages
char* error_messages[] = {
  "***** Error number 0. FILE NOT FOUND.",
  "***** Error number 1. Use = instead of :=.",
  "***** Error number 2. = must be followed by a number.",
  "***** Error number 3. Identifier must be followed by =.",
  "***** Error number 4. const, var, procedure must be followed by identifier.",
  "***** Error number 5. Semicolon or comma missing.",
  "***** Error number 6. Incorrect symbol after procedure declaration.",
  "***** Error number 7. Statement expected.",
  "***** Error number 8. Incorrect symbol after statement part in block.",
  "***** Error number 9. Period expected.",
  "***** Error number 10. Semicolon between statements missing.",
  "***** Error number 11. Undeclared identifier.",
  "***** Error number 12. Assignment to constant or procedure is not allowed.",
  "***** Error number 13. Assignment operator expected.",
  "***** Error number 14. call must be followed by an identifier.",
  "***** Error number 15. Call of a constant or variable is meaningless.",
  "***** Error number 16. then expected.",
  "***** Error number 17. Semicolon or end expected.",
  "***** Error number 18. do expected.",
  "***** Error number 19. Incorrect symbol following statement.",
  "***** Error number 20. Relational operator expected.",
  "***** Error number 21. Expression must not contain a procedure identifier.",
  "***** Error number 22. Right parenthesis missing.",
  "***** Error number 23. The preceding factor cannot begin with this symbol.",
  "***** Error number 24. An expression cannot begin with this symbol.",
  "***** Error number 25. This number is too large.",
  "***** Error number 26. Identifier too long.",
  "***** Error number 27. Invalid symbol.",
  "***** Error number 28. This variable does not start with letter.",
  "***** Error number 29. Invalid comment.",
  "***** Error number 30. Out of index.",
  "***** Error number 31. Exceeded max lexical level."
};

// adds global "should print" for each
int printLex = 0;
int printParser = 0;
int printVm = 0;

// tokens
const char* tokens[] = {"+", "-", "*", "/", "odd", "=", "<>", "<", "<=",
                        ">", ">=", "(", ")", ",", ";", ".",  ":=", "begin",
                        "end", "if", "then", "while", "do", "call", "const",
                        "var", "procedure", "write", "read", "else"};

// token numbers
typedef enum
{
  nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6, slashsym = 7, oddsym = 8,
  eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16,
  commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23,
  thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
  readsym = 32, elsesym = 33
}token_type;

// definitions
#define LIT 1
#define RTN 2
#define LOD 3
#define STO 4
#define CAL 5
#define INC 6
#define JMP 7
#define JPC 8
#define SIO9 9
#define SIO10 10
#define SIO11 11
#define NEG 12
#define ADD 13
#define SUB 14
#define MUL 15
#define DIV 16
#define ODD 17
#define MOD 18
#define EQL 19
#define NEQ 20
#define LSS 21
#define LEQ 22
#define GTR 23
#define GEQ 24


#endif
