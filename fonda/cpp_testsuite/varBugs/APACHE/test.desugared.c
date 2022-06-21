#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__z_0", "z");
__static_renaming("__main_1", "main");


};

int  __z_0;// L6
int  (__main_1) () {

{
{



 __z_0  += 3 ; // L13
return 0 ;// L14
}
}


}

