#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H
#include "Observer.h"
#include "Helpers.h"



class AudioPlayer : public Observer {
public:
  AudioPlayer();
  void update();
  void begin();
  void onNotify(Event event);


};

#endif
