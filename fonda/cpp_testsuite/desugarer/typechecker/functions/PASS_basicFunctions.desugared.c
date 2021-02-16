#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_2", "y");
__static_renaming("__y2_3", "y2");
__static_renaming("__z_6", "z");
__static_renaming("__w_8", "w");
__static_renaming("__main_9", "main");


};

int  __x_0 () {
{
return 0 ;

}


}
float  (* __y_2 (int  __y1_1)) {
{
float  (* __y2_3);
return  __y2_3  ;

}


}
char  __z_6 (int  __z1_4, int  __z2_5) {
{
return 'a' ;

}


}
short  __w_8 (int  __x_7,  ... ) {
{
return 0 ;

}


}
int  __main_9 (void  ) {
{
return 0 ;

}


}

