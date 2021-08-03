#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__i_0", "i");
__static_renaming("__j_1", "j");
__static_renaming("__main_2", "main");


};

int  __main_2 () {

{



int  __i_0;// L2

int  __j_1;// L3

for (  __i_0  = 0 ;  __i_0  < 10 ;  __i_0  ++ )// L4

{



 __j_1  ++ ; // L5
}
}



}

