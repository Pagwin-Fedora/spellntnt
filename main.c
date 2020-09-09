#include <aspell.h>
int main(){
    //Setting up some configuration
    AspellConfig *spell_config = new_aspell_config();
    aspell_config_replace(spell_config,"lang", "en_US");

}
