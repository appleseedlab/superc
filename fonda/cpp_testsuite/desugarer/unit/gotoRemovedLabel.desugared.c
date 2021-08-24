#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined X) && !(defined Y)");
__static_condition_renaming("__static_condition_default_4", "!(defined X) && (defined Y) || (defined X)");

};

int  __a_0;// L7
int  __b_1;// L8
int  (__main_2) () {

{
{



if (  __a_0  >  __b_1  )// L11
{

{
goto L_0;
}
}
if (__static_condition_default_3) {
switch (  __a_0  )// L14
{
case 2 :
{




L_0:
{
 __a_0  = 3 ; // L17
}
break ; // L18
}
case 3 :
{



 __a_0  = 4 ; // L20
}
default:
{



 __b_1  = 1 ; // L22
}
}
}
if (__static_condition_default_4) {
__static_type_error("Switch cases are incompatible");
}
return 0 ;// L24
}
}


}

