#ifndef OBSERVER_H
#define OBSERVER_H

#include "Helpers.h"
class Observer
{
public:
  virtual ~Observer() {}
  virtual void onNotify(Event event) = 0;
};

#endif
