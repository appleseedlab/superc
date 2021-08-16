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

void  __printf_0 (const char  [],  ... );// L1
enum ____anonymous_tag_4_5 ;// L2
static void  __decode_spi_frequency_7 (unsigned int  __freq_6) {

{
{



__static_type_error("Switch cases are incompatible");
}
}


}

