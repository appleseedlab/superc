#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_24;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_25;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_26;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__z_21", "z");
__static_renaming("__main_22", "main");

__static_condition_renaming("__static_condition_default_10", "!(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_11", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_20", "!(defined A)");
__static_condition_renaming("__static_condition_default_23", "(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_24", "(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_25", "(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_26", "(defined A) && (defined B) && !(defined C)");

};
typedef int  __a_0;// L2
struct __one_3 {
__a_0  __a_4;
};
struct __one_6 {
__a_0  __a_7;
int  __b_9;
};
struct __two_12 {
int  __a_13;
long long  __c_14;
int  __b_15;
unsigned long long  __d_16;
struct __one_3  __x_17;
struct __one_6  __x_18;
};

// typedef moved to top of scope
int  __x_1;// L4
int  __x_2;// L4
struct __one_3 ;// L5
struct __one_6 ;// L5

struct __two_12 ;// L13

int  __main_22 () {

{



int  __z_21;// L27

if (__static_condition_default_23) {
 __z_21  = ( sizeof(int  )  +  sizeof(int  )  +  ( sizeof(__a_0  ) ) ) ; // L28
}
if (__static_condition_default_24) {
 __z_21  = ( sizeof(int  )  +  sizeof(int  )  +  ( sizeof(__a_0  )  +  sizeof(int  ) ) ) ; // L28
}
if (__static_condition_default_25) {
 __z_21  = ( sizeof(long long  )  +  sizeof(unsigned long long  )  +  ( sizeof(__a_0  ) ) ) ; // L28
}
if (__static_condition_default_26) {
 __z_21  = ( sizeof(long long  )  +  sizeof(unsigned long long  )  +  ( sizeof(__a_0  )  +  sizeof(int  ) ) ) ; // L28
}
if (__static_condition_default_20) {
__static_type_error("type error") ; // L28
}
return 0 ;// L29
}



}

