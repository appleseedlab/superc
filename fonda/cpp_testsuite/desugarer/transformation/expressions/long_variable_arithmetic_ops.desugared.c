#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__z_3", "z");
__static_renaming("__w_4", "w");
__static_renaming("__u_5", "u");
__static_renaming("__v_6", "v");
__static_renaming("__t_7", "t");


};

int  __main_0 (void  ) {
{
int  __x_1;
int  __y_2;
int  __z_3;
int  __w_4;
int  __u_5;
int  __v_6;
int  __t_7;
 __x_1  = 2 ;

 __y_2  = 3 ;

 __z_3  = 5 ;

 __w_4  = 1 ;

 __u_5  = 7 ;

 __v_6  = 6 ;

 __t_7  = 8 ;

 __x_1  =  __y_2  +  __z_3  -  __w_4  *  __u_5  /  __v_6  %  __t_7  ;

return 0 ;

}


}

