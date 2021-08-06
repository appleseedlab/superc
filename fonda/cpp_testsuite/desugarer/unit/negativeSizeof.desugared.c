#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__y_9", "y");
__static_renaming("__a_10", "a");
__static_renaming("__a_11", "a");
__static_renaming("__main_12", "main");


};
struct __X_0 {
int  __a_1;
int  __b_2;
int  __c_3;
};
struct __Y_4 {
int  __a_5;
int  __a_6;
int  __b_7;
int  __b_8;
};

struct __X_0 ;// L1
struct __Y_4  __y_9;// L7:L15
int  __main_12 () {

{
{



int  (__a_10[( sizeof(int  )  +  sizeof(int  )  +  sizeof(int  ) ) - ( sizeof(int  )  +  sizeof(int  ) )]);// L19

int  (__a_11[( sizeof(int  )  +  sizeof(int  )  +  sizeof(int  ) ) - ( sizeof(int  )  +  sizeof(int  ) )]);// L19

return 0 ;// L20
}
}



}

