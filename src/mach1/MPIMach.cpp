#include <iostream>
#include <math.h>
#include <mpi.h>
#include <vector>
#include "../utils.hpp"

double MPIMachBcast(int n, int rank, int size, MPI_Comm myComm) {
  std::vector<double> values;
  values.resize(n);
  double result = 0;

  if (rank == 0) {
    // Fill values-vector with values from Machin
    for (int i = 1; i <= n; ++i) {
      double thisValue = 0;
      thisValue += 4 * machin((double)1/5, i);
      thisValue +=     machin((double)1/239, i);
      thisValue *= 4;
      values.at(i - 1) = thisValue;
    }
  }
  MPI_Bcast(values.data(), values.size(), MPI_DOUBLE, 0, myComm);

  for (int i = 0; i < values.size(); ++i) {
    result += values.at(i);
  }
  return result;
}
