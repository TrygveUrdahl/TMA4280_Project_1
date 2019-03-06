#include <iostream>
#include <math.h>
#include <vector>
#include <mpi.h>
#include <assert.h>
#include <omp.h>
#include "../utils.hpp"

double hybridMach(int n, int rank, int size, MPI_Comm myComm) {
  std::vector<double> values;
  std::vector<double> scattered;
  scattered.resize(n/size);
  values.resize(n);
  double localResult = 0;
  double result = 0;

  // Check that size is a power of two
  assert((size != 0) && ((size &(size - 1)) == 0));

  if (rank == 0) {
    // Fill values-vector with values from Machin
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
      double thisValue = 0;
      thisValue += 4 * machin((double)1/5, i + 1);
      thisValue +=     machin((double)1/239, i + 1);
      thisValue *= 4;
      values.at(i) = thisValue;
    }
  }

  MPI_Scatter(values.data(),values.size()/size, MPI_DOUBLE, scattered.data(), values.size()/size, MPI_DOUBLE, 0, myComm);

  #pragma omp parallel for reduction(+:localResult) schedule(static)
  for (int i = 0; i < scattered.size(); ++i) {
    localResult += scattered.at(i);
  }

  MPI_Reduce(&localResult, &result, 1, MPI_DOUBLE, MPI_SUM, 0, myComm);

  return result;
}
