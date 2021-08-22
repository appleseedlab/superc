#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_17;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_19;
void __static_initializer_default() {
__static_renaming("__z_12", "z");
__static_renaming("__main_13", "main");

__static_condition_renaming("__static_condition_default_14", "(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_15", "!(defined A) && !(defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_16", "(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_17", "!(defined A) && (defined B) && (defined C)");
__static_condition_renaming("__static_condition_default_18", "(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_19", "!(defined A) && !(defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_20", "(defined A) && (defined B) && !(defined C)");
__static_condition_renaming("__static_condition_default_21", "!(defined A) && (defined B) && !(defined C)");

};
struct __one_0 {
int  __a_1;// L4
};
struct __one_2 {
int  __a_3;// L4
int  __b_4;// L7
};
struct __two_5 {
int  __a_6;// L14
long long  __c_7;// L17
int  __b_8;// L15
unsigned long long  __d_9;// L18
struct __one_0  __x_10;// L20
struct __one_2  __x_11;// L20
};

struct __one_0 ;// L1
struct __one_2 ;// L1
struct __two_5 ;// L11
int  (__main_13) () {

{
{



int  __z_12;// L25

if (__static_condition_default_14) {
 __z_12  = ( sizeof(int  )  +  sizeof(int  )  +  ( sizeof(int  ) ) ) ; // L26
}
if (__static_condition_default_15) {
 __z_12  = ( sizeof(int  )  +  sizeof(int  )  +  ( 0 ) ) ; // L26
}
if (__static_condition_default_16) {
 __z_12  = ( sizeof(int  )  +  sizeof(int  )  +  ( sizeof(int  )  +  sizeof(int  ) ) ) ; // L26
}
if (__static_condition_default_17) {
 __z_12  = ( sizeof(int  )  +  sizeof(int  )  +  ( sizeof(int  ) ) ) ; // L26
}
if (__static_condition_default_18) {
 __z_12  = ( sizeof(long long  )  +  sizeof(unsigned long long  )  +  ( sizeof(int  ) ) ) ; // L26
}
if (__static_condition_default_19) {
 __z_12  = ( sizeof(long long  )  +  sizeof(unsigned long long  )  +  ( 0 ) ) ; // L26
}
if (__static_condition_default_20) {
 __z_12  = ( sizeof(long long  )  +  sizeof(unsigned long long  )  +  ( sizeof(int  )  +  sizeof(int  ) ) ) ; // L26
}
if (__static_condition_default_21) {
 __z_12  = ( sizeof(long long  )  +  sizeof(unsigned long long  )  +  ( sizeof(int  ) ) ) ; // L26
}
return 0 ;// L27
}
}


}

