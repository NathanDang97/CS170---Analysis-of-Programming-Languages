/*****************************************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 2
Prompt: The goal of this assignment is to begin the semantic analysis 
function of your interpreter. The first step is to represent the lists 
internally via a tree structure. Once this is done, it is easy to implement 
basic functions quote, car, cdr, cons, and symbol?, as will be done in 
the next assignment. 
*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h" 

int main() {
 
	printf("\n");
	printf("A parser for a subset of Scheme.\n");
	printf("Type any Scheme expression and its\n");
	printf("internal structure will be printed out\n");
	printf("which is the same expression for now.\n");
	printf("Type Ctrl-c to quit.\n");

	while (1) {
    	printf("\nscheme>");
    	S_Expression();
    	printf("\n");
 	}

 	return 0;
}