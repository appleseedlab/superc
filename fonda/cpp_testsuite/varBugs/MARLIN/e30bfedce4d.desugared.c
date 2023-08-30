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
__static_renaming("__left_probe_bed_position_0", "left_probe_bed_position");
__static_renaming("__xGridSpacing_1", "xGridSpacing");
__static_renaming("__process_commands_2", "process_commands");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined ENABLE_AUTO_BED_LEVELING)");
__static_condition_renaming("__static_condition_default_4", "(defined ENABLE_AUTO_BED_LEVELING)");

};

void  (__process_commands_2) () {

{
if (__static_condition_default_3) {

{// L18
{



}
}// L29


}

if (__static_condition_default_4) {

{// L18
{



int  __left_probe_bed_position_0= 15;// L21

int  __xGridSpacing_1=  __left_probe_bed_position_0 ;// L24

}
}// L29


}

}}
int  (__main_7) (int  __argc_5, char  * (* (__argv_6))) {

{// L32
{



 __process_commands_2 ( ) ; // L33
return 0 ;// L34
}
}// L35


}

