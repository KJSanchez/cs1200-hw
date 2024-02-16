#define CATCH_CONFIG_MAIN
#include "hockey_stats.cpp"
#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("test", "test") {
  std::istringstream iss(R"(
Friday, November 9, 2012
Clarkson at Yale
PERIOD 1
10:28 Clarkson penalty Jarrett_Burton  2:00 Holding
17:51 Clarkson goal Jarrett_Burton (   )
17:51 Clarkson goal Jarrett_Burton ( Will_Frederick  )
17:51 Clarkson goal Jarrett_Burton ( Will_Frederick  Brock_Higgs )
PERIOD 2
PERIOD 3
FINAL
Clarkson 1
Yale 0
)");
  HockeyStats stats;
  iss >> stats;
  REQUIRE(stats.goals == 3);
  REQUIRE(stats.penalties == 1);
  REQUIRE(stats.stats["Clarkson"]["Jarrett_Burton"]["penalties"] == 1);
  REQUIRE(stats.stats["Clarkson"]["Jarrett_Burton"]["goals"] == 3);
  REQUIRE(stats.stats["Clarkson"]["Will_Frederick"]["assists"] == 2);
  REQUIRE(stats.stats["Clarkson"]["Brock_Higgs"]["assists"] == 1);
}
