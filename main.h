//headers
#include <aspell.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


//types
typedef char* string;
typedef struct string_builder{
    int value;
    struct string_builder* next;
} string_builder;


//function stubs
static void signalHandler(int);
size_t getWord(string*);
size_t getLine(string*);
int checkWord(string, size_t);
size_t unravelBuilder(string_builder*, string*);
void parseCliWord(string);
int printError(string);
int printCorrect(string);
char minorParse(char);

//Macros
#define HELP_MESSAGE "--output=[FILE]\t\t\tspecifies the output file(stdout by default)\n--input=[FILE]\t\t\tspecifies the input file(stdin by default)\n--encoding=[ENCODING STRING]\tspecifies the encoding to be used(UTF-8 by default)\n--lang=[LANG STRING]\t\tspecifies the language to he used(en_US by default)\n"
#define USAGE_MESSAGE "spellntnt [OPTIONS]"

#define START_CLI			\
    for(int argnum = 0;argnum<argc;argnum++){		\
	if(argv[argnum][0]=='-'){	\
	    for(int argindex = 0;argv[argnum][argindex]!=0;argindex++){\
		switch(argv[argnum][argindex]){	

#define CHAR_ARG(character,action)	\
    case character:			\
	action;				\
	break

#define END_CLI_ARGS }}}}
