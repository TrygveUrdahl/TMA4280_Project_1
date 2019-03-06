#include <iostream>
#include <math.h>
#include <vector>
#include <omp.h>
#include "../utils.hpp"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

double ompMach(int n) {
  double result = 0;
  #pragma omp parallel for reduction(+:result) schedule(static)
  for (int i = 1; i <= n; ++i) {
    result += 4 * machin((double)1/5, i);
    result +=     machin((double)1/239, i);
  }
  result *= 4;
  return abs(result - M_PI);
}
