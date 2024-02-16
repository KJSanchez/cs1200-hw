#include "hockey_stats.cpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    throw std::runtime_error("usage");
  }

  ifstream input_file(argv[1]);
  ofstream output_file(argv[2]);
  HockeyStats stats;
  input_file >> stats;
  output_file << stats;
  return 0;
}
