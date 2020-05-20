int main() {

#if A
	int
#else
	#if B
	char
	#else
	float
	#endif
#endif

#ifdef C
	arr;
#else
	#ifdef D
	arr[];
	#else
	*arr;
	#endif
#endif

	return 0;
}
