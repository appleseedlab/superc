#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_3", "x");
__static_renaming("__main_4", "main");


};
struct __xx_0 {
int  __a_1;// L2
int  __b_2;// L3
};

struct __xx_0 ;// L1
struct __xx_0  __x_3=  { .__a_1 = 2 ,  .__b_2 = 1 };// L5
int  (__main_4) () {

{
{



return 0 ;// L9
}
}


}

