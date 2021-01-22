#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_3", "a");
__static_renaming("__a_8", "a");
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");
__static_renaming("__a_11", "a");
__static_renaming("__a_12", "a");
__static_renaming("__a_13", "a");

__static_condition_renaming("__static_condition_default_2", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_5", "(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_14", "(defined A) && !(defined B) && (defined C) || (defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_15", "!(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_16", "!(defined C)");
__static_condition_renaming("__static_condition_default_17", "(defined C)");

};
typedef int  __a_0;

typedef char  __a_3;

typedef char char  __a_6;

typedef char char  __a_8;

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
int  __main_9 () {

if (__static_condition_default_16) {
{
const __a_0  __a_11;
const __a_3  __a_12;
const __a_8  __a_13;
if (__static_condition_default_14) {
__static_type_error("invalid declaration of a under this presence condition");
}
if (__static_condition_default_15) {
__static_type_error("invalid declaration of a under this presence condition");
}
}

}

}
int  __main_10 () {

if (__static_condition_default_17) {
{
const __a_0  __a_11;
const __a_3  __a_12;
const __a_8  __a_13;
if (__static_condition_default_14) {
__static_type_error("invalid declaration of a under this presence condition");
}
if (__static_condition_default_15) {
__static_type_error("invalid declaration of a under this presence condition");
}
}

}

}

