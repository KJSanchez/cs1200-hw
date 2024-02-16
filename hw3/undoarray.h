#ifndef UNDOARRAY_H_
#define UNDOARRAY_H_
#include <stdexcept>

template <typename T> class UndoArray {
public:
  unsigned int *counts_;
  int size_;
  T **values_;

  UndoArray(unsigned int size) {
    this->size_ = size;
    this->counts_ = new unsigned int[size];
    this->values_ = new T *[size];
  };

  unsigned int size() {
    return this->size_;
  };

  bool initialized(unsigned int key) {
    return this->values_[key] != nullptr;
  };

  void set(unsigned int key, T value) {
    unsigned int size = this->counts_[key];
    T *new_values = new T[size + 1];
    for (unsigned int i = 0; i < size; i++) {
      new_values[i] = this->values_[key][i];
    }
    new_values[size] = value;
    delete[] this->values_[key];
    this->values_[key] = new_values;
    this->counts_[key]++;
  }

  void undo(unsigned int key) {
    unsigned int size = this->counts_[key];
    if (size == 0) {
      throw std::domain_error("UndoException");
    }
    T *new_values = new T[size - 1];
    for (int i = 0; i < size - 1; i++) {
      new_values[i] = this->values_[key][i];
    }
    delete[] this->values_[key];
    this->values_[key] = new_values;
    this->counts_[key]--;
  }

  T get(unsigned int key) {
    unsigned int index = this->counts_[key];
    if (index == 0) {
      throw std::domain_error("GetException");
    }
    return this->values_[key][index - 1];
  }
};

#endif // UNDOARRAY_H_
