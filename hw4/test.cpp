#define CATCH_CONFIG_MAIN
#include "algorithm.cpp"
#include <catch2/catch.hpp>
#include <list>
#include <string>

TEST_CASE("InventoryItem") {
  InventoryItem item = InventoryItem("Into the Wild", 0);
  item.copies()++;
  REQUIRE(item.copies() == 1);
  item.copies() += 4;
  REQUIRE(item.copies() == 5);
  REQUIRE(item == "Into the Wild");
}

TEST_CASE("Inventory::contains") {
  Inventory inventory = {};
  InventoryItem item = InventoryItem("Into the Wild", 0);
  inventory.push_back(item);
  REQUIRE(inventory.contains("Into the Wild"));
}

TEST_CASE("Inventory::operator[]") {
  Inventory inventory = {};
  inventory["Into the Wild"];
  REQUIRE(inventory.size() == 1);

  InventoryItem *item = inventory["Into the Wild"];
  REQUIRE(*item == "Into the Wild");

  REQUIRE(item->copies() == 0);
  REQUIRE(inventory["Into the Wild"]->copies() == 0);

  item->copies()++;
  REQUIRE(item->copies() == 1);
  REQUIRE(inventory["Into the Wild"]->copies() == 1);

  item->copies()++;
  REQUIRE(item->copies() == 2);
  REQUIRE(inventory["Into the Wild"]->copies() == 2);

  *inventory["Into the Wild"] += 1;
  REQUIRE(item->copies() == 3);
  REQUIRE(inventory["Into the Wild"]->copies() == 3);
}

TEST_CASE("Customers::operator[]") {
  Customers customers = {};
  REQUIRE(customers["Keenan"]->preference_list_empty());
  customers["Keenan"]->get_preferences().push_back("Into the Wild");
  REQUIRE(!customers["Keenan"]->preference_list_empty());
}

TEST_CASE("Customer::customer()") {
  Customer customer("Keenan", {});
  REQUIRE(customer.get_preferences().size() == 0);
  customer.get_preferences().push_back("Boyhood");
  REQUIRE(customer.get_preferences().size() == 1);
}

TEST_CASE("Customer::get_movies()") {
  Customer customer("Keenan", {});
  customer.get_movies().push_back("Boyhood");
  std::list<std::string> &movies = customer.get_movies();
  REQUIRE(movies.size() == 1);
  movies.pop_back();
  REQUIRE(customer.get_movies().size() == 0);
}

TEST_CASE("Customer::get_movies() const") {
  const Customer customer("Keenan", {});
  std::list<std::string> movies = customer.get_movies();
  movies.push_back("Boyhood");
  REQUIRE(customer.get_movies().size() == 0);
}
