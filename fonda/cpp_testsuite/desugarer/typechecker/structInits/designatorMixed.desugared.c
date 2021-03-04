#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_9;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__main_6", "main");
__static_renaming("__x_7", "x");

__static_condition_renaming("__static_condition_default_8", "(defined A)");
__static_condition_renaming("__static_condition_default_9", "!(defined A)");

};
struct __x_0 {
int  __a_1;
int  __b_2;
int  __c_3;
int  __d_4;
int  __d_5;
};

struct __x_0 ;
int  __main_6 () {
{
struct __x_0  __x_7;
{
if (__static_condition_default_8) {
__x_7.__a_1 = 1;
__x_7.__b_2 = 2;
__x_7.__c_3 = 3;
__x_7.__b_2 = 4;
__x_7.__c_3 = 5;
}
if (__static_condition_default_9) {
__x_7.__a_1 = 1;
__x_7.__b_2 = 2;
__x_7.__d_4 = 3;
__x_7.__b_2 = 4;
__x_7.__d_4 = 5;
}
}
return 0 ;

}


}

