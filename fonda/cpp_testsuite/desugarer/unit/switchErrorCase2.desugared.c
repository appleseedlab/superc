#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__main_1", "main");

__static_condition_renaming("__static_condition_default_2", "!(defined X) && !(defined Y)");
__static_condition_renaming("__static_condition_default_3", "!(defined X) && (defined Y) || (defined X)");

};

int  __a_0;// L4
int  (__main_1) () {

{
{



if (__static_condition_default_2) {
switch (  __a_0  )// L10
{
case 254 :
{



return 0 ;// L12
}
case 1 :
{



return 0 ;// L14
}
}
}
if (__static_condition_default_3) {
__static_type_error("Switch cases are incompatible");
}
return 1 ;// L16
}
}


}

