#define APLOG_LEVELMASK 1
#define APLOG_NOTICE 2
#define APLOG_MAX 3

#ifdef HAVE_SYSLOG
//#include "http_config.h" contains ap_get_server_module_loglevel()
void ap_get_server_module_loglevel();
#if !defined(AP_DEBUG)
#define ap_get_server_module_loglevel() do {} while(0)
#endif /* AP_DEBUG */
#endif

int main(void)
{
#ifndef APLOG_MAX_LOGLEVEL
    if (APLOG_LEVELMASK <= APLOG_NOTICE)
          ap_get_server_module_loglevel();
          #else
              if (APLOG_LEVELMASK <= APLOG_MAX)
                    ap_get_server_module_loglevel();
                    #endif

  return 0;
  }