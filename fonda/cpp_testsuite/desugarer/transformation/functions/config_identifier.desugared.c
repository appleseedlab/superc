#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__add_5", "add");
__static_renaming("__adder_6", "adder");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_3", "A");
__static_condition_renaming("__static_condition_default_4", "!A");
__static_condition_renaming("__static_condition_default_7", "!A");

};

int  __add_5 (int  __a_0, int  __b_2) {

if (__static_condition_default_3) {
{

{
if (__static_condition_default_3) {
return  __a_0  +  __b_2  ;

}

if (__static_condition_default_4) {
return  __a_1  +  __b_2  ;

}

}}

}

}
int  __adder_6 (int  __a_1, int  __b_2) {

if (__static_condition_default_7) {
{

{
if (__static_condition_default_3) {
return  __a_0  +  __b_2  ;

}

if (__static_condition_default_4) {
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

