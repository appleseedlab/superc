#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__g_0", "g");
__static_renaming("__i_1", "i");
__static_renaming("__h_2", "h");
__static_renaming("__main_3", "main");


};

int  __main_3 (void  ) {

{



const const float  __g_0;

const const const const const float  __i_1;

volatile volatile volatile volatile int  __h_2;

return 0 ;// L5
}



}

