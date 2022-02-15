void printf(const char[], ...);
enum {
      SPI_FREQUENCY_20MHZ,
      SPI_FREQUENCY_33MHZ,
      SPI_FREQUENCY_50MHZ,
};

static void decode_spi_frequency(unsigned int freq)
{
	switch (freq) {
	case SPI_FREQUENCY_20MHZ:
		printf("20MHz");
		break;
	case SPI_FREQUENCY_33MHZ:
		printf("33MHz");
		break;
	case SPI_FREQUENCY_50MHZ:
		printf("50MHz");
		break;
	default:
		printf("unknown<%x>MHz", freq);
	}
}
