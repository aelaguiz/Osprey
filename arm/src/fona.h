#ifndef FONA_H
#define FONA_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_FONA.h>
#include "sensor.h"

#define FONA_RX  9
#define FONA_TX  8
#define FONA_RST 4
#define FONA_RI  7

#define NET_STATUS_NOT_REGISTERED 0
#define NET_STATUS_REGISTERED 1
#define NET_STATUS_SEARCHING 2
#define NET_STATUS_DENIED 3
#define NET_STATUS_UNK 4
#define NET_STATUS_ROAMING 5

#define KALMAN_PROCESS_NOISE 0.01
#define KALMAN_MEASUREMENT_NOISE 0.25
#define KALMAN_ERROR 1

class FONA : public virtual Sensor {
	public:
		FONA();
		int init();

		Adafruit_FONA &getFona() {
			return fona;
		}
	protected:
		bool initNetwork();

		static Adafruit_FONA fona;
};

#endif
