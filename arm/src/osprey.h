#ifndef OSPREY_H
#define OSPREY_H

#include "accelerometer.h"
#include "barometer.h"
#include "battery.h"
#include "clock.h"
#include "constants.h"
#include "event.h"
#include "gps.h"
#include "radio.h"
#include "fona.h"

#define HEARTBEAT_LED 13
#define HEARTBEAT_INTERVAL 25

namespace Osprey {
  Accelerometer accelerometer;
  Barometer barometer;
  Battery battery;
  Event event;
  Osprey::Clock clock;
  FONA fona;
  GPS gps(fona);
  Radio radio;

  extern int commandStatus;
  int counter;

  void printJSON();
  void heartbeat();
  void initSensors();
  void printInitError(const char* const message);
  extern void processCommand();
}

#endif
