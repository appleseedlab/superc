#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__a_2", "a");
__static_renaming("__b_3", "b");
__static_renaming("__b_4", "b");
__static_renaming("__main_5", "main");


};

extern int  __x_0;// L2
extern int  __x_1;// L4
static void  __main_5 () {

{
{



int  __a_2;// L8

int  __b_3=  __x_0 ;// L8

int  __b_4=  __x_1 ;// L8

}
}



}

