#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__apple_7", "apple");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_9", "APPLE");
__static_condition_renaming("__static_condition_default_10", "!APPLE");

};
enum someLetters {
__b_1,
__a_0,
__b_2,
__c_3,
__d_4,
__e_5,
__f_6,
};

enum someLetters ;// L1
int  __main_8 (void  ) {

{
{



enum letter  __apple_7;// L9

if (__static_condition_default_9) {
 __apple_7  =  __a_0  ; // L10
}
if (__static_condition_default_10) {
__static_type_error("type error") ; // L10
}
return 0 ;// L12
}
}



}

