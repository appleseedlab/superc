#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_3", "x");
__static_renaming("__x_5", "x");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_7", "(defined A)");

};
struct __anonymous_tag_0 {
char  __a_1;
};

struct __anonymous_tag_0  __x_5;
char  __x_3 (int  __y_2) {

if (__static_condition_default_4) {
{

if (__static_condition_default_4) {
return  __y_2  ;

}
}

}

}
int  __main_6 () {
{

{
if (__static_condition_default_7) {
 __x_5  . __a_1 ;

}

if (__static_condition_default_4) {
__static_type_error("type error") ;

}

}return 0 ;

}


}
