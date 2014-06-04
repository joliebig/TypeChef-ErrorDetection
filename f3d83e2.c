
#if defined(CONFIG_X86) && defined(CONFIG_ACPI_WMI)
#include <string.h>

static char block_object_id[3] = "XX";

void wmi_query_block()
{
  char method[4];

  strcpy(method, "WQ");
  strncat(method, block_object_id, 2); // ERROR
}

int get_wmid_devices(void)
{
  wmi_query_block();
  return 0;
}

int acer_wmi_init(void)
{
  get_wmid_devices();
  return 0;
}
#endif


int main()
{
#if defined(CONFIG_X86) && defined(CONFIG_ACPI_WMI)
  acer_wmi_init();
#endif
  return 0;
}

