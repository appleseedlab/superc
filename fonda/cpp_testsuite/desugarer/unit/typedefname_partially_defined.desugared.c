#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_3", "a");
__static_renaming("__a_5", "a");
__static_renaming("__a_6", "a");
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_4", "(defined C)");
__static_condition_renaming("__static_condition_default_7", "!(defined A) && (defined C) || (defined A) && !(defined B) && (defined C) || (defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_8", "!(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_11", "!(defined C)");
__static_condition_renaming("__static_condition_default_12", "(defined C)");

};
typedef int  __a_0;

typedef char  __a_3;

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
int  __main_9 () {

if (__static_condition_default_11) {

{



const __a_0  __a_5;

const __a_3  __a_6;

if (__static_condition_default_7) {
__static_type_error("invalid declaration of a under this presence condition");
}

if (__static_condition_default_8) {
__static_type_error("invalid declaration of a under this presence condition");
}

}


}

}
int  __main_10 () {

if (__static_condition_default_12) {

{



if (__static_condition_default_7) {
__static_type_error("invalid declaration of a under this presence condition");
}

}


}

}

