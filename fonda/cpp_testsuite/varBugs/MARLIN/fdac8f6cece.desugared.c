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
__static_renaming("__zprobe_zoffset_0", "zprobe_zoffset");
__static_renaming("__Config_ResetDefault_1", "Config_ResetDefault");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_2", "(defined ENABLE_AUTO_BED_LEVELING)");
__static_condition_renaming("__static_condition_default_3", "!(defined ENABLE_AUTO_BED_LEVELING)");

};

float  __zprobe_zoffset_0;// L5
void  (__Config_ResetDefault_1) () {

{// L8
{



if (__static_condition_default_2) {
 __zprobe_zoffset_0  = - 7 ; // L2:L9
}
if (__static_condition_default_3) {
__static_type_error("type error : no valid expression"); // L9
}
}
}// L10


}
int  (__main_6) (int  __argc_4, char  * (* (__argv_5))) {

{// L13
{



 __Config_ResetDefault_1 ( ) ; // L15
return 0 ;// L16
}
}// L17


}

