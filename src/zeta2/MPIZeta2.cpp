#include <iostream>
#include <math.h>
#include <mpi.h>
#include <vector>
#include "../utils.hpp"

double MPIZetaScatterReduce(int n, int rank, int size, MPI_Comm myComm) {
  std::vector<double> values;
  std::vector<double> scattered;
  scattered.reserve(n/size);
  double localResult = 0;
  double result;

  if (rank == 0) {
    // Fill values-vector with values from Riemann Zeta
    for (int i = 1; i <= n; ++i) {
      double value = sqrt(6.0/static_cast<double>(pow(i, 2)));
      values.push_back(value);
    }
  }

  MPI_Scatter(values.data(), values.size()/size, MPI_DOUBLE, scattered.data(), values.size()/size, MPI_DOUBLE, 0, myComm);
  for (int i = 0; i < scattered.size(); ++i) {
    localResult += scattered.at(i);
  }

  MPI_Reduce(&localResult, &result, 1, MPI_DOUBLE, MPI_SUM, 0, myComm);
  return result;
}
