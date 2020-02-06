/****************************************************************
 File: main.c
 ------------
 A main program to demonstrate the Stack ADT.
 It reads the input from a text file and prints the states
 of the stack in an interpreter-like way.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main(void) { 
	Stack stack = createStack();
	char in; // variable to store character in the input file
	/* idea: print the command on one line, then print the corresponding state
		of the stack on the next line */
	while (in != 'q') {
		in = getchar();
		// if prompted to insert
		if (in == 'i') {
			int data = getchar() - '0';
			printf("(i)nsert#, (p)op, (q)uit: %c%d", in, data);
			printf("\n");
			push(stack, data);
			printStack(stack);
		}
		// if prompted to pop
		else if (in == 'p') {
			printf("(i)nsert#, (p)op, (q)uit: %c", in);
			printf("\n");
			if (isEmpty(stack))
				printf("pop from empty stack failed.\n");
			else {
				int data = pop(stack);
				if (isEmpty(stack))
					printf("Empty stack.\n");
				else
					printStack(stack);
			}
		}
		// if prompted to quit
		else if (in == 'q') {
			printf("(i)nsert#, (p)op, (q)uit: %c", in);
			printf("\n");
		}
	}

	// clean up
	deleteStack(stack);

	return 0;
}