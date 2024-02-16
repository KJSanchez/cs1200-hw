// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include "algorithm.cpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

using std::list, std::string;

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);

// ==================================================================

void usage(const char *program_name) {
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>"
            << std::endl;
  std::cerr << " -or-  " << program_name
            << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name
            << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name
            << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}

int main(int argc, char *argv[]) {

  if (argc < 3 || argc > 5) {
    usage(argv[0]);
  }

  // open input and output file streams
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "ERROR: Could not open " << argv[1] << " for reading."
              << std::endl;
    usage(argv[0]);
  }
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "ERROR: Could not open " << argv[2] << " for writing."
              << std::endl;
    usage(argv[0]);
  }

  // // optional parameters for extra credit
  // bool use_improved_algorithm = false;
  // bool print_analysis = false;
  // for (int i = 3; i < argc; i++) {
  //   if (std::string(argv[i]) == "--improved") {
  //     use_improved_algorithm = true;
  //   } else if (std::string(argv[i]) == "--analysis") {
  //     print_analysis = true;
  //   } else {
  //     usage(argv[0]);
  //   }
  // }

  // stores information about the DVDs
  inventory_type inventory;
  // stores information about the customers
  customers_type customers;

  // read in and handle each of the 8 keyword tokens
  std::string token;
  while (istr >> token) {
    if (token == "dvd") {
      std::string dvd_name = read_dvd_name(istr);
      int copies;
      istr >> copies;
      *inventory[dvd_name] += copies;
      ostr << copies << " copies of " << dvd_name << " added" << std::endl;
    } else if (token == "customer") {
      std::string customer_name = read_customer_name(istr);
      int num_movies;
      istr >> num_movies;
      std::list<string> preferences;
      for (int i = 0; i < num_movies; i++) {
        std::string dvd_name = read_dvd_name(istr);
        preferences.push_back(dvd_name);
      }
      Customer customer(customer_name, preferences);
      customers.push_back(customer);
      ostr << "new customer: " << customer_name << std::endl;
    } else if (token == "ship") {
      shipping_algorithm(inventory, customers, ostr);
    } else if (token == "return_oldest") {
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = customers[customer_name]->get_movies().back();
      inventory[dvd_name]->copies()++;
      customers[customer_name]->get_movies().pop_front();
    } else if (token == "return_newest") {
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = customers[customer_name]->get_movies().front();
      inventory[dvd_name]->copies()++;
      customers[customer_name]->get_movies().pop_back();
    } else if (token == "print_customer") {
      std::string customer_name = read_customer_name(istr);
      ostr << *customers[customer_name] << std::endl;
    } else if (token == "print_dvd") {
      std::string dvd_name = read_dvd_name(istr);
      ostr << *inventory[dvd_name] << std::endl;
    } else if (token == "add_preference") {
      std::string customer_name = read_customer_name(istr);
      std::string dvd_name = read_dvd_name(istr);
      customers[customer_name]->get_preferences().push_back(dvd_name);
    } else {
      std::cerr << "ERROR: Unknown token " << token << std::endl;
      exit(1);
    }
  }
}

// ==================================================================

// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}

// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
  std::string token;
  istr >> token;
  assert(token[0] == '"');
  std::string answer = token;
  while (answer[answer.size() - 1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}
