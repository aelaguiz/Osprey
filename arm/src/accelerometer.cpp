#include "accelerometer.h"

Adafruit_LSM9DS1 Accelerometer::lsm = Adafruit_LSM9DS1();

Accelerometer::Accelerometer() : Sensor(KALMAN_PROCESS_NOISE, KALMAN_MEASUREMENT_NOISE, KALMAN_ERROR) {
	roll = kalmanInit(0);
	pitch = kalmanInit(90);
	heading  = kalmanInit(0);
	acceleration  = kalmanInit(1);
}

int Accelerometer::init() {
	return lsm.begin();
}

float Accelerometer::getRoll() {
	sensors_vec_t orientation;
	getAccelOrientation(&orientation);

	if(!orientation.roll) {
		return NO_DATA;
	}

	kalmanUpdate(&roll, orientation.roll);
	return roll.value;
}

float Accelerometer::getPitch() {
	sensors_vec_t orientation;
	getAccelOrientation(&orientation);

	if(!orientation.pitch) {
		return NO_DATA;
	}

	kalmanUpdate(&pitch, orientation.pitch);
	return pitch.value;
}

float Accelerometer::getHeading() {
	sensors_event_t a, m, g, temp;
	lsm.getEvent(&a, &m, &g, &temp);

	float fHeading;

	if (m.magnetic.y > 0)
	{
		fHeading = 90 - (atan(m.magnetic.x / m.magnetic.y) * (180 / M_PI));
	}
	else if (m.magnetic.y < 0)
	{
		fHeading = - (atan(m.magnetic.x / m.magnetic.y) * (180 / M_PI));
	}
	else // hy = 0
	{
		if (m.magnetic.x < 0) fHeading = 180;
		else fHeading = 0;
	}

	kalmanUpdate(&heading, fHeading);
	return heading.value;
}

float Accelerometer::getAcceleration() {
	kalmanUpdate(&acceleration, getRawAcceleration());
	return acceleration.value;
}

float Accelerometer::getRawAcceleration() {
	sensors_event_t a, m, g, temp;
	lsm.getEvent(&a, &m, &g, &temp);

	return sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)) * MS2_TO_G;
}

void Accelerometer::getAccelOrientation(sensors_vec_t *orientation) {
	//sensors_event_t a, m, g, temp;
	//lsm.getEvent(&a, &m, &g, &temp);

	//dof.accelGetOrientation(&event, orientation);
}
