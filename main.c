#include "main.h"
AspellConfig* spell_config;
int main(int argc, char* argv[]){
    //setup signal handler
    signal(SIGINT,signalHandler);

    //Setting up some configuration
    spell_config = new_aspell_config();
    aspell_config_replace(spell_config, "lang", "en_US");
    aspell_config_replace(spell_config, "encoding", "UTF-8");

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
	system("Color 06");
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
