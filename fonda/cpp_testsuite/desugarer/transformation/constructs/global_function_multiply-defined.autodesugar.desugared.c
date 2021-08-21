#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_12;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("___C_40496_0", "_C_40496");
__static_renaming("___C_40496_DEFINED_1", "_C_40496_DEFINED");
__static_renaming("___F0iceH4_x_2", "_F0iceH4_x");
__static_renaming("___F1yFZOZ_x_4", "_F1yFZOZ_x");
__static_renaming("___F2JFFUV_main_6", "_F2JFFUV_main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_5", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_7", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_11", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_12", "(defined __cplusplus)");

if (__static_condition_default_12)
{
__static_parse_error("Unable to parse");
}
};

extern _Bool  ___C_40496_0;// L3:L33
extern _Bool  ___C_40496_DEFINED_1;// L4:L33
int  (___F0iceH4_x_2) () {

if (__static_condition_default_3) {

{
{



if (  ___C_40496_DEFINED_1  )// L7
{

{
{




{
{



if (  ___C_40496_DEFINED_1  )// L8
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
}
char  (___F1yFZOZ_x_4) () {

if (__static_condition_default_5) {

{
{



if ( !  ___C_40496_DEFINED_1  )// L17
{

{
{




{
{



if ( !  ___C_40496_DEFINED_1  )// L18
{

{
{



return 2 ;// L19
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
int  (___F2JFFUV_main_6) () {

if (__static_condition_default_7) {

{
{



if ( 1 )// L27
{

{
{




{
{



if (  ___C_40496_DEFINED_1  )// L28
{

{
{



 ___F0iceH4_x_2 ( ) ; // L29
}
}
}
if ( !  ___C_40496_DEFINED_1  )// L31
{

{
{



 ___F1yFZOZ_x_4 ( ) ; // L32
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
int  (__main_10) (int  __argc_8, char  * (* (__argv_9))) {

if (__static_condition_default_11) {

{
{



if ( 1 )// L39
{

{
{



__static_type_error("type error : no valid expression"); // L40
}
}
}
}
}


}
}

