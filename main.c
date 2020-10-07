#include <aspell.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int main(int argc, char* argv[]){
    //setup signal handler
    signal(SIGINT,sighandler);

    //Setting up some configuration
    AspellConfig *spell_config = new_aspell_config();
    aspell_config_replace(spell_config, "lang", "en_US");
    aspell_config_replace(spell_config, "encoding", "UTF-8");

    //Creating an instance of the actual speller
    AspellCanHaveError *possible_err = new_aspell_speller(spell_config);
    AspellSpeller *spell_checker  = 0;
    if (aspell_error_number(possible_err) !=0)
	puts(aspell_error_message(possible_err));
    else
	spell_checker = to_aspell_speller(possible_err);


}
static void sighandler(int signal){
    //lol no reason to do anything special with any signals but I felt like adding this anyways
    if(signal == SIGINT) exit();
}
