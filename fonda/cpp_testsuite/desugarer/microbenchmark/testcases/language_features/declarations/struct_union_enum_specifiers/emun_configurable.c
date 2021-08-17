typedef struct len_and_sockaddr {
	int len;
	union {
		struct sockaddr sa;
		struct sockaddr_in sin;
#if ENABLE_FEATURE_IPV6
		struct sockaddr_in6 sin6;
#endif
	} u;
} len_and_sockaddr;
