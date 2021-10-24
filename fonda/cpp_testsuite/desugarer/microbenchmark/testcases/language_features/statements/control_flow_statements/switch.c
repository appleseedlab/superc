#ifdef SWITCH
enum {
      SPI_FREQUENCY_20MHZ,
      SPI_FREQUENCY_33MHZ,
      SPI_FREQUENCY_50MHZ,
};

static void decode_spi_frequency(unsigned int freq)
{
    int a = 0;
	switch (freq) {
	case SPI_FREQUENCY_20MHZ:
		a = 20;
		break;
	case SPI_FREQUENCY_33MHZ:
		a = 33;
		break;
	case SPI_FREQUENCY_50MHZ:
		a = 50;
		break;
	default:
		a = -1;
	}
}
#endif
