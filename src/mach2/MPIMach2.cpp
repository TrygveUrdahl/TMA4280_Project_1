#include <iostream>
#include <math.h>
#include <mpi.h>
#include <vector>
#include <assert.h>
#include "../utils.hpp"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

double MPIMachScatterReduce(int n, int rank, int size, MPI_Comm myComm) {
  std::vector<double> values, scattered;
  scattered.resize(n/size);
  double localResult = 0;
  double result = 0;

  // Check that size is a power of two
  assert((size != 0) && ((size &(size - 1)) == 0));

  if (rank == 0) {
    // Fill values-vector with values from Machin
    for (int i = 1; i <= n; ++i) {
      double thisValue = 0;
      thisValue += 4 * machin((double)1/5, i);
      thisValue +=     machin((double)1/239, i);
      thisValue *= 4;
      values.push_back(thisValue);
    }
  }
  // Distribute data
  MPI_Scatter(values.data(),values.size()/size, MPI_DOUBLE, scattered.data(), values.size()/size, MPI_DOUBLE, 0, myComm);
  // Do calculations on each process
  for (int i = 0; i < scattered.size(); ++i) {
    localResult += scattered.at(i);
  }
  // Reduce all back to root
  MPI_Reduce(&localResult, &result, 1, MPI_DOUBLE, MPI_SUM, 0, myComm);
  return abs(result - M_PI);
}
