/***************************************
Author: Nathan Dang
CS170 - Analysis of Programming Language
Project - Part 3
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
Function: eval() 
----------------
The function that evaluates the given scheme expression.
****************************************************************/
CellList eval(CellList list);

#endif