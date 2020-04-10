/***************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 2
Prompt: see main.c
****************************************/

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
Data members
------------
* token: "String" variable containing the token as the parser runs
* struct node: a structure of a cons-cell node containing 3 members:
	- data: a string containing the data of the note
	- first: a pointer for the car of the list
	- rest: a pointer for the cdr of the list
* struct celllist: The state of the cell list is encapsulated in this 
struct, which contains a pointer to the head of the list. The CellList 
ADT is a pointer to a struct of this type.

NOTE: there are two types of nodes, cons-cell and symbol node,
and it is possible to implement a different structure for symbols
nodes but for simplicity, the same node strucure is used for both 
types. With that being said, if the node is a symbol node, then
first and rest pointers are NULL, and if the node is a cons-cell,
then the data string is ignored.
****************************************************************/
static char token[20]; 

struct node {
    char data[20];
    struct node *first;
    struct node *rest;
};
typedef struct node Node;

struct celllist {
	Node *head;
};
typedef struct celllist *CellList;

/****************************************************************
Function: createNode(char data[20])
--------------------
Private function for creating an cell pointer with the given data 
contents.
***************************************************************/
static Node *createNode(char data[20]) {
    Node *node = (Node *) malloc(sizeof(Node));

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
--------------------
The function that creates the cons-cell node. the data string 
is left as "" meaning that the data content of the note is ignored 
as stated. 
***************************************************************/
static Node *createConsCellNode() {
    Node *node = createNode("");
    return node;
}

/****************************************************************
Function: createSymbolNode(char data[20])
--------------------
The function that creates the symbol node. First and rest pointers
are left as NULL as stated.
***************************************************************/
static Node *createSymbolNode(char data[20]) {
    Node *node = createNode(data);
    return node;
}

/****************************************************************
Function: createList()
--------------------
The function that initialises the Cell List.
***************************************************************/
static CellList createList() {
	CellList cl = (CellList) malloc(sizeof(struct celllist));
	
	if (cl == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	
	cl->head = NULL;
	
	return cl;
}

/****************************************************************
Function: S_Expression_recursive_descent(int level)
--------------------
Private helper function that parse the given scheme input and print
the parse tree in the indented form with a given level. The function
returns a pointer to the node which is supposed to be the head of 
the list.
****************************************************************/
static Node *S_Expression_recursive_descent(int level) {
	Node *local, *tmp;
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
--------------------
Private function that print the ons-cell structure back out so that 
the list looked like what is put in.
****************************************************************/
static void printList(Node *n) {
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
--------------------
Private helper function that free the allocated cells
****************************************************************/
static void freeCell(Node *n) {
	if (n == NULL)
		return;
	// when n is a cons-cell node
	if (strcmp(n->data, "") == 0) {
		while (n != NULL) {
			freeCell(n->first);
			Node *tmp = n;
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
Function: freeList(Node *n)
--------------------
Private function that deallocates the list before terminating
the program.
****************************************************************/
static void freeList(CellList list) {
	freeCell(list->head);
	free(list);
}

/****************************************************************
Function: S_Expression() 
--------------------
See header file for documentation
****************************************************************/
void S_Expression() {
	startTokens(20);
	strcpy(token, getToken());
	CellList cl = createList();
	cl->head = S_Expression_recursive_descent(0);
	printList(cl->head);
	freeList(cl);
}