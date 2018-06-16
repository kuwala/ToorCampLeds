#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include "Helpers.h"

#define MAX_OBSERVERS 8

class Subject {
private:
  Observer* observers_[MAX_OBSERVERS];
  int numObservers_;
protected:
  void notify(Event event);

public:
  Subject();
  void addObserver(Observer* observer);
  void removeObserver(Observer* observer);



};

#endif
