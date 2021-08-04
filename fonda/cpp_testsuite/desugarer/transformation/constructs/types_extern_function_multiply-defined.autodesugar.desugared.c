#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("___C_40496_0", "_C_40496");
__static_renaming("___C_40496_DEFINED_1", "_C_40496_DEFINED");
__static_renaming("___V0y6ixj_x_2", "_V0y6ixj_x");
__static_renaming("___V1Imfho_x_3", "_V1Imfho_x");
__static_renaming("___F2UnsOl_main_4", "_F2UnsOl_main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_5", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_6", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_7", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_11", "(defined __cplusplus)");

if (__static_condition_default_11)
{
__static_parse_error("Unable to parse");
}
};

extern _Bool  ___C_40496_0;// L3:L33
extern _Bool  ___C_40496_DEFINED_1;// L4:L33
extern int  ___V0y6ixj_x_2 ();// L6
extern float  ___V1Imfho_x_3 (int  );// L8
int  ___F2UnsOl_main_4 () {

{



if ( 1 )// L11

{




{



if (__static_condition_default_5) {
if (  ___C_40496_DEFINED_1  )// L12

{



 ___V0y6ixj_x_2 ( ) ; // L13
}
}
if (__static_condition_default_6) {
__static_type_error("invalid type found in if statement");
}
if (__static_condition_default_5) {
if ( !  ___C_40496_DEFINED_1  )// L15

{



__static_type_error("type error : no valid expression"); // L16
}
}
if (__static_condition_default_7) {
__static_type_error("invalid type found in if statement");
}
}
}
}



}
int  __main_10 (int  __argc_8, char  (* (* __argv_9))) {

{



if ( 1 )// L23

{



__static_type_error("type error : no valid expression"); // L24
}
}



}

