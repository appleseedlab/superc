#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_4", "main");


};

int  __main_4 () {

{
{

union ____anonymous_tag_0_1 {
int  __a_2;
long  __b_3;
};


( ( union ____anonymous_tag_0_1   ) { .__a_2 = 2 } ) . __b_3 ; // L2
return 0 ;// L3
}
}


}

