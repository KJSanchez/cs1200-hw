#ifndef _TRAIN_H_
#define _TRAIN_H_
#include <cstddef>
#include <iterator>
#include <ostream>
#include <vector>

class TrainCar {
public:
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
