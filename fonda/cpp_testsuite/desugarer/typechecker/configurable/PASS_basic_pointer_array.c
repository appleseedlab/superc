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
  // arr -> { int:A, char:!A & B, float:!A & !B
#else
	#ifdef D
	arr[];
  // arr -> { int:A & (C | !D), char:!A & B & (C | !D), float:!A & !B & (C | !D), int[]:A & !C & D, char[]:!A & B & !C & D, float[]:!A & !B & !C & D }
	#else
	*arr;
  // arr -> { int:A & (C | !D) & (C | D), char:!A & B & (C | !D) & (C | D), float:!A & !B & (C | !D) & (C | D), int[]:A & !C & D & (C | D), char[]:!A & B & !C & D & (C | D), float[]:!A & !B & !C & D & (C | D), int*:A & !C & !D, char*:!A & B & !C & !D, float*:!A & !B & !C & !D }
	#endif
#endif

  #ifdef D
  char arr;
  // arr -> { int:A & (C | !D) & (C | D) & !D, char:!A & B & (C | !D) & (C | D) & !D, float:!A & !B & (C | !D) & (C | D) & !D, int[]:A & !C & D & (C | D) & !D, char[]:!A & B & !C & D & (C | D) & !D, float[]:!A & !B & !C & D & (C | D) & !D, int*:A & !C & !D & !D, char*:!A & B & !C & !D & !D, float*:!A & !B & !C & !D & !D, char:D }
  // arr -> { int:A & C & !D, char:!A & B & C & !D, float:!A & !B & C & !D, int[]:False, char[]:False, float[]:False, int*:A & !C & !D, char*:!A & B & !C & !D, float*:!A & !B & !C & !D, char:D }
  #endif

	return 0;
}
