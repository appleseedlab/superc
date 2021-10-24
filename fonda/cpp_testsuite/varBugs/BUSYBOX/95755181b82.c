#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef ENABLE_FEATURE_HTTPD_GZIP
int content_gzip = 0;
#endif

#if ENABLE_FEATURE_HTTPD_BASIC_AUTH
int authorized = 0;
#endif

#define HTTP_UNAUTHORIZED  401
#define IOBUF_SIZE         8192
char *iobuf = malloc(IOBUF_SIZE);

void send_headers(int responseNum)
{
  const char *mime_type;
  int len;

  /* error message is HTML */
  mime_type = responseNum == HTTP_OK ? "application/octet-stream" : "text/html";

  len = sprintf(iobuf, "HTTP/1.0 %d\r\nContent-type: %s\r\n",
                responseNum, mime_type);

  #ifdef ENABLE_FEATURE_HTTPD_BASIC_AUTH
  if (responseNum == HTTP_UNAUTHORIZED) {
    len += sprintf(iobuf + len,
                   "WWW-Authenticate: Basic realm=\"Web Server Authentication\"\r\n");
  }
  #endif

  if (content_gzip)
    len += sprintf(iobuf + len, "Content-Encoding: gzip\r\n");

  printf("headers: '%s'\n", iobuf);
}

void send_headers_and_exit(int responseNum)
{
  send_headers(responseNum);
}

void handle_incoming_and_exit()
{

  #ifdef ENABLE_FEATURE_HTTPD_GZIP
  const char *s = strstr(iobuf, "gzip");
  if (s)
    content_gzip = 1;
  #endif

  #ifdef ENABLE_FEATURE_HTTPD_BASIC_AUTH
  if(!authorized)
    send_headers_and_exit(HTTP_UNAUTHORIZED);
  #endif
}

#ifdef BB_MMU
void mini_httpd()
{
  handle_incoming_and_exit();
}
#endif

int main(int argc, char** argv)
{
  #ifdef BB_MMU
  mini_httpd();
  #endif
  return 0;
}
