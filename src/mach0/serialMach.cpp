#include <iostream>
#include <math.h>

double machin(double x, int i) {
  double result = 1;
  result *= pow(x, 2 * i - 1)/(2 * i - 1);
  result *= pow(-1, i - 1);
  return result;
}

double serialMach(int n) {
  double result = 0;
  for (int i = 1; i <= n; ++i) {
    result += 4 * machin((double)1/5, i);
    result +=     machin((double)1/239, i);
  }
  result *= 4;
  return result;
}
