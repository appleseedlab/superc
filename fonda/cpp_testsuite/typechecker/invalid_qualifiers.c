_Thread_local register int x;
int main(void) {
	inline int a;
	inline long b;
	static extern int c;
	_Thread_local auto int d;
	_Thread_local int e;
	return 0;
}
