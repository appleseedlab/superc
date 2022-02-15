#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int r = rand() % 2;
  char *p;
  char c;

  scanf("%c", &c);

  switch (c)
    {
    case 'W':
      if (r)
        p = *argv++, --argc;
      break;
      #ifdef CONFIG_FEATURE_HDPARM_HDIO_UNREGISTER_HWIF
    case 'U':
      if(!p)
        goto expected_hwif_error; //ERROR
      break;
#endif /* CONFIG_FEATURE_HDPARM_HDIO_UNREGISTER_HWIF */

      #ifdef CONFIG_FEATURE_HDPARM_HDIO_SCAN_HWIF
    case 'R':
      if(!p)
        goto expected_hwif_error;


    expected_hwif_error:
      printf("expected hwif value");

#endif /* CONFIG_FEATURE_HDPARM_HDIO_SCAN_HWIF */
    }
  return 0;
}
