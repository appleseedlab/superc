#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_16;
extern const bool __static_condition_default_17;
void __static_initializer_default() {
__static_renaming("__apple_13", "apple");
__static_renaming("__apple_14", "apple");
__static_renaming("__main_15", "main");

__static_condition_renaming("__static_condition_default_16", "APPLE");
__static_condition_renaming("__static_condition_default_17", "!APPLE");

};
enum __someLetters_6 {
__a_0,
__b_1,
__c_2,
__d_3,
__e_4,
__f_5,
};
enum __someLetters_12 {
__b_7,
__c_8,
__d_9,
__e_10,
__f_11,
};

enum __someLetters_6 ;// L2
enum __someLetters_12 ;// L7
int  __main_15 (void  ) {

{
{



enum __someLetters_6  __apple_13;// L13

enum __someLetters_12  __apple_14;// L13

if (__static_condition_default_16) {
 __apple_13  =  __a_0  ; // L14
}
if (__static_condition_default_17) {
__static_type_error("type error") ; // L14
}
return 0 ;// L16
}
}


}

