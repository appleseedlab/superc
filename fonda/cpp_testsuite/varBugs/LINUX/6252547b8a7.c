#define NULL (void*)0

#ifdef CONFIG_TWL4030_CORE
#define CONFIG_IRQ_DOMAIN
#endif

#ifdef CONFIG_IRQ_DOMAIN
int irq_domain_simple_ops = 1;

void irq_domain_add(int *ops)
{
  int irq = *ops; // (4) ERROR
}
#endif

#ifdef CONFIG_TWL4030_CORE
int twl_probe()
{
  int *ops = NULL; // (2)

  #ifdef CONFIG_OF_IRQ
  ops = &irq_domain_simple_ops;
  #endif

  irq_domain_add(ops); // (3)
}
#endif

int main()
{
  #ifdef CONFIG_TWL4030_CORE
  twl_probe(); // (1)
  #endif
  return 0;
}
