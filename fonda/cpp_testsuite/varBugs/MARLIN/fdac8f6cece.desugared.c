#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__zprobe_zoffset_0", "zprobe_zoffset");
__static_renaming("__Config_ResetDefault_1", "Config_ResetDefault");
__static_renaming("__main_4", "main");


};

float  __zprobe_zoffset_0;// L5
void  (__Config_ResetDefault_1) () {

{
{



 __zprobe_zoffset_0  = - 7 ; // L2:L9
}
}


}
int  (__main_4) (int  __argc_2, char  * (* (__argv_3))) {

{
{



 __Config_ResetDefault_1 ( ) ; // L15
return 0 ;// L16
}
}


}

