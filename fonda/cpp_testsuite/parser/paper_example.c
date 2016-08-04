// From linux-3.2.9/drivers/input/mousedev.c

#include "major.h"

#define MOUSEDEV_MIX 31
#define MOUSEDEV_MINOR_BASE 23

static int mousedev_open(struct inode *inode, struct file *file)
{
        int i;

#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
        if (imajor(inode) == MISC_MAJOR)
                i = MOUSEDEV_MIX;
        else
#endif
                i = iminor(inode) - MOUSEDEV_MINOR_BASE;

        return 0;
}
