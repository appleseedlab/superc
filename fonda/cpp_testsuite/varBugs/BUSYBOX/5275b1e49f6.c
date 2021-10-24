#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int r = rand() % 2;
  int m_has_modinfo;
  int exit_status = -1;
  int someInt = 1;

  #ifdef CONFIG_FEATURE_INSMOD_VERSION_CHECKING
  int k_crcs;
  #endif

  if (r)
    m_has_modinfo = 0;
  else
    m_has_modinfo = 1;

  #ifdef CONFIG_FEATURE_INSMOD_VERSION_CHECKING
  k_crcs = 0;
  #endif

  if (r) {
    k_crcs = someInt;
  } else {
    printf("Not configured to support old kernels");
    goto out;
  }

 out:
  return(exit_status);

  return 0;
}
