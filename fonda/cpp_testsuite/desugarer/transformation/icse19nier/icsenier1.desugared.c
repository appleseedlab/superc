extern bool CONFIG_INPUT_MOUSEDEV_PSAUX; /* originally a macro */

extern int imajor(int);
extern int iminor(int);
extern int MISC_MAJOR;
extern int MOUSEDEV_MINOR_BASE;
extern int MOUSEDEV_MIX;

int main() {
if (CONFIG_INPUT_MOUSEDEV_PSAUX) { /* originally a static conditional */
  if (imajor(inode) == 10)
    i = 31;
  else
    i = iminor(inode) - 32;
} else {
  i = iminor(inode) - 32;
}  
}
