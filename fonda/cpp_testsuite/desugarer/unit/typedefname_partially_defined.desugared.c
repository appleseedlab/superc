#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_11;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_3", "a");
__static_renaming("__main_5", "main");
__static_renaming("__main_6", "main");
__static_renaming("__a_7", "a");
__static_renaming("__a_8", "a");

__static_condition_renaming("__static_condition_default_2", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_4", "(defined C)");
__static_condition_renaming("__static_condition_default_9", "!(defined A) && (defined C) || (defined A) && !(defined B) && (defined C) || (defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_10", "!(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_11", "!(defined C)");
__static_condition_renaming("__static_condition_default_12", "(defined C)");

};
typedef int  __a_0;

typedef char  __a_3;

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
int  __main_5 () {

if (__static_condition_default_11) {
{
const __a_0  __a_7;
const __a_3  __a_8;
if (__static_condition_default_9) {
__static_type_error("invalid declaration of a under this presence condition");
}
if (__static_condition_default_10) {
__static_type_error("invalid declaration of a under this presence condition");
}
}

}

}
int  __main_6 () {

if (__static_condition_default_12) {
{
const __a_0  __a_7;
const __a_3  __a_8;
if (__static_condition_default_9) {
__static_type_error("invalid declaration of a under this presence condition");
}
if (__static_condition_default_10) {
__static_type_error("invalid declaration of a under this presence condition");
}
}

}

}

