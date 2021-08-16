#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__s_10", "s");
__static_renaming("__main_11", "main");


};
struct __x_0 {
int  __a_1;// L2
int  __b_2;// L3
};
union __U_4 {
int  __a_5;// L8
long  __b_6;// L8
};
enum __sizes_9 {
__A_3 = ( sizeof(int  )  +  sizeof(int  ) ),
__B_7 = sizeof(union __U_4  ),
__C_8,
};

struct __x_0 ;// L1
enum __sizes_9 ;// L6
int  __main_11 () {

{
{



enum __sizes_9  __s_10;// L14

return 0 ;// L15
}
}


}

