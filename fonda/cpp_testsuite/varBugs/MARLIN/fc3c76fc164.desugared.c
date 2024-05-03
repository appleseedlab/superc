#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_9;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__thermal_runaway_4", "thermal_runaway");
__static_renaming("__thermal_runaway_state_machine_5", "thermal_runaway_state_machine");
__static_renaming("__thermal_runaway_timer_6", "thermal_runaway_timer");
__static_renaming("__main_7", "main");

__static_condition_renaming("__static_condition_default_8", "!HAS_BED_THERMAL_PROTECTION");
__static_condition_renaming("__static_condition_default_9", "HAS_BED_THERMAL_PROTECTION");

if (__static_condition_default_9) {
__static_parse_error("Unable to parse");
}
};
enum __TRState_3 {
__TRInactive_0,
__TRFirstHeating_1,
__TRStable_2,
};

enum __TRState_3 ;// L4
static _Bool  __thermal_runaway_4= 0;// L5:L33
enum __TRState_3  __thermal_runaway_state_machine_5[4]=  {  __TRInactive_0  ,   __TRInactive_0  ,   __TRInactive_0  ,   __TRInactive_0  };// L7
static unsigned long  __thermal_runaway_timer_6[4];// L8
int  (__main_7) (void  ) {

if (__static_condition_default_8) {

{// L17
{



return 0 ;// L18
}
}// L19


}
}

