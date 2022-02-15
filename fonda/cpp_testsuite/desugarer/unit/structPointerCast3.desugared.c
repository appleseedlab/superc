#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__TEST_BUFFER_BLOCKS_0", "TEST_BUFFER_BLOCKS");
__static_renaming("__TEST_BUFFER_BLOCKS_1", "TEST_BUFFER_BLOCKS");
__static_renaming("__xx_2", "xx");
__static_renaming("__ptr_to_globals_4", "ptr_to_globals");
__static_renaming("__main_9", "main");

__static_condition_renaming("__static_condition_default_8", "!(defined A)");
__static_condition_renaming("__static_condition_default_10", "(defined A)");

};
const int  __TEST_BUFFER_BLOCKS_0= 16;// L3


int  __TEST_BUFFER_BLOCKS_1= 10;// L5
int  __xx_2;// L7
int  (__main_9) () {

{
{

struct __globals_5 {
char  __check_blocks_buffer_6[ __TEST_BUFFER_BLOCKS_0 ];// L11
};

struct __forward_tag_reference_3 { // generated union of struct variations
union {
struct __globals_5 __globals_5;
};
};


const struct __forward_tag_reference_3  * (__ptr_to_globals_4);// L9

if (__static_condition_default_8) {
__static_type_error("invalid declaration of struct: TODO_struct_tag4");
}// L0


struct __globals_5 ;// L10

if (__static_condition_default_10) {
( * ( struct __globals_5  * (*) ) &  __ptr_to_globals_4  ) = ( void  * ) ( 0 ) ; // L13
}
if (__static_condition_default_8) {
__static_type_error("type error") ; // L13
}
return 0 ;// L14
}
}


}

