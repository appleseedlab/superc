#if defined(CONFIG_X86) && defined(CONFIG_ACPI_WMI)
#include <string.h>

static char block_object_id[3] = "XX";

void wmi_query_block()
{
  char method[4]; // (4) just four bytes long

  strcpy(method, "WQ"); // (5) writes two bytes plus '\0'
  strncat(method, block_object_id, 2); // (6) ERROR: no space for the final '\0'
}

int get_wmid_devices(void)
{
  wmi_query_block(); // (3)
  return 0;
}

int acer_wmi_init(void)
{
  get_wmid_devices(); // (2)
  return 0;
}
#endif


int main()
{
#if defined(CONFIG_X86) && defined(CONFIG_ACPI_WMI)
  acer_wmi_init(); // (1)
  #endif
  return 0;
}
