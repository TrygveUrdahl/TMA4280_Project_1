#pragma once

// Helper-function to write largest cluster to file.
// Inputs
// theVector: the vector to print to file.
// filename: name of output file to which the lattice is written.
void writeVectorToFile(std::vector<double> &theVector, std::string filename = "../output/vector.txt");


// Function to return one value of the sum for the Machin formula
// Inputs
// x: the value for which to evaluate the Machin formula
// i: which index in the sum to evaluate
double machin(double x, int i);
