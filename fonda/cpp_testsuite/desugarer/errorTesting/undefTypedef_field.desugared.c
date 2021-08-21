#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__c_3", "c");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_5", "(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");

if (__static_condition_default_6)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __x_0;// L2
struct __x_1 {
__x_0  __a_2;// L0
};

// typedef moved to top of scope
struct __x_1 ;// L5
int  (__main_4) () {

if (__static_condition_default_5) {

{
{



struct __x_1  __c_3;// L15

return 0 ;// L16
}
}


}
}

