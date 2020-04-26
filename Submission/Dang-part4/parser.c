/***************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 4
Prompt: see main.c
****************************************/

/****************************************************************
File: parser.c
--------------
This file implements the interface given in parser.h.
****************************************************************/
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

/****************************************************************
Private Data member(s)
----------------------
* token: "String" variable containing the token as the parser runs
****************************************************************/
static char token[20]; 

/****************************************************************
Function: createNode(char data[20])
-----------------------------------
Private function for creating an cell pointer with the given data 
contents.
***************************************************************/
static CellList createNode(char data[20]) {
    CellList node = (CellList) malloc(sizeof(struct node));

   	if (node == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 

    char tmp[20] = "";
    strcpy(tmp, data);
    strcpy(node->data, tmp);  
    node->first = NULL;
    node->rest = NULL;

    return node;
}

/****************************************************************
Function: createConsCellNode(char data[20])
-------------------------------------------
See header file, parser.h, for documentation.
***************************************************************/
CellList createConsCellNode() {
    CellList node = createNode("");
    return node;
}

/****************************************************************
Function: createSymbolNode(char data[20])
-----------------------------------------
See header file, parser.h, for documentation.
***************************************************************/
CellList createSymbolNode(char data[20]) {
    CellList node = createNode(data);
    return node;
}

/****************************************************************
Function: S_Expression_recursive_descent(int level)
---------------------------------------------------
Private helper function that parse the given scheme input and print
the parse tree in the indented form with a given level. The function
returns a pointer to the node which is supposed to be the head of 
the list.
****************************************************************/
static CellList S_Expression_recursive_descent(int level) {
	CellList local, tmp;
	if (strcmp(token, "(") == 0) {
		strcpy(token, getToken());
		local = createConsCellNode();
		local->first = S_Expression_recursive_descent(level + 1);
		tmp = local;
		while (strcmp(token, ")") != 0) {
			tmp->rest = createConsCellNode();
			tmp = tmp->rest;
			tmp->first = S_Expression_recursive_descent(level + 1);
		}
		tmp->rest = NULL;
		if (level != 0)
			strcpy(token, getToken());
	}
	// handling the quote symbol "'"
	else if (strcmp(token, "\'") == 0) {
		strcpy(token, getToken());
		// create cons-cell note for "quote"
		local = createConsCellNode();
		local->first = createSymbolNode("quote");
		tmp = local;
		tmp->rest = createConsCellNode();
		tmp = tmp->rest;
		tmp->first = S_Expression_recursive_descent(level);
		tmp->rest = NULL;
	}
	// base case
	else {
		local = createSymbolNode(token);
		if (level != 0)
			strcpy(token, getToken());
	}
	return local;
}

/****************************************************************
Function: printList(Node *n)
----------------------------
Private function that print the ons-cell structure back out so that 
the list looked like what is put in.
****************************************************************/
static void printList(CellList n) {
	if (n == NULL)
		return;
	// when n is a cons-cell node
	if (strcmp(n->data, "") == 0) {
		printf("(");
		while (n != NULL) {
			// separate the elements with a space
			// when there are still more to print
			if (n->rest != NULL) {
				printList(n->first);
				if (strcmp(n->first->data, "()") != 0)
					printf(" ");
			}
			// no need for a space
			// when there is no more element to print
			else
				printList(n->first);
			n = n->rest;
		}
		printf(")");
	}
	// when n is a symbol node
	else
		printf("%s", n->data);
}

/****************************************************************
Function: freeCell(Node *n)
---------------------------
See header file, parser.h, for documentation
****************************************************************/
void freeList(CellList n) {
	if (n == NULL)
		return;
	// when n is a cons-cell node
	if (strcmp(n->data, "") == 0) {
		while (n != NULL) {
			freeList(n->first);
			CellList tmp = n;
			n = n->rest;
			tmp->rest = NULL;
			tmp->first = NULL;
			free(tmp);
		}
	}
	// when n is a symbol node
	else
		free(n);
}

/****************************************************************
Function: S_Expression() 
------------------------
See header file, parser.h, for documentation
****************************************************************/
void S_Expression(int flag) {

	// initialise sharpF and sharpT
	sharpF = createSymbolNode("()");
	sharpT = createSymbolNode("#t");

	// initialise global environment if called for first time
	if (flag == 1)
		globalEnv = createSymbolNode("()");

	// start evaluating
	startTokens(20);
	strcpy(token, getToken());
	CellList list = S_Expression_recursive_descent(0);
	printList(eval(list, globalEnv));

	// garbage collector
	// TEMPORARYLY OUT OF ORDER
	// if (strcmp(list->first->data, "define") != 0) {
	// 	// printf("here\n");
	// 	printList(eval(list, globalEnv));
	// 	// freeList(list);
	// }
	// else {
	// 	printList(eval(list, globalEnv));
	// }

	/* NOTE: freeList() does not manage to reclaim all allocated 
	memory for some reasons that are yet to be determined. Valgrind
	said some of the memory from createSymbolNode() was not reclaimed.
	Also, for part 4 and beyond, freeList() should be called with caution
	when user-defined vars/functions are available. */

	free(sharpF);
	free(sharpT);
}
