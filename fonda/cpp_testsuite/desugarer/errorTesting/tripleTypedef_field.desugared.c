#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__b_1", "b");
__static_renaming("__c_2", "c");
__static_renaming("__d_4", "d");
__static_renaming("__d_5", "d");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "!(defined A) || (defined A) && !(defined B) && (defined C) || (defined A) && (defined B)");

if (__static_condition_default_7)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __a_0;
typedef int  __b_1;
typedef int  __c_2;
struct __y_3 {
};

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
struct __y_3 ;
int  __main_6 () {
{
int  __d_4= 2;
int  __d_5= 2;
return 0 ;

}


}

