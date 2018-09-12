#include "accelerometer.h"

Adafruit_LSM303 Accelerometer::lsm = Adafruit_LSM303();

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
	float fHeading;

	if (lsm.magData.y > 0)
	{
		fHeading = 90 - (atan(lsm.magData.x / lsm.magData.y) * (180 / M_PI));
	}
	else if (lsm.magData.y < 0)
	{
		fHeading = - (atan(lsm.magData.x / lsm.magData.y) * (180 / M_PI));
	}
	else // hy = 0
	{
		if (lsm.magData.x < 0) fHeading = 180;
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
	return sqrt(pow(lsm.accelData.x, 2) + pow(lsm.accelData.y, 2) + pow(lsm.accelData.z, 2)) * MS2_TO_G;
}

void Accelerometer::getAccelOrientation(sensors_vec_t *orientation) {
	orientation->roll = atan2(lsm.accelData.y, lsm.accelData.z) * 180/M_PI;
	orientation->pitch = atan2(-lsm.accelData.x, sqrt(lsm.accelData.y*lsm.accelData.y + lsm.accelData.z*lsm.accelData.z)) * 180/M_PI;
}
