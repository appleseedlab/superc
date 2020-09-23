/* struct _SSL_CTX */
/* { */
/*     uint32_t options; */
/*     uint8_t chain_length; */
/*     RSA_CTX *rsa_ctx; */
/* #ifdef CONFIG_SSL_CERT_VERIFICATION */
/*     CA_CERT_CTX *ca_cert_ctx; */
/* #endif */
/*     SSL *head; */
/*     SSL *tail; */
/*     SSL_CERT certs[CONFIG_SSL_MAX_CERTS]; */
/* #ifndef CONFIG_SSL_SKELETON_MODE */
/*     uint16_t num_sessions; */
/*     SSL_SESSION **ssl_sessions; */
/* #endif */
/* #ifdef CONFIG_SSL_CTX_MUTEXING */
/*     SSL_CTX_MUTEX_TYPE mutex; */
/* #endif */
/* #ifdef CONFIG_OPENSSL_COMPATIBLE */
/*     void *bonus_attr; */
/* #endif */
/* }; */
