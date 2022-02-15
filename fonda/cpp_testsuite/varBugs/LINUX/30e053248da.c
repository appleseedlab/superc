__attribute__ ((noinline)) int nondet() { return 42; }

#ifdef CONFIG_SECURITY
int security_old_inode_init_security(int *len)
{
  if (nondet()) {
    *len = 0;
    return 0;
  }
  else
    return -1;
}
#else
int security_old_inode_init_security(int *len)
{
  return 0;
}
#endif

int reiserfs_security_init(int *length)
{
  int error;

  error = security_old_inode_init_security(length); // (4) length is never written if !SECURITY

  if (error) { // (5) guaranteed false if !SECURITY
    *length = 0;
    return error;
  }

  int x = *length; // (6) ERROR

  return 0;
}

int reiserfs_create()
{
  int retval;
  int length; // (2)

  retval = reiserfs_security_init(&length); // (3) length not initialized
  if (retval < 0)
    {
      return retval;
    }

  return 0;
}

int main(void)
{
  reiserfs_create(); // (1)
  return 0;
}
