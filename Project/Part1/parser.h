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

/****************************************************************
Data members
------------
token:    "String" variable containing the token as the parser runs
****************************************************************/
char token[20]; 

/****************************************************************
Function: S_Expression() 
--------------------
The function that parse the given S_expression scheme input 
****************************************************************/
void S_Expression();

#endif