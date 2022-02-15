int bfin_pm_suspend_mem_enter(void)
{
  int wakeup; // ERROR

  #ifndef CONFIG_BF60x
  wakeup = 0;
  #endif

  return 0;
}

int main(int argc, char** argv)
{
  bfin_pm_suspend_mem_enter();
  return 0;
}
