#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Adafruit_LSM9DS1.h>
#include <math.h>

#include "constants.h"
#include "kalman.h"
#include "sensor.h"

#define KALMAN_PROCESS_NOISE 0.01
#define KALMAN_MEASUREMENT_NOISE 0.25
#define KALMAN_ERROR 1

class Accelerometer : public virtual Sensor {
  public:
    Accelerometer();
    int init();
    float getRoll();
    float getPitch();
    float getHeading();
    float getAcceleration();
    float getRawAcceleration();
    void getAccelOrientation(sensors_vec_t *orientation);
    void getMagOrientation(sensors_vec_t *orientation);

  protected:
    static Adafruit_LSM9DS1 lsm;

    kalman_t roll;
    kalman_t pitch;
    kalman_t heading;
    kalman_t acceleration;
};

#endif
