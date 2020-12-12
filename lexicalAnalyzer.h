// Zefeng Yao
// Alexandra French
// System Software
// HW2 - lex analyzer
// Modified for HW4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

FILE *input;


// creates an structure to store all lex token names and types.
arrays *createArrays(int capacity)
{
  int i,j;
  arrays *arrs = malloc(sizeof(arrays));
  // establish all values
  arrs->capacity = capacity;
  arrs->capacity_xy = capacity;
  arrs->capacity_only_num = capacity;
  arrs->num_size = 0;
  arrs->xy_size = 0;
  arrs->only_num_size = 0;

  // allocate memory
  arrs->array_num = malloc(sizeof(int) * arrs->capacity);
  arrs->array_only_num = malloc(sizeof(char*) * arrs->capacity_only_num);
  // allocate memory for entire num area
  for (j = 0; j < arrs->capacity; j++)
  {
    arrs->array_only_num[j] = malloc(sizeof(char) * 15);
  }
  // allocate memory for entire xy area
  arrs->array_xy = malloc(sizeof(char*) * arrs->capacity_xy);
  for (i = 0; i < arrs->capacity; i++)
  {
    arrs->array_xy[i] = malloc(sizeof(char) * 15);
  }
  return arrs;
}

// Destroys(frees) entire array structure
arrays *destroy(arrays *arr)
{
  int i,j;
  free(arr->array_num);
  // free inside num
  for(i = 0; i < arr->only_num_size; i++)
  {
    free(arr->array_only_num[i]);
  }
  free(arr->array_only_num);
  // free inside xy
  for(j = 0; j < arr->xy_size; j++)
  {
    free(arr->array_xy[j]);
  }
  free(arr->array_xy);
  free(arr);
  return NULL;
}

// Expands the array to accomodate more tokens/lexemes.
void expand(arrays *all_array)
{
  int capacity = 2 * all_array->capacity + 1;
  int *new_array = realloc(all_array->array_num, sizeof(int) * capacity);
  all_array->capacity = capacity;
  all_array->array_num = new_array;
}

// Expands the array out to accomodate more lexeme names.
void expand_xy(arrays *all_array)
{
  int i;
  int capacity = 2 * all_array->capacity_xy + 1;
  char **new_array = realloc(all_array->array_xy, sizeof(char *) * capacity);
  for (i = all_array->capacity_xy; i < capacity; i++)
  {
    new_array[i] = malloc(sizeof(char) * 15);
  }
  all_array->capacity_xy = capacity;
  all_array->array_xy = new_array;
}

// expand the array out to accomodate more numbers
void expand_only_num(arrays *all_array)
{
  int i;
  int capacity = 2 * all_array->capacity_only_num + 1;
  char **new_array = realloc(all_array->array_only_num, sizeof(char *) * capacity);
  for (i = all_array->capacity_only_num; i < capacity; i++)
  {
    new_array[i] = malloc(sizeof(char) * 15);
  }
  all_array->capacity_only_num = capacity;
  all_array->array_only_num = new_array;
}

// Adds the format for lexeme table
void format(char *str, int token, FILE *output)
{
  int total_space = 11 - strlen(str);
  int i = 0;
  fprintf(output, "%s", str);
  fprintf(finalOutput, "%s", str);
  for (i = 0; i < total_space; i++)
  {
    fprintf(output, " ");
    fprintf(finalOutput, " ");
  }
  fprintf(output, "%d\n", token);
  fprintf(finalOutput, "%d\n", token);
}

// Inserts the token into the lexeme array
void insert(arrays *all_array, char *str, int token, FILE *output)
{
  if (all_array->num_size >= all_array->capacity)
  {
    expand(all_array);
  }
  all_array->array_num[all_array->num_size] = token;
  format(str, all_array->array_num[all_array->num_size], output);
  all_array->num_size++;
}

// Inserts numbers into the lexeme array
void insert_num(arrays *all_array, char *str)
{
  int index;
  if (all_array->only_num_size >= all_array->capacity_only_num)
  {
    expand_only_num(all_array);
  }
  for (index = 0; index < strlen(str); index++)
  {
    all_array->array_only_num[all_array->only_num_size][index] = str[index];
  }
  all_array->array_only_num[all_array->only_num_size][index] = '\0'; // important, don't delete
  all_array->only_num_size++;
}

// Inserts letters into the lexeme array
void insert_xy(arrays *all_array, char *str)
{
  int index;
  if (all_array->xy_size >= all_array->capacity_xy)
  {
    expand_xy(all_array);
  }
  for (index = 0; index < strlen(str); index++)
  {
    all_array->array_xy[all_array->xy_size][index] = str[index];
  }
  all_array->array_xy[all_array->xy_size][index] = '\0'; // important, don't delete
  all_array->xy_size++;
}

// Resets the string to a new line character
char *reset(char *str, int size)
{
  /*
  printf("the str is %s\n", str);
  free(str);
  str=NULL;
  if(str==NULL)
  {
    printf("the str is NULL\n");
  }
  printf("he str should be NULL\n");
  char *new_str = NULL;
  new_str = calloc(size, sizeof(char));
  new_str[0] = '\0';
  if(new_str!=NULL)
  {
    printf("created\n");
  }*/
  str[0] = '\0';
  //return new_str;
  return str;
}

// Removes any spaces and adds a string terminator.
void forspace(char *str)
{
  int count = 0;
  int i = 0;
  while (str[i])
  {
    if (str[i] != ' ')
    {
      str[count] = str[i];
      count++;
    }
    i++;
  }
  str[count] = '\0';
}

// Removes any new lines and adds a string terminator.
void fornextline(char *str)
{
  int count = 0;
  int i = 0;
  while (str[i])
  {
    if (str[i] != '\n')
    {
      str[count] = str[i];
      count++;
    }
    i++;
  }
  str[count] = '\0';
}

// Removes any tabs and adds a string terminator.
void fortab(char *str)
{
  int count = 0;
  int i = 0;
  while (str[i])
  {
    if (str[i] != '\t')
    {
      str[count] = str[i];
      count++;
    }
    i++;
  }
  str[count] = '\0';
}

// Removes any carriage returns and adds a string terminator.
void forcarriagereturn(char *str)
{
  int count = 0;
  int i = 0;
  while (str[i])
  {
    if (str[i] != '\r')
    {
      str[count] = str[i];
      count++;
    }
    i++;
  }
  str[count] = '\0';
}

// ensures that ( has a  )
void for_left_right(char *str)
{
  int count = 0;
  int i = 0;
  if(str[strlen(str) - 1] == ')')
  {
    str[strlen(str)-1] = '\0';
  }
  while (str[i])
  {
    if (str[i] != '(')
    {
      str[count] = str[i];
      count++;
    }
    i++;
  }
  str[count] = '\0';
}

// Removes tabs, new lines, and carriage retunrs from the string.
void only_useful(char *str)
{
  fortab(str); // remove tabs
  fornextline(str); // remove new lines
  forcarriagereturn(str); // remove carriage return
}

// checks that identifier
int check_ident(char *str)
{
  int i;
  if (strlen(str) > 1)
  {
    for (i = 0; i< strlen(str); i++)
    {
      if(isalpha(str[i]) == 0 && isdigit(str[i]) == 0)
      {
        return 0;
      }
    }
  }
  return 1;
}

// for any identifiers, add and check )
void for_ident(arrays *all_array, char *str, int right_parent, FILE *output)
{
  insert(all_array, str, 2, output); // token ID: identsym = 2
  insert_xy(all_array, str);
  if (right_parent == 1)
  {
    insert(all_array, ")", 16, output);
  }
}

// for symbgol add and check )
void for_sym(arrays *all_array, char *str, int right_parent, FILE *output)
{
  int place = 0;
  int i = 0;
  while (tokens[i])
  {
    // If string is in tokens, add it.
    if (strcmp(str, tokens[i]) == 0)
    {
      place = i + 4;
      insert(all_array, str, place, output);
      if(right_parent==1)
      {
        insert(all_array, ")", 16, output);
      }
      return;
    }
    i++;
  }
}

// for num check digits and add )
void for_num(arrays *all_array, char *str, int right_parent, FILE *output)
{
    int t = 0;
    int many_digit = 0;
    // If variable
    if (all_array->array_num[all_array->num_size - 1] == varsym)
    {
      return;
    }
    // Increment digit count
    while (str[t])
    {
      if (isdigit(str[t]) != 0)
      {
        many_digit++;
      }
      t++;
    }
    // If number less than length of 6, add token
    if (many_digit <= 5)
    {
        insert(all_array, str, 3, output); // token ID: numbersym
        insert_num(all_array, str);
        if (right_parent==1)
        {
          insert(all_array, ")", 16, output);
        }
        return;
    }
}

// check long strings
void check_long_str(arrays *all_array, char *str, int right_parent, FILE *output)
{
  int index_for_not_symb = 0;
  int index_for_symb = 0;
  int i = 0;
  char *not_symb = malloc(sizeof(char)*50);
  char *symb = malloc(sizeof(char)*12);

  for (i=0; i< strlen(str); i++)
  {
    if (isalpha(str[i]) == 0 && isdigit(str[i]) == 0)
    {
      symb[index_for_symb] = str[i];
      index_for_symb++;
      symb[index_for_symb] = '\0';
      // check next char, if it is not symbol and it is last char, go in
      // else forgot
      if((isalpha(str[i+1]) != 0 && isdigit(str[i+1]) == 0) ||
      (isalpha(str[i + 1]) == 0 && isdigit(str[i + 1]) != 0) || i == strlen(str) - 1)
      {
        for_sym(all_array, symb, right_parent, output);
        symb=reset(symb, 12);
        index_for_symb = 0;
      }
    }
    else
    {
      not_symb[index_for_not_symb] = str[i];
      index_for_not_symb++;
      not_symb[index_for_not_symb] = '\0';
      // check next char, if it is not symbol and it is last char, go in
      // else forgot
      if ((isalpha(str[i + 1]) == 0 && isdigit(str[i + 1]) == 0) || i == strlen(str) - 1)
      {
        // num version
        if (isdigit(not_symb[0]) != 0)
        {
          for_num(all_array, not_symb, right_parent, output);
          not_symb=reset(not_symb, 50);
          index_for_not_symb = 0;
        }
        // letter version
        else if (isalpha(not_symb[0]) != 0)
        {
          for_ident(all_array, not_symb, right_parent, output);
          not_symb = reset(not_symb, 50);
          index_for_not_symb = 0;
        }
      }
    }
  }

  free(not_symb);
  free(symb);
}

// Checks for what the token is.
// Resets the str before return
void lexical_conventions(arrays *all_array, char *str, int *str_size, FILE *output)
{
  int left_parent = 0;
  int right_parent = 0;

  // if string is empty, return
  if (strlen(str) == 0 || str[0] == '\0')
  {
    return;
  }

  if (str[0] == '(')
  {
    left_parent = 1;
    insert(all_array, "(", 15, output);
    if(strlen(str) == 1)
    {
      *str_size = 0;
      str = reset(str, 15);
      return;
    }
  }

  if (str[strlen(str) - 1] == ')')
  {
    right_parent = 1;
    if(strlen(str) == 1)
    {
      insert(all_array, ")", 16, output);
      *str_size = 0;
      str = reset(str, 15);
      return;
    }
  }

  if (left_parent == 1 || right_parent == 1)
  {
    for_left_right(str);
  }

  // Remove any spaces.
  forspace(str);
  int i = 0, old;
  int place = 0;
  int num = atoi(str);

  // Checks if the string is a number
  if (isdigit(str[0]) != 0 || num != 0)
  {
    int t = 0;
    int many_digit = 0;
    int many_letter = 0;

    // If variable
    if (all_array->array_num[all_array->num_size - 1] == varsym)
    {
      *str_size = 0;
      str = reset(str, 15);
      return;
    }
    // Increment digit count
    while (str[t])
    {
      if(isdigit(str[t]) != 0)
      {
        many_digit++;
      }
      if(isalpha(str[t]) != 0 || str[t] == '=')
      {
        many_letter++;
      }
      t++;
    }
    // check letter size
    if(many_letter > 0)
    {
      check_long_str(all_array, str, right_parent, output);
      *str_size = 0;
      str = reset(str, 15);
      return;
    }

    // If number less than length of 6, add token
    if (many_digit <= 5)
    {
        insert(all_array, str, 3, output); // token ID: numbersym
        insert_num(all_array, str);
        if(right_parent == 1)
        {
          insert(all_array, ")", 16, output);
        }
        *str_size = 0;
        str = reset(str, 15);
        return;
    }
  }

  i = 0;
  // Checks if the string is in any of the tokens[][]
  while (tokens[i])
  {
    // If string is in tokens, add it.
    if(strcmp(str, tokens[i]) == 0)
    {
      place = i + 4;
      insert(all_array, str, place, output);
      if(right_parent == 1)
      {
        insert(all_array, ")", 16, output);
      }
      *str_size = 0;
      str=reset(str, 15);
      return;
    }
    i++;
  }

  // checks - and +, allows with a number
  if ((str[0] == '-' || str[0] == '+') && strlen(str) > 1)
  {
  	// add the - or +
    if (str[0] == '-')
    {
      insert(all_array, "-", 5, output);
    }
    else if (str[0] == '+')
    {
      insert(all_array, "+", 4, output);
    }

    int new = 0;

	   // make new string = old
    for (old = 1; old < strlen(str); old++)
    {
      str[new] = str[old];
      new++;
    }
    str[new] = '\0';

    int t = 0;
    int many_digit = 0;
    int many_letter = 0;

    // while string, add to digit or letter
    while (str[t])
    {
      if(isdigit(str[t]) != 0)
      {
        many_digit++;
      }
      if(isalpha(str[t]) != 0)
      {
        many_letter++;
      }
      t++;
    }

    // if letters > 0, check if long
    if(many_letter > 0)
    {
      check_long_str(all_array, str, right_parent, output);
      *str_size = 0;
      str = reset(str, 15);
      return;
    }

    // If number less than length of 6, add token
    if (many_digit <= 5)
    {
        insert(all_array, str, 3, output); // token ID: numbersym
        insert_num(all_array, str);
        if (right_parent == 1)
        {
          insert(all_array, ")", 16, output);
        }
        *str_size = 0;
        str = reset(str, 15);
        return;
    }
  }

  // Checks if the string is a letter ex(x,y,z,a,b, etc)
  // Less than length 11
  if (isalpha(str[0]) != 0)
  {
    // Add all letters to the array
    if (check_ident(str) == 1 && strlen(str) < 11)
    {
      insert(all_array, str, 2, output); // token ID: identsym = 2
      insert_xy(all_array, str);
      if (right_parent == 1)
      {
        insert(all_array, ")", 16, output);
      }
      *str_size = 0;
      str = reset(str, 15);
      return;
    }
    else if (check_ident(str) == 0)
    {
      check_long_str(all_array, str, right_parent, output);
      *str_size = 0;
      str = reset(str, 15);
      return;
    }
  }
  if (right_parent == 1)
  {
    insert(all_array, ")", 16, output);
  }
  *str_size = 0;
  str = reset(str, 15);
}

// prints for the lexeme list
void printdata(arrays *all_array, FILE *output, FILE *screenOutput)
{
  int i = 0;
  int j = 0;
  int n = 0;

  // if print = 1, print out the lexeme list to screen
  if (printLex == 1)
  {
    printf("Lexeme List:\n");
    fprintf(screenOutput, "\nLexeme List:\n");

  }
  // always print to overall output file.
  fprintf(finalOutput, "\n");
  fprintf(finalOutput, "Lexeme List:\n");

  for (i = 0; i < all_array->num_size; i++)
  {
    // Print out all of the tokens/names
    if (all_array->array_num[i] == 2)
    {
      // if print = 1, print out the lexeme list to screen and to a final output file
      if (printLex == 1)
      {
      	printf("%d ", all_array->array_num[i]);
      	fprintf(screenOutput, "%d ", all_array->array_num[i]);
	  }
	  // always print to overall output file.
	  fprintf(finalOutput, "%d ", all_array->array_num[i]);
      fprintf(output, "%d ", all_array->array_num[i]);
      printf("%d, %d\n", j, all_array->xy_size);
      if (j <= all_array->xy_size)
      {
      	// if print = 1, print out the lexeme list to screen and to a final output file
      	if (printLex == 1)
     	{
     	  printf("%s ", all_array->array_xy[j]);
     	  fprintf(screenOutput, "%s ", all_array->array_xy[j]);
	    }
	    // always print to overall output file.
	    fprintf(finalOutput, "%s ", all_array->array_xy[j]);
        fprintf(output, "%s ", all_array->array_xy[j]);
        j++;
      }
      else
      {
      	printf("%s\n", error_messages[30]);
      	fprintf(screenOutput, "%s\n", error_messages[30]);
      	fprintf(finalOutput, "%s\n", error_messages[30]);
      	remove_end(DEBUGFAIL);
    	exit(EXIT_SUCCESS);
      }
    }
    else if (all_array->array_num[i] == 3)
    {
      // if print = 1, print out the lexeme list to screen and to a final output file
      if (printLex == 1)
      {
      	printf("%d ", all_array->array_num[i]);
      	fprintf(screenOutput, "%d ", all_array->array_num[i]);
	  }
	  // always print to overall output file.
      fprintf(finalOutput, "%d ", all_array->array_num[i]);
      fprintf(output, "%d ", all_array->array_num[i]);
      if (n <= all_array->only_num_size)
      {
      	// if print = 1, print out the lexeme list to screen and to a final output file
      	if (printLex == 1)
      	{
      		printf("%s ", all_array->array_only_num[n]);
      		fprintf(screenOutput, "%s ", all_array->array_only_num[n]);
		}
		// always print to overall output file.
		fprintf(finalOutput, "%s ", all_array->array_only_num[n]);
        fprintf(output, "%s ", all_array->array_only_num[n]);
        n++;
      }
      else
      {
      	printf("%s\n", error_messages[30]);
      	fprintf(screenOutput, "%s\n", error_messages[30]);
      	fprintf(finalOutput, "%s\n", error_messages[30]);
      	remove_end(DEBUGFAIL);
      	exit(EXIT_SUCCESS);
      }
    }
    else
    {
      // if print = 1, print out the lexeme list to screen and to a final output file
      if (printLex == 1)
      {
      	printf("%d ", all_array->array_num[i]);
      	fprintf(screenOutput, "%d ", all_array->array_num[i]);
	  }
	  // always print to overall output file.
	  fprintf(finalOutput, "%d ", all_array->array_num[i]);
      fprintf(output, "%d ", all_array->array_num[i]);
    }
  }
  // if print = 1, print out the lexeme list to screen and to a final output file
  if (printLex == 1)
  {
  	printf("\n");
  	fprintf(screenOutput, "\n");
  }
  // always print to overall output file.
  fprintf(finalOutput, "\n");
}

// prints the source program
void readData_only_for_output(FILE *input, FILE *output)
{
  char *line = malloc(sizeof(char) * 100);
  int flag = 0;
  // open up a file just for the input (in case the program dies)
  FILE *inputOutput = fopen("initialInput.txt", "w");

  // While not end of file, scan in each line and print it back out.
  fprintf(inputOutput, "Source Program:\n");
  fprintf(output, "Source Program:\n");
  fprintf(finalOutput, "Source Program:\n");
  while (fgets(line, 100, input) != NULL)
  {
    fprintf(inputOutput, "%s", line);
    fprintf(output, "%s", line);
    fprintf(finalOutput, "%s", line);
  }
  fprintf(output, "\n");
  fprintf(finalOutput, "\n");
  free(line);
  fclose(inputOutput);
}

// This finds the start or end of a comment.
int for_comments(char *line)
{
  int index = 0;
  int i = 0;
  for (i = 0; i < strlen(line); i++)
  {
    if (line[i] == '*' && line[i+1] == '/')
    {
      index = i + 2;
      return index;
    }
  }
  return INT_MIN;
}


// read the file and check with the token array and print lexeme list
void readData_lexeme_table(arrays *all_array, FILE *input)
{
  char *line = malloc(sizeof(char) * 100);
  char *str = malloc(sizeof(char) * 15);
  char *only = calloc(15, sizeof(char));
  int i = 0;
  int str_size = 0;
  int iscomment = 0;

  // open a file just for lexeme table output
  FILE *tableOutput = fopen("lexemeTable.txt", "w");
  fprintf(tableOutput, "Lexeme Table:\n");
  fprintf(tableOutput, "lexeme     token type\n");

  fprintf(finalOutput, "\nLexeme Table:\n");
  fprintf(finalOutput, "lexeme     token type\n");

  // While not end of file, scan in each line and check for errors.
  while (!feof(input))
  {
    if (fgets(line, 100, input) != NULL) // save the line in to string "line"
    {
      only_useful(line);
      for (i = 0; i < strlen(line); i++)
      {
        if ((line[i] == '/' && line[i+1] == '*') || iscomment == INT_MIN)
        {
          str[str_size] = '\0';
          //lexical_conventions(all_array,str, &str_size, tableOutput);
          iscomment = for_comments(line);
          if (iscomment != INT_MIN)
          {
            i = iscomment;
          }
          else
          {
            break;
          }
        }
        // if the char is a space or it is the last char
        // call lexical_conventions (still has the string before the space)
        // then continue
        else if (line[i] == ' ')
        {
          str[str_size] = '\0';
          lexical_conventions(all_array, str, &str_size, tableOutput);
          continue;
        }
        // if the char is ";" or "," or "." etc
        // call the lexical_conventions (still has the string before)
        // then insert ";" or "," or "." etc into str
        // call the lexical_conventions (has ";", ",","." etc) again
        else if (line[i] == ';' || line[i] == ',' || line[i] == '.')
        {
          str[str_size]='\0';
          lexical_conventions(all_array, str, &str_size, tableOutput);
          only[0] = line[i];
          only[1]='\0';
          lexical_conventions(all_array, only, &str_size, tableOutput);
        }
        else if ((i==strlen(line) - 1 && isalpha(line[i]) != 0) || (i==strlen(line) - 1 && isdigit(line[i]) != 0))
        {
          str[str_size] = line[i];
          str_size++;
          str[str_size] = '\0';
          lexical_conventions(all_array,str, &str_size, tableOutput);
        }
        // insert letter into str
        else
        {
          str[str_size] = line[i];
          str_size++;
          str[str_size]='\0';
        }
      }
    }
  }
  free(line);
  free(str);
  free(only);
  // close all files
  fclose(tableOutput);
}

// Checks if the string is a symbol or otherwise
int check_valid(char *str)
{
  int i = 0;
  for (i = 0; i < strlen(str); i++)
  {
    if (isalpha(str[i]) == 0 && isdigit(str[i]) == 0)
    {
      return 1;
    }
  }
  return 0;
}

// Checks for the name being too long
int error3(char *str, FILE *screenOutput)
{
  forspace(str);
  // If string is blank, return success
  if (strlen(str) == 0 || str[0] == '\0')
  {
    return 0;
  }

  int error = 0;
  // If the string is not a character
  if (isalpha(str[0]) != 0)
  {
    // and if the string is more than 11 characters long, error
    if (strlen(str) > 11)
    {
      printf("%s\n", error_messages[26]);
      printf("Name %s is too long\n", str);
      fprintf(screenOutput, "%s\n", error_messages[26]);
      fprintf(screenOutput, "Name %s is too long\n", str);
      fprintf(finalOutput, "%s\n", error_messages[26]);
      fprintf(finalOutput, "Name %s is too long\n", str);
      remove_end(DEBUGFAIL);
      exit(EXIT_SUCCESS);
      error = 1;
      return error;
    }
    // If the string isnt valid, error
    if (check_valid(str)==1)
    {
      error = 1;
      return error;
    }
    else
    {
      error = 0;
      return error;
    }
  }
  return error;
}

// Checks for the number being too long.
int error2(char *str, FILE *screenOutput)
{
  forspace(str);
  // If the string is blank, success.
  if (strlen(str) == 0 || str[0] == '\0')
  {
    return 0;
  }

  int error = 0;
  // If a digit
  if (isdigit(str[0]) != 0)
  {
    int t = 0;
    int many_digit = 0;
    int many_letter = 0;
    while(str[t])
    {
        // Increment digit counter if exists
      if (isdigit(str[t]) != 0 || str[t]=='0')
      {
        many_digit++;
      }
      else if (isalpha(str[t]) != 0)
      {
        many_letter++;
      }
      t++;
    }
    if (many_letter >= 1)
    {
      error = 1;
      printf("%s\n", error_messages[28]);
      printf("%s is invalid\n", str);
      fprintf(screenOutput, "%s\n", error_messages[28]);
      fprintf(screenOutput, "%s is invalid\n", str);
      fprintf(finalOutput, "%s\n", error_messages[28]);
      fprintf(finalOutput, "%s is invalid\n", str);
      remove_end(DEBUGFAIL);
      exit(EXIT_SUCCESS);
      str = reset(str, 100);
      return error;
    }
    // If too many digits, error
    if (many_digit >= 6)
    {
      printf("%s\n", error_messages[25]);
      printf("Number %s is too long\n", str);
      fprintf(screenOutput, "%s\n", error_messages[25]);
      fprintf(screenOutput, "Number %s is too long\n", str);
      fprintf(finalOutput, "%s\n", error_messages[25]);
      fprintf(finalOutput, "Number %s is too long\n", str);
      remove_end(DEBUGFAIL);
      exit(EXIT_SUCCESS);
      error = 1;
      return error;
    }
    else
    {
      return error;
    }
  }
  return error;
}

// Checks for invalid symbol error
int error4(char *str, FILE *screenOutput)
{
  forspace(str);
  // If string blank, success

  int left_parent = 0;
  int right_parent = 0;
  if (str[0] == '(')
  {
    left_parent = 1;

  }
  if (str[strlen(str) - 1] == ')')
  {
    right_parent = 1;
  }
  if(left_parent == 1 || right_parent == 1)
  {
    for_left_right(str);
  }

  if (strlen(str) == 0 || str[0] == '\0')
  {
    return 0;
  }

  int i = 0;
  int error = 0;
  int flag = 0;

  while (tokens[i])
  {
      // if the string is a token, not an error
    if (strcmp(str, tokens[i]) == 0)
    {
      error = 0;
      flag = 1;
      return error;
    }
    i++;
  }
  // If within the string limit
  if (strlen(str) < 11)
  {
    // If neither a digit not a char, error
    if (isdigit(str[0]) == 0 && isalpha(str[0]) == 0)
    {
      error = 1;
      printf("%s\n", error_messages[27]);
      printf("%s is invalid\n", str);
      fprintf(screenOutput, "%s\n", error_messages[27]);
      fprintf(screenOutput, "%s is invalid\n", str);
      fprintf(finalOutput, "%s\n", error_messages[27]);
      fprintf(finalOutput, "%s is invalid\n", str);
      remove_end(DEBUGFAIL);
      exit(EXIT_SUCCESS);
    }
    else if (isdigit(str[0]) != 0 && strlen(str) >= 6)
    {
      error = 1;
    }
  }
  else
  {
    error = 1;
  }
  return error;
}

// Runs the code four times, to check for each error.
int run_four_time(char *str, int *str_size, FILE *screenOutput)
{
  int error = 0;
  int firsterror = 0;
  int seconderror = 0;
  int thirderror = 0;
  int old;

  if (str[0] == '-' || str[0] == '+')
  {
    int new = 0;

    for (old = 1; old < strlen(str); old++)
    {
      str[new] = str[old];
      new++;
    }
    str[new] = '\0';
  }

  int index_for_not_symb = 0;
  int index_for_symb = 0;
  int i = 0;
  char *not_symb = malloc(sizeof(char)*50);
  char *symb = malloc(sizeof(char)*12);
  char *replace = calloc(strlen(str), sizeof(char));

  strcpy(replace, str);

  for (i = 0; i< strlen(str); i++)
  {
    if (isalpha(str[i]) == 0 && isdigit(str[i]) == 0)
    {
      symb[index_for_symb] = str[i];
      index_for_symb++;
      symb[index_for_symb] = '\0';
      // check next char, if it is not symbol and it is last char, go in
      // else forgot
      if((isalpha(str[i + 1])!=0 && isdigit(str[i+1]) == 0) ||
      (isalpha(str[i + 1]) == 0 && isdigit(str[i + 1]) != 0) || i == strlen(str) - 1)
      {
        thirderror = error4(symb, screenOutput);
        symb=reset(symb, 12);
        index_for_symb = 0;
      }
    }
    else
    {
      not_symb[index_for_not_symb] = str[i];
      index_for_not_symb++;
      not_symb[index_for_not_symb] = '\0';
      if ((isalpha(str[i + 1]) == 0 && isdigit(str[i + 1]) == 0) || i == strlen(str) - 1)
      {
        // num version
        if (isdigit(not_symb[0]) != 0)
        {
          seconderror = error2(not_symb, screenOutput);
          not_symb = reset(not_symb, 50);
          index_for_not_symb = 0;
        }
        // letterre version
        else if (isalpha(not_symb[0]) != 0)
        {
          seconderror = error3(not_symb, screenOutput);
          not_symb = reset(not_symb, 50);
          index_for_not_symb = 0;
        }
      }
    }
  }
  free(not_symb);
  free(symb);
  free(replace);
  *str_size = 0;
  str = reset(str, 15);

  // if any of the errors, return 1.
  if (firsterror == 1 || seconderror == 1 || thirderror == 1)
  {
    error = 1;
  }

  return error;
}

// checks for variable not starting with a letter error
int error1(char *str, FILE *screenOutput)
{
  forspace(str);
  // if string is blank, return success
  if (strlen(str) == 0 || str[0] == '\0')
  {
    return 0;
  }
  // If a letter, success
  if (isalpha(str[0]) != 0)
  {
    return 0;
  }

  int error = 0;
  // If a digit, invalid.
  if (isdigit(str[0]) != 0)
  {
  	error = 1;
    printf("%s\n", error_messages[28]);
    printf("%s is invalid\n", str);
    fprintf(screenOutput, "%s\n", error_messages[28]);
    fprintf(screenOutput, "%s is invalid\n", str);
    fprintf(finalOutput, "%s\n", error_messages[28]);
    fprintf(finalOutput, "%s is invalid\n", str);
    remove_end(DEBUGFAIL);
    exit(EXIT_SUCCESS);
    str = reset(str, 100);
    return error;
  }
  str = reset(str, 100);
  return error;
}

// Check error 1
int check_the_error1(char *line, FILE *screenOutput)
{
  char *varia = malloc(sizeof(char) * 100);
  int *array = malloc(sizeof(int) * 30);
  int index = 0;
  int varia_size = 0;
  int place = 0;
  int error = 0;
  int iscomment = 0;
  int i = 0;
  int j = 0;
  // Check if "var"
  for (j = 0; j < strlen(line); j++)
  {
    if (line[j] == 'v' && line[j + 1] == 'a' && line[j + 2] == 'r' && line[j + 3] == ' ')
    {
      j = j + 2;
      place = j;
      break;
    }
  }
  i = place;
  if (i > 0)
  {
    for (i = i; i < strlen(line); i++)
    {
      // see if a comment.
      if ((line[i] == '/' && line[i + 1] == '*') || iscomment == INT_MIN)
      {
        iscomment = for_comments(line);
        if (iscomment != INT_MIN)
        {
          i = iscomment;
        }
        else
        {
          break;
        }
      }
      // if a space, continue
      else if (line[i] == ' ')
      {
        varia[varia_size]='\0';
        array[index] = error1(varia, screenOutput);
        index++;
        varia_size = 0;
        continue;
      }
      // if semicolon or comma, incr size
      else if (line[i] == ';' || line[i] == ',')
      {
        varia[varia_size] = '\0';
        array[index] = error1(varia, screenOutput);
        index++;
        varia_size = 0;
        varia[varia_size] = line[i];
        varia_size++;
        varia[varia_size] = '\0';
        array[index] = error1(varia, screenOutput);
        index++;
        varia_size = 0;
      }
      else if((i == strlen(line) - 1 && isalpha(line[i]) != 0) || (i == strlen(line) - 1 && isdigit(line[i]) != 0))
      {
        varia[varia_size] = line[i];
        varia_size++;
        varia[varia_size] = '\0';
        array[index] = error1(varia, screenOutput);
        index++;
        varia_size = 0;
      }
      else
      {
        varia[varia_size] = line[i];
        varia_size++;
        varia[varia_size] = '\0';
      }
    }
  }
  int e = 0;
    // if any of the errors are active, return an error.
  for (e = 0; e < index; e++)
  {
    if (array[e] == 1)
    {
      error = 1;
      return error;
    }
  }

  // free used values
  free(varia);
  free(array);
  return error;
}

// don't know if the symbol is invalid or is identifiers
int HQ(FILE *input, FILE *screenOutput)
{
  char *line = malloc(sizeof(char) * 100);
  char *str = malloc(sizeof(char) * 15);
  int *array = malloc(sizeof(int) * 256);
  char *only = calloc(15, sizeof(char));
  int index = 0;
  int error = 0;
  int i = 0;
  int str_size = 0;
  int iscomment = 0;

  // while not end of file, continue
  while (!feof(input))
  {
    if (fgets(line, 100, input) != NULL)
    {
      // gets the line minus any blank characters
      only_useful(line);
      // checks if any error
      array[index] = check_the_error1(line, screenOutput);

      index++;
      for (i = 0; i < strlen(line); i++)
      {
        // checks for comments
        if ((line[i] == '/' && line[i + 1] == '*') || iscomment == INT_MIN)
        {
          iscomment = for_comments(line);
          if (iscomment != INT_MIN)
          {
            i = iscomment;
          }
          else
          {
            break;
          }
        }
        // runs to get any errors
        else if (line[i] == ' ')
        {
          str[str_size] = '\0';
          array[index] = run_four_time(str, &str_size, screenOutput);
          index++;
          continue;
        }
        // runs to get any errors
        else if (line[i] == ';' || line[i] == ',' || line[i] == '.')
        {
          str[str_size] = '\0';
          array[index] = run_four_time(str, &str_size, screenOutput);
          index++;
          only[0] = line[i];
          only[1] = '\0';
          array[index] = run_four_time(only, &str_size, screenOutput);
          index++;
        }
        // runs to get any errors
        else if ((i == strlen(line) - 1 && isalpha(line[i]) != 0) || (i == strlen(line) - 1 && isdigit(line[i]) != 0))
        {
          str[str_size] = line[i];
          str_size++;
          str[str_size] = '\0';
          array[index] = run_four_time(str, &str_size, screenOutput);
          index++;
        }
        else
        {
          str[str_size] = line[i];
          str_size++;
          str[str_size] = '\0';
        }
      }
    }
  }
  // checks invalid comment
  if (iscomment == INT_MIN)
  {
  	error = 1;
    printf("%s\n", error_messages[29]);
    fprintf(screenOutput, "%s\n", error_messages[29]);
    fprintf(finalOutput, "%s\n", error_messages[29]);
    remove_end(DEBUGFAIL);
    exit(EXIT_SUCCESS);
  }
  int e = 0;
  // if any errors, returns 1.
  for (e = 0; e < index; e++)
  {
    if (array[e] == 1)
    {
      error = 1;
      return error;
    }
  }
  free(array);
  free(line);
  return error;
}

// run the full lexical analyzer program
void lexicalAnalyzer(FILE *input, FILE *screenOutput)
{
  int count = 0;
  int line_num = 0;
  arrays *all_array = createArrays(10);

  // Check errors
  int error = HQ(input, screenOutput);

  // If errors, return 1
  if (error == 1)
  {
    printf("An error has occured. Cancelling run.\n");
    fprintf(screenOutput, "An error has occured. Cancelling run.\n");
    fprintf(finalOutput, "An error has occured. Cancelling run.\n");
    fclose(screenOutput);
    remove_end(DEBUGFAIL);
    exit(EXIT_SUCCESS);
  }

  // Go back to start of file
  fseek(input, 0, SEEK_SET);

  // print the source program to the final output
  readData_only_for_output(input, screenOutput);

  // go back to start of file
  fseek(input, 0, SEEK_SET);

  // read the file and check with the token array
  // and print lexeme table to its own output
  readData_lexeme_table(all_array, input);

  // Create an output file for the lexeme list
  FILE *output = fopen("lexemeList.txt", "w");

  // print the lexeme list to both its own output and final output (if selected)
  printdata(all_array, output, screenOutput);

  // close lexeme list output
  fclose(output);

  // free arrays
  all_array = destroy(all_array);
}
