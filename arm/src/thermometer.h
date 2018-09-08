#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <Adafruit_BMP280.h>
#include "constants.h"
#include "sensor.h"

class Thermometer : public virtual Sensor {
  public:
    Thermometer();
    int init();
    float getTemperature();

  protected:
    static Adafruit_BMP280 thermometer;
};

#endif
