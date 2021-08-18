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
__static_renaming("__a_1", "a");
__static_renaming("__main_2", "main");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");

};

const int  __x_0= 2;// L2
int  __main_2 () {

if (__static_condition_default_4) {

{
{



int  __a_1;// L7

__static_type_error("Switch cases are incompatible");
return 0 ;// L16
}
}


}
}
int  __main_3 () {

if (__static_condition_default_5) {

{
{



int  __a_1;// L7

switch (  __a_1  )// L8
{
case  __x_0  :
{



 __a_1  = 1 ; // L11
break ; // L12
}
default:
{



 __a_1  = 2 ; // L14
}
}
return 0 ;// L16
}
}


}
}

