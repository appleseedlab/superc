#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__main_1", "main");

__static_condition_renaming("__static_condition_default_2", "A");
__static_condition_renaming("__static_condition_default_3", "!A");

};

int  __main_1 (void  ) {

{



int  __x_0= 2;

if (__static_condition_default_2) {
if (  __x_0  == 2 )// L4:L12

{



 __x_0  ++ ; // L13
}
}
if (__static_condition_default_3) {
if (  __x_0  == 3 )// L4:L12

{



 __x_0  ++ ; // L13
}
}
return 0 ;// L16
}



}

