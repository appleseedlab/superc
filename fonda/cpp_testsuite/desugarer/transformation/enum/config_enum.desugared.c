#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_13;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("__apple_11", "apple");
__static_renaming("__main_12", "main");

__static_condition_renaming("__static_condition_default_13", "APPLE");
__static_condition_renaming("__static_condition_default_14", "!APPLE");

};
enum someLetters {
__a_0,
__b_1,
__c_2,
__d_3,
__e_4,
__f_5,
__b_6,
__c_7,
__d_8,
__e_9,
__f_10,
};

enum someLetters ;// L2
enum someLetters ;// L7
int  __main_12 (void  ) {

{
{



enum someLetters  __apple_11;// L13

if (__static_condition_default_13) {
 __apple_11  =  __a_0  ; // L14
}
if (__static_condition_default_14) {
__static_type_error("type error") ; // L14
}
return 0 ;// L16
}
}


}

