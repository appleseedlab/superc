#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__y_1", "y");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A)");
__static_condition_renaming("__static_condition_default_3", "!(defined A)");
__static_condition_renaming("__static_condition_default_4", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_5", "!(defined A) || (defined A) && !(defined B)");

if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __x_0;
char  __y_1;
int  __main_6 () {
{

if (__static_condition_default_2) {
 __x_0  = 10 ;

}

if (__static_condition_default_3) {
 __y_1  = 'c' ;

}

{
if (__static_condition_default_4) {
return 1 ;

}

if (__static_condition_default_5) {
return 0 ;

}

}}


}

