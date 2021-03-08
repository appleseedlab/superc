#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_2", "main");
__static_renaming("__a_3", "a");


};
struct __x_0 {
int  (__a_1[5]);
};

struct __x_0 ;
int  __main_2 () {
{
struct __x_0  __a_3;
{
if (1) {
if (1) {
__a_3.__a_1[0] = 1;
}
if (1) {
__a_3.__a_1[2] = 2;
}
if (1) {
__a_3.__a_1[3] = 3;
}
}
}
}


}

