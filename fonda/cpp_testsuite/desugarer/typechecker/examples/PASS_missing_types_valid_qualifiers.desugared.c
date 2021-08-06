#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__d_3", "d");
__static_renaming("__e_4", "e");
__static_renaming("__f_5", "f");
__static_renaming("__g_6", "g");
__static_renaming("__h_7", "h");
__static_renaming("__i_8", "i");
__static_renaming("__main_9", "main");


};

int  __main_9 (void  ) {

{
{



static const int  __a_0;// L3

extern const int  __b_1;// L4

auto const int  __c_2;// L5

auto volatile int  __d_3;// L6

const volatile int  __e_4;// L7

static volatile int  __f_5;// L8

extern volatile int  __g_6;// L9

register const int  __h_7;// L10

register volatile int  __i_8;// L11

return 0 ;// L12
}
}



}

