#include "fona.h"

Adafruit_FONA FONA::fona = Adafruit_FONA(FONA_RST);

HardwareSerial *fonaSerial = &Serial1;

FONA::FONA() : Sensor(KALMAN_PROCESS_NOISE, KALMAN_MEASUREMENT_NOISE, KALMAN_ERROR) {
}

int FONA::init() {
	fonaSerial->begin(4800);
	if (! fona.begin(*fonaSerial)) {
		Serial.println(F("Couldn't find FONA"));
		while (1);
	}

	uint8_t iFonaType = fona.type();
	Serial.println(F("FONA is OK"));
	Serial.print(F("Found "));
	switch (iFonaType) {
		case FONA800L:
			Serial.println(F("FONA 800L")); break;
		case FONA800H:
			Serial.println(F("FONA 800H")); break;
		case FONA808_V1:
			Serial.println(F("FONA 808 (v1)")); break;
		case FONA808_V2:
			Serial.println(F("FONA 808 (v2)")); break;
		case FONA3G_A:
			Serial.println(F("FONA 3G (American)")); break;
		case FONA3G_E:
			Serial.println(F("FONA 3G (European)")); break;
		default:
			Serial.println(F("???")); break;
	}

	// Print module IMEI number.
	char cIMEI[16] = {0}; // MUST use a 16 character buffer for IMEI!
	uint8_t iIMEILen = fona.getIMEI(cIMEI);
	if (iIMEILen > 0) {
		Serial.print("Module IMEI: "); Serial.println(cIMEI);
	}

	initNetwork();
}

bool FONA::initNetwork() {
	while(1) {
		uint8_t iNetworkStatus = fona.getNetworkStatus();

		if(iNetworkStatus == NET_STATUS_SEARCHING) {
			Serial.print(".");
			delay(1000);
		}
		else if(iNetworkStatus == NET_STATUS_DENIED) {
			Serial.println("Network status denied");
			return false;
		}
		else if(iNetworkStatus == NET_STATUS_UNK) {
			Serial.println("Network status unknown");
		}
		else if(iNetworkStatus == NET_STATUS_REGISTERED) {
			Serial.println("Network Registered Home");
			return true;
		}
		else if(iNetworkStatus == NET_STATUS_ROAMING) {
			Serial.println("Network Registered ROAMING");
			return true;
		}
	}
}
