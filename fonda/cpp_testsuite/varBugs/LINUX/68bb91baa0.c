#ifdef CONFIG_I2C_DESIGNWARE_PLATFORM
int i2c_dw_init()
{
  return 0;
}
#endif

#ifdef CONFIG_I2C_DESIGNWARE_PCI
int i2c_dw_init()// ERROR
{
  return 0;
}

#endif

int main(void)
{
#if defined(CONFIG_I2C_DESIGNWARE_PLATFORM) || defined(CONFIG_I2C_DESIGNWARE_PCI)
  i2c_dw_init();
  #endif
  return 0;
}
