#if A
int
#else
void
#endif
main(void) {
	#if A
	return 0;
	#else
	return;
	#endif
} 
