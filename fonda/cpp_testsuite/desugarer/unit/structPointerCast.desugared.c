#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__var_4", "var");
__static_renaming("__main_5", "main");


};
struct __x_0 {
int  __a_1;// L2
int  __b_2;// L3
int  __c_3;// L4
};

struct __x_0 ;// L1
const struct __x_0  (* (__var_4));// L7
int  __main_5 () {

{
{



( * ( struct __x_0  (* (*)) ) &  __var_4  ) = ( void  * ) 0 ; // L11
return 0 ;// L12
}
}


}

