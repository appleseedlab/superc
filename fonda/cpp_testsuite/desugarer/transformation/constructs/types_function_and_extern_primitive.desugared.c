#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__f_0", "f");
__static_renaming("__f_1", "f");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A)");
__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");

};

extern int  __f_0;// L6
float  (__f_1) () {

if (__static_condition_default_2) {

{
{



return 0 ;// L3
}
}


}
}
int  (__main_3) () {

{
{



if (__static_condition_default_4) {
 __f_1 ( ) ; // L11
}
if (__static_condition_default_5) {
 __f_0  ; // L13
}
return 0 ;// L15
}
}


}

