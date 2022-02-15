#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_2", "a");
__static_renaming("__b_3", "b");
__static_renaming("__i_4", "i");
__static_renaming("__i_5", "i");
__static_renaming("__main_6", "main");


};
struct __x_0 {
int  __field_1 : 4;// L3
};

struct __x_0 ;// L1
int  (__main_6) () {

{
{



struct __x_0  __a_2;// L7

struct __x_0  * (__b_3);// L7

if (  __a_2  . __field_1 )// L8
{

{
{



int  __i_4= 0;// L9

}
}
}
if (  __b_3  -> __field_1 )// L11
{

{
{



int  __i_5= 0;// L12

}
}
}
return 0 ;// L14
}
}


}

