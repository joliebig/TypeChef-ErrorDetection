
#include <stdlib.h>

#ifdef CONFIG_TWL4030_CORE
#define CONFIG_IRQ_DOMAIN
#endif

#ifdef CONFIG_IRQ_DOMAIN
int irq_domain_simple_ops = 1;

void irq_domain_add(int *ops)
{
  int irq = *ops; // ERROR
}
#endif

#ifdef CONFIG_TWL4030_CORE
int twl_probe()
{
  int *ops = NULL;

#ifdef CONFIG_OF_IRQ
  ops = &irq_domain_simple_ops;
#endif

  irq_domain_add(ops);
}
#endif

int main()
{
#ifdef CONFIG_TWL4030_CORE
  twl_probe();
#endif
  return 0;
}

