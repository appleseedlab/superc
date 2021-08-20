#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("___C_40496_0", "_C_40496");
__static_renaming("___C_40496_DEFINED_1", "_C_40496_DEFINED");
__static_renaming("___V03VpEz_x_2", "_V03VpEz_x");
__static_renaming("___F1KCEey_main_3", "_F1KCEey_main");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_8", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_9", "(defined __cplusplus)");

if (__static_condition_default_9)
{
__static_parse_error("Unable to parse");
}
};

extern _Bool  ___C_40496_0;// L3:L33
extern _Bool  ___C_40496_DEFINED_1;// L4:L33
extern int  ___V03VpEz_x_2;// L6
int  ___F1KCEey_main_3 () {

if (__static_condition_default_4) {

{
{



if ( 1 )// L9
{

{
{




{
{



if (  ___C_40496_DEFINED_1  )// L10
{

{
{



 ___V03VpEz_x_2  ++ ; // L11
}
}
}
}
}
}
}
}
}
}


}
}
int  __main_7 (int  __argc_5, char  (* ((* (__argv_6))))) {

if (__static_condition_default_8) {

{
{



if ( 1 )// L18
{

{
{



__static_type_error("type error : no valid expression"); // L19
}
}
}
}
}


}
}

