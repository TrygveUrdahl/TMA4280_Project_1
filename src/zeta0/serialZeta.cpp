#include <math.h>

double serialZeta(int n) {
  double result = 0;
  for (int i = 1; i <= n; ++i) {
    result += 1.0/static_cast<double>(pow(i, 2));
  }
  result *= 6;
  return sqrt(result);
}
