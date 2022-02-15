#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__a_1", "a");
__static_renaming("__main_2", "main");


};
const int  __x_0= 10;// L1


int  (__main_2) () {

{
{



int  __a_1;// L4

__static_type_error("Switch cases are incompatible");
return 0 ;// L13
}
}


}

