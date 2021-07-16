#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__main_2", "main");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");

};

int  __x_0;
int  __main_2 () {

if (__static_condition_default_4) {

{



int  __y_1;

__static_type_error("invalid switch expression");
return  __y_1  ;// L18
}


}

}
int  __main_3 () {

if (__static_condition_default_5) {

{



int  __y_1;

switch (  __x_0  )// L8
{
case 1 :



 __y_1  = 2 ; // L10
break ; // L11
case 2 :



 __y_1  = 3 ; // L13
break ; // L14
default:



 __y_1  = 0 ; // L16
}
return  __y_1  ;// L18
}


}

}

