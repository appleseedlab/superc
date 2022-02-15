#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__printf_0", "printf");
__static_renaming("__decode_spi_frequency_7", "decode_spi_frequency");


};
enum ____anonymous_tag_4_5 {
__SPI_FREQUENCY_20MHZ_1,
__SPI_FREQUENCY_33MHZ_2,
__SPI_FREQUENCY_50MHZ_3,
};

void  (__printf_0) (const char  [],  ... );// L1
enum ____anonymous_tag_4_5 ;// L2
static void  (__decode_spi_frequency_7) (unsigned int  __freq_6) {

{
{



switch (  __freq_6  )// L10
{
case  __SPI_FREQUENCY_20MHZ_1  :
{



 __printf_0  ("20MHz") ; // L12
break ; // L13
}
case  __SPI_FREQUENCY_33MHZ_2  :
{



 __printf_0  ("33MHz") ; // L15
break ; // L16
}
case  __SPI_FREQUENCY_50MHZ_3  :
{



 __printf_0  ("50MHz") ; // L18
break ; // L19
}
default:
{



 __printf_0  ("unknown<%x>MHz", __freq_6 ) ; // L21
}
}
}
}


}

