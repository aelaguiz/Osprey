#include "clock.h"

Osprey::Clock::Clock() {}

int Osprey::Clock::init() {
  reset();

  return 1;
}

void Osprey::Clock::reset() {
  startTime = millis();
}

int Osprey::Clock::getSeconds() {
  unsigned long runTime = millis() - startTime;

  return runTime / 1000;
}
