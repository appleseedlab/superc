#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__y_4", "y");
__static_renaming("__z_5", "z");

__static_condition_renaming("__static_condition_default_6", "!CONFIG_A");

};

int  __main_0 (void  ) {
{
int  __x_1= 2;
char  __x_2= 4;
int  __y_3= 3;
int  __y_4= 5;
int  __z_5=  __x_1  +  __y_3 ;
if (__static_condition_default_6) {
__static_type_error("invalid declaration of z under this presence condition");
}
return 0 ;

}


}

