/***************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 5
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
Function: isList() 
------------------
Private function that checks if the given input is a list or not.
****************************************************************/
static CellList isList(CellList source) {
	// given source is list if it's not a symbol
	if (isSymbol(source) == sharpF)
		return sharpT;
	return sharpF;
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
Function: last() 
------------------
Private function that returns the last element of the list.
****************************************************************/
static CellList last(CellList source) {
	// if source is NULL or a symbol, return ()
	if (isNull(source) == sharpT || isSymbol(source) == sharpT)
		return sharpF;
	// if reach the end, return that element
	if (cdr(source) == sharpF)
		return car(source);
	// recursive call
	return last(cdr(source));
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
Function: makeList() 
--------------------
Private helper function that takes any number of arguments and 
returns a list of them in a reversed order.
****************************************************************/
static CellList makeList(CellList list, CellList args, CellList environment) {
	// "consing" each element to the list, one by one
	list = cons(eval(car(args), environment), list);
	if(cdr(args) != sharpF)
		return makeList(list, cdr(args), environment);
	// result will be reversed
	return list;
}

/****************************************************************
Function: finalList() 
---------------------
Private function that takes any number of arguments and returns a 
list of them. This function takes the output of the makeList()
function, which is a list in reversed order, and reverses it to
get the final result.
****************************************************************/
static CellList finalList(CellList source, CellList environment) {
	CellList reversed = makeList(createSymbolNode("()"), source, environment);
	CellList result = createSymbolNode("()");
	// "un-reverse" the list to get the final result
	while (reversed != sharpF) {
		result = cons(car(reversed), result);
		reversed = cdr(reversed);
	}
	return result;
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
Function: isFunction() 
----------------------
Private function that checks if the given input is a funciton or 
not. This method is not standard Scheme but shows to be useful
during the debugging process.
****************************************************************/
static CellList isFunction(CellList source) {
	// filter out regular symbols/built-in fuctions' names
	if (car(source) != NULL) {
		// check for structure of user defined function
		if (isList(car(cdr(source))) == sharpT)
			return sharpT;
		return sharpF;
	}
	return sharpF;
}

/****************************************************************
Function: cond() 
----------------
Private function that evaluates conditional statements.
****************************************************************/
static CellList cond(CellList source, CellList environment) {
	// evaluate the current condition
	CellList condResult = eval(car(car(source)), environment);
	// if true or reach default case, evaluate the outcome
	if (strcmp(condResult->data, "#t") == 0 || strcmp(condResult->data, "else") == 0)
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
	// add the pair to the global environment
	globalEnv = cons(pair, globalEnv);
	return symbol;
}

/****************************************************************
Function: addUserDefFunc() 
--------------------------
Private function that "conses" the user-defined function to the
global envinronment.
****************************************************************/
static CellList addUserDefFunc(CellList source) {
	// extract the function name
	CellList symbol = car(car(cdr(source)));
	// create the function name - definition pair
	CellList pair = cons(symbol, cons(source, createSymbolNode("()")));
	// add the pair to the global environment
	globalEnv = cons(pair, globalEnv);
	return symbol;
}

/****************************************************************
Function: bindingVars() 
-----------------------
Private helper function that binds variables to the parameters of
a user defined function.
****************************************************************/
static CellList bindingVars(CellList args, CellList params, CellList environment) {
	// evaluate the argument
	CellList evaluated = eval(car(args), environment);
	// bind the argument with the corresponding parameter
	CellList binded = cons(car(params), cons(evaluated, createSymbolNode("()")));
	// add the binded arg-param to the local environment
	environment = cons(binded, environment);
	// repeat the process if there are more params/args
	if (cdr(params) != sharpF)
		return bindingVars(cdr(args), cdr(params), environment);
	return environment;
}

/****************************************************************
Function: evalUserDefFunc() 
-----------------------
Private function that evaluates a given user defined function. 
****************************************************************/
static CellList evalUserDefFunc(CellList source, CellList environment) {
	// extract the function's definition
	CellList funcDef = car(cdr(assoc(car(source), environment)));
	// get the argument(s)
	CellList arguments = cdr(source);
	// get the parameter(s)
	CellList parameters = cdr(car(cdr(funcDef)));
	// bind arguments to coressponding parameters in local environment
	environment = bindingVars(arguments, parameters, environment);
	// extract the form of the function
	CellList funcForm = car(cdr(cdr(funcDef)));
	return eval(funcForm, environment);
}

/****************************************************************
Function: eval() 
----------------
See header file, evaluator.h, for documentation.
****************************************************************/
CellList eval(CellList list, CellList environment) {
	// base case
	if (car(list) == NULL) {
		if (assoc(list, environment) != sharpF)
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
			// if the in put is (define (member l1 l2) (...))
			// the it is a user defined function
			if (isList(car(cdr(list))) == sharpT)
				return addUserDefFunc(list);
			// else, it's a user defined symbol
			// i.e. (define l1 (quote(a b c)))
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
		// eval last
		else if (strcmp(symbol, "last") == 0)
			return last(eval(argument1, environment));
		// eval list
		else if (strcmp(symbol, "list") == 0)
			return finalList(cdr(list), environment);
		// eval symbol?
		else if (strcmp(symbol, "symbol?") == 0)
			return isSymbol(eval(argument1, environment));
		// eval list?
		else if (strcmp(symbol, "list?") == 0)
			return isList(eval(argument1, environment));
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
		// eval function?
		// mainly for debugging purpose
		else if (strcmp(symbol, "function?") == 0)
			return isFunction(eval(argument1, environment));
		// eval special (environment) method
		// which will show the environment
		// for debugging purpose
		else if(strcmp(symbol, "environment") == 0)
			return environment;
		// eval user-defined function
		else if (assoc(car(list), environment) != sharpF)
			return evalUserDefFunc(list, environment);
		else // if function is not yet defined
			return list;
	}
}