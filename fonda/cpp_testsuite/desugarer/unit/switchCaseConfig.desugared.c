#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__main_1", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A)");
__static_condition_renaming("__static_condition_default_3", "!(defined A)");

};

int  __main_1 () {

{
{



int  __x_0;// L3

if (__static_condition_default_2) {
switch (  __x_0  )// L4
{
case 1 :
{



 __x_0  = 2 ; // L6
break ; // L7
}
case 2 :
{



 __x_0  = 3 ; // L10
break ; // L11
 __x_0  = 0 ; // L18
}
}
}
if (__static_condition_default_3) {
switch (  __x_0  )// L4
{
case 1 :
{



 __x_0  = 2 ; // L6
break ; // L7
}
case 2 :
{



 __x_0  = 4 ; // L14
break ; // L15
 __x_0  = 0 ; // L18
}
}
}
return  __x_0  ;// L20
}
}



}

