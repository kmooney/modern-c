#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

unsigned fib (unsigned n) {
  if (n < 3) {
      return 1;
  }
  return fib(n-1) + fib(n - 2);
}

signed main(int argc, char* argv[1]) {
  assert(argc == 2);   
  char** end = 0; 
  long a = strtol(argv[1], end, 10);
   
  printf("fib %i = %i", a, fib(a));

  return EXIT_SUCCESS;
}
