void ssl_array_index()
{
}

#ifdef HAVE_TLS_ALPN
void ssl_cmp_alpn_protos()
{
  ssl_array_index();
}

void ssl_callback_alpn_select()
{
  ssl_cmp_alpn_protos();
}
#endif

int main(void)
{
  #ifdef HAVE_TLS_ALPN
  ssl_callback_alpn_select();
  #endif
  return 0;
}
