#include <stdlib.h>

#ifdef HAVE_TLSV1_X
#define SSL_PROTOCOL_TLSV1_1 (1<<3)
#endif

void ssl_cmd_protocol_parse()
{
  int thisopt;

  if (rand() % 2)
    {
      thisopt = SSL_PROTOCOL_TLSV1_1;
    }
}

int main(void)
{
  ssl_cmd_protocol_parse();
  return 0;
}
