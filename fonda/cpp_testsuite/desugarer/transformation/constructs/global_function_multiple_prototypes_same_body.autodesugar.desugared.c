#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("___C_40496_0", "_C_40496");
__static_renaming("___C_40496_DEFINED_1", "_C_40496_DEFINED");
__static_renaming("___F0Awc8x_x_2", "_F0Awc8x_x");
__static_renaming("___F1fDwXV_main_3", "_F1fDwXV_main");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "(defined __cplusplus)");

if (__static_condition_default_7)
{
__static_parse_error("Unable to parse");
}
};

extern _Bool  ___C_40496_0;// L3:L33
extern _Bool  ___C_40496_DEFINED_1;// L4:L33
int  ___F0Awc8x_x_2 () {

{
{



if ( 1 )// L7
{

{
{




{
{



if ( 1 )// L8
{

{
{



return 1 ;// L9
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
int  ___F1fDwXV_main_3 () {

{
{



if ( 1 )// L17
{

{
{




{
{



if ( 1 )// L18
{

{
{



 ___F0Awc8x_x_2 ( ) ; // L19
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
int  __main_6 (int  __argc_4, char  (* (* __argv_5))) {

{
{



if ( 1 )// L26
{

{
{



__static_type_error("type error : no valid expression"); // L27
}
}
}
}
}



}

