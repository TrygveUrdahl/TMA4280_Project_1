#include <iostream>
#include <mpi.h>
#include <vector>
#include <chrono>
#include <omp.h>

#include "utils.hpp"
#include "zeta0/serialZeta.hpp"
#include "mach0/serialMach.hpp"
#include "zeta1/MPIZeta.hpp"
#include "mach1/MPIMach.hpp"
#include "zeta2/MPIZeta2.hpp"
#include "mach2/MPIMach2.hpp"
#include "zeta3/ompZeta.hpp"
#include "mach3/ompMach.hpp"
#include "zeta4/hybridZeta.hpp"
#include "mach4/hybridMach.hpp"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  if (argc < 2){
    std::cout << "Error in program arguments given! " << std::endl;
    std::cout << "\tMandatory arguments: " << std::endl;
    std::cout << "\t  int: which exercise number to run" << std::endl;
    std::cout << "\tVoluntary arguments: " << std::endl;
    std::cout << "\t  int: number of iterations to use (default 100)" << std::endl;

    MPI_Finalize();
    return 1;
  }

  int n = 100;
  int exercise = atoi(argv[1]);
  if (argc > 2) {
    n = atoi(argv[2]);
  }

  MPI_Comm myComm;
  MPI_Comm_dup(MPI_COMM_WORLD, &myComm);

  int rank, size;
  MPI_Comm_rank(myComm, &rank);
  MPI_Comm_size(myComm, &size);


  // Selection of which program to run, rank 0 prints to terminal
  switch(exercise) {
    case 1: {
      if (rank == 0) std::cout << "Question 1: " << std::endl;
      double zeta, mach;
      if (rank == 0) std::cout << "Serial implementation of Zeta and Machin" << std::endl;
      zeta = serialMach(n);
      mach = serialZeta(n);
      if (rank == 0) std::cout << "Returned values for Pi: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << zeta << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << mach << std::endl;
      break;
    }
    case 2: {
      if (rank == 0) std::cout << "Question 2: " << std::endl;
      double zeta, mach;
      if (rank == 0) std::cout << "Unit tests for the serial Zeta and Machin implementations" << std::endl;
      zeta = unitTestSerialZeta();
      mach = unitTestSerialMach();
      if (rank == 0) std::cout << "Returned values for error in calculated Pi: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << zeta << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << mach << std::endl;
      break;
    }
    case 3: {
      if (rank == 0) std::cout << "Question 3: " << std::endl;
      if (rank == 0) std::cout << "Verification tests for the serial Zeta and Machin implementations" << std::endl;
      verificationTestSerialZeta();
      verificationTestSerialMach();
      if (rank == 0) std::cout << "\tReturned values for error in calculated Pi saved to files in ../output " << std::endl;
      break;
    }
    case 4: {
      if (rank == 0) std::cout << "Question 4: " << std::endl;
      double zeta, mach;
      if (rank == 0) std::cout << "Data distributed implementation of Zeta and Machin" << std::endl;
      zeta = MPIZetaBcast(n, rank, size, myComm);
      mach = MPIMachBcast(n, rank, size, myComm);
      if (rank == 0) std::cout << "Returned values for Pi: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << zeta << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << mach << std::endl;
      break;
    }
    case 5: {
      if (rank == 0) std::cout << "Question 5: " << std::endl;
      double zeta, mach;
      if (rank == 0) std::cout << "Simple parallel implementation of Zeta and Machin using MPI Scatter and Reduce" << std::endl;
      auto startTimeMach = std::chrono::high_resolution_clock::now();
      mach = MPIMachScatterReduce(n, rank, size, myComm);
      auto endTimeMach = std::chrono::high_resolution_clock::now();
      auto startTimeZeta = std::chrono::high_resolution_clock::now();
      zeta = MPIZetaScatterReduce(n, rank, size, myComm);
      auto endTimeZeta = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> durationMach = endTimeMach - startTimeMach;
      std::chrono::duration<double> durationZeta = endTimeZeta - startTimeZeta;

      if (rank == 0) std::cout << "Returned values for absolute error in Pi: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << zeta << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << mach << std::endl;
      if (rank == 0) std::cout << "Time taken for calculations: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << durationZeta.count() << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << durationMach.count() << std::endl;


      // Multiple error calculations and timings here, with priting to files
      std::vector<double> errorsMach, errorsZeta, timingsMach, timingsZeta;
      for (int iterations = 1; iterations <= 500; iterations++) {
        auto startTimeMach = std::chrono::high_resolution_clock::now();
        double errorMach = MPIMachScatterReduce(iterations, rank, size, myComm);
        auto endTimeMach = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationMach = endTimeMach - startTimeMach;
        errorsMach.push_back(errorMach);
        timingsMach.push_back(durationMach.count()*1000000);

        auto startTimeZeta = std::chrono::high_resolution_clock::now();
        double errorZeta = MPIZetaScatterReduce(iterations, rank, size, myComm);
        auto endTimeZeta = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationZeta = endTimeZeta - startTimeZeta;
        errorsZeta.push_back(errorZeta);
        timingsZeta.push_back(durationZeta.count()*1000000);
      }
      writeVectorToFile(errorsMach, "../output/errorMach.txt");
      writeVectorToFile(errorsZeta, "../output/errorZeta.txt");
      writeVectorToFile(timingsMach, "../output/timingMach.txt");
      writeVectorToFile(timingsZeta, "../output/timingZeta.txt");

      if (rank == 0) std::cout << "Error vectors calculated and output. " << std::endl;


      break;
    }
    case 6: {
      if (rank == 0) std::cout << "Question 6: " << std::endl;
      if (rank == 0) std::cout << "No calculations done. " << std::endl;
      break;
    }
    case 7: {
      if (rank == 0) std::cout << "Question 7: " << std::endl;
      double zeta, mach;
      if (rank == 0) std::cout << "OpenMP implementation of Zeta and Machin. " << std::endl;
      auto startTimeMach = std::chrono::high_resolution_clock::now();
      mach = ompMach(n);
      auto endTimeMach = std::chrono::high_resolution_clock::now();
      auto startTimeZeta = std::chrono::high_resolution_clock::now();
      zeta = ompZeta(n);
      auto endTimeZeta = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> durationMach = endTimeMach - startTimeMach;
      std::chrono::duration<double> durationZeta = endTimeZeta - startTimeZeta;

      if (rank == 0) std::cout << "Returned values for Pi: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << zeta << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << mach << std::endl;
      if (rank == 0) std::cout << "Time taken for calculations: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << durationZeta.count() << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << durationMach.count() << std::endl;


      // Multiple error calculations and timings here, with priting to files
      std::vector<double> errorsMach, errorsZeta, timingsMach, timingsZeta;
      for (int iterations = 1; iterations <= 1000; iterations++) {
        auto startTimeMach = std::chrono::high_resolution_clock::now();
        double errorMach = ompMach(iterations);
        auto endTimeMach = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationMach = endTimeMach - startTimeMach;
        errorsMach.push_back(errorMach);
        timingsMach.push_back(durationMach.count()*1000000);

        auto startTimeZeta = std::chrono::high_resolution_clock::now();
        double errorZeta = ompZeta(iterations);
        auto endTimeZeta = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationZeta = endTimeZeta - startTimeZeta;
        errorsZeta.push_back(errorZeta);
        timingsZeta.push_back(durationZeta.count()*1000000);
      }
      writeVectorToFile(errorsMach, "../output/errorMach.txt");
      writeVectorToFile(errorsZeta, "../output/errorZeta.txt");
      writeVectorToFile(timingsMach, "../output/timingMach.txt");
      writeVectorToFile(timingsZeta, "../output/timingZeta.txt");

      if (rank == 0) std::cout << "Error vectors calculated and output. " << std::endl;
      if (rank == 0) std::cout << "Number of threads (openMP, maximum): " << omp_get_max_threads() << std::endl;

      break;
    }
    case 8: {
      if (rank == 0) std::cout << "Question 8: " << std::endl;
      double zeta, mach;
      if (rank == 0) std::cout << "Hybrid implementation of Zeta and Machin with MPI and OpenMP. " << std::endl;
      auto startTimeMach = std::chrono::high_resolution_clock::now();
      mach = hybridMach(n, rank, size, myComm);
      auto endTimeMach = std::chrono::high_resolution_clock::now();
      auto startTimeZeta = std::chrono::high_resolution_clock::now();
      zeta = hybridZeta(n, rank, size, myComm);
      auto endTimeZeta = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> durationMach = endTimeMach - startTimeMach;
      std::chrono::duration<double> durationZeta = endTimeZeta - startTimeZeta;

      if (rank == 0) std::cout << "Returned values for Pi: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << zeta << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << mach << std::endl;
      if (rank == 0) std::cout << "Time taken for calculations: " << std::endl;
      if (rank == 0) std::cout << "\tZeta: " << durationZeta.count() << std::endl;
      if (rank == 0) std::cout << "\tMachin: " << durationMach.count() << std::endl;

      break;
    }
    case 9: {
      if (rank == 0) std::cout << "Question 9: " << std::endl;
      if (rank == 0) std::cout << "No calculations done. " << std::endl;
      break;
    }
    case 10: {
      if (rank == 0) std::cout << "Question 10: " << std::endl;
      if (rank == 0) std::cout << "No calculations done. " << std::endl;
      break;
    }
    default: {
      std::cout << "Exercise number incorrect. Please try again. " << std::endl;
      MPI_Finalize();
      return 1;
    }
  }

  MPI_Finalize();
  return 0;
}
