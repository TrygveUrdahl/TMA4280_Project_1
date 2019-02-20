#include <iostream>
#include <mpi.h>

#include "zeta0/serialZeta.hpp"
#include "mach0/serialMach.hpp"

int main(int argc, char** argv) {
  if (argc < 2){
    std::cout << "Requires arguments: " << std::endl;
    std::cout << "\tn: iterations to use" << std::endl;

    return 1;
  }
  int n = atoi(argv[1]);

  std::cout << "Pi is approx.: " << serialMach(n) << std::endl;
  return 0;
}
