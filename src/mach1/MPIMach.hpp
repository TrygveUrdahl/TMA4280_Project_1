#pragma once

double MPIMachBcast(int n, int rank, int size, MPI_Comm myComm);

double MPIMachScatterReduce(int n, int rank, int size, MPI_Comm myComm);
