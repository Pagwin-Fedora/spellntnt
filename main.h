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
    char value;
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
#define HELP_MESSAGE "--correct=[FILE]\tspecifies the file all the correct words should be written too(stdout by default)\n--incorrect=[FILE]\tspecifies the file all the incorrect words should be written too(stderr by default)\n--input=[FILE]\tspecifies the file that the program should read from to parse correct and incorrect words(stdin by default)\n--encoding=[ENCODING STRING]\tspecifies the encoding to be used(UTF-8 by default)\n--lang=[LANG STRING]\tspecifies the language to he used(en_US by default)\n\n-o\tredirects errors to stdout instead of stderr\n-e\tredirects correct spellings to stderr instead of stdout\n-r\tenables reparsing which splits every word into it's own line, removes coloring and prefixes the correct words with [C] and the erroneous words with [E]"
#define USAGE_MESSAGE "spellntnt -[oer] --correct=[FILE] --incorrect=[FILE] --input=[FILE] --encoding=[ENCODING STRING] --lang=[LANG STRING]"

#define START_CLI			\
    for(int argnum = 0;argnum<argc;argnum++){		\
	if(argv[argnum][0]=='-'){	\
	    switch(argv[argnum][1]){	

#define CHAR_ARG(character,action)	\
    case character:			\
	action;				\
	break

#define END_CLI_ARGS }}}
