#ifndef GPS_H
#define GPS_H

#include <stdlib.h>
#include "fona.h"

#include "sensor.h"

#define ISO_8601_LENGTH 32

#define OUT_OF_RANGE_DELTA 0.001
#define OUT_OF_RANGE_LIMIT 5

#define KALMAN_PROCESS_NOISE 0.01
#define KALMAN_MEASUREMENT_NOISE 0.25
#define KALMAN_ERROR 1

class GPS : public virtual Sensor {
  public:
    GPS(FONA &fona);
    int init();

    bool update();
    float getLatitude();
    float getLongitude();
    float getSpeed();
    float getAltitude();
    int getQuality();
    char* getIso8601();

  protected:
    FONA &fona;
    int validCoordinate(float previous, float next, int *outOfRange);

    char iso8601[ISO_8601_LENGTH];

    float latitude;
    float longitude;

    int latitudeOutOfRange;
    int longitudeOutOfRange;

    kalman_t speed;
    kalman_t altitude;
};

#endif
