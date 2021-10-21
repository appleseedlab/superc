extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
                    const char *__restrict __format, ...) __attribute__ ((__nothrow__));

#ifdef CONFIG_RCU_CPU_STALL_INFO

#ifdef CONFIG_RCU_FAST_NO_HZ
void print_cpu_stall_fast_no_hz(char *cp, int cpu)
{
  sprintf(cp, "foobar");
}
#else /* #ifdef CONFIG_RCU_FAST_NO_HZ */
void print_cpu_stall_fast_no_hz(char *cp, int cpu)
{ // (3)
}
#endif /* #else #ifdef CONFIG_RCU_FAST_NO_HZ */

void print_cpu_stall_info(int cpu)
{
  char fast_no_hz[72];

  print_cpu_stall_fast_no_hz(fast_no_hz, cpu); // (2)
  printf("\t%d: %s\n", cpu, fast_no_hz); // ERROR (4)
}
#else /* #ifdef CONFIG_RCU_CPU_STALL_INFO */
void print_cpu_stall_info(int cpu)
{
  printf(" %d", cpu);
}
#endif /* #else #ifdef CONFIG_RCU_CPU_STALL_INFO */

int main(void)
{
  #ifdef CONFIG_RCU_CPU_STALL_INFO
  print_cpu_stall_info(0); // (1)
  #endif
  return 0;
}
