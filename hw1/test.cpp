#define CATCH_CONFIG_MAIN
#include "justify.hpp"
#include <catch2/catch.hpp>
#include <string>

TEST_CASE("[example_16_flush_left.txt]") {
  std::string expected = R"(
--------------------
| Here is an       |
| example of text  |
| justification.   |
--------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 20, "flush_left");
  REQUIRE(expected == actual);
}

TEST_CASE("[example_16_flush_right.txt]") {
  std::string expected = R"(
--------------------
|       Here is an |
|  example of text |
|   justification. |
--------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 20, "flush_right");
  REQUIRE(expected == actual);
}

TEST_CASE("[example_16_full_justify.txt]") {
  std::string expected = R"(
--------------------
| Here    is    an |
| example  of text |
| justification.   |
--------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 20, "full_justify");
  REQUIRE(expected == actual);
}

TEST_CASE("[example_15_flush_left.txt]") {
  std::string expected = R"(
-------------------
| Here is an      |
| example of text |
| justification.  |
-------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 19, "flush_left");
  REQUIRE(expected == actual);
}

TEST_CASE("[example_15_flush_right.txt]") {
  std::string expected = R"(
-------------------
|      Here is an |
| example of text |
|  justification. |
-------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 19, "flush_right");
  REQUIRE(expected == actual);
}

TEST_CASE("[example_15_full_justify.txt]") {
  std::string expected = R"(
-------------------
| Here    is   an |
| example of text |
| justification.  |
-------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 19, "full_justify");
  REQUIRE(expected == actual);
}

TEST_CASE("[example_14_flush_left.txt]") {
  std::string expected = R"(
------------------
| Here is an     |
| example of     |
| text           |
| justification. |
------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 18, "flush_left");
  REQUIRE(expected == actual);
}

TEST_CASE("[example_14_flush_right.txt]") {
  std::string expected = R"(
------------------
|     Here is an |
|     example of |
|           text |
| justification. |
------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 18, "flush_right");
  REQUIRE(expected == actual);
}

TEST_CASE("[example_14_full_justify.txt]") {
  std::string expected = R"(
------------------
| Here   is   an |
| example     of |
| text           |
| justification. |
------------------
)";

  std::string fcontents = "Here is an example of text justification.";

  std::string actual = justify(fcontents, 18, "full_justify");
  REQUIRE(expected == actual);
}
