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



int  __x_0;

int  __y_1;

int  __z_2;

int  __w_3;

int  __u_4;

int  __v_5;

int  __t_6;

 __x_0  = 2 ;
 __y_1  = 3 ;
 __z_2  = 5 ;
 __w_3  = 1 ;
 __u_4  = 7 ;
 __v_5  = 6 ;
 __t_6  = 8 ;
 __x_0  =  __y_1  +  __z_2  -  __w_3  *  __u_4  /  __v_5  %  __t_6  ;
return 0 ;
}



}

