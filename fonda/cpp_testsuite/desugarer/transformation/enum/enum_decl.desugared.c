#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_6", "main");
__static_renaming("__apple_7", "apple");


};
enum letter {
__a_0,
__b_1,
__c_2,
__d_3,
__e_4,
__f_5,
};

enum letter ;
int  __main_6 (void  ) {
{
enum letter  __apple_7;
__static_type_error("type error");

return 0 ;

}


}

