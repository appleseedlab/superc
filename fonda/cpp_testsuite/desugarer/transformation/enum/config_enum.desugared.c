#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__apple_11", "apple");
__static_renaming("__main_12", "main");


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

enum someLetters ;
enum someLetters ;
int  __main_12 (void  ) {
{
enum someLetters  __apple_11;
__static_type_error("type error : no valid expression");

return 0 ;

}


}

