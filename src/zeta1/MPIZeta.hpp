#pragma once

double MPIZetaBcast(int n, int rank, int size, MPI_Comm myComm);

double MPIZetaScatterReduce(int n, int rank, int size, MPI_Comm myComm);
