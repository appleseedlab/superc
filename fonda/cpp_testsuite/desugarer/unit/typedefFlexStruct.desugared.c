#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__s_0", "s");
__static_renaming("__s_1", "s");
__static_renaming("__a_8", "a");
__static_renaming("__a_9", "a");
__static_renaming("__main_10", "main");


};
typedef int  __s_0;// L2
typedef long  __s_1;// L4
struct __x_2 {
int  __data_3;// L8
__s_0  __id_4[];// L0
};
struct __x_5 {
int  __data_6;// L8
__s_1  __id_7[];// L0
};

// typedef moved to top of scope
// typedef moved to top of scope
struct __x_2 ;// L7
struct __x_5 ;// L7
int  (__main_10) () {

{
{



struct __x_2  __a_8;// L14

struct __x_5  __a_9;// L14

return 0 ;// L15
}
}


}

