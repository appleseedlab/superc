#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__letter_6", "letter");
__static_renaming("__apple_7", "apple");
__static_renaming("__main_8", "main");


};
enum letter {
__a_0,
__b_1,
__c_2,
__d_3,
__e_4,
__f_5,
};
typedef enum letter  __letter_6;

 // typedef moved to top of scope
 int  __main_8 (void  ) {

{



__letter_6  __apple_7;

 __apple_7  =  __a_0  ;
return 0 ;
}



}

