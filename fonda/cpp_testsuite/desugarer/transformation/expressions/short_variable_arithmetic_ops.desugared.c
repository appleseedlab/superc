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


};

int  __main_0 (void  ) {
{
int  __x_1;
int  __y_2;
int  __z_3;
 __x_1  = 1 ;

 __y_2  = 2 ;

 __z_3  = 3 ;

 __x_1  =  __y_2  +  __z_3  ;

 __x_1  =  __y_2  -  __z_3  ;

 __x_1  =  __y_2  *  __z_3  ;

 __x_1  =  __y_2  /  __z_3  ;

 __x_1  =  __y_2  %  __z_3  ;

return 0 ;

}


}

