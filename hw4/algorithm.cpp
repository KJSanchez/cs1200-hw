#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

using std::string, std::vector, std::list;

class InventoryItem {
private:
  const string name_;
  unsigned int copies_;
  unsigned int checked_out_;

public:
  InventoryItem(string name, int copies)
      : name_(name), copies_(copies), checked_out_(0){};

  string get_name() const {
    return this->name_;
  }

  unsigned int &copies() {
    return this->copies_;
  }

  unsigned int copies() const {
    return this->copies_;
  }

  unsigned int checked_out() const {
    return this->checked_out_;
  }

  bool available() const {
    return this->copies_ > 0;
  }

  bool operator==(string name) const {
    return this->name_ == name;
  }

  void operator+=(int copies) {
    this->copies_ += copies;
  }

  void shipped() {
    this->copies_ -= 1;
    this->checked_out_ += 1;
  }
};

std::ostream &operator<<(std::ostream &os, const InventoryItem &item) {
  os << item.get_name() << ":" << std::endl;
  os << "\t" << item.checked_out() << " copy checked out and " << item.copies()
     << " available" << std::endl;
  return os;
}

class Customer {
private:
  const string name_;
  std::list<string> preferences_;
  std::list<string> movies_;

public:
  Customer(string name, list<string> preferences)
      : name_(name), preferences_(preferences) {
  }

  string get_name() const {
    return this->name_;
  }

  void receives(const string &preference) {
    preferences_.remove(preference);
    movies_.push_back(preference);
  }

  bool has_max_num_movies() const {
    return this->movies_.size() >= 3;
  }

  bool preference_list_empty() const {
    return this->preferences_.size() == 0;
  }

  std::list<string> &get_preferences() {
    return this->preferences_;
  }

  std::list<string> get_preferences() const {
    return this->preferences_;
  }

  std::list<string> &get_movies() {
    return this->movies_;
  }

  std::list<string> get_movies() const {
    return this->movies_;
  }

  bool operator==(string name) const {
    return this->name_ == name;
  }
};

std::ostream &operator<<(std::ostream &os, Customer &customer) {
  os << customer.get_name() << " has " << customer.get_movies().size()
     << " movies:" << std::endl;
  for (auto movie : customer.get_movies()) {
    os << "\t" << movie << std::endl;
  }
  return os;
}

class Inventory : public std::list<InventoryItem> {
public:
  bool contains(string dvd_name) {
    return std::find(this->begin(), this->end(), dvd_name) != this->end();
  }

  InventoryItem *operator[](string dvd_name) {
    if (!this->contains(dvd_name)) {
      InventoryItem item = InventoryItem(dvd_name, 0);
      this->push_back(item);
    }
    Inventory::iterator itr = std::find(this->begin(), this->end(), dvd_name);
    return &(*itr);
  }

  // A helper function to find a DVD from the inventory
  Inventory::iterator find_DVD(const std::string &dvd_name) {
    return find(this->begin(), this->end(), dvd_name);
  };
};

class Customers : public std::list<Customer> {
public:
  bool contains(string name) {
    return std::find(this->begin(), this->end(), name) != this->end();
  }

  Customer *operator[](string name) {
    if (!this->contains(name)) {
      Customer customer(name, {});
      this->push_back(customer);
    }
    Customers::iterator itr = find(this->begin(), this->end(), name);
    return &(*itr);
  }
};

typedef Inventory inventory_type;
typedef Customers customers_type;
typedef std::vector<string> preference_type;

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers,
                        std::ostream &ostr) {
  ostr << "Ship DVDs" << std::endl;

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  Customers::iterator customer_itr = customers.begin();

  while (customer_itr != customers.end()) {

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->has_max_num_movies() ||
        customer_itr->preference_list_empty()) {
      // move on to the next customer
      customer_itr++;

      continue;
    }

    // a helper flag variable
    bool sent_dvd = false;

    // loop over the customer's preferences
    for (auto preference : customer_itr->get_preferences()) {
      // locate this DVD in the inventory

      inventory_type::iterator inventory_itr = inventory.find_DVD(preference);
      if (inventory_itr != inventory.end() && inventory_itr->available()) {

        // if the DVD is available, ship it to the customer!

        ostr << "  " << customer_itr->get_name() << " receives " << preference
             << std::endl;
        inventory_itr->shipped();
        customer_itr->receives(preference);

        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        // after setting the flag to true, leave the iteration over
        // preferences
        sent_dvd = true;
        break;
      }
    }

    // if no DVD was sent to this customer, then we move on to the next
    // customer (do not change this customer's priority for tomorrow's
    // shipment)
    if (!sent_dvd) {
      customer_itr++;
    }
  }
}
