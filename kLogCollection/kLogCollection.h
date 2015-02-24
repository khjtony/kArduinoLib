#ifndef _KLOGCOLLECTION_H_
#define _KLOGCOLLECTION_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


//***********************s*************Macro definition*****************
#define SN_ADD1    (0x00)
#define SN1        (0x00)
#define SN_ADD2    (0x01)
#define SN2        (0x0f)
#define CLK_COUNT  (0x05)
#define CLK_INI    (0x10)
#define NOTE_FLAG  (0x15)
#define SD_CHIP_SELECT      10
//***********************s*************Macro definition*****************




#include <inttypes.h>
#include "SdFat/SdFat.h"
#include <stdio.h>
#include <EEPROM.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include "Adafruit_ADS1015.h"
#include "DS3231.h"
#include <SoftwareSerial.h>
#include <string.h>

class kADS1115{
public:
	kADS1115(uint8_t addr=0x48,uint8_t pwrPin=3,uint8_t newID=0):obj(addr){
		ID=newID;
		setLogName("ADC");
	}
	~kADS1115();
	void setLogName(char* fname);
	void setFormat();
	void setGain(adsGain_t);
	int log(DateTime nowTime);

private:
	Adafruit_ADS1115 obj;
	int _log_cell(SdFile&);
	uint8_t addr;
	uint8_t pwrPin;
	char* fname;
	uint8_t ID;
};



class kMCP9808{
public:
	kMCP9808(uint8_t addr=0x18,uint8_t pwrPin=3,uint8_t newID=0):obj(){
		obj.begin(addr);
		ID=newID;
		setLogName("Temperature");
	}
	~kMCP9808();
	void setLogName(char* fname);
	void setFormat();
	int log(DateTime nowTime);
private:
	Adafruit_MCP9808 obj;
	float _read();
	uint8_t addr;
	uint8_t pwrPin;
	uint8_t ID;
};


class k5TE{
public:
	k5TE(uint8_t addr=0x0,uint8_t pwrPin=3,uint8_t RXPin=4,uint8_t TXPin=3,uint8_t newID=0): mySerial(RXPin,TXPin){
		ID=newID;
		setLogName("5TE");
	}
	~k5TE();
	void setLogName(char* fname);
	void setFormat();
	int log(DateTime nowTime);
private:
	SoftwareSerial mySerial;
	void _5TE_mearure(uint8_t* raw);
	int _log_cell(SdFile&);
	uint8_t addr;
	uint8_t pwrPin;
	char* fname;
	uint8_t comPin;
	float mos,cond,temp;
	uint8_t ID;
};






#endif