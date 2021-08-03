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



static const int  __a_0;// L2

extern const char  __b_1;// L3

auto const float  __c_2;// L4

auto volatile double  __d_3;// L5

const volatile long  __e_4;// L6

static volatile long long  __f_5;// L7

extern volatile long double  __g_6;// L8

register const float  __h_7;// L9

register volatile int  __i_8;// L10

}



}

