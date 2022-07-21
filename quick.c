#include <stddef.h>
#include <stdio.h>

void printArray(double A[1], int len) {
  for (int i = 0; i < len; i++) {
    printf(" %f ", A[i]);
  }
  printf("\n");
}

void swap(double A[1], int i, int j) {
  double temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

int partition(double A[1], int lo, int hi) {
   int pivot = A[hi];
   int i = lo - 1;

   for (int j = lo; j < hi; j++) {
     if (A[j] <= pivot) {
       i++;
       swap(A, i, j);
     }
   }

   i++;
   swap(A, i, hi); 
   return i;
}

void quickSort(double A[1], int lo, int hi) {
  if (lo >= hi || lo < 0) return;

  int p = partition(A, lo, hi);

  quickSort(A, lo, p - 1);
  quickSort(A, p + 1, hi);
}

int main(int argc, char* argv[1]) {
  double A[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0};
  int len = sizeof A / sizeof A[0];
  quickSort(A, 0, len-1);
  printArray(A, len);
  return 0;
}
