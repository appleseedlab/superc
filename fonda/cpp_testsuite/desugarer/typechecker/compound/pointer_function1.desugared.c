#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__num_0", "num");
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_2", "!(defined A)");
__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");

if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __num_0= 1;
int  (* __x_3);
char  __x_4 (int  __y_1) {

if (__static_condition_default_2) {
{

if (__static_condition_default_2) {
return  __y_1  ;

}
}

}

}
int  __main_7 () {
{

{
if (__static_condition_default_5) {
 __x_3  = &  __num_0  ;

}

if (__static_condition_default_6) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_5) {
*  __x_3  ;

}

if (__static_condition_default_6) {
__static_type_error("type error") ;

}

}return 0 ;

}


}

