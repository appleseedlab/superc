#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_35;
extern const bool __static_condition_default_36;
extern const bool __static_condition_default_37;
extern const bool __static_condition_default_34;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__x_1", "x");
__static_renaming("__z_14", "z");
__static_renaming("__main_33", "main");

__static_condition_renaming("__static_condition_default_34", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_35", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_36", "!(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_37", "(defined A) && !(defined B)");

};
typedef int  __a_0;// L1
struct __one_2 {
__a_0  __a_3;// L0
};
struct __one_4 {
__a_0  __a_5;// L0
int  __b_6;// L8
};
struct __two_7 {
int  __a_8;// L15
long long  __c_9;// L18
int  __b_10;// L16
unsigned long long  __d_11;// L19
struct __one_2  __x_12;// L21
struct __one_4  __x_13;// L21
};

// typedef moved to top of scope
int  __x_1;// L2
struct __one_2 ;// L4
struct __one_4 ;// L4
struct __two_7 ;// L12
int  (__main_33) () {

{
{



int  __z_14;// L26

if (__static_condition_default_34) {
 __z_14  = sizeof( struct { int  __tmp_15; int  __tmp_16; struct { __a_0  __tmp_17; } __tmp_18; } ) ; // L27
}
if (__static_condition_default_35) {
 __z_14  = sizeof( struct { int  __tmp_19; int  __tmp_20; struct { __a_0  __tmp_21; int  __tmp_22; } __tmp_23; } ) ; // L27
}
if (__static_condition_default_36) {
 __z_14  = sizeof( struct { long long  __tmp_24; unsigned long long  __tmp_25; struct { __a_0  __tmp_26; } __tmp_27; } ) ; // L27
}
if (__static_condition_default_37) {
 __z_14  = sizeof( struct { long long  __tmp_28; unsigned long long  __tmp_29; struct { __a_0  __tmp_30; int  __tmp_31; } __tmp_32; } ) ; // L27
}
return  __z_14  ;// L28
}
}


}

int main () {
  return __main_33();
}
