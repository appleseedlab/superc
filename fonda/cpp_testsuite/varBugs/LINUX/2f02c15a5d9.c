#ifdef CONFIG_SSB_DRIVER_EXTIF
int ssb_extif_gpio_in()
{
  return 0;
}
#endif

#ifdef CONFIG_BCM47XX
int bcm47xx_gpio_get_value()
{
  return ssb_extif_gpio_in();
}
#endif

int main(int argc, char** argv)
{
  #ifdef CONFIG_BCM47XX
  bcm47xx_gpio_get_value();
  #endif
  return 0;
}
