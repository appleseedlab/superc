void sendfile_nonblocking();

void send_brigade_nonblocking()
{
  #if APR_HAS_SENDFILE
  sendfile_nonblocking();
  #endif
}

int main(void)
{
  send_brigade_nonblocking();
  return 0;
}
