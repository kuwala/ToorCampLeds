#ifndef KEYBOARD_PRESSER_H
#define KEYBOARD_PRESSER_H
#include "usb_keyboard.h"
#include "Observer.h"
#include "Helpers.h"

class KeyboardPresser : public Observer {
public:
  KeyboardPresser();
  void update();
  void onNotify(Event event);

};

#endif
