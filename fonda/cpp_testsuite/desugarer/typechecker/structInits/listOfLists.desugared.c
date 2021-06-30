#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__main_1", "main");


};

 int  __main_1 () {

{



int  (__a_0[3]);
{
__a_0[0][0][0] = 1;
__a_0[0][1][0] = 2;
__a_0[3][1][0] = 3;
}

}



}

