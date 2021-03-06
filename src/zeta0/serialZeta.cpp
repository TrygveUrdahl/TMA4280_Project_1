#include <iostream>
#include <math.h>
#include <vector>
#include "../utils.hpp"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

double serialZeta(int n) {
  double result = 0;
  for (int i = 1; i <= n; ++i) {
    result += 1.0/static_cast<double>(pow(i, 2));
  }
  result *= 6;
  return sqrt(result);
}

double unitTestSerialZeta(int n = 3) {
  double err;
  double pi = serialZeta(n);
  err = abs(M_PI - pi);
  return err;
}

std::vector<double> verificationTestSerialZeta(std::string outputName = "../output/errorZeta.txt") {
  std::vector<double> errVec;
  errVec.reserve(24);
  for (int k = 1; k <= 24; ++k) {
    int n = pow(k, 2);
    double pi = serialZeta(n);
    double err = abs(M_PI - pi);
    errVec.push_back(err);
  }
  writeVectorToFile(errVec, outputName);
  return errVec;
}
