#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__myFirstArr_1", "myFirstArr");
__static_renaming("__myFirstArr_2", "myFirstArr");
__static_renaming("__expressionArr_3", "expressionArr");
__static_renaming("__string_4", "string");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_6", "A");
__static_condition_renaming("__static_condition_default_7", "!A");

};

int  __main_5 (void  ) {

{
{



int  __x_0= 5;// L2

int  (__myFirstArr_1[3]);// L5

char  (__myFirstArr_2[3]);// L7

int  (__expressionArr_3[2 + 8]);// L10

char  (__string_4[2]);// L11

if (1) {
__static_type_error("invalid declaration of variableLength under this presence condition");
}

if (__static_condition_default_6) {
 __myFirstArr_1  [ 1 ] = 7 ; // L15
}
if (__static_condition_default_7) {
 __myFirstArr_2  [ 1 ] = 7 ; // L15
}
if (__static_condition_default_6) {
 __myFirstArr_1  [  __x_0  ] = 3 ; // L17
}
if (__static_condition_default_7) {
 __myFirstArr_2  [  __x_0  ] = 3 ; // L17
}
return 0 ;// L19
}
}



}

