#ifndef SERIALINPUTS_H
#define SERIALINPUTS_H
#include <Arduino.h>
#include "usb_keyboard.h"
#include "Subject.h"
#include "Helpers.h"

#define NUM_KEYS 21

class SerialInputs : public Subject {
private:
  byte keysOnSerial1[NUM_KEYS];
  byte keysOnSerial4[NUM_KEYS];
  byte keysOnSerial5[NUM_KEYS];

public:
  SerialInputs();
  void begin();
  void update();
};

#endif
