#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_1", "!(defined A)");
__static_condition_renaming("__static_condition_default_4", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");

if (0)
{
__static_parse_error("Unable to parse");
}
};

int  (__x_2[5]);
char  __x_3 (int  __y_0) {

if (__static_condition_default_1) {
{

if (__static_condition_default_1) {
return  __y_0  ;

}
}

}

}
int  __main_6 () {
{

{
if (__static_condition_default_4) {
 __x_3  ( 2 ) ;

}

if (__static_condition_default_5) {
__static_type_error("type error") ;

}

}return 0 ;

}


}

