#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
// #include <vector>
#include <vector>
// import <iostream>;
// import container;
// #include "container.cpp"
// import container;

using std::vector;

TEST_CASE("reference type demonstration") {
  vector<int> vec = {1, 2, 3};
  REQUIRE(vec == vector<int>{1, 2, 3});
  vector<int> &vec2 = vec;
  vec.pop_back();
  REQUIRE(vec == vector<int>{1, 2});
  REQUIRE(vec2 == vector<int>{1, 2});
}

TEST_CASE("non-reference type demonstration") {
  vector<int> vec = {1, 2, 3};
  REQUIRE(vec == vector<int>{1, 2, 3});
  vector<int> vec2 = vec;
  vec.pop_back();
  REQUIRE(vec == vector<int>{1, 2});
  REQUIRE(vec2 == vector<int>{1, 2, 3});
}

TEST_CASE("module demo") {
  REQUIRE(container::foo == 100);
}
