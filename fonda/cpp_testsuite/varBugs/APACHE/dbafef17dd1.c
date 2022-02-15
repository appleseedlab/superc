#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 20

void apply_rewrite_rule()
{
  char newuri[MAX_STRING_LEN];

  #ifdef HAS_APACHE_REGEX_LIB
  strncpy(newuri, "pregsub()", sizeof(newuri)-1);
  newuri[sizeof(newuri-1)] = '\0';
  #endif

  // more code making of 'newuri'
}

int main(void)
{
  apply_rewrite_rule();
  return 0;
}
