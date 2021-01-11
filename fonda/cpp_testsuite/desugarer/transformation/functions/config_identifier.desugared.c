#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__add_3", "add");
__static_renaming("__adder_4", "adder");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_5", "(declare-fun A () Bool)(assert A)");
__static_condition_renaming("__static_condition_default_6", "(declare-fun A () Bool)(assert (not A))");
__static_condition_renaming("__static_condition_default_7", "(declare-fun A () Bool)(assert (not A))");

};

int  __add_3 (int  __a_0, int  __b_2) {

if (__static_condition_default_5) {
{

{
if (__static_condition_default_5) {
return  __a_0  +  __b_2  ;

}

if (__static_condition_default_6) {
return  __a_1  +  __b_2  ;

}

}}

}

}
int  __adder_4 (int  __a_1, int  __b_2) {

if (__static_condition_default_7) {
{

{
if (__static_condition_default_5) {
return  __a_0  +  __b_2  ;

}

if (__static_condition_default_6) {
return  __a_1  +  __b_2  ;

}

}}

}

}
int  __main_8 (void  ) {
{
return 0 ;

}


}

