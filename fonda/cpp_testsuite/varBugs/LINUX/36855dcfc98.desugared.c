#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__wakeup_0", "wakeup");
__static_renaming("__bfin_pm_suspend_mem_enter_1", "bfin_pm_suspend_mem_enter");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_2", "!(defined CONFIG_BF60x)");
__static_condition_renaming("__static_condition_default_3", "(defined CONFIG_BF60x)");

};

int  (__bfin_pm_suspend_mem_enter_1) (void  ) {

{// L2
{



int  __wakeup_0;// L3

if (__static_condition_default_2) {
 __wakeup_0  = 0 ; // L6
}
if (__static_condition_default_3) {
return 0 ;// L9
}
if (__static_condition_default_2) {
return 0 ;// L9
}
}
}// L10


}
int  (__main_6) (int  __argc_4, char  * (* (__argv_5))) {

{// L13
{



 __bfin_pm_suspend_mem_enter_1 ( ) ; // L14
return 0 ;// L15
}
}// L16


}

