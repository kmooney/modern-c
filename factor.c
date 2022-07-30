#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

void factor(long n) {
  long r = n;
  for (size_t i = 2; i <= n/2; i++) {
      if (n % i == 0) {
         factor(n/i);
         r = i;
         break;
      }
  }
  printf(" %i", r);
}

signed main(int argc, char* argv[1]) {
   assert(argc >= 2);
   for (size_t i = 1; i < argc; i++) {
     long n = strtol(argv[i], 0, 10);
     printf ("prime factors of %i =", n);
     factor(n);
     printf("\n");
   }
}
