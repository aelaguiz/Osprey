#include "gps.h"

GPS::GPS(FONA &fona) : Sensor(KALMAN_PROCESS_NOISE, KALMAN_MEASUREMENT_NOISE, KALMAN_ERROR), fona(fona) {
	latitude = 0;
	longitude = 0;

	latitudeOutOfRange = 0;
	longitudeOutOfRange = 0;

	speed = kalmanInit(0);
	altitude = kalmanInit(0);
}

int GPS::init() {
	/*
	// Get RMC (recommended minimum) and GGA (fix data) data
	gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

	// Refresh data 5 times per second
	gps.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
	gps.sendCommand(PMTK_API_SET_FIX_CTL_5HZ);

	delay(1000);*/

	if(!fona.getFona().enableGPS(true)) {
		return 0;
	}

	Serial.print("Waiting for gps fix...");
	while(!update()) {
		Serial.print(".");
		delay(50);
	}
	Serial.println("");

	return 1;
}

bool GPS::update() {
	float fLatitude, fLongitude, fSpeed_kph, fHeading, fAltitude;
	if(!fona.getFona().getGPS(&fLatitude, &fLongitude, &fSpeed_kph, &fHeading, &fAltitude)) {
		Serial.println("Failed to get GPS fix");
		return false;
	}

	if(validCoordinate(latitude, fLatitude, &latitudeOutOfRange)) {
		latitude = fLatitude;
	}
	if(validCoordinate(longitude, fLongitude, &longitudeOutOfRange)) {
		longitude = fLongitude;
	}

	kalmanUpdate(&speed, fSpeed_kph);
	kalmanUpdate(&altitude, fAltitude);
	return true;
}

float GPS::getLatitude() {
	return latitude;
}

float GPS::getLongitude() {
	return longitude;
}

int GPS::validCoordinate(float previous, float next, int *outOfRange) {
	// If we keep reading seemingly invali coordinates over and over, they're probably valid
	if(*outOfRange > OUT_OF_RANGE_LIMIT) {
		*outOfRange = 0;
		return 1;
	}

	// Ignore ~0.00 coordinates (obviously doesn't work if within 1 degree of the equator or meridian, but good enough for now)
	if(next < 1 && next > -1) {
		return 0;
	}

	// Ignore anything greater than the out of range delta from the previous coordinate as there's
	// no way to move that fast except in the case of initially acquiring a location when the
	// previous coordinate will be 0
	if(previous != 0 && abs(next - previous) > OUT_OF_RANGE_DELTA) {
		(*outOfRange)++;
		return 0;
	}

	// Reset the out of range counter if valid
	*outOfRange = 0;

	return 1;
}

float GPS::getSpeed() {
	return speed.value;
}

float GPS::getAltitude() {
	return altitude.value;
}

int GPS::getQuality() {
	return fona.getFona().GPSstatus();
}

char* GPS::getIso8601() {
	//sprintf(iso8601, "20%02d-%02d-%02dT%02d:%02d:%02d.%02dZ", gps.year, gps.month, gps.day, gps.hour, gps.minute, gps.seconds, gps.milliseconds);
	//return iso8601;
}
