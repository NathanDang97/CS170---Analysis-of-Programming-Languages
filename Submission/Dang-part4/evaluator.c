/***************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 4
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
Function: isNull() 
------------------
Private function that checks if the given list is null or not.
****************************************************************/
static CellList isNull(CellList source) {
	if (source == NULL)
		return sharpT;
	if (strcmp(source->data, "#f") == 0 || strcmp(source->data, "()") == 0) {
		return sharpT;
	}
	return sharpF;
}

/****************************************************************
Function: isEqual() 
-------------------
Private function that checks if the given two lists are equal to
each other or not.
****************************************************************/
static CellList isEqual(CellList first, CellList second) {
	// base case
	// if reach here, then two symbols are equal
	if (isNull(first) == sharpT && isNull(second) == sharpT)
		return sharpT;
	// return #f if any two symbols are not equal
	if (strcmp(first->data, second->data) != 0)
		return sharpF;

	// recursive call
	if (isEqual(car(first), car(second)) == sharpT) {
		if (isEqual(cdr(first), cdr(second)) == sharpT)
			return sharpT;
		else
			return sharpF;
	}
	else
		return sharpF;
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
Function: assoc() 
-----------------
Private function that evaluates assoc.
****************************************************************/
static CellList assoc(CellList symbol, CellList source) {
	// base case
	// if reach here, then no match
	if (isNull(source) == sharpT)
		return sharpF;
	// if it's a hit, return the pair
	if (strcmp(symbol->data, source->first->first->data) == 0)
		return source->first;

	// recursive call
	return assoc(symbol, cdr(source));
}


/****************************************************************
Function: append() 
------------------
Private function that appends two given lists.
****************************************************************/
static CellList append(CellList first, CellList second) {
	if (isNull(first) == sharpT)
		return second;
	return cons(car(first), append(cdr(first), second));
}

/****************************************************************
Function: cond() 
----------------
Private function that evaluates conditional statements.
****************************************************************/
static CellList cond(CellList source, CellList environment) {
	// evaluate the current condition
	CellList condResult = eval(car(car(source)), environment);
	// if true evaluate the outcome
	if (strcmp(condResult->data, "#t") == 0)
		return eval(car(cdr(car(source))), environment);
	// if not, move on to next condition
	return cond(cdr(source), environment);
}

/****************************************************************
Function: addUserDefVar() 
-------------------------
Private function that "conses" the user-defined variable to the
global envinronment.
****************************************************************/
static CellList addUserDefVar(CellList source) {
	// extract the symbol and the value
	CellList symbol = car(cdr(source));
	CellList value = car(cdr(cdr(source)));
	// evaluate the value
	CellList evaluatedValue = eval(value, globalEnv);
	// create the pair
	CellList pair = cons(symbol, cons(evaluatedValue, createSymbolNode("()")));
	// add the pair to the environment
	globalEnv = cons(pair, globalEnv);
	return symbol;
}

/****************************************************************
Function: eval() 
----------------
See header file, evaluator.h, for documentation.
****************************************************************/
CellList eval(CellList list, CellList environment) {
	// base case
	if (car(list) == NULL) {
		if (car(assoc(list, environment)) != NULL)
			return car(cdr(assoc(list, environment)));
		return list;
	}

	// recursive evaluation
	else {
		// get the function prompt
		char symbol[20];
		strcpy(symbol, car(list)->data);

		// check for exit prompt
		if (strcmp(symbol, "exit") == 0) {
			printf("Have a nice day!\n\n");
			freeList(globalEnv);
			free(sharpF);
			free(sharpT);
			exit(0);
		}

		// check for user-defined var
		if (strcmp(symbol, "define") == 0) {
			return addUserDefVar(list);
		}

		// getting the arguments for the functions
		CellList argument1 = car(cdr(list));
		CellList argument2 = car(cdr(cdr(list)));

		// eval quote
		if (strcmp(symbol, "quote") == 0)
			return quote(eval(argument1, environment));
		// eval car
		else if (strcmp(symbol, "car") == 0)
			return car(eval(argument1, environment));
		// eval cdr
		else if (strcmp(symbol, "cdr") == 0)
			return cdr(eval(argument1, environment));
		// eval symbol?
		else if (strcmp(symbol, "symbol?") == 0)
			return isSymbol(eval(argument1, environment));
		// eval cons
		else if (strcmp(symbol, "cons") == 0)
			return cons(eval(argument1, environment), eval(argument2, environment));
		// eval null?
		else if (strcmp(symbol, "null?") == 0)
			return isNull(eval(argument1, environment));
		// eval equal?
		else if (strcmp(symbol, "equal?") == 0)
			return isEqual(eval(argument1, environment), eval(argument2, environment));
		// eval assoc
		else if (strcmp(symbol, "assoc") == 0)
			return assoc(eval(argument1, environment), eval(argument2, environment));
		// eval append
		else if (strcmp(symbol, "append") == 0) 
			return append(eval(argument1, environment), eval(argument2, environment));
		// eval cond
		else if (strcmp(symbol, "cond") == 0)
			return cond(cdr(list), environment);
		else // if function is not yet defined
			return list;
	}
}