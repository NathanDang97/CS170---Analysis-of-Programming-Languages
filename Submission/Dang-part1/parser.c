/****************************************************************
File: parser.c
-------------
This file implements the interface given in parser.h.
****************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"

/****************************************************************
Function: indent()
--------------------
Private function that provides indentation for a given level of 
the parse tree. 
****************************************************************/
static void indent(int level) {
	for (int i = 0; i < level; ++i)
        printf("   ");
}

/****************************************************************
Function: S_Expression_recursive_descent()
--------------------
Private helper function that parse the given scheme input and print
the parse tree in the indented form with a given level.
****************************************************************/
static void S_Expression_recursive_descent(int level) {
	indent(level);
	printf("S_Expression\n");
	if (strcmp(token, "(") == 0) {
		indent(level);
		printf("(\n");
		strcpy(token, getToken());
		S_Expression_recursive_descent(level + 1);
		while (strcmp(token, ")") != 0)
			S_Expression_recursive_descent(level + 1);
		indent(level);
		printf(")\n");
		if (level != 0)
			strcpy(token, getToken());
	}
	else {
		indent(level + 1);
		printf("%s \n", token);
		if (level != 0)
			strcpy(token, getToken());
	}
}

/****************************************************************
Function: S_Expression() 
--------------------
See header file for documentation
****************************************************************/
void S_Expression() {
	strcpy(token, getToken());
	S_Expression_recursive_descent(0);
}