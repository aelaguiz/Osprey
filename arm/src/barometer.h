#ifndef BAROMETER_H
#define BAROMETER_H

#include <Adafruit_BMP280.h>

#include "constants.h"
#include "sensor.h"

#define KALMAN_PROCESS_NOISE 0.01
#define KALMAN_MEASUREMENT_NOISE 0.25
#define KALMAN_ERROR 1

class Barometer : public virtual Sensor {
	public:
		Barometer();
		int init();
		float getPressure();
		float getAltitudeAboveSeaLevel();
		float getAltitudeAboveGround();
		void setPressureSetting(float pressure);
		float getPressureSetting();
		float getTemperature();
		void zero();

	protected:
		static float pressureSetting;

		static Adafruit_BMP280 barometer;

		float groundLevel;
		kalman_t altitude;

		float getPressureAltitude(float setting);
		void setGroundLevel();
};

#endif
