#include "main.h"
AspellConfig* spell_config;
FILE* correct = stdout;
FILE* errors = stderr;
FILE* input = stdin;
string lang = "en_US";
string encoding = "UTF-8"
int main(int argc, char* argv[]){
    //parse cli args
    START_CLI
	CHAR_ARG('-', parseCliWord(argv[argnum][2]));
	CHAR_ARG('o', errors=stdout);
	CHAR_ARG('e', correct=stderr);
    END_CLI_ARGS
    
    //setup signal handler
    signal(SIGINT,signalHandler);
    //Setting up some configuration
    spell_config = new_aspell_config();
    aspell_config_replace(spell_config, "lang", lang);
    aspell_config_replace(spell_config, "encoding", encoding);

    //Creating an instance of the actual speller
    AspellCanHaveError *possible_err = new_aspell_speller(spell_config);
    AspellSpeller *spell_checker  = 0;
    if (aspell_error_number(possible_err) !=0)
	puts(aspell_error_message(possible_err));
    else
	spell_checker = to_aspell_speller(possible_err);
    string word;
    size_t word_size;
    if()
    while(word_size){
    }

}
static void signalHandler(int signal){
    //lol no reason to do anything special with any signals but I felt like adding this anyways
    if(signal == SIGINT) exit();
    else exit();
}
size_t getWord(string* loc){
    string_builder first;
    string_builder* current_link = &first;
    for(char current_char = getchar();!isspace(current);current = getchar()){
	current->value = current_char;
	current->next = malloc(sizeof(string_builder));
    }
    free(current->next);
    current->next = NULL;
    return unravelBuilder(first,loc);
}
size_t getLine(string* loc){
    string_builder* first = malloc(sizeof(string_builder));
    string_builder* current_link = first;
    for(char current_char = getchar();current_char != '\n';current = getchar()){
	current->value = current_char;
	current->next = malloc(sizeof(string_builder));
    }
    free(current->next);
    current->next = NULL;
    return unravelBuilder(first,loc);
}
size_t unravelBuilder(string_builder* start, string* output){
    size_t size = 0;
    string_builder* current = start;
    while(current){
	size++;
	current = current->next;
    }
    current = start;
    *output = malloc(size);
    for(size_t i = 0;i<size;i++){
	(*output)[i] = current->value;
	free(current);
    }
    return size;
}
// function that processes arguments
void parseCliWord(string arg){
    if(*arg == 0 || arg == NULL)
	return;
    if(!memcmp(arg, "correct=",8)){
	if(strlen(arg)>8){
	    correct = fopen(arg+8);
	}
    }
    if(!memcmp(arg, "incorrect=",10)){
	if(strlen(arg)>10){
	    
	}
	else{
	    fprintf(stderr,"no filename provided for spellntnt to write incorrect words too");
	}
    }
    if(!memcmp(arg, "help",4)){
	printf("%s",HELP_MESSAGE);
	exit(0);
    }
    if(!memcmp(arg, "encoding=",9)){
	if(strlen(arg)>9){
	    encoding = arg+9;
	}
    }
    if(!memcmp(arg, "lang=",5)){
	if(strlen(arg)>5){
	    lang = arg+5;
	}
    }
}
int printError(string){
    fprintf(errors,"\033[0;31m%s\033[0m",string);
}
int printCorrect(string){
    fprintf(correct,"\033[0;32m%s\033[0m",string);
}
