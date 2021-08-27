int main(void) {
#ifdef INVALID
	inline int a;
	inline long b;
	static extern int c;
 	static auto int d;
	auto extern int e;
	auto register int f;
	static register int g;
	register extern int h;
#endif

#ifdef SIGNED
	signed unsigned int i;
	signed float j;
	unsigned float k;
	signed double l;
	unsigned double m;
#endif

#ifdef DUPLICATE
	signed signed int n;
	unsigned unsigned unsigned int o;
	static const static int p;
	auto auto float q;
	extern extern int r;
	register register int s;
#endif

#ifdef INVALID_LONG
	long long double t;
	long float u;
	long long long v;
#endif

	return 0;
}
