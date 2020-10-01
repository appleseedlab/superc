#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_7();

extern const bool __static_condition_5;
extern const bool __static_condition_6;
void __static_initializer_7() {
__static_renaming("__imajor_0", "imajor");
__static_renaming("__iminor_1", "iminor");
__static_renaming("__main_2", "main");
__static_renaming("__i_3", "i");
__static_renaming("__inode_4", "inode");

__static_condition_renaming("__static_condition_5", "(not |(defined CONFIG_INPUT_MOUSEDEV_PSAUX)|)");
__static_condition_renaming("__static_condition_6", "|(defined CONFIG_INPUT_MOUSEDEV_PSAUX)|");

};
int  __main_2 ();

extern int  __imajor_0 (int  );
extern int  __iminor_1 (int  );
int  __main_2 () {

{
if (__static_condition_5) {
{
int  __i_3;
int  __inode_4;

if (__static_condition_5) {
 __i_3  =  __iminor_1  (  __inode_4  ) - 32 ;

}
}

}

if (__static_condition_6) {
{
int  __i_3;
int  __inode_4;

if (__static_condition_5) {
 __i_3  =  __iminor_1  (  __inode_4  ) - 32 ;

}

if (__static_condition_6) {
if (  __imajor_0  (  __inode_4  ) == 10 ) 
if (__static_condition_6) {
 __i_3  = 31 ;

}
 else 
if (__static_condition_6) {
 __i_3  =  __iminor_1  (  __inode_4  ) - 32 ;

}


}
}

}

}
}

