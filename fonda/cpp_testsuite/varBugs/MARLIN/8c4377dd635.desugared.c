#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__pid_output_0", "pid_output");
__static_renaming("__e_1", "e");
__static_renaming("__manage_heater_2", "manage_heater");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_3", "(defined PIDTEMP) && !(defined PID_DEBUG)");
__static_condition_renaming("__static_condition_default_4", "!(defined PIDTEMP) || (defined PIDTEMP) && (defined PID_DEBUG)");
__static_condition_renaming("__static_condition_default_5", "!(defined PIDTEMP)");
__static_condition_renaming("__static_condition_default_6", "(defined PIDTEMP) && (defined PID_DEBUG)");

};

void  (__manage_heater_2) () {

{
if (__static_condition_default_3) {

{
{



float  __pid_output_0= 1;// L11

int  __e_1= 0;// L12

}
}


}

if (__static_condition_default_4) {

{
{



float  __pid_output_0= 1;// L11

int  __e_1= 0;// L12

if (__static_condition_default_5) {
 __pid_output_0  = 0 ; // L19
}
if (__static_condition_default_6) {
__static_type_error("type error : no valid expression"); // L16
}
}
}


}

}}
int  (__main_9) (int  __argc_7, char  * (* (__argv_8))) {

{
{



 __manage_heater_2 ( ) ; // L26
return 0 ;// L27
}
}


}

