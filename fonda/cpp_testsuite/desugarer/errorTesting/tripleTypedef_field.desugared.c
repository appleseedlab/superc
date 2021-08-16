#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__d_8", "d");
__static_renaming("__d_9", "d");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_7", "(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_11", "!(defined A) && (defined C) || (defined A) && (defined B) && !(defined C)");

if (__static_condition_default_11)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __a_0;// L2
typedef int  __b_1;// L6
typedef int  __c_2;// L10
struct __y_3 {
};
struct __y_4 {
__c_2  __k_5;// L0
};

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __y_3 ;// L13
struct __y_4 ;// L13

int  __main_10 () {

{
{



int  __d_8= 2;// L28

int  __d_9= 2;// L30

return 0 ;// L32
}
}


}

