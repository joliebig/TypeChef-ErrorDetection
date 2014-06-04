
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define panic() \
  do { fprintf(stderr, "panic!\n"); exit(1); } while(0)

#ifdef CONFIG_SMP
int smp_found_config; /* found an SMP configuration at boot time ? */
#endif

void enable_IR_x2apic(void)
{
  static int called = 0;

  called++;
  if (called > 1) panic();
}

int APIC_init_uniprocessor(void)
{
  enable_IR_x2apic();
}

#ifdef CONFIG_SMP
static int smp_sanity_check()
{
  if (!smp_found_config)
    APIC_init_uniprocessor();
  return 0;
}

void native_smp_prepare_cpus()
{
  enable_IR_x2apic();
  smp_sanity_check();
}
#endif

int main(int argc, char** argv)
{
#ifdef CONFIG_SMP
  smp_found_config = false;
  native_smp_prepare_cpus();
#endif
  return 0;
}

