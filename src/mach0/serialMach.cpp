#include <iostream>
#include <math.h>
#include <vector>
#include "../utils.hpp"

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

double unitTestSerialMach(int n = 3) {
  double err;
  double pi = serialMach(n);
  err = abs(M_PI - pi);
  return err;
}

std::vector<double> verificationTestSerialMach(std::string outputName = "../output/errorMach.txt") {
  std::vector<double> errVec;
  errVec.reserve(24);
  for (int k = 1; k <= 24; ++k) {
    int n = pow(k, 2);
    double pi = serialMach(n);
    double err = abs(M_PI - pi);
    errVec.push_back(err);
  }
  writeVectorToFile(errVec, outputName);
  return errVec;
}
