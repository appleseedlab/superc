#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_1", "a");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "L");
__static_condition_renaming("__static_condition_default_4", "!L");

if (__static_condition_default_4)
{
__static_parse_error("Unable to parse");
}
};

int  * (__a_1);// L6
int  * (__a_0);// L6
int  (__main_2) () {

if (__static_condition_default_3) {

{
{



 __a_0  ; // L3:L12
}
}


}
}

