#include "barometer.h"

Adafruit_MPL3115A2 Barometer::barometer = Adafruit_MPL3115A2();
float Barometer::pressureSetting = DEFAULT_PRESSURE_SETTING;

Barometer::Barometer() : Sensor(KALMAN_PROCESS_NOISE, KALMAN_MEASUREMENT_NOISE, KALMAN_ERROR) {
	altitude = kalmanInit(0);
}

int Barometer::init() {
	return barometer.begin();
}

float Barometer::getTemperature() {
	// Get ambient temperature (in celsius)
	float temperature = barometer.getTemperature();

	return temperature;
}

float Barometer::getPressure() {
	float pressure = barometer.getPressure();

	if(!pressure) {
		return NO_DATA;
	}

	kalmanUpdate(&altitude, pressure);
	return altitude.value;
}

float Barometer::getAltitudeAboveSeaLevel() {
	return barometer.getAltitude();
}

float Barometer::getAltitudeAboveGround() {
	return barometer.getAltitude() - groundLevel;
}

void Barometer::setPressureSetting(float pressureSetting) {
	Barometer::pressureSetting = pressureSetting;
}

float Barometer::getPressureSetting() {
	return pressureSetting;
}

void Barometer::zero() {
	setGroundLevel();
}

float Barometer::getPressureAltitude(float setting) {
	// Convert atmospheric pressure, SLP, and temp to altitude
	barometer.setSeaPressure(setting);
	return barometer.getAltitude();
}

void Barometer::setGroundLevel() {
	groundLevel = barometer.getAltitude();
}
