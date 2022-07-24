#include<stdio.h>
#include<stdlib.h>
#include<tgmath.h>

double factorial(double k) {
  double result = k;
  if (k == 0) {
    return 1;
  }
  for (size_t i = k-1; i >= 1; --i) {
     result *= i; 
  }
  return result;
}

double seq(double k) {
    return (pow(2, k) * pow(factorial(k), 2)) / factorial(2 * k + 1);
}

double pi(double k) {
  double result = 0.0; 
  for (size_t i = 0; i < k; i++) {
    result += seq(i); 
  }
  return 2 * result;
}

int main(int argc, char* argv[1]) {
  for (size_t i = 0; i < 10; i++) {
    printf("fact %i = %i\n", i, factorial(i));
  }

  for (size_t i = 0; i < 100; i++) {
    printf("%i pi? %g\n", i, pi(i)); 
  }

  return EXIT_SUCCESS;
}
