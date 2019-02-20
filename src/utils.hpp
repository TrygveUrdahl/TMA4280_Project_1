#pragma once

// Helper-function to write largest cluster to file.
// Inputs
// theVector: the vector to print to file.
// filename: name of output file to which the lattice is written.
void writeVectorToFile(std::vector<double> &theVector, std::string filename = "../output/vector.txt");
