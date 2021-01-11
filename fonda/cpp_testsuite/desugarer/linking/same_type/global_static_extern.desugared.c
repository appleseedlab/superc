#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__f_1", "f");
__static_renaming("__f_4", "f");
__static_renaming("__f_7", "f");

__static_condition_renaming("__static_condition_default_2", "(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_A)|)");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun CONFIG_B () Bool)(assert (not |(defined CONFIG_A)|))(assert CONFIG_B)");
__static_condition_renaming("__static_condition_default_8", "(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun CONFIG_B () Bool)(assert |(defined CONFIG_A)|)(assert (or |(defined CONFIG_A)| (and (not |(defined CONFIG_A)|) CONFIG_B)))");
__static_condition_renaming("__static_condition_default_9", "(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun CONFIG_B () Bool)(assert (not |(defined CONFIG_A)|))(assert CONFIG_B)(assert (or |(defined CONFIG_A)| (and (not |(defined CONFIG_A)|) CONFIG_B)))");

};

extern int  __f_7 (int  __x_6);
int  __f_1 (int  __x_0) {

{
if (__static_condition_default_8) {
{

if (__static_condition_default_2) {
return  __x_0  + 1 ;

}
}

}

}
}
static int  __f_4 (int  __x_3) {

{
if (__static_condition_default_9) {
{

if (__static_condition_default_5) {
return  __x_3  + 1 ;

}
}

}

}
}
extern int  __f_7 (int  __x_6);
int  __f_1 (int  __x_0) {

{
if (__static_condition_default_8) {
{

if (__static_condition_default_2) {
return  __x_0  + 1 ;

}
}

}

}
}
static int  __f_4 (int  __x_3) {

{
if (__static_condition_default_9) {
{

if (__static_condition_default_5) {
return  __x_3  + 1 ;

}
}

}

}
}

