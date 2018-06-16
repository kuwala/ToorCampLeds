#ifndef SERIALINPUTS_H
#define SERIALINPUTS_H
#include <Arduino.h>
#include "usb_keyboard.h"
#include "Subject.h"
#include "Helpers.h"

#define NUM_KEYS 21

class SerialInputs : public Subject {
private:
  const byte keysOnSerial1[NUM_KEYS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
  const byte keysOnSerial4[NUM_KEYS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
  const byte keysOnSerial5[NUM_KEYS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};

public:
  SerialInputs();
  void begin();
  void update();
};

#endif
