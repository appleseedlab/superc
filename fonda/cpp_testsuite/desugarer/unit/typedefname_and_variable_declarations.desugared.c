#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_1", "a");
__static_renaming("__main_2", "main");
__static_renaming("__a_3", "a");
__static_renaming("__f_5", "f");
__static_renaming("__a_6", "a");

__static_condition_renaming("__static_condition_default_4", "(defined A)");

};
typedef int  __a_0;

// typedef moved to top of scope
int  __a_1;
int  __main_2 () {

if (__static_condition_default_4) {
{
__a_0  __a_3;
}

}

}
int  __f_5 () {

if (__static_condition_default_4) {
{
const __a_0  __a_6;
}

}

}

