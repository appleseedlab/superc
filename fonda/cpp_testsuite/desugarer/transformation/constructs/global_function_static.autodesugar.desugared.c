#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_13;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("___C_40496_0", "_C_40496");
__static_renaming("___C_40496_DEFINED_1", "_C_40496_DEFINED");
__static_renaming("___F01FqLq_x_2", "_F01FqLq_x");
__static_renaming("___F1d6hXF_x_5", "_F1d6hXF_x");
__static_renaming("___F2UMx8F_main_7", "_F2UMx8F_main");
__static_renaming("__main_12", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_4", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_6", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_8", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_9", "(defined __cplusplus)");
__static_condition_renaming("__static_condition_default_13", "(defined __cplusplus)");

if (__static_condition_default_13)
{
__static_parse_error("Unable to parse");
}
};

extern _Bool  ___C_40496_0;// L3:L33
extern _Bool  ___C_40496_DEFINED_1;// L4:L33
static int  ___F01FqLq_x_2 () {

{
{



if (__static_condition_default_3) {
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
if (__static_condition_default_4) {
__static_type_error("invalid type found in if statement");
}
}
}



}
static char  ___F1d6hXF_x_5 () {

{
{



if (__static_condition_default_3) {
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
if (__static_condition_default_6) {
__static_type_error("invalid type found in if statement");
}
}
}



}
int  ___F2UMx8F_main_7 () {

{
{



if ( 1 )// L27
{

{
{




{
{



if (__static_condition_default_3) {
if (  ___C_40496_DEFINED_1  )// L28
{

{
{



 ___F01FqLq_x_2 ( ) ; // L29
}
}
}
}
if (__static_condition_default_8) {
__static_type_error("invalid type found in if statement");
}
if (__static_condition_default_3) {
if ( !  ___C_40496_DEFINED_1  )// L31
{

{
{



 ___F1d6hXF_x_5 ( ) ; // L32
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

