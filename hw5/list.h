#ifndef LIST_H_
#define LIST_H_
#include <concepts>
#include <initializer_list>
#include <iterator>
#include <optional>

// template <typename T>
// concept pointer = std::is_pointer_v<T>;

template <typename T>
class List {
  class Iterator;

public:
  T front_;
  std::optional<T> last_;

  List(){};

  List(std::initializer_list<T> initlist) {
    for (auto item : initlist) {
      this->push_back(item);
    }
  }

  // Iterator begin() {
  //   return Iterator(this, last_);
  // }

  // Iterator end() {
  //   return Iterator(nullptr, last_);
  // }

  // std::reverse_iterator<Iterator> rbegin() {
  //   std::vector<TrainCar> vec(begin(), end());
  //   TrainCar caboose = *vec.rbegin();
  //   Iterator itr(&caboose);
  //   return std::reverse_iterator<Iterator>(itr);
  // }

  // std::reverse_iterator<Iterator> rend() {
  //   return std::reverse_iterator<Iterator>(this->begin());
  // }

  void push_back(T item) {
    if (this->front_ == nullptr) {
      this->front_ = item;
    }
    // this->front_ = item;
    // this->last_->next = item;
    // item->prev = this->last;
    // this->last_ = item;
  }
};

template <pointer T>
class List<T>::Iterator {
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T *;
  using reference = T &;

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

#endif // LIST_H_
