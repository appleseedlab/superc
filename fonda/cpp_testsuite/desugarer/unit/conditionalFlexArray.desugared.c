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
__static_renaming("__main_9", "main");


};
typedef int  __x_0;// L2
typedef short  __x_1;// L4
struct __s_3 {
int  __data_4;// L9
__x_0  (__id_5[]);// L0
};
struct __s_6 {
int  __data_7;// L9
__x_1  (__id_8[]);// L0
};

// typedef moved to top of scope
// typedef moved to top of scope
int  __a_2;// L7
struct __s_3 ;// L8
struct __s_6 ;// L8
int  __main_9 () {

{
{



return 0 ;// L15
}
}


}

