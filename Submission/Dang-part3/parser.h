/***************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 3
Prompt: see main.c
****************************************/

/****************************************************************
File: parser.h
----------------
This is the interface for a parser for part of Scheme.
It has an operation for parsing a S_Expression of the Scheme
language.
****************************************************************/
#ifndef PARSER
#define PARSER

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/****************************************************************
Data member(s)
--------------
* struct node: a structure of a cons-cell node containing 3 members:
	- data: a string containing the data of the note
	- first: a pointer for the car of the list
	- rest: a pointer for the cdr of the list
* The CellList ADT is a pointer to a struct of "node" type.
* sharpF, sharpT: 2 symbol nodes representing #f and #t respectively.

NOTE: there are two types of nodes, cons-cell and symbol node,
and it is possible to implement a different structure for symbols
nodes but for simplicity, the same node strucure is used for both 
types. With that being said, if the node is a symbol node, then
first and rest pointers are NULL, and if the node is a cons-cell,
then the data string is ignored.
***************************************************************/
struct node {
    char data[20];
    struct node *first;
    struct node *rest;
};
typedef struct node *CellList;

CellList sharpF;
CellList sharpT;

/****************************************************************
Function: createConsCellNode(char data[20])
--------------------
The function that creates the cons-cell node. the data string 
is left as "" meaning that the data content of the note is ignored 
as stated. 
***************************************************************/
CellList createConsCellNode();

/****************************************************************
Function: createSymbolNode(char data[20])
--------------------
The function that creates the symbol node. First and rest pointers
are left as NULL as stated.
***************************************************************/
CellList createSymbolNode(char data[20]);

/****************************************************************
Function: S_Expression() 
--------------------
The function that parse the given S_expression scheme input.
****************************************************************/
void S_Expression();

#endif