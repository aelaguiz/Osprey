#include "barometer.h"

Adafruit_BMP280 Barometer::barometer = Adafruit_BMP280();
float Barometer::pressureSetting = DEFAULT_PRESSURE_SETTING;

Barometer::Barometer() : Sensor(KALMAN_PROCESS_NOISE, KALMAN_MEASUREMENT_NOISE, KALMAN_ERROR) {
	altitude = kalmanInit(0);
}

int Barometer::init() {
	return barometer.begin();
}

float Barometer::getTemperature() {
	// Get ambient temperature (in celsius)
	float temperature = barometer.readTemperature();

	return temperature;
}

float Barometer::getPressure() {
	float pressure = barometer.readPressure();

	if(!pressure) {
		return NO_DATA;
	}

	kalmanUpdate(&altitude, pressure);
	return altitude.value;
}

float Barometer::getAltitudeAboveSeaLevel() {
	return getPressureAltitude(pressureSetting * MERCURY_TO_HPA_CONVERSION);
}

float Barometer::getAltitudeAboveGround() {
	return getPressureAltitude(SENSORS_PRESSURE_SEALEVELHPA) - groundLevel;
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
	return barometer.readAltitude(setting);
}

void Barometer::setGroundLevel() {
	groundLevel = getPressureAltitude(SENSORS_PRESSURE_SEALEVELHPA);
}
