/*****************************************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 5
Prompt: The goal of this assignment is to implement more basic 
functions such as assoc, append, null?, and cond. Also, it is
required that the users can define their own variables and functions.

CAUTION: this is just a prototype version of the interpreter, thus,
there is no guarantee that the program will behave perfectly upon
receiving inputs that have syntax errors.
*****************************************************************/

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

int main() {
 
 	// program prompt
	printf("\n");
	printf("*** A prototype evaluator for Scheme ***\n");
	printf("- Type any Scheme expression using quote,\n");
	printf("car, cdr, cons, append, symbol?, null?,\n");
	printf("assoc, list, list?, last, and cond.\n");
	printf("- The users can also define their own variables\n");
	printf("and functions, using the key word \'define\'.\n");
	printf("- If the users type any undefined function,\n");
	printf("the same expression will be printed for now.\n");
	printf("- The function call (exit) to quit.\n");

	int flag = 1; // set to 0 if S_Exp() is called after the first call

	// infinite loop to run the interpreter until prompted to exit
	while (1) {
    	printf("\nscheme>");
    	S_Expression(flag);
    	flag = 0; // after first call, set flag to 0
    	printf("\n");
 	}
 	
 	return 0;
}