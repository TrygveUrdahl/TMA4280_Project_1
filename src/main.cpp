#include <iostream>
#include <mpi.h>
#include <vector>

#include "zeta0/serialZeta.hpp"
#include "mach0/serialMach.hpp"
#include "zeta1/MPIZeta.hpp"
#include "mach1/MPIMach.hpp"
#include "zeta2/MPIZeta2.hpp"
#include "mach2/MPIMach2.hpp"
#include "zeta3/ompZeta.hpp"
#include "mach3/ompMach.hpp"

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  if (argc < 3){
    std::cout << "Requires arguments: " << std::endl;
    std::cout << "\tint: which exercise to run" << std::endl;
    std::cout << "\tint: number of iterations to use" << std::endl;

    MPI_Finalize();
    return 1;
  }
  int n = atoi(argv[2]);
  int exercise = atoi(argv[1]);

  MPI_Comm myComm;
  MPI_Comm_dup(MPI_COMM_WORLD, &myComm);

  int rank, size;
  MPI_Comm_rank(myComm, &rank);
  MPI_Comm_size(myComm, &size);

  // Selection of program to run, rank 0 prints to terminal
  if (rank == 0) {
    switch(exercise) {
      case 1: {
        std::cout << "Question 1: " << std::endl;
        double zeta, mach;
        std::cout << "Serial implementation of Zeta and Machin" << std::endl;
        zeta = serialMach(n);
        mach = serialZeta(n);
        std::cout << "Returned values for Pi: " << std::endl;
        std::cout << "\tZeta: " << zeta << std::endl;
        std::cout << "\tMachin: " << mach << std::endl;
        break;
      }
      case 2: {
        std::cout << "Question 2: " << std::endl;
        double zeta, mach;
        std::cout << "Unit tests for the serial Zeta and Machin implementations" << std::endl;
        zeta = unitTestSerialZeta();
        mach = unitTestSerialMach();
        std::cout << "Returned values for error in calculated Pi: " << std::endl;
        std::cout << "\tZeta: " << zeta << std::endl;
        std::cout << "\tMachin: " << mach << std::endl;
        break;
      }
      case 3: {
        std::cout << "Question 3: " << std::endl;
        std::cout << "Verification tests for the serial Zeta and Machin implementations" << std::endl;
        verificationTestSerialZeta();
        verificationTestSerialMach();
        std::cout << "\tReturned values for error in calculated Pi saved to files in ../output " << std::endl;

        break;
      }
      case 4: {
        std::cout << "Question 4: " << std::endl;
        double zeta, mach;
        std::cout << "Data distributed implementation of Zeta and Machin" << std::endl;
        zeta = MPIMachBcast(n, rank, size, myComm);
        mach = MPIZetaBcast(n, rank, size, myComm);
        std::cout << "Returned values for Pi: " << std::endl;
        std::cout << "\tZeta: " << zeta << std::endl;
        std::cout << "\tMachin: " << mach << std::endl;
        break;
      }
      case 5: {
        std::cout << "Question 5: " << std::endl;
        double zeta, mach;
        std::cout << "Simple parallel implementation of Zeta and Machin using MPI Scatter and Reduce" << std::endl;
        //zeta = MPIMachScatterReduce(n, rank, size, myComm);
        mach = MPIZetaScatterReduce(n, rank, size, myComm);
        std::cout << "Returned values for Pi: " << std::endl;
        std::cout << "\tZeta: " << zeta << std::endl;
        std::cout << "\tMachin: " << mach << std::endl;
        break;
      }
      case 6: {
        std::cout << "Question 6: " << std::endl;
        std::cout << "No calculations done. " << std::endl;
        break;
      }
      case 7: {
        std::cout << "Question 7: " << std::endl;
        double zeta, mach;
        std::cout << "OpenMP implementation of Zeta and Machin. " << std::endl;
        zeta = ompZeta(n);
        mach = ompMach(n);
        std::cout << "Returned values for Pi: " << std::endl;
        std::cout << "\tZeta: " << zeta << std::endl;
        std::cout << "\tMachin: " << mach << std::endl;
        break;
      }
      case 8: {
        std::cout << "Question 7: " << std::endl;
        double zeta, mach;
        std::cout << "Hybrid implementation of Zeta and Machin with MPI and OpenMP. " << std::endl;
        //zeta =
        //mach =
        std::cout << "Returned values for Pi: " << std::endl;
        std::cout << "\tZeta: " << zeta << std::endl;
        std::cout << "\tMachin: " << mach << std::endl;
        break;
      }
      case 9: {
        std::cout << "Question 9: " << std::endl;
        std::cout << "No calculations done. " << std::endl;
        break;
      }
      case 10: {
        std::cout << "Question 10: " << std::endl;
        std::cout << "No calculations done. " << std::endl;
        break;
      }
      default: {
        std::cout << "Exercise number incorrect. Please try again. " << std::endl;
        MPI_Finalize();
        return 1;
      }
    }
  }


  //double val =  MPIZetaScatterReduce(n, rank, size, myComm);
  //std::cout << "Rank: "<< rank <<". MPIZetaScatterReduce: " << val << std::endl;

  //std::cout << "OpenMP with Mach: " << ompMach(n) << std::endl; // Q7
  //std::cout << "OpenMP with Zeta: " << ompZeta(n) << std::endl; // Q7
  MPI_Finalize();
  return 0;
}
