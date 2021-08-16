#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__apple_9", "apple");
__static_renaming("__main_10", "main");


};
enum __someLetters_7 {
__b_1,
__a_0,
__b_2,
__c_3,
__d_4,
__e_5,
__f_6,
};

enum __someLetters_7 ;// L1
int  __main_10 (void  ) {

{
{


union __forward_tag_reference_8 { // generated union of enum variations
};


union __forward_tag_reference_8  __apple_9;// L9

__static_type_error("type error : no valid expression"); // L10
return 0 ;// L12
}
}


}

