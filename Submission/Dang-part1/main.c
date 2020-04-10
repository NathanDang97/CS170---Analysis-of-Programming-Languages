#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h" 

int main() {
	startTokens(20);
 
	printf("\n");
	printf("A parser for a subset of Scheme.\n");
	printf("Type any Scheme expression and its\n");
	printf("\"parse tree\" will be printed out.\n");
	printf("Type Ctrl-c to quit.\n");

	while (1) {
    	printf("\nscheme>");
    	S_Expression();
 	}

 	return 0;
}