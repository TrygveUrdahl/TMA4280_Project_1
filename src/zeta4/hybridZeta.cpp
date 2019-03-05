#include <iostream>
#include <math.h>
#include <vector>
#include <mpi.h>
#include <assert.h>
#include <omp.h>
#include "../utils.hpp"

double hybridZeta(int n, int rank, int size, MPI_Comm myComm) {
  std::vector<double> values(n);
  std::vector<double> scattered(n/size);
  double localResult = 0;
  double result;

  // Check that size is a power of two
  assert((size != 0) && ((size &(size - 1)) == 0));

  if (rank == 0) {
    // Fill values-vector with values from Riemann Zeta
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
      double value = 6.0/static_cast<double>(pow(i + 1, 2));
      values.at(i) = value;
    }
  }

  MPI_Scatter(values.data(), values.size()/size, MPI_DOUBLE, scattered.data(),
        values.size()/size, MPI_DOUBLE, 0, myComm);
  //std::cout << "value: " << scattered.at(0) << std::endl; // Causes segfault

  #pragma omp parallel for reduction(+:localResult) schedule(static)
  for (int i = 0; i < scattered.size(); ++i) {
    localResult += scattered.at(i);
  }

  MPI_Reduce(&localResult, &result, 1, MPI_DOUBLE, MPI_SUM, 0, myComm);
  return sqrt(result);
}
