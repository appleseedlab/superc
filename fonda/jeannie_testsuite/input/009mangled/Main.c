#include <jni.h>
#include <stdio.h>

void quickSort(int* a, int left, int right) {
  if (left < right) {
    int pivot;
    { /* partition */
      int x, i, j;
      x = a[left];
      i = left - 1;
      j = right + 1;
      while (1) {
        do j--; while (a[j]>x);
        do i++; while (a[i]<x);
        if (i < j) { /* swap */
          int tmp = a[i];
          a[i] = a[j];
          a[j] = tmp;
        } else {
          pivot = j;
          break;
        }
      }
    }
    quickSort(a, left, pivot);
    quickSort(a, pivot+1, right);
  }
}

void sortArray(int* a, int length){
  quickSort(a, 0, length-1);
}

void printArray(int* a, int length){
  int i;
  for(i=0; i<length; i++)
    printf(" %d", a[i]);
  printf("\n");
}


void JNICALL Java_Main_sayHi(JNIEnv *env, jclass clazz) {
# define LENGTH 7
  int a[LENGTH] = { 3, 2, 6, 1, 2, 0, 7 };
  printArray(a, LENGTH);
  sortArray(a, LENGTH);
  printArray(a, LENGTH);
}
