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

//Macros
#define START_CLI			\
    for(int i = 0;i<argc;i++){		\
	if(argv[0]=='-'){	\
	    for(size_t i = 1;argv[i]!=0){\
		switch(argv[1]){	
#define CHAR_ARG(character,action)	\
    case character:			\
	action				\
	break
#define END_CHAR_ARGS }}}}

#define END_CLI_ARGS
