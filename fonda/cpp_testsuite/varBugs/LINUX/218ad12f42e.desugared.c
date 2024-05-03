#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__malloc_1", "malloc");
__static_renaming("__free_3", "free");
__static_renaming("__x_4", "x");
__static_renaming("__size_5", "size");
__static_renaming("__inet_ehash_locks_alloc_6", "inet_ehash_locks_alloc");
__static_renaming("__inet_ehash_locks_free_9", "inet_ehash_locks_free");
__static_renaming("__main_12", "main");

__static_condition_renaming("__static_condition_default_7", "!(defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_8", "(defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_10", "!(defined CONFIG_NUMA)");
__static_condition_renaming("__static_condition_default_11", "(defined CONFIG_NUMA)");

};

extern void  * ((__malloc_1) (unsigned long  ____size_0));// L5
extern void  (__free_3) (void  * (____ptr_2));// L7
int  * (__x_4)= ( void  * ) 0;// L11
unsigned int  __size_5= 12 + 1;// L12
int  (__inet_ehash_locks_alloc_6) () {

{// L15
{



if (__static_condition_default_7) {
 __x_4  = malloc ( __size_5 ) ; // L21
}
if (__static_condition_default_8) {
if (  __size_5  > 12 )// L17
{
 __x_4  = malloc ( __size_5 ) ; // L18
}
else// L19
{
 __x_4  = malloc ( __size_5 ) ; // L21
}
}
if ( !  __x_4  )// L22
{
return 12 ;// L23
}
return 0 ;// L24
}
}// L25


}
void  (__inet_ehash_locks_free_9) () {

{// L28
{



if (  __x_4  )// L29
{
if (__static_condition_default_10) {

{// L29
{



free ( __x_4 ) ; // L35
 __x_4  = ( void  * ) 0 ; // L3:L37
}
}// L38
}
if (__static_condition_default_11) {

{// L29
{



if (  __size_5  > 12 )// L31
{
free ( __x_4 ) ; // L32
}
else// L33
{
 __x_4  = ( void  * ) 0 ; // L3:L37
}
}
}// L38
}
}
}
}// L39


}
int  (__main_12) (void  ) {

{// L42
{



 __inet_ehash_locks_alloc_6 ( ) ; // L43
 __inet_ehash_locks_free_9 ( ) ; // L44
return 0 ;// L45
}
}// L46


}

