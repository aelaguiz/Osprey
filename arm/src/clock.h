#ifndef CLOCK_H
#define CLOCK_H

#include "sensor.h"

// For now, removing RTC uspport and just using harware clock
//#include <RTCZero.h>

namespace Osprey {
  class Clock : public virtual Sensor {
    public:
      Clock();
      int init();
      void reset();
      int getSeconds();

    protected:
      // RTCZero rtc;
      unsigned long startTime;
  };
}

#endif
