#define CATCH_CONFIG_MAIN
#include "undoarray.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

using std::cout, std::endl;

TEST_CASE("sizeof", "size") {
  int a[] = {1, 2, 3};
  REQUIRE(sizeof(a) / sizeof(int) == 3);

  UndoArray<std::string> ua(300);
  REQUIRE(ua.values_[0] == nullptr);
  REQUIRE(sizeof(ua.values_[0]) == 8);
  REQUIRE(sizeof(nullptr) == 8);
  REQUIRE(sizeof(unsigned int) == 4);
}

TEST_CASE("test", "test") {
  UndoArray<std::string> ua(2);
  REQUIRE(ua.size() == 2);

  for (unsigned int i = 0; i < ua.size(); i++) {
    REQUIRE(ua.counts_[i] == 0);
    REQUIRE(ua.initialized(i) == false);
    REQUIRE_THROWS_AS(ua.get(i), std::domain_error);
    REQUIRE_THROWS_AS(ua.undo(i), std::domain_error);
  }

  ua.set(0, "a");
  REQUIRE(ua.initialized(0) == true);
  REQUIRE(ua.counts_[0] == 1);
  REQUIRE(ua.values_[0][0] == "a");
  REQUIRE(ua.get(0) == "a");
  ua.undo(0);
  REQUIRE_THROWS_AS(ua.undo(0), std::domain_error);
  REQUIRE(ua.counts_[0] == 0);
  REQUIRE(ua.initialized(0) == true);
  REQUIRE_THROWS_AS(ua.get(0), std::domain_error);

  ua.set(0, "a");
  ua.set(0, "aa");
  REQUIRE(ua.initialized(0) == true);
  REQUIRE(ua.counts_[0] == 2);
  REQUIRE(ua.values_[0][0] == "a");
  REQUIRE(ua.values_[0][1] == "aa");
  REQUIRE(ua.get(0) == "aa");

  ua.undo(0);
  REQUIRE(ua.get(0) == "a");
  REQUIRE(ua.initialized(0) == true);
  REQUIRE(ua.counts_[0] == 1);
  REQUIRE(ua.values_[0][0] == "a");
  REQUIRE(ua.get(0) == "a");

  ua.set(1, "b");
  assert(ua.initialized(1) == true);
  REQUIRE(ua.counts_[1] == 1);
  REQUIRE(ua.values_[1][0] == "b");
  assert(ua.get(1) == "b");
}
