#include "Subject.h"

Subject::Subject() {
  numObservers_ = 0;
}

void Subject::addObserver(Observer* observer) {
  if (numObservers_ < MAX_OBSERVERS) {
    observers_[numObservers_] = observer;
    numObservers_++;
  }
}

void Subject::removeObserver(Observer* observer) {
  for (int i = 0; i < numObservers_; i++) {
    if (observers_[i] == observer) {
      // observers_[i] = NULL;
      for (int j = i; j < numObservers_ - 1; j++) {
        // shift all these after the one to fill the removed observers spot
        observers_[j] = observers_[j+1];
      }

    }
  }
}
void Subject::notify(Event event) {
  for (int i = 0; i < numObservers_; i++) {
    if (observers_[i]) {
      observers_[i]->onNotify(event);
    }
  }
}
