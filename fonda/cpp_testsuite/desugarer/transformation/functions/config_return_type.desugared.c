#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_1;
extern const bool __static_condition_default_0;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__main_2", "main");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_0", "A");
__static_condition_renaming("__static_condition_default_1", "!A");
__static_condition_renaming("__static_condition_default_4", "A");
__static_condition_renaming("__static_condition_default_5", "!A");

};

int  __main_2 (void  ) {

if (__static_condition_default_4) {
{

{
if (__static_condition_default_0) {
return 0 ;

}

if (__static_condition_default_1) {
return  ;

}

}}

}

}
void  __main_3 (void  ) {

if (__static_condition_default_5) {
{

{
if (__static_condition_default_0) {
return 0 ;

}

if (__static_condition_default_1) {
return  ;

}

}}

}

}

