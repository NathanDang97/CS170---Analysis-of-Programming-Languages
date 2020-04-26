/***************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 4
Prompt: see main.c
****************************************/

/****************************************************************
File: evaluator.h
----------------
This is the interface for a parser for part of Scheme.
It has an operation for parsing a S_Expression of the Scheme
language.
****************************************************************/
#ifndef EVALUATOR
#define EVALUATOR

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/****************************************************************
Data member(s)
--------------
* globalEnv: the environment storing the user-defined variables
and functions. The lifetime of this environment will last until
the point when the program is forced to terminate (i.e. when the
users call (exit))
***************************************************************/
CellList globalEnv; // global environment

/****************************************************************
Function: eval() 
----------------
The function that evaluates the given scheme expression.
****************************************************************/
CellList eval(CellList list, CellList environment);

#endif