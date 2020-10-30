#include "main.h"
AspellConfig* spell_config;
FILE* output;
FILE* input;
bool outChanged = false;
string lang = "en_US";
string encoding = "UTF-8";
int main(int argc, char* argv[]){
    output = stdout;
    input = stdin;
    //parse cli args
    START_CLI
	CHAR_ARG('-', parseCliWord(argv[argnum]+2));
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
    if(!spell_checker)
	exit(1);

    //checking spelling of words
    string word;
    size_t word_size = getWord(&word);
    while(word_size>0){
	int correct;
	if(strcmp("ucs-2",encoding) || strcmp("ucs-4", encoding)){
	    correct = aspell_speller_check_w(spell_checker,word,word_size);
	}
	else{
	    correct = aspell_speller_check(spell_checker,word,word_size);
	}
	if(correct) printCorrect(word);
	else printError(word);
	word_size = getWord(&word);
    }

}
static void signalHandler(int signal){
    //lol no reason to do anything special with any signals but I felt like adding this anyways
    if(signal == SIGINT) exit(1);
    else exit(1);
}
size_t getWord(string* loc){
    string_builder* first = malloc(sizeof(string_builder));
    first->value = EOF;
    first->next = NULL;
    string_builder* current_link = first;
    string_builder* last = current_link;
    int current_char = fgetc(input);
    while(!isspace(current_char)&&current_char!=EOF){
	last = current_link;
	//printf("%d",!isspace(current_char));
	current_link->value = current_char;
	current_link->next = malloc(sizeof(string_builder));
	current_link = current_link->next;
	current_char = fgetc(input);
    }
    last->next = NULL;
    size_t temp =  unravelBuilder(first,loc);
    //fprintf(stderr,"%lu\n",temp);
    return temp;
}
size_t unravelBuilder(string_builder* start, string* output){
    size_t size = 0;
    bool notEOF = start->value !=EOF;
    string_builder* current = start;
    string_builder* last = current;
    while(current){
	size++;
	current = current->next;
    }
    current = start;
    *output = calloc(1,size);
    for(size_t i = 0;i<size;i++){
	(*output)[i] = current->value;
	current = current->next;
	free(last);
	last = current;
    }
    return notEOF?size:0;
}
// function that processes arguments
void parseCliWord(string arg){
    if(*arg == 0 || arg == NULL)
	return;
    if(!memcmp(arg, "output=",7)){
	outChanged = true;
	if(strlen(arg)>7){
	    output = fopen(arg+7,"w+");
	}
	else{
	    fprintf(stderr,"no filename provided to the \"correct\" cli option continuing with default(stdout)");
	}
    }
    if(!memcmp(arg, "input=",6)){
	if(strlen(arg)>6){
	    input = fopen(arg+6,"r");
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
	else{
	    fprintf(stderr,"no encoding provided to the \"encoding\" cli option continuing with default(%s)", encoding);
	}
    }
    if(!memcmp(arg, "lang=",5)){
	if(strlen(arg)>5){
	    lang = arg+5;
	}
	else{
	    fprintf(stderr,"no lang provided to the \"lang\" cli option continuing with default(%s)",lang);
	}
    }
}
int printError(string message){
    //nope we're doing this differently now
//    return fprintf(errors,"\033[0;31m%s\033[0m ",message);
    return fprintf(output,"%sError: %s%s\n",!outChanged?"\033[0;31m":"",message,!outChanged?"\033[0m":"");
}
int printCorrect(string message){
    //nope we're redoing this
//    return fprintf(correct,"\033[0;32m%s\033[0m ",message);
    return fprintf(output,"%sCorrect: %s%s\n",!outChanged?"\033[0;32m":"",message,!outChanged?"\033[0m":"");
}
