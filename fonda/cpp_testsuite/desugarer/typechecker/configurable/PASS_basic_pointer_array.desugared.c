#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_19;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_22;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__arr_1", "arr");
__static_renaming("__arr_2", "arr");
__static_renaming("__arr_3", "arr");
__static_renaming("__arr_4", "arr");
__static_renaming("__arr_5", "arr");
__static_renaming("__arr_6", "arr");
__static_renaming("__arr_7", "arr");
__static_renaming("__arr_8", "arr");
__static_renaming("__arr_9", "arr");

__static_condition_renaming("__static_condition_default_11", "A && !(defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_13", "!A && !B && !(defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_15", "!A && B && !(defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_17", "A && (defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_19", "!A && !B && (defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_21", "!A && B && (defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_22", "(defined C) && !(defined D)");
__static_condition_renaming("__static_condition_default_23", "!(defined C) || (defined C) && (defined D)");

};

int  __main_0 () {
{
int  __arr_7;
float  __arr_8;
char  __arr_9;
int  (__arr_1[]);
float  (__arr_2[]);
char  (__arr_3[]);
int  (* __arr_4);
float  (* __arr_5);
char  (* __arr_6);
if (__static_condition_default_11) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_13) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_15) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_17) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_19) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_21) {
__static_type_error("redeclaration of local symbol: arr");
}


{
if (__static_condition_default_22) {
return 0 ;

}

if (__static_condition_default_23) {
return 0 ;

}

}}


}

