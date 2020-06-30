extern int imajor(int);
extern int iminor(int);
#define MISC_MAJOR 10
#define MOUSEDEV_MIX 31
#define MOUSEDEV_MINOR_BASE 32

int main() {
  int i;
  int inode;
#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
  if (imajor(inode) == MISC_MAJOR)
    i = MOUSEDEV_MIX;
  else
#endif
    i = iminor(inode) - MOUSEDEV_MINOR_BASE;
}
