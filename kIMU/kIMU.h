#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
 #include "TinyWireM.h"
 #define Wire TinyWireM
#else
 #include <Wire.h>
#endif

#ifndef _KIMU_H_
 #define _KIMU_H_

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_HMC5883_U.h>

class kIMU_GY_801{
public:
	kIMU_GY_801();
	boolean begin();
	// virtual uint16_t readGyro();
	// virtual uint16_t readAccel();
	// virtual uint16_t readMag();
	// virtual uint16_t readAtom();
	// virtual void printGyro();
	void printAccel();
	// virtual void printMag();
	// virtual void printAtom();
private:
	Adafruit_ADXL345_Unified ADXL345;
	Adafruit_HMC5883_Unified HMC5883;
};

#endif