#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__y_3", "y");
__static_renaming("__z_4", "z");
__static_renaming("__z_5", "z");
__static_renaming("__main_6", "main");


};

int  __main_6 (void  ) {

{
{



int  __x_0= 2;// L4

char  __x_1= 4;// L7

int  __y_2= 3;// L5

int  __y_3= 5;// L8

int  __z_4=  __x_0  +  __y_2 ;// L13

int  __z_5=  __x_1  +  __y_3 ;// L13

return 0 ;// L15
}
}



}

