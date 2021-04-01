#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__a_1", "a");


};

int  __main_0 () {
{
int  (__a_1[5][5][5]);
{
if (1) {
__a_1[0][0][0] = 1;
}
if (1) {
__a_1[0][0][1] = 2;
}
if (1) {
__a_1[3][1][0] = 3;
}
}
}


}

