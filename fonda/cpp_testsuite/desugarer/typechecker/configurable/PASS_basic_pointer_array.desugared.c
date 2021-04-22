#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_18;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_22;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("__arr_0", "arr");
__static_renaming("__arr_1", "arr");
__static_renaming("__arr_2", "arr");
__static_renaming("__arr_3", "arr");
__static_renaming("__arr_4", "arr");
__static_renaming("__arr_5", "arr");
__static_renaming("__arr_6", "arr");
__static_renaming("__arr_7", "arr");
__static_renaming("__arr_8", "arr");
__static_renaming("__main_23", "main");

__static_condition_renaming("__static_condition_default_10", "A && !(defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_12", "!A && !B && !(defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_14", "!A && B && !(defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_16", "A && (defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_18", "!A && !B && (defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_20", "!A && B && (defined C) && (defined D)");
__static_condition_renaming("__static_condition_default_21", "(defined C) && !(defined D)");
__static_condition_renaming("__static_condition_default_22", "!(defined C) || (defined C) && (defined D)");

if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __main_23 () {
{
int  __arr_6;
float  __arr_7;
char  __arr_8;
int  (__arr_0[]);
float  (__arr_1[]);
char  (__arr_2[]);
int  (* __arr_3);
float  (* __arr_4);
char  (* __arr_5);
if (__static_condition_default_10) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_12) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_14) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_16) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_18) {
__static_type_error("redeclaration of local symbol: arr");
}

if (__static_condition_default_20) {
__static_type_error("redeclaration of local symbol: arr");
}


{
if (__static_condition_default_21) {
return 0 ;

}

if (__static_condition_default_22) {
return 0 ;

}

}}


}

