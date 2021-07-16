#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__foo_3", "foo");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_6", "!(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_7", "!(defined A) && !(defined B) || !(defined A) && (defined B) && !(defined C) || (defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A) && !(defined B) || (defined A)");

if (__static_condition_default_8)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __a_0;
typedef int  __b_1;
typedef int  __c_2;

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
__c_2  __foo_3 ();
int  __main_5 () {

{



if (__static_condition_default_6) {
 __foo_3 ( ) ; // L23
}
if (__static_condition_default_7) {
__static_type_error("type error") ; // L23
}
return 0 ;// L24
}



}

