#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_1", "a");
__static_renaming("__main_2", "main");
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");
__static_renaming("__y_5", "y");
__static_renaming("__y_6", "y");
__static_renaming("__z_7", "z");
__static_renaming("__w_8", "w");
__static_renaming("__w_9", "w");
__static_renaming("__w_10", "w");


};
typedef int  __a_0;
typedef float  __a_1;

// typedef moved to top of scope
// typedef moved to top of scope
int  __main_2 () {
{
__a_0  __x_3;
__a_1  __x_4;
__a_0  __y_5;
int  __y_6;
__a_1  __z_7;
__a_0  __w_8;
__a_1  __w_9;
char  __w_10;
return 0 ;

}


}
