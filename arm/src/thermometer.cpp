#include "thermometer.h"

Adafruit_BMP280 Thermometer::thermometer = Adafruit_BMP280();

Thermometer::Thermometer() {}

int Thermometer::init() {
  return thermometer.begin();
}

float Thermometer::getTemperature() {
  // Get ambient temperature (in celsius)
  float temperature = thermometer.readTemperature();

  return temperature;
}
