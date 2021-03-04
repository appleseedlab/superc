#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_8", "main");
__static_renaming("__bee_9", "bee");


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
__bee_9.__field_7 = { 2, 3 };
}
}
return 0 ;

}


}

