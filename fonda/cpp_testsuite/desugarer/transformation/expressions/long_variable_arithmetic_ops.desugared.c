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
__static_renaming("__w_3", "w");
__static_renaming("__u_4", "u");
__static_renaming("__v_5", "v");
__static_renaming("__t_6", "t");
__static_renaming("__main_7", "main");


};

int  __main_7 (void  ) {

{
{



int  __x_0;// L2

int  __y_1;// L3

int  __z_2;// L4

int  __w_3;// L5

int  __u_4;// L6

int  __v_5;// L7

int  __t_6;// L8

 __x_0  = 2 ; // L10
 __y_1  = 3 ; // L11
 __z_2  = 5 ; // L12
 __w_3  = 1 ; // L13
 __u_4  = 7 ; // L14
 __v_5  = 6 ; // L15
 __t_6  = 8 ; // L16
 __x_0  =  __y_1  +  __z_2  -  __w_3  *  __u_4  /  __v_5  %  __t_6  ; // L18
return 0 ;// L20
}
}


}

