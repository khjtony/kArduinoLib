#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>
#include <limits.h>

#include "kIMU.h"

kIMU_GY_801::kIMU_GY_801()
{	
	//deal with ADXL345
	// if(!ADXL345.begin())
 //  	{
 //   		/* There was a problem detecting the ADXL345 ... check your connections */
 //   		Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
 //  	}//ADXL345 begin

 //  	ADXL345.setDataRate(ADXL345_DATARATE_50_HZ);
 //  	ADXL345.setRange(ADXL345_RANGE_4_G);

 //  	//deal with HMC5883
 //  	if(!HMC5883.begin())
 //  	{
 //   		/* There was a problem detecting the ADXL345 ... check your connections */
 //   		Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
 //  	}
	// return;
}

boolean kIMU_GY_801::begin() {
	return 1;
}

void kIMU_GY_801::printAccel(){
	// sensors_event_t event; 
 //  	ADXL345.getEvent(&event);

 //  	/* Display the results (acceleration is measured in m/s^2) */
 //  	Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
 //  	Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
 //  	Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
 //  	return;
}

