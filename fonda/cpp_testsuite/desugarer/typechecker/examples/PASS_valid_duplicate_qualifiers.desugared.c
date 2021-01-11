#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__g_1", "g");
__static_renaming("__i_2", "i");
__static_renaming("__h_3", "h");


};

int  __main_0 (void  ) {
{
const const float  __g_1;
const const const const const float  __i_2;
volatile volatile volatile volatile int  __h_3;
return 0 ;

}


}

