#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__num_0", "num");
__static_renaming("__x_2", "x");
__static_renaming("__x_4", "x");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "(defined A)");

};

int  __num_0= 1;
int  (* __x_4);
char  __x_2 (int  __y_1) {

if (__static_condition_default_3) {
{

if (__static_condition_default_3) {
return  __y_1  ;

}
}

}

}
int  __main_5 () {
{

if (__static_condition_default_6) {
 __x_4  = &  __num_0  ;

}

{
if (__static_condition_default_3) {
*  __x_2  ;

}

if (__static_condition_default_6) {
*  __x_4  ;

}

}return 0 ;

}


}

