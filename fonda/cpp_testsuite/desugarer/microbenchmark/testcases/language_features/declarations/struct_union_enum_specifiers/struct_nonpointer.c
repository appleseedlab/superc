typedef struct X509_algor_st X509_ALGOR;
struct X509_algor_st {
    int *algorithm;
    char *parameter;
} ;
typedef struct Netscape_spki_st {
    X509_ALGOR sig_algor;
} NETSCAPE_SPKI;
