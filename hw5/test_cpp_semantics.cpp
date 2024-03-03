#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <optional>
#include <vector>

using std::vector;

vector<int> &identity(vector<int> &vec) {
  return vec;
}

TEST_CASE("test") {
  vector<int> vec = {1, 2, 3};
  vector<int> &vec2 = identity(vec);
  vec.pop_back();
  REQUIRE(&vec == &vec2);
  REQUIRE(vec == vec2);
  REQUIRE(vec2 == vector<int>{1, 2});
}

TEST_CASE("optional") {
  std::optional<int> var;
  REQUIRE(var == std::nullopt);
  var = 1;
  REQUIRE(var == 1);
  var.reset();
  REQUIRE(var == std::nullopt);
}
