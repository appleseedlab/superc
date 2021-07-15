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
int main() {
  __builtin_offsetof(len_and_sockaddr, u);
  __builtin_offsetof(int, u);
}

/* enum { */
/* 	LSA_LEN_SIZE = offsetof(len_and_sockaddr, u), */
/* 	LSA_SIZEOF_SA = sizeof( */
/* 		union { */
/* 			struct sockaddr sa; */
/* 			struct sockaddr_in sin; */
/* #if ENABLE_FEATURE_IPV6 */
/* 			struct sockaddr_in6 sin6; */
/* #endif */
/* 		} */
/* 	) */
/* }; */
