/*****************************************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 3
Prompt: The goal of this assignment is to implement the basic 
functions such as quote, car, cdr, cons, and symbol?.
*****************************************************************/

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

int main() {
 
 	// program prompt
	printf("\n");
	printf("A prototype evaluator for Scheme.\n");
	printf("Type any Scheme expression using quote,\n");
	printf("car, cdr, cons, and symbol?.\n");
	printf("If the users type any undefined function,\n");
	printf("the same expression will be printed for now.\n");
	printf("The function call (exit) to quit.\n");

	// infinite loop to run the interpreter until prompted to exit
	while (1) {
    	printf("\nscheme>");
    	S_Expression();
    	printf("\n");
 	}
 	
 	return 0;
}