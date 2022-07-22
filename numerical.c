#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* calculate the numerical derivative of a 
   function that takes and returns a double 
*/
double deriv(double fn(double), double p) {
  double h = 0.00001;
  return (fn(p + h) - fn(p - h)) / (2 * h);
}

int main(size_t argc, char* argv[1]) {
  
  double x = deriv(sin, 1.5);
  double y = cos(-1.5);
  /* we know that (sin x)' == cos -x 
     so verify here 
  */
  printf("%f %f", x, y);
  return EXIT_SUCCESS;
}
