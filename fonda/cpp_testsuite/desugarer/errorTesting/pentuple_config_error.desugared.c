#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_24;
extern const bool __static_condition_default_26;
extern const bool __static_condition_default_31;
extern const bool __static_condition_default_29;
extern const bool __static_condition_default_25;
extern const bool __static_condition_default_28;
extern const bool __static_condition_default_22;
extern const bool __static_condition_default_33;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_27;
extern const bool __static_condition_default_30;
void __static_initializer_default() {
__static_renaming("__ourType_0", "ourType");
__static_renaming("__ourType_1", "ourType");
__static_renaming("__ourType_2", "ourType");
__static_renaming("__ourType_3", "ourType");
__static_renaming("__foo_9", "foo");
__static_renaming("__foo_10", "foo");
__static_renaming("__foo_11", "foo");
__static_renaming("__foo_12", "foo");
__static_renaming("__foo_13", "foo");
__static_renaming("__foo_14", "foo");
__static_renaming("__foo_15", "foo");
__static_renaming("__foo_16", "foo");
__static_renaming("__foo_17", "foo");
__static_renaming("__foo_18", "foo");
__static_renaming("__main_32", "main");

__static_condition_renaming("__static_condition_default_22", "!(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_23", "(defined A) && !(defined B) && (defined C) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_24", "(defined A) && !(defined B) && (defined C) && !(defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_25", "(defined A) && !(defined B) && (defined C) && (defined E)");
__static_condition_renaming("__static_condition_default_26", "(defined A) && (defined B) && (defined C) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_27", "(defined A) && (defined B) && (defined C) && !(defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_28", "(defined A) && (defined B) && (defined C) && (defined E)");
__static_condition_renaming("__static_condition_default_29", "!(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_30", "(defined A) && !(defined B) && !(defined C) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_31", "(defined A) && (defined B) && !(defined C) && (defined D) && !(defined E)");
__static_condition_renaming("__static_condition_default_33", "!(defined A) || (defined A) && !(defined D) || (defined A) && (defined D) && (defined E)");

if (__static_condition_default_33)
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
__ourType_0  __foo_9 () {

if (__static_condition_default_22) {

{
{



return 0 ;// L30
}
}


}

}
__ourType_1  __foo_10 (int  __x_4, int  __y_5, __ourType_1  __z_7) {

if (__static_condition_default_23) {

{
{



return 0 ;// L30
}
}


}

}
__ourType_1  __foo_11 (int  __x_4, __ourType_1  __z_7) {

if (__static_condition_default_24) {

{
{



return 0 ;// L30
}
}


}

}
__ourType_1  __foo_12 () {

if (__static_condition_default_25) {

{
{



return 0 ;// L30
}
}


}

}
__ourType_2  __foo_13 (int  __x_4, int  __y_5, __ourType_2  __z_8) {

if (__static_condition_default_26) {

{
{



return 0 ;// L30
}
}


}

}
__ourType_2  __foo_14 (int  __x_4, __ourType_2  __z_8) {

if (__static_condition_default_27) {

{
{



return 0 ;// L30
}
}


}

}
__ourType_2  __foo_15 () {

if (__static_condition_default_28) {

{
{



return 0 ;// L30
}
}


}

}
__ourType_3  __foo_16 () {

if (__static_condition_default_29) {

{
{



return 0 ;// L30
}
}


}

}
short  __foo_17 (int  __x_4, int  __y_5, __ourType_1  __z_7) {

if (__static_condition_default_30) {

{
{



return 0 ;// L30
}
}


}

}
short  __foo_18 (int  __x_4, int  __y_5, __ourType_2  __z_8) {

if (__static_condition_default_31) {

{
{



return 0 ;// L30
}
}


}

}
int  __main_32 () {

{
{



return 0 ;// L35
}
}



}

