
void doNothingOne() {
	return;
} 

void doNothingTwo() {
} 


int main(void) {
	#if A
	doNothingOne();
	#else
	doNothingTwo();
	#endif

	return 0;
} 
