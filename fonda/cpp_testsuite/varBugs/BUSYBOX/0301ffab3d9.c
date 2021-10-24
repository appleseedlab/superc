
void ext2fs_open2(void)
{
  char *gdp;

  #ifdef EXT2FS_ENABLE_SWAPFS
  gdp = "group_desc";
  for (int j = 0; j < 10; j++)
    {
      printf("%c\n", (*gdp)++);
    }
#endif
}

void ext2fs_open(void)
{
  ext2fs_open2();
}

int main(int argc, char** argv)
{
  ext2fs_open();
  return 0;
}
