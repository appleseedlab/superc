#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__imajor_0", "imajor");
__static_renaming("__iminor_1", "iminor");
__static_renaming("__i_2", "i");
__static_renaming("__inode_3", "inode");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_4", "!(defined CONFIG_INPUT_MOUSEDEV_PSAUX)");
__static_condition_renaming("__static_condition_default_5", "(defined CONFIG_INPUT_MOUSEDEV_PSAUX)");

};

extern int  __imajor_0 (int  );
extern int  __iminor_1 (int  );
int  __main_6 () {

{
if (__static_condition_default_4) {
{
int  __i_2;
int  __inode_3;

if (__static_condition_default_4) {
 __i_2  =  __iminor_1  (  __inode_3  ) - 32 ;

}
}

}

if (__static_condition_default_5) {
{
int  __i_2;
int  __inode_3;

if (__static_condition_default_4) {
 __i_2  =  __iminor_1  (  __inode_3  ) - 32 ;

}

if (__static_condition_default_5) {
if (  __imajor_0  (  __inode_3  ) == 10 ) 
if (__static_condition_default_5) {
 __i_2  = 31 ;

}
 
if (__static_condition_default_5) {
 __i_2  =  __iminor_1  (  __inode_3  ) - 32 ;

}


}
}

}

}
}

