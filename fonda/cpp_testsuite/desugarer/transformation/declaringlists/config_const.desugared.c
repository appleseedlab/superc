#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__y_4", "y");


};

int  __main_0 (void  ) {
{
int  __x_1= 2;
char  __x_2= 3;
int  __y_3=  __x_1 ;
int  __y_4=  __x_2 ;
return 0 ;

}


}

