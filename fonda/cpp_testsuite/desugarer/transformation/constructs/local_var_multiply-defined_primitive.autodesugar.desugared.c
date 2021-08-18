#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_13;
void __static_initializer_default() {
__static_renaming("___C_n1583398147_0", "_C_n1583398147");
__static_renaming("___C_n1583398147_DEFINED_1", "_C_n1583398147_DEFINED");
__static_renaming("___V1GQ30P_x_2", "_V1GQ30P_x");
__static_renaming("___V25ZLJX_x_3", "_V25ZLJX_x");
__static_renaming("___F0cClHB_main_4", "_F0cClHB_main");
__static_renaming("__main_12", "main");

__static_condition_renaming("__static_condition_default_5", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_6", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_7", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_8", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_9", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_13", "(defined __cplusplus)");

if (__static_condition_default_13)
{
__static_parse_error("Unable to parse");
}
};

extern _Bool  ___C_n1583398147_0;// L3:L33
extern _Bool  ___C_n1583398147_DEFINED_1;// L4:L33
int  ___F0cClHB_main_4 () {

{
{



if ( 1 )// L7
{

{
{




{
{



int  ___V1GQ30P_x_2;// L9

char  ___V25ZLJX_x_3;// L11

if (__static_condition_default_5) {
if (  ___C_n1583398147_DEFINED_1  )// L12
{

{
{



 ___V1GQ30P_x_2  ++ ; // L13
}
}
}
}
if (__static_condition_default_6) {
__static_type_error("invalid type found in if statement");
}
if (__static_condition_default_5) {
if ( !  ___C_n1583398147_DEFINED_1  )// L15
{

{
{



 ___V25ZLJX_x_3  ++ ; // L16
}
}
}
}
if (__static_condition_default_7) {
__static_type_error("invalid type found in if statement");
}
if (__static_condition_default_5) {
if (  ___C_n1583398147_DEFINED_1  )// L18
{

{
{



return  ___V1GQ30P_x_2  ;// L19
}
}
}
}
if (__static_condition_default_8) {
__static_type_error("invalid type found in if statement");
}
if (__static_condition_default_5) {
if ( !  ___C_n1583398147_DEFINED_1  )// L21
{

{
{



return  ___V25ZLJX_x_3  ;// L22
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
int  __main_12 (int  __argc_10, char  (* ((* (__argv_11))))) {

{
{



if ( 1 )// L29
{

{
{



__static_type_error("type error : no valid expression"); // L30
}
}
}
}
}


}

