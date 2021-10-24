#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__u1_9", "u1");
__static_renaming("__array_10", "array");
__static_renaming("__array_11", "array");
__static_renaming("__main_12", "main");


};
struct __S_0 {
int  __a_1;// L3
int  __a_2;// L6
int  __b_3;// L4
int  __b_4;// L7
};
union __U_5 {
struct __S_0  __one_6;// L12
int  __two_7;// L13
long long  __three_8;// L14
};

struct __S_0 ;// L1
union __U_5  __u1_9;// L11:L15
int  (__main_12) () {

{
{



int  __array_10[9 - ( ( ( ( sizeof(int  )  +  sizeof(int  ) )  >=  sizeof(int) )  &&  ( ( sizeof(int  )  +  sizeof(int  ) )  >=  sizeof(long long) ) ) ? ( sizeof(int  )  +  sizeof(int  ) ) : ( ( ( sizeof(int)  >=  sizeof(long long) ) ) ? sizeof(int) : ( sizeof(long long) ) ) )];// L20

int  __array_11[9 - ( ( ( ( sizeof(int  )  +  sizeof(int  ) )  >=  sizeof(int) )  &&  ( ( sizeof(int  )  +  sizeof(int  ) )  >=  sizeof(long long) ) ) ? ( sizeof(int  )  +  sizeof(int  ) ) : ( ( ( sizeof(int)  >=  sizeof(long long) ) ) ? sizeof(int) : ( sizeof(long long) ) ) )];// L20

return 0 ;// L21
}
}


}

