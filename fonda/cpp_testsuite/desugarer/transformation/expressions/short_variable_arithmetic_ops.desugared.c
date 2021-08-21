#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__z_2", "z");
__static_renaming("__main_3", "main");


};

int  (__main_3) (void  ) {

{
{



int  __x_0;// L2

int  __y_1;// L3

int  __z_2;// L4

 __x_0  = 1 ; // L5
 __y_1  = 2 ; // L6
 __z_2  = 3 ; // L7
 __x_0  =  __y_1  +  __z_2  ; // L9
 __x_0  =  __y_1  -  __z_2  ; // L11
 __x_0  =  __y_1  *  __z_2  ; // L13
 __x_0  =  __y_1  /  __z_2  ; // L15
 __x_0  =  __y_1  %  __z_2  ; // L17
return 0 ;// L19
}
}


}

