#define CATCH_CONFIG_MAIN
#include "list.h"
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

TEST_CASE("test") {
  TrainCar *car = TrainCar::MakeEngine();
  // TrainCar *car2 = TrainCar::MakeEngine();
  List<TrainCar &> train;
  // train.front_ = car;
  train.push_back(car);
  // REQUIRE(train.front_ == car);
  REQUIRE(*train.front_ == *car);
}

// TEST_CASE("List::Iterator (1)") {
//   TrainCar *car = TrainCar::MakeEngine();
//   List<TrainCar> train = {car};
//   // TrainCar::Iterator itr = car->begin();
//   REQUIRE(*itr == *car);
//   int len = std::distance(train.begin(), train.end());
//   REQUIRE(len == 1);

//   for (TrainCar traincar : train) {
//     REQUIRE(traincar == *car);
//   }

//   TrainCar *passenger_car = TrainCar::MakePassengerCar();
//   train.push_back(passenger_car);
//   len = std::distance(train.begin(), train.end());
//   REQUIRE(len == 2);
// }

// TEST_CASE("TrainCar::Iterator (2)") {
//   TrainCar *car = TrainCar::MakeEngine();
//   TrainCar *passenger_car = TrainCar::MakePassengerCar();
//   List<TrainCar> train = {car, passenger_car};
//   auto itr = std::make_reverse_iterator(train.end());
//   REQUIRE(*itr == *passenger_car);
// }

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
