#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__data_2", "data");
__static_renaming("__main_4", "main");


};

int  __x_0= 2;// L1

int  __main_4 () {

{
{



int  (__data_2[4]);// L6
{
__data_2[0] = 1;
__data_2[1] = 5;
__data_2[2] = 6 + 2;
__data_2[3] =  __x_0  + 5;
}

if (1) {
__static_type_error("non const value in constant list or struct: data2");
}


return 0 ;// L8
}
}


}

