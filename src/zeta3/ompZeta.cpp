#include <iostream>
#include <math.h>
#include <vector>
#include <omp.h>
#include "../utils.hpp"

double ompZeta(int n) {
  double result = 0;
  #pragma omp parallel for reduction(+:result) schedule(static)
  for (int i = 1; i <= n; ++i) {
    result += 1.0/static_cast<double>(pow(i, 2));
  }
  result *= 6;
  return sqrt(result);
}
