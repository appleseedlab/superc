#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__main_8", "main");
__static_renaming("__bee_9", "bee");

__static_condition_renaming("__static_condition_default_10", "(defined A)");
__static_condition_renaming("__static_condition_default_11", "!(defined A)");

};
struct __a_0 {
int  __a_1;
int  __b_2;
int  __c_3;
int  __c_4;
};
struct __b_5 {
int  __a_6;
struct __a_0  __field_7;
};

struct __a_0 ;
struct __b_5 ;
int  __main_8 () {
{
struct __b_5  __bee_9;
{
if (1) {
__bee_9.__a_6 = 1;
if (__static_condition_default_10) {
__bee_9.__field_7.__a_1 = 2;
__bee_9.__field_7.__b_2 = 3;
}
if (__static_condition_default_11) {
__bee_9.__field_7.__a_1 = 2;
__bee_9.__field_7.__c_3 = 3;
}
}
}
return 0 ;

}


}
