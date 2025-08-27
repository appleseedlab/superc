#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__gdp_0", "gdp");
__static_renaming("__j_1", "j");
__static_renaming("__ext2fs_open2_2", "ext2fs_open2");
__static_renaming("__ext2fs_open_5", "ext2fs_open");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined EXT2FS_ENABLE_SWAPFS)");
__static_condition_renaming("__static_condition_default_4", "(defined EXT2FS_ENABLE_SWAPFS)");

};

void  (__ext2fs_open2_2) (void  ) {

{
if (__static_condition_default_3) {

{// L3
{



char  * (__gdp_0);// L4

}
}// L13


}

if (__static_condition_default_4) {

{// L3
{



char  * (__gdp_0);// L4

 __gdp_0  = "group_desc" ; // L7
{ int  __j_1= 0;// L8
 for ( ;  __j_1  < 10 ;  __j_1  ++ ) // L8
{

{// L9
{



__static_type_error("type error : no valid expression"); // L10
}
}// L11
}
}
}
}// L13


}

}}
void  (__ext2fs_open_5) (void  ) {

{// L16
{



 __ext2fs_open2_2 ( ) ; // L17
}
}// L18


}
int  (__main_8) (int  __argc_6, char  * (* (__argv_7))) {

{// L21
{



 __ext2fs_open_5 ( ) ; // L22
return 0 ;// L23
}
}// L24


}

