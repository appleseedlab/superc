#include <stdbool.h>
#include <stdlib.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__some_int_0", "some_int");
__static_renaming("____alloc_pages_nodemask_2", "__alloc_pages_nodemask");
__static_renaming("__descs_5", "descs");
__static_renaming("__ep93xx_alloc_buffers_6", "ep93xx_alloc_buffers");
__static_renaming("__ep93xx_open_8", "ep93xx_open");
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_3", "!(defined CONFIG_ZONE_DMA)");
__static_condition_renaming("__static_condition_default_4", "(defined CONFIG_ZONE_DMA)");
__static_condition_renaming("__static_condition_default_7", "(defined CONFIG_EP93XX_ETH)");
__static_condition_renaming("__static_condition_default_11", "!(defined CONFIG_EP93XX_ETH)");
__static_condition_renaming("__static_condition_default_12", "(defined CONFIG_EP93XX_ETH)");

};

static int  __some_int_0= 0;// L17
int  * ((____alloc_pages_nodemask_2) (int  __gfp_mask_1)) {

{// L20
{



if (__static_condition_default_3) {
if (  __gfp_mask_1  & ( ( int   ) 0x01u ) )// L22
{
return ( void  * ) 0 ;// L23
}
}
if (__static_condition_default_4) {
return &  __some_int_0  ;// L25
}
if (__static_condition_default_3) {
return &  __some_int_0  ;// L25
}
}
}// L26


}
int  (__ep93xx_alloc_buffers_6) () {

if (__static_condition_default_7) {

{// L30
{



int  * (__descs_5)=  ____alloc_pages_nodemask_2  (( ( ( int   ) 0x10u ) | ( ( int   ) 0x40u ) | ( ( int   ) 0x80u ) ) | ( ( int   ) 0x01u ));// L31

if (  __descs_5  == ( void  * ) 0 )// L32
{
return 1 ;// L33
}
}
}// L34


}
}
int  (__ep93xx_open_8) () {

if (__static_condition_default_7) {

{// L37
{



if (  __ep93xx_alloc_buffers_6 ( ) )// L38
{
return - 12 ;// L39
}
}
}// L40


}
}
int  (__main_9) (void  ) {

if (__static_condition_default_11) {

{// L44
{



return 0 ;// L48
}
}// L49


}
}
int  (__main_10) (void  ) {

if (__static_condition_default_12) {

{// L44
{



 __ep93xx_open_8 ( ) ; // L46
return 0 ;// L48
}
}// L49


}
}

