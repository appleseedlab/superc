#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_0;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__f_1", "f");
__static_renaming("__f_2", "f");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_0", "(defined A)");
__static_condition_renaming("__static_condition_default_3", "(defined A)");
__static_condition_renaming("__static_condition_default_4", "!(defined A)");

};

extern int  __f_1;
float  __f_2 () {

if (__static_condition_default_0) {
{

if (__static_condition_default_0) {
return 0 ;

}
}

}

}
int  __main_5 () {
{

{
if (__static_condition_default_3) {
 __f_2  ( ) ;

}

if (__static_condition_default_4) {
 __f_1  ;

}

}return 0 ;

}


}

