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
__static_renaming("__j_9", "j");
__static_renaming("__k_10", "k");
__static_renaming("__l_11", "l");
__static_renaming("__m_12", "m");
__static_renaming("__main_13", "main");


};

int  (__main_13) () {

{
{



int  __a_0;// L3

long  __b_1;// L4

long long  __c_2;// L5

char  __d_3;// L6

short  __e_4;// L7

float  __f_5;// L8

double  __g_6;// L9

if (1) {
__static_type_error("invalid declaration of q under this presence condition");
}

double _Complex  __h_7;// L11

long int  __i_8;// L12

long long int  __j_9;// L13

long double  __k_10;// L14

long double _Complex  __l_11;// L15

float _Complex  __m_12;// L16

if (1) {
__static_type_error("invalid declaration of x under this presence condition");
}

return 0 ;// L18
}
}


}

