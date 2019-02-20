#include <iostream>
#include <mpi.h>
#include <vector>

#include "zeta0/serialZeta.hpp"
#include "mach0/serialMach.hpp"

int main(int argc, char** argv) {
  if (argc < 2){
    std::cout << "Requires arguments: " << std::endl;
    std::cout << "\tn: iterations to use" << std::endl;

    return 1;
  }
  int n = atoi(argv[1]);


  // unitTestSerialMach() // Q2
  // unitTestSerialZeta() // Q2

  //verificationTestSerialMach(); // Q3
  //verificationTestSerialZeta(); // Q3
  return 0;
}
