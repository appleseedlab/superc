#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__u1_7", "u1");
__static_renaming("__array_8", "array");
__static_renaming("__array_9", "array");
__static_renaming("__main_10", "main");


};
struct __S_0 {
int  __a_1;// L3
int  __a_2;// L5
};
union __U_3 {
struct __S_0  __one_4;// L10
int  __two_5;// L11
int  __three_6;// L12
};

struct __S_0 ;// L1
union __U_3  __u1_7;// L9:L13
int  (__main_10) () {

{
{



int  __array_8[5 - ( ( ( ( ( sizeof(int  ) )  >=  sizeof(int) )  &&  ( ( sizeof(int  ) )  >=  sizeof(int) ) ) ? ( sizeof(int  ) ) : ( ( sizeof(int)  >=  sizeof(int) ) ) ? sizeof(int) : sizeof(int) ) )];// L18

int  __array_9[5 - ( ( ( ( ( sizeof(int  ) )  >=  sizeof(int) )  &&  ( ( sizeof(int  ) )  >=  sizeof(int) ) ) ? ( sizeof(int  ) ) : ( ( sizeof(int)  >=  sizeof(int) ) ) ? sizeof(int) : sizeof(int) ) )];// L18

return 0 ;// L19
}
}


}

