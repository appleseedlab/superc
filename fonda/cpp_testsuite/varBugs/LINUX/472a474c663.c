#define NULL (void*)0

__attribute__ ((noinline)) int nondet() { return 0; }

#ifdef CONFIG_SMP
int smp_found_config; /* found an SMP configuration at boot time ? */
#endif

void enable_IR_x2apic(void)
{
  static char c;
  static char *ptr = &c;

  *ptr = 'a';
  if (ptr)
    ptr = NULL;
}

int APIC_init_uniprocessor(void)
{
  enable_IR_x2apic(); // (6) ERROR: enable_IR_x2apic() is not idempotent
}

#ifdef CONFIG_SMP
int smp_sanity_check()
{
  if (!smp_found_config)
    APIC_init_uniprocessor(); // (5)
  return 0;
}

void native_smp_prepare_cpus()
{
  enable_IR_x2apic(); // (3) first call
  smp_sanity_check(); // (4)
}
#endif

int main(void)
{
  #ifdef CONFIG_SMP
  smp_found_config = nondet(); // (1)
  native_smp_prepare_cpus(); // (2)
  #endif
  return 0;
}
