//headers
#include <aspell.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


//types
typdef char* string;
typdef struct string_builder{
    char value;
    string_builder* next;
} string_builder;


//function stubs
static void signalHandler(int);
size_t getWord(string*);
size_t getLine(string*);
int checkWord(string, size_t);
size_t unravelBuilder(string_builder, string*);
void parseCliWord(string);
int printError(string);
int printCorrect(string);


//Macros
#define HELP_MESSAGE ""

#define START_CLI			\
    for(int argnum = 0;i<argc;i++){		\
	if(argv[argnum][0]=='-'){	\
	    switch(argv[argnum][1]){	

#define CHAR_ARG(character,action)	\
    case character:			\
	action				\
	break

#define END_CLI_ARGS }}}
