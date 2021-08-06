#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__y_0", "y");
__static_renaming("__y_1", "y");
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A) && (defined B) && !(defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_5", "(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_7", "!(defined A) && !(defined B) && (defined C) && !(defined D)");
__static_condition_renaming("__static_condition_default_8", "!(defined A) && !(defined B) && !(defined C) && !(defined D)");
__static_condition_renaming("__static_condition_default_9", "!(defined A) && !(defined B) && !(defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_10", "!(defined A) && !(defined B) && (defined C) && (defined D) || !(defined A) && (defined B) && !(defined C) && !(defined D) || !(defined A) && (defined B) && (defined C) && (defined D) || (defined A) && !(defined C) && !(defined D) || (defined A) && (defined C) && (defined D)");

if (__static_condition_default_10)
{
__static_parse_error("Unable to parse");
}
};

int  __main_6 () {

{
{



if (__static_condition_default_7) {
__static_type_error("type error : no valid expression"); // L10:L15
}
if (__static_condition_default_8) {
 ; // L15
}
if (__static_condition_default_9) {
__static_type_error("type error : no valid expression"); // L13:L15
}
int  __x_3;// L4:L15

char  __x_4;// L4:L15

if (__static_condition_default_5) {
__static_type_error("invalid declaration of x under this presence condition");
}


int  __y_0;// L4:L15

char  __y_1;// L4:L15

if (__static_condition_default_2) {
__static_type_error("invalid declaration of y under this presence condition");
}

return 0 ;// L16
}
}



}

