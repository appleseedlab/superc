#if APR_HAVE_IPV6
#define APR_INET6 6
#endif

int parse_url()
{
  int family = APR_INET6;
}

int main(void)
{
  parse_url();
  return 0;
}
