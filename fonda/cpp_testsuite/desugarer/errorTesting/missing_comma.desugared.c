#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_10;
void __static_initializer_default() {
__static_renaming("__foo_4", "foo");
__static_renaming("__foo_5", "foo");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_6", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "!(defined A)");
__static_condition_renaming("__static_condition_default_9", "(defined A)");
__static_condition_renaming("__static_condition_default_10", "(defined A)");

if (__static_condition_default_10)
{
__static_parse_error("Unable to parse");
}
};

int  __foo_4 (int  __a_0, float  __b1_2, char  __x_3) {

if (__static_condition_default_6) {

{
{



return 0 ;// L10
}
}


}

}
int  __foo_5 (int  __a_0, float  __b2_1, char  __x_3) {

if (__static_condition_default_7) {

{
{



return 0 ;// L10
}
}


}

}
int  __main_8 () {

{
{



if (__static_condition_default_7) {
return  __foo_5  ( 1, 2, 3 ) ;// L14
}
if (__static_condition_default_9) {
__static_type_error("invalid type found in return expression");
}
}
}



}

