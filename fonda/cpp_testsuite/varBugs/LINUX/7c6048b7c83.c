#if defined(CONFIG_ACPI) && defined(CONFIG_STUB_POULSBO)
#define CONFIG_ACPI_VIDEO
#endif

#ifdef CONFIG_BACKLIGHT_CLASS_DEVICE
void backlight_device_unregister()
{
  return;
}
#endif

#ifdef CONFIG_ACPI_VIDEO
static int acpi_video_bus_put_one_device()
{
  backlight_device_unregister();
  return 0;
}
#endif

int main(int argc, char** argv)
{
#if defined(CONFIG_ACPI) && defined(CONFIG_STUB_POULSBO)
  acpi_video_bus_put_one_device();
  #endif
  return 0;
}
