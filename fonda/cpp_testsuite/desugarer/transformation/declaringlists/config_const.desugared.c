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
__static_renaming("__main_4", "main");


};

int  (__main_4) (void  ) {

{
{



int  __x_0= 2;// L3

char  __x_1= 3;// L5

int  __y_2=  __x_0 ;// L8

int  __y_3=  __x_1 ;// L8

return 0 ;// L10
}
}


}

