#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__j_0", "j");
__static_renaming("__i_1", "i");
__static_renaming("__main_2", "main");


};

int  (__main_2) () {

{
{



int  __j_0;// L2

{ int  __i_1= 0;// L3
 for ( ;  __i_1  < 10 ;  __i_1  ++ ) // L3
{

{
{



 __j_0  ++ ; // L4
}
}
}
}
}
}


}

