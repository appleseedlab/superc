_Thread_local static int x;

int main(void) {
	static const int a;
	extern const char b;
	auto const float c;
	auto volatile double d;
	const volatile long e;
	static volatile long long f;
	extern volatile long double g;
	register const float h;
	register volatile int i;
	_Thread_local static int j;
	return 0;
}
