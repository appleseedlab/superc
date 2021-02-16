#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__adder_2", "adder");
__static_renaming("__main_3", "main");


};

int  __adder_2 (int  __a_0, int  __b_1) {
{
return  __a_0  +  __b_1  ;

}


}
int  __main_3 (void  ) {
{
return 0 ;

}


}

