#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__ptr_to_globals_1", "ptr_to_globals");
__static_renaming("__main_7", "main");


};
extern const struct __forward_tag_reference_0  * (__ptr_to_globals_1);// L2
enum ____anonymous_tag_3_4 {
__TEST_BUFFER_BLOCKS_2 = 16,
};
struct __globals_5 {
char  __check_blocks_buffer_6[ __TEST_BUFFER_BLOCKS_2 ];// L8
};

struct __forward_tag_reference_0 { // generated union of struct variations
union {
struct __globals_5 __globals_5;
};
};


enum ____anonymous_tag_3_4 ;// L3
struct __globals_5 ;// L7
int  (__main_7) () {

{
{



( * ( struct __globals_5  * (*) ) &  __ptr_to_globals_1  ) = ( void  * ) ( 0 ) ; // L12
return 0 ;// L13
}
}


}

