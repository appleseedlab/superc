#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_9;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("___C_40496_0", "_C_40496");
__static_renaming("___C_40496_DEFINED_1", "_C_40496_DEFINED");
__static_renaming("___V2n3sqb_var_4", "_V2n3sqb_var");
__static_renaming("___V3nkcU9_var_5", "_V3nkcU9_var");
__static_renaming("___F1K4sj1_main_6", "_F1K4sj1_main");
__static_renaming("__main_12", "main");

__static_condition_renaming("__static_condition_default_7", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_8", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_9", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_13", "(defined __cplusplus)");

if (__static_condition_default_13)
{
__static_parse_error("Unable to parse");
}
};
struct __test_2 {
int  __x_3;// L6
};

extern _Bool  ___C_40496_0;// L3:L33
extern _Bool  ___C_40496_DEFINED_1;// L4:L33
struct __test_2 ;// L6
int  ___F1K4sj1_main_6 () {

{
{



if ( 1 )// L9
{

{
{




{
{



struct __test_2  ___V2n3sqb_var_4;// L11

int  ___V3nkcU9_var_5;// L13

if (__static_condition_default_7) {
if (  ___C_40496_DEFINED_1  )// L14
{

{
{



 ___V2n3sqb_var_4  . __x_3 = 1 ; // L15
}
}
}
}
if (__static_condition_default_8) {
__static_type_error("invalid type found in if statement");
}
if (__static_condition_default_7) {
if ( !  ___C_40496_DEFINED_1  )// L17
{

{
{



__static_type_error("type error : no valid expression"); // L18
}
}
}
}
if (__static_condition_default_9) {
__static_type_error("invalid type found in if statement");
}
}
}
}
}
}
}
}


}
int  __main_12 (int  __argc_10, char  (* (* __argv_11))) {

{
{



if ( 1 )// L25
{

{
{



__static_type_error("type error : no valid expression"); // L26
}
}
}
}
}


}

