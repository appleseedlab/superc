#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__main_1", "main");


};

int  __main_1 () {

{



int  __x_0;// L2

 __x_0  = 300 ; // L3
 __x_0  ++ ; // L4
return  __x_0  ;// L5
}



}

