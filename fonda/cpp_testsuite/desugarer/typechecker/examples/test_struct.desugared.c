#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__globalvar_2", "globalvar");
__static_renaming("__bobvar_3", "bobvar");
__static_renaming("__main_4", "main");


};
struct __bob_0 {
int  __x_1;
};

struct __bob_0  __globalvar_2;
int  __main_4 () {
{
struct __bob_0  __bobvar_3;
}


}

