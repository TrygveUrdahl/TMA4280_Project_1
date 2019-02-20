#include <iostream>
#include <mpi.h>
#include <vector>

#include "zeta0/serialZeta.hpp"
#include "mach0/serialMach.hpp"
#include "zeta1/MPIZeta.hpp"
#include "mach1/MPIMach.hpp"

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  if (argc < 2){
    std::cout << "Requires arguments: " << std::endl;
    std::cout << "\tn: iterations to use" << std::endl;

    MPI_Finalize();
    return 1;
  }
  int n = atoi(argv[1]);


  MPI_Comm myComm;
  MPI_Comm_dup(MPI_COMM_WORLD, &myComm);

  int rank, size;
  MPI_Comm_rank(myComm, &rank);
  MPI_Comm_size(myComm, &size);

  // unitTestSerialMach() // Q2
  // unitTestSerialZeta() // Q2

  //verificationTestSerialMach(); // Q3
  //verificationTestSerialZeta(); // Q3


  std::cout << "Rank: "<< rank <<". MPIZetaScatterReduce: " << MPIZetaScatterReduce(n, rank, size, myComm) << std::endl;
  MPI_Finalize();
  return 0;
}
