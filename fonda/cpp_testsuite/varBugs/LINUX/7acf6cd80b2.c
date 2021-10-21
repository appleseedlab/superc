__attribute__ ((noinline)) int nondet() { return 42; }

int some_int = 1;

void pts_sb_from_inode(int *inode)
{
  #ifdef CONFIG_DEVPTS_MULTIPLE_INSTANCES
  int x = *inode; // ERROR (7)
  #endif
}

void devpts_pty_kill(int *inode)
{
  pts_sb_from_inode(inode); // (6)
}

void pty_close(int *driver_data)
{
  #ifdef CONFIG_UNIX98_PTYS
  devpts_pty_kill(driver_data); // (5)
  #endif
}

int tty_release(int *driver_data)
{
  pty_close(driver_data); // (4)
  return 0;
}

#ifdef CONFIG_UNIX98_PTYS
int ptmx_open()
{
  int *driver_data;

  if (nondet()) {
    goto err_release; // (2)
  }

  driver_data = &some_int;

  return 0;

 err_release:
  tty_release(driver_data); // (3)
  return -1;
}
#endif

int main()
{
  #ifdef CONFIG_UNIX98_PTYS
  ptmx_open(); // (1)
  #endif
  return 0;
}
