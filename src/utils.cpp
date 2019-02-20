#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Helper-function to write largest cluster to file.
// Inputs
// theVector: the vector to print to file, by reference to avoid copying.
// filename: name of output file to which the lattice is written.

void writeVectorToFile(std::vector<double> &theVector, std::string filename = "../output/vector.txt") {
  std::ofstream file;
  file.open(filename);
  if (!file.is_open()) {
    // TODO: Raise error!
  }
  for (auto elem : theVector) {
    file << elem << std::endl;
  }
  file.close();
}
