#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__main_5", "main");
__static_renaming("__myFirstStruct_6", "myFirstStruct");

__static_condition_renaming("__static_condition_default_7", "A");
__static_condition_renaming("__static_condition_default_8", "!A");

};
struct __x_0 {
int  __a_1;
int  __b_2;
int  __c_3;
int  __c_4;
};

struct __x_0 ;
int  __main_5 (void  ) {
{
struct __x_0  __myFirstStruct_6;
{
if (__static_condition_default_7) {
__myFirstStruct_6.__a_1 = 1;
__myFirstStruct_6.__b_2 = 2;
}
if (__static_condition_default_8) {
__myFirstStruct_6.__a_1 = 1;
__myFirstStruct_6.__c_3 = 2;
}
}
return 0 ;

}


}

