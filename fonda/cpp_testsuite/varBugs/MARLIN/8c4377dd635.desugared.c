#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_15;
void __static_initializer_default() {
__static_renaming("__echomagic_0", "echomagic");
__static_renaming("__serialprint_2", "serialprint");
__static_renaming("__pid_output_4", "pid_output");
__static_renaming("__e_5", "e");
__static_renaming("__manage_heater_6", "manage_heater");
__static_renaming("__manage_heater_7", "manage_heater");
__static_renaming("__main_18", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined MARLIN_H)");
__static_condition_renaming("__static_condition_default_8", "(defined MARLIN_H) && (defined PIDTEMP) && !(defined PID_DEBUG)");
__static_condition_renaming("__static_condition_default_9", "(defined MARLIN_H) && !(defined PIDTEMP) || (defined MARLIN_H) && (defined PIDTEMP) && (defined PID_DEBUG)");
__static_condition_renaming("__static_condition_default_10", "(defined MARLIN_H) && !(defined PIDTEMP)");
__static_condition_renaming("__static_condition_default_11", "(defined MARLIN_H) && (defined PIDTEMP) && (defined PID_DEBUG)");
__static_condition_renaming("__static_condition_default_12", "!(defined MARLIN_H) && (defined PIDTEMP) && !(defined PID_DEBUG)");
__static_condition_renaming("__static_condition_default_13", "!(defined MARLIN_H) && !(defined PIDTEMP) || !(defined MARLIN_H) && (defined PIDTEMP) && (defined PID_DEBUG)");
__static_condition_renaming("__static_condition_default_14", "!(defined MARLIN_H) && !(defined PIDTEMP)");
__static_condition_renaming("__static_condition_default_15", "!(defined MARLIN_H) && (defined PIDTEMP) && (defined PID_DEBUG)");
__static_condition_renaming("__static_condition_default_19", "(defined MARLIN_H)");
__static_condition_renaming("__static_condition_default_20", "!(defined MARLIN_H)");

};
const char  __echomagic_0[]= "echo:";// L2


void  (__serialprint_2) (const char  * (__str_1)) {

if (__static_condition_default_3) {

{// L5
{



__static_type_error("type error : no valid expression"); // L6
}
}// L7


}
}
void  (__manage_heater_6) () {

{
if (__static_condition_default_8) {

{// L10
{



float  __pid_output_4= 1;// L11

int  __e_5= 0;// L12

}
}// L22


}

if (__static_condition_default_9) {

{// L10
{



float  __pid_output_4= 1;// L11

int  __e_5= 0;// L12

if (__static_condition_default_10) {
 __pid_output_4  = 0 ; // L19
}
if (__static_condition_default_11) {
__static_type_error("type error : no valid expression"); // L16
}
}
}// L22


}

}}
void  (__manage_heater_7) () {

{
if (__static_condition_default_12) {

{// L10
{



float  __pid_output_4= 1;// L11

int  __e_5= 0;// L12

}
}// L22


}

if (__static_condition_default_13) {

{// L10
{



float  __pid_output_4= 1;// L11

int  __e_5= 0;// L12

if (__static_condition_default_14) {
 __pid_output_4  = 0 ; // L19
}
if (__static_condition_default_15) {
__static_type_error("type error : no valid expression"); // L3:L16
}
}
}// L22


}

}}
int  (__main_18) (int  __argc_16, char  * (* (__argv_17))) {

{// L25
{



if (__static_condition_default_19) {
 __manage_heater_6 ( ) ; // L26
}
if (__static_condition_default_20) {
 __manage_heater_7 ( ) ; // L26
}
return 0 ;// L27
}
}// L28


}

