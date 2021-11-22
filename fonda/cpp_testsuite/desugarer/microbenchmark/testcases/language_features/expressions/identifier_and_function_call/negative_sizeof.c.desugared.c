#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_12;
extern const bool __static_condition_default_13;
void __static_initializer_default() {
__static_renaming("__y_8", "y");
__static_renaming("__a_9", "a");
__static_renaming("__a_10", "a");
__static_renaming("__main_11", "main");

__static_condition_renaming("__static_condition_default_12", "(defined A)");
__static_condition_renaming("__static_condition_default_13", "!(defined A)");

};
struct __X_0 {
int  __a_1;// L2
int  __b_2;// L3
int  __c_3;// L4
};
struct __Y_4 {
int  __a_5;// L9
int  __b_6;// L10
int  __a_7;// L12
};

struct __X_0 ;// L1
struct __Y_4  __y_8;// L7:L14
int  (__main_11) () {

{
{



int  __a_9[( sizeof(int  )  +  sizeof(int  )  +  sizeof(int  ) ) - ( sizeof(int  )  +  sizeof(int  ) )];// L18

int  __a_10[( sizeof(int  )  +  sizeof(int  )  +  sizeof(int  ) ) - ( sizeof(int  ) )];// L18

if (__static_condition_default_12) {
return ( sizeof(int  )  +  sizeof(int  )  +  sizeof(int  ) ) - ( sizeof(int  )  +  sizeof(int  ) ) ;// L19
}
if (__static_condition_default_13) {
return ( sizeof(int  )  +  sizeof(int  )  +  sizeof(int  ) ) - ( sizeof(int  ) ) ;// L19
}
}
}


}


int main () {
  return __main_11();
}
