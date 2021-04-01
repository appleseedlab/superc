#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__main_6", "main");
__static_renaming("__a_7", "a");

__static_condition_renaming("__static_condition_default_8", "(defined A)");
__static_condition_renaming("__static_condition_default_9", "!(defined A)");

};
struct __x_0 {
int  __a_1;
unsigned  __a_2;
};
struct __y_3 {
struct __x_0  __a_4;
int  __b_5;
};

struct __x_0 ;
struct __y_3 ;
int  __main_6 () {
{
struct __y_3  __a_7;
{
if (1) {
if (__static_condition_default_8) {
__a_7.__a_4.__a_1 = 2;
}
if (__static_condition_default_9) {
__a_7.__a_4.__a_2 = 2;
}
}
}
return 0 ;

}


}

