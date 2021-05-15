#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__myFirstArr_1", "myFirstArr");
__static_renaming("__myFirstArr_2", "myFirstArr");
__static_renaming("__expressionArr_3", "expressionArr");
__static_renaming("__string_4", "string");
__static_renaming("__variableLength_5", "variableLength");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "A");
__static_condition_renaming("__static_condition_default_8", "!A");

};

int  __main_6 (void  ) {

{



int  __x_0= 5;

int  (__myFirstArr_1[3]);

char  (__myFirstArr_2[3]);

int  (__expressionArr_3[2 + 8]);

char  (__string_4[2]);

int  (__variableLength_5[ __x_0 ]);

if (__static_condition_default_7) {
 __myFirstArr_1  [ 1 ] = 7 ;
}
if (__static_condition_default_8) {
 __myFirstArr_2  [ 1 ] = 7 ;
}
if (__static_condition_default_7) {
 __myFirstArr_1  [  __x_0  ] = 3 ;
}
if (__static_condition_default_8) {
 __myFirstArr_2  [  __x_0  ] = 3 ;
}
return 0 ;
}



}

