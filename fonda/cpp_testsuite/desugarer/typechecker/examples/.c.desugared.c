#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_3();

void __static_initializer_3() {
__static_renaming("__a_0", "a");
__static_renaming("__main_1", "main");
__static_renaming("__a_2", "a");


};
typedef int  __a_0;
int  __main_1 ();

// typedef moved to top of scope
int  __main_1 () {
{
const __a_0  __a_2;
}


}

