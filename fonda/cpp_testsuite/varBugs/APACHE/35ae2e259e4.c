#include <stdlib.h>

int ssl_init_server_certs()
{
  #ifdef HAVE_ECC
  int *eckey;
  #endif

  #ifdef HAVE_ECC
  eckey = malloc(sizeof(int));
  if (rand() % 2) {
    *eckey = 30;
  } else {
#if defined(SSL_CTX_set_ecdh_auto)
    // do something
    #else
    *eckey = 15;
    #endif
  }
  #endif

  // code making use of 'eckey'
  // return having forgotten to free the memory
  return 0;
}

int ssl_init_server_ctx()
{
  return ssl_init_server_certs();
}

int ssl_init_ConfigureServer()
{
  return ssl_init_server_ctx();
}

int ssl_init_Module()
{
  return ssl_init_ConfigureServer();
}

int main(void)
{
  ssl_init_Module();
  return 0;
}
