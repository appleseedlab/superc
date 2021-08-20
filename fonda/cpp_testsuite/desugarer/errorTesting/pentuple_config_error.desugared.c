#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_15;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_18;
void __static_initializer_default() {
__static_renaming("__ourType_0", "ourType");
__static_renaming("__ourType_1", "ourType");
__static_renaming("__ourType_2", "ourType");
__static_renaming("__ourType_3", "ourType");
__static_renaming("__foo_9", "foo");
__static_renaming("__foo_10", "foo");
__static_renaming("__foo_11", "foo");
__static_renaming("__foo_12", "foo");
__static_renaming("__main_17", "main");

__static_condition_renaming("__static_condition_default_13", "(defined A) && !(defined B) && (defined C) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_14", "(defined A) && (defined B) && (defined C) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_15", "(defined A) && !(defined B) && !(defined C) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_16", "(defined A) && (defined B) && !(defined C) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_18", "(defined A) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_19", "!(defined A) || (defined A) && !(defined D) || (defined A) && (defined D) && (defined E)");

if (__static_condition_default_19)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __ourType_0;// L1:L10
typedef long int  __ourType_1;// L1:L10
typedef long int unsigned  __ourType_2;// L1:L10
typedef int unsigned  __ourType_3;// L1:L10

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
__ourType_1  __foo_9 (int  __x_4, int  __y_5, __ourType_1  __z_7) {

if (__static_condition_default_13) {

{
{



return 0 ;// L30
}
}


}
}
__ourType_2  __foo_10 (int  __x_4, int  __y_5, __ourType_2  __z_8) {

if (__static_condition_default_14) {

{
{



return 0 ;// L30
}
}


}
}
short  __foo_11 (int  __x_4, int  __y_5, __ourType_1  __z_7) {

if (__static_condition_default_15) {

{
{



return 0 ;// L30
}
}


}
}
short  __foo_12 (int  __x_4, int  __y_5, __ourType_2  __z_8) {

if (__static_condition_default_16) {

{
{



return 0 ;// L30
}
}


}
}
int  __main_17 () {

if (__static_condition_default_18) {

{
{



return 0 ;// L35
}
}


}
}

