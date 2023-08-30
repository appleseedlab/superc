#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__do_page_fault_0", "do_page_fault");
__static_renaming("__do_sect_fault_1", "do_sect_fault");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined CONFIG_ARM_LPAE)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_ARM_LPAE)");

};

static int  (__do_page_fault_0) () {

{// L2
{



return 0 ;// L3
}
}// L4


}
static int  (__do_sect_fault_1) () {

{// L7
{



return 0 ;// L8
}
}// L9


}
int  (__main_2) () {

{// L12
{



if (__static_condition_default_3) {
 __do_page_fault_0 ( ) ; // L16
}
if (__static_condition_default_4) {
 __do_page_fault_0 ( ) ; // L14
}
if (__static_condition_default_3) {
 __do_sect_fault_1 ( ) ; // L17
}
return 0 ;// L19
}
}// L20


}

