#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__z_2", "z");
__static_renaming("__f_3", "f");


};

int  __f_3 (char  __x_0, int  __y_1) {

{
{



int  __z_2;// L5

 __y_1  =  __x_0  +  __y_1  ; // L7
 __z_2  =  __y_1  ; // L9
return  __z_2  ;// L11
}
}



}

