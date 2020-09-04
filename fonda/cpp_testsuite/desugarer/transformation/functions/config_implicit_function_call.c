#if A
void doNothing() {
	return;
} 
#else
void doNothing() {
} 
#endif

int main(void) {
	doNothing();

	return 0;
}
 
