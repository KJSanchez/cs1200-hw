#ifndef _TRAIN_H_
#define _TRAIN_H_
#include <cstddef>
#include <iterator>
#include <ostream>
#include <vector>

class TrainCar {
public:
  class Iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = TrainCar;
    using pointer = TrainCar *;
    using reference = TrainCar &;

    explicit Iterator(pointer ptr, pointer last)
        : m_ptr(ptr), m_ptr_last(last) {
    }

    reference operator*() const {
      return *m_ptr;
    }

    pointer operator->() {
      return m_ptr;
    }

    Iterator &operator++() {
      m_ptr = m_ptr->next;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    Iterator &operator--() {
      if (m_ptr != nullptr) {
        m_ptr = m_ptr->prev;
      } else {
        m_ptr = m_ptr_last;
      }
      return *this;
    }

    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.m_ptr == b.m_ptr;
    };

    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.m_ptr != b.m_ptr;
    };

  private:
    pointer m_ptr;
    pointer m_ptr_last;
  };

  static TrainCar *MakeEngine() {
    return new TrainCar('e', 150);
  }
  static TrainCar *MakeFreightCar(int weight) {
    return new TrainCar('f', weight);
  }
  static TrainCar *MakePassengerCar() {
    return new TrainCar('p', 50);
  }
  static TrainCar *MakeDiningCar() {
    return new TrainCar('d', 50);
  }
  static TrainCar *MakeSleepingCar() {
    return new TrainCar('s', 50);
  }

  Iterator begin() {
    return Iterator(this, last);
  }

  Iterator end() {
    return Iterator(nullptr, last);
  }

  std::reverse_iterator<Iterator> rbegin() {
    std::vector<TrainCar> vec(begin(), end());
    TrainCar caboose = *vec.rbegin();
    Iterator itr(&caboose);
    return std::reverse_iterator<Iterator>(itr);
  }

  std::reverse_iterator<Iterator> rend() {
    return std::reverse_iterator<Iterator>(this->begin());
  }

  TrainCar *connect(TrainCar *other) {
    this->next = other;
    other->prev = this;
    return other;
  }

  int getID() const {
    return id;
  }
  int getWeight() const {
    return weight;
  }
  bool isEngine() const {
    return type == 'e';
  }
  bool isFreightCar() const {
    return type == 'f';
  }
  bool isPassengerCar() const {
    return type == 'p';
  }
  bool isDiningCar() const {
    return type == 'd';
  }
  bool isSleepingCar() const {
    return type == 's';
  }
  bool operator==(const TrainCar &other) const {
    return this->getID() == other.getID();
  }
  bool operator!=(const TrainCar &other) const {
    return this->getID() != other.getID();
  }

  char getType() const {
    return this->type;
  }

private:
  TrainCar(char t, int w)
      : type(t), weight(w), prev(NULL), next(NULL) {
    static int next_id = 100;
    id = next_id;
    next_id++;
  }

  int id;
  char type;
  int weight;

public:
  TrainCar *prev;
  TrainCar *next;
  TrainCar *last;
};

std::ostream &operator<<(std::ostream &os, const TrainCar &car);

void SanityCheck(TrainCar *train);
void PrintTrain(TrainCar *train);

#endif
