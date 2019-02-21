#include <iostream>
#include <math.h>
#include <vector>
#include <omp.h>
#include "../utils.hpp"

inline double machinOmp(double x, int i) {
  double result = 1;
  result *= pow(x, 2 * i - 1)/(2 * i - 1);
  result *= pow(-1, i - 1);
  return result;
}

double ompMach(int n) {
  double result = 0;
  #pragma omp parallel for reduction(+:result) schedule(static)
  for (int i = 1; i <= n; ++i) {
    result += 4 * machinOmp((double)1/5, i);
    result +=     machinOmp((double)1/239, i);
  }
  result *= 4;
  return result;
}
