#include <aspell.h>
#include <stdio.h>
int main(){
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
