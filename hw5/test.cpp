#define CATCH_CONFIG_MAIN
#include "traincar.h"
#include <algorithm>
#include <catch2/catch.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

TEST_CASE("TrainCar::operator==") {
  TrainCar *car = TrainCar::MakeEngine();
  TrainCar *car2 = TrainCar::MakeEngine();
  REQUIRE(*car == *car);
  REQUIRE(*car2 == *car2);
  REQUIRE(*car != *car2);
}

TEST_CASE("TrainCar::Iterator (1)") {
  TrainCar *car = TrainCar::MakeEngine();
  TrainCar::Iterator itr = car->begin();
  REQUIRE(*itr == *car);
  int len = std::distance(car->begin(), car->end());
  REQUIRE(len == 1);

  for (TrainCar traincar : *car) {
    REQUIRE(traincar == *car);
  }

  TrainCar *passenger_car = TrainCar::MakePassengerCar();
  car->connect(passenger_car);
  len = std::distance(car->begin(), car->end());
  REQUIRE(len == 2);
}

TEST_CASE("TrainCar::Iterator (2)") {
  TrainCar *car = TrainCar::MakeEngine();
  TrainCar *passenger_car = TrainCar::MakePassengerCar();
  car->connect(passenger_car);
  auto itr = std::make_reverse_iterator(car->end());
  REQUIRE(*itr == *passenger_car);
}

// TEST_CASE("reverse iterator") {
//   std::string str = "abcd";
//   REQUIRE(*str.begin() == 'a');
//   auto itr = std::make_reverse_iterator(str.end());
//   REQUIRE(*itr == 'd');
//   itr++;
//   REQUIRE(*itr == 'c');
//   std::vector<int> vec = {10, 20, 30};
//   REQUIRE(vec.front() == 10);
//   REQUIRE(*vec.begin() == 10);
//   REQUIRE(*vec.rbegin() == 30);
// }
