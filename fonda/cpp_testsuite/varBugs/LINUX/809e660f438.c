static int do_page_fault()
{
  return 0;
}

static int do_sect_fault() // ERROR: dead code
{
  return 0;
}

int main()
{
  #ifdef CONFIG_ARM_LPAE
  do_page_fault();
  #else
  do_page_fault();
  do_sect_fault();
  #endif
  return 0;
}
