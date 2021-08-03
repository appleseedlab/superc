#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__aaa_1", "aaa");
__static_renaming("__aaa_2", "aaa");
__static_renaming("__y_3", "y");
__static_renaming("__c_6", "c");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_8", "!(defined A)");

if (__static_condition_default_8)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __x_0;// L2
typedef int  __y_3;// L8
struct __x_4 {
__x_0  __a_5;
};

// typedef moved to top of scope
int  __aaa_1;// L5
int  __aaa_2;// L5
// typedef moved to top of scope
struct __x_4 ;// L11
int  __main_7 () {

{



struct __x_4  __c_6;// L21

return 0 ;// L22
}



}

