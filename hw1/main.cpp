#include "justify.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  string input_filename = argv[1];
  string output_filename = argv[2];
  int width = atoi(argv[3]);
  string flush_type = argv[4];
  unique_ptr<ifstream> input_file = make_unique<ifstream>(argv[1]);
  unique_ptr<ofstream> output_file = make_unique<ofstream>(argv[2]);

  string fcontents;
  fcontents.assign(istreambuf_iterator<char>(*input_file),
                   istreambuf_iterator<char>());
  *output_file << justify(fcontents, width, flush_type);
  return 0;
}
