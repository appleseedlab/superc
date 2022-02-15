__attribute__ ((noinline)) int nondet() { return 42; }

#ifdef CONFIG_NETPOLL
int netpoll_setup()
{
  int err;

  #ifdef CONFIG_IPV6
  err = -1;
  if (nondet())
    goto put;
  #else
  goto put; // (2)
  #endif

 put:
  return err; // ERROR (3)
}
#endif

int main(void)
{
  #ifdef CONFIG_NETPOLL
  netpoll_setup(); // (1)
  #endif
  return 0;
}
