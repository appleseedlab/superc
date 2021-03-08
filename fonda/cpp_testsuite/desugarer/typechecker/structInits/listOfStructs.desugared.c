#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_2", "main");
__static_renaming("__b_3", "b");


};
struct __x_0 {
int  __a_1;
};

struct __x_0 ;
int  __main_2 () {
{
array(struct __x_0) (__b_3[5]);
{
if (1) {
__b_3[0].__a_1 = 2;
}
if (1) {
__b_3[1].__a_1 = 2;
}
if (1) {
__b_3[4].__a_1 = 1;
}
if (1) {
__b_3[5].__a_1 = 5;
}
}
}


}

