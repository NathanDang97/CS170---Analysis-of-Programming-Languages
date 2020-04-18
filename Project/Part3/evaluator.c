/***************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 3
Prompt: see main.c
****************************************/

/****************************************************************
File: evaluator.c
-----------------
This file implements the interface given in parser.h.
****************************************************************/
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

/****************************************************************
Function: quote() 
-----------------
Private function that evaluates quote.
****************************************************************/
static CellList quote(CellList source) {
	return source;
}

/****************************************************************
Function: car() 
---------------
Private function that evaluates car. If cannot get the "car" of
the list, the function will return NULL.
****************************************************************/
static CellList car(CellList source) {
	return source->first;
}

/****************************************************************
Function: cdr() 
---------------
Private function that evaluates cdr. If the rest (i.e. everything
except the first element) is empty, the function will return the
empty list.
****************************************************************/
static CellList cdr(CellList source) {
	if (source->rest == NULL)
		return sharpF;
	return source->rest;
}

/****************************************************************
Function: isSymbol() 
--------------------
Private function that checks if the given input is a symbol or not.
****************************************************************/
static CellList isSymbol(CellList source) {
	// #t and #f doesn't count as a symbol
	if (strcmp(source->data, "") == 0 || (strcmp(source->data, "#f") == 0) || (strcmp(source->data, "#t") == 0))
		return sharpF;
	return sharpT;
}

/****************************************************************
Function: cons() 
----------------
Private function that evaluates cons.
****************************************************************/
static CellList cons(CellList first, CellList second) {
	CellList newList = createConsCellNode();
	// if the second list is empty
	if (strcmp(second->data, "#f") == 0 || strcmp(second->data, "()") == 0) {
		// if both lists are empty
		if (strcmp(first->data, "#f") == 0 || strcmp(first->data, "()") == 0) {
			newList->first = sharpF;
			newList->rest = sharpF;
			return newList;
		}
		newList->first = first;
		return newList;
	}
	// if none of the lists are empty
	newList->first = first;
	newList->rest = second;
	return newList;
}

/****************************************************************
Function: eval() 
----------------
See header file, evaluator.h, for documentation.
****************************************************************/
CellList eval(CellList list) {
	// base case
	if (car(list) == NULL)
		return list;

	// recursive evaluation
	else {
		// get the function prompt
		char symbol[20];
		strcpy(symbol, car(list)->data);

		// check for exit prompt
		if (strcmp(symbol, "exit") == 0) {
			printf("Have a nice day!\n\n");
			exit(0);
		}

		// getting the arguments for the functions
		CellList argument1 = car(cdr(list));
		CellList argument2 = car(cdr(cdr(list)));

		// eval quote
		if (strcmp(symbol, "quote") == 0)
			return quote(eval(argument1));
		// eval car
		else if (strcmp(symbol, "car") == 0)
			return car(eval(argument1));
		// eval cdr
		else if (strcmp(symbol, "cdr") == 0)
			return cdr(eval(argument1));
		// eval symbol?
		else if (strcmp(symbol, "symbol?") == 0)
			return isSymbol(eval(argument1));
		// eval cons
		else if (strcmp(symbol, "cons") == 0)
			return cons(eval(argument1), eval(argument2));
		else // if function is not yet defined
			return list;
	}
}