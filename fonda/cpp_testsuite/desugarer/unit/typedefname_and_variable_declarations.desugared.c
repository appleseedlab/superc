#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_1", "a");
__static_renaming("__a_2", "a");
__static_renaming("__main_3", "main");
__static_renaming("__a_5", "a");
__static_renaming("__f_6", "f");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

if (__static_condition_default_8)
{
__static_parse_error("Unable to parse");
}
};
typedef int  __a_0;// L2

// typedef moved to top of scope
int  __a_1;// L4
int  __main_3 () {

if (__static_condition_default_4) {

{
{



__a_0  __a_2;// L8

}
}


}
}
int  __f_6 () {

if (__static_condition_default_7) {

{
{



const __a_0  __a_5;// L12

}
}


}
}

