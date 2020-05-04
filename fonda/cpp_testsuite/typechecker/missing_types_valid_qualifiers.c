_Thread_local static x;

int main(void) {
	static const a;
	extern const b;
	auto const c;
	auto volatile d;
	const volatile e;
	static volatile f;
	extern volatile g;
	register const h;
	register volatile i;
	return 0;
}
