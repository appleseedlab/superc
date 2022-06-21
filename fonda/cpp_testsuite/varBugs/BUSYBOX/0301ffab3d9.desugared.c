#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__gdp_0", "gdp");
__static_renaming("__ext2fs_open2_1", "ext2fs_open2");
__static_renaming("__ext2fs_open_2", "ext2fs_open");
__static_renaming("__main_5", "main");


};

void  (__ext2fs_open2_1) (void  ) {

{
{



char  * (__gdp_0);// L4

}
}


}
void  (__ext2fs_open_2) (void  ) {

{
{



 __ext2fs_open2_1 ( ) ; // L17
}
}


}
int  (__main_5) (int  __argc_3, char  * (* (__argv_4))) {

{
{



 __ext2fs_open_2 ( ) ; // L22
return 0 ;// L23
}
}


}

