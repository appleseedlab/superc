#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_1", "a");
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");
__static_renaming("__y_4", "y");
__static_renaming("__y_5", "y");
__static_renaming("__z_6", "z");
__static_renaming("__w_7", "w");
__static_renaming("__w_8", "w");
__static_renaming("__w_9", "w");
__static_renaming("__main_10", "main");


};
typedef int  __a_0;// L1:L7
typedef float  __a_1;// L1:L7

// typedef moved to top of scope
// typedef moved to top of scope
int  (__main_10) () {

{
{



__a_0  __x_2;// L10

__a_1  __x_3;// L10

__a_0  __y_4;// L14:L16

int  __y_5;// L14:L16

__a_1  __z_6;// L18

__a_0  __w_7;// L23:L25

__a_1  __w_8;// L23:L25

char  __w_9;// L23:L25

return 0 ;// L26
}
}


}

