#include <stdlib.h>
#include <stdio.h>

void printArray(char* fmt, double A[1], size_t len) {
  printf("%s", fmt); 
  for (size_t i = 0; i < len; i++) {
    printf("%f ",A[i]); 
  }
  printf("\n");
}

void mergeSort(double A[1], size_t len) {
  if (len <= 1) {
      return;
  }
  double left[len];
  double right[len];
 
  size_t len_r = 0;
  size_t len_l = 0;
  for (size_t i = 0; i < len; i++) {
    if (i < (len / 2)) {
      left[i] = A[i]; 
      len_l ++;
    } else {
      right[i - (len / 2)] = A[i];
      len_r ++;
    }
  }
  
  mergeSort(left, len_l);
  mergeSort(right, len_r);

  size_t ri = 0;
  size_t li = 0;
  size_t i = 0;
  while (li < len_l && ri < len_r) {
    if (left[li] <= right[ri]) {
      A[i] = left[li];
      li ++;
    } else {
      A[i] = right[ri];
      ri ++;
    }
    i++;
  }
  
  while (li < len_l) {
    A[i] = left[li];
    i++;
    li++;
  }
  while (ri < len_r) {
    A[i] = right[ri];
    i++;
    ri++;
  }
}

static const int LEN = 10;

int main(int argc, const char* argv[argc+1]) {
  double A[] = { 4.21, 9.487, 3.492, 8.395,2.48756, 1.934, 0.2349, 8.39, 5.329, 2.49, 5.532 };
  size_t len = sizeof A / sizeof A[0];
  mergeSort(A, len);
  for (size_t i = 0; i < len; i++) { printf("%i %f \n", i, A[i]); }
  return EXIT_SUCCESS;
}
