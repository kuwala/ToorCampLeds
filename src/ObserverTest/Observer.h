#ifndef OBSERVER_H
#define OBSERVER_H
class Observer
{
public:
  virtual ~Observer() {}
  virtual void onNotify(const Entity& entity, Event event) = 0;
};

#endif
