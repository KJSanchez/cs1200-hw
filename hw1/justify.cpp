#include "justify.hpp"
#include <boost/algorithm/string.hpp>
#include <memory>
#include <set>
#include <string>
#include <vector>

using namespace std;

string justify(string fcontents, int width, string flush_type) {
  set<string> flush_types = {"flush_left", "flush_right"};
  if (!flush_types.contains(flush_type)) {
    throw runtime_error("unrecognized flush_type");
  }
  vector<string> tokens;
  boost::split(tokens, fcontents, boost::is_any_of(" "));
  string result;
  string parts;

  int actual_width = width - 4;

  for (const string &word : tokens) {
    if (parts.length() == 0) {
      parts = word;
      continue;
    }

    if ((parts + " " + word).length() <= actual_width) {
      parts += " " + word;
    } else {
      if (flush_type == "flush_left") {
        result +=
            "| " + parts + string(actual_width - parts.length(), ' ') + " |\n";
      } else if (flush_type == "flush_right") {
        result +=
            "| " + string(actual_width - parts.length(), ' ') + parts + " |\n";
      }
      parts.clear();
      parts = word;
    }
  }
  if (parts.length() != 0) {
    if (flush_type == "flush_left") {
      result +=
          "| " + parts + string(actual_width - parts.length(), ' ') + " |";
    } else if (flush_type == "flush_right") {
      result +=
          "| " + string(actual_width - parts.length(), ' ') + parts + " |";
    }
  }

  return "\n" + string(width, '-') + "\n" + result + "\n" + string(width, '-') +
         "\n";
}
