#include "kLogCollection.h"

//******************************************************
//  kADS1115
//******************************************************

// kADS1115::kADS1115(uint8_t addr=0x48,uint8_t pwrPin=3,uint8_t newID=0){
// 	ID=newID;
// 	obj=new Adafruit_ADS1115(addr);
// 	setLogName("ADC");
// }

kADS1115::~kADS1115(){
	delete fname;
}

void kADS1115::setLogName(char* newName){
	int flength=strlen(newName);
	fname=new char[flength+2+4+1];
	strcpy(fname,newName);
	strcpy(fname+flength,'_');
	strcpy(fname+flength+1,ID+'0');
	strcpy(fname+flength+2,".log");
	return;
}

void kADS1115::setFormat(){
	return;
}


void kADS1115::setGain(adsGain_t newGain){
	obj.setGain(newGain);
	return;
}

int kADS1115::_log_cell(SdFile& myLog){

  float multiplier = 0.0625F;
  int16_t results;
  int16_t results_1;
  delay(100);
      obj.begin();
      results=-obj.readADC_Differential_0_1();
      results_1=-obj.readADC_Differential_2_3();
  myFile.print(",");
  myFile.print(results*multiplier);
  myFile.print(" ");
  myFile.print(results_1*multiplier);
  return 0;
  }   


int kADS1115::log(DateTime nowTime){
	analogWrite(pwrPin,255);
	char timeBuf[50];
	snprintf(timeBuf, sizeof(timeBuf), "%04d-%02d-%02d %02d:%02d",

	nowTime.year(), nowTime.month(), nowTime.date(),
	nowTime.hour(), nowTime.minute());


	if (!myLog.open(fname, O_RDWR | O_CREAT | O_AT_END)) {
		return 1;
	}

	myLog.print(EEPROM.read(SN_ADD1),HEX);
	myLog.print(EEPROM.read(SN_ADD2),HEX);
	myLog.print(",");
	myLog.print(timeBuf); 
	_log_cell(myLog);
	if (!myLog.open(fname, O_RDWR | O_CREAT | O_AT_END)) {
	sd.errorHalt("opening %s for write failed",fname);
	}
	myLog.println("");
	myLog.close();
	analogWrite(pwrPin,0);
	return 0;
 
}


//******************************************************
//  kMCP9808
//******************************************************
// kMCP9808::kMCP9808(uint8_t addr=0x48,uint8_t pwrPin=3,uint8_t newID=0){
// 	ID=newID;
// 	setLogName("Temperature");
// 	obj=new Adafruit_MCP9808(addr);
// }

kMCP9808::~kMCP9808(){
	delete obj;
	delete fname;
}

void kMCP9808::setLogName(char* fname){
	int flength=strlen(newName);
	fname=new char[flength+2+4+1];
	strcpy(fname,newName);
	strcpy(fname+flength,'_');
	strcpy(fname+flength+1,ID+'0');
	strcpy(fname+flength+2,".log");
	return;
}

void kMCP9808::setFormat(){
	return;
}


float kMCP9808::_read() {
  // Read and print out the temperature, then convert to *F
   if (!obj->begin(addr)) {
    return -255;
  }
  float c = obj->readTempC();
  float f = c * 9.0 / 5.0 + 32;
  return f;
}


int kMCP9808::log(DateTime nowTime){
	char timeBuf[50];
	snprintf(timeBuf, sizeof(timeBuf), "%04d-%02d-%02d %02d:%02d",
	now.year(), now.month(), now.date(),
	now.hour(), now.minute());


	if (!myFile.open(fname, O_RDWR | O_CREAT | O_AT_END)) {
	return 0;
	}
	myFile.print(EEPROM.read(SN_ADD1),HEX);
	myFile.print(EEPROM.read(SN_ADD2),HEX);
	myFile.print(",");
	myFile.print(timeBuf); 
	myFile.print(",");
	myFile.print(_read());
	myFile.println("");
	myFile.close();
    return 0;  
}




//******************************************************
//  k5TE
//******************************************************
// k5TE::k5TE(uint8_t addr=0x0,uint8_t pwrPin=3,uint8_t newID=0){
// 	ID=newID;
// 	mySerial=new SoftwareSerial(RXPin,TXPin);
// 	setLogName("5TE");
// }

k5TE::~k5TE(){
	delete obj;
	delete fname;
}

void k5TE::setLogName(char* fname){
	int flength=strlen(newName);
	fname=new char[flength+2+4+1];
	strcpy(fname,newName);
	strcpy(fname+flength,'_');
	strcpy(fname+flength+1,ID+'0');
	strcpy(fname+flength+2,".log");
	return;
}

void k5TE::setFormat(){
	return;
}
float k5TE::_5TE_measure(){
  mos=0;
  cond=0;
  temp=0;
  int i=0;
  while (raw[i]<'0' || raw[i]>'9'){
    i++;
  }
  while (raw[i]!=' '){
   //    Serial.println(raw[i]-'0');
       mos=mos*10+raw[i]-'0';
       i++;            
     }
  mos=mos/50.0;
  mos=4.3*pow(10,-6)*pow(mos,3)-5.5*pow(10,-4)*pow(mos,2)+2.92*pow(10,-2)*mos-5.3*pow(10,-2); 
  //moisture
  
  i++;
  while (raw[i]!=' '){
       cond=cond*10+raw[i]-'0';
       i++;
     }
  if(cond>700){
  cond=5*(cond-700)+700;
  }
  cond=cond/100;
  //conductivity
  
  i++;
  while (raw[i]!=0x0d){
       temp=temp*10+raw[i]-'0';
       i++;
     }
  if (temp>900){
  temp=5*(temp-900)+900;
  }
  temp=(temp-400)/10;
  return;
}


int k5TE::_log_cell(SdFile myLog){
  mySerial->listen();
  byte income;
  int i=0;
  byte raw[20];
  delay(100);
  analogWrite(pwrPin,255);
  delay(80);
  while (mySerial->available()){
    income=mySerial->read();
    raw[i]=income;
    i++;
    if (income==0x0A){ 
      analogWrite(power,0);
      break;
    }
    
  }
  analogWrite(pwrPin,0);
   if (!myFile.open(fname, O_RDWR | O_CREAT | O_AT_END)) {
   	return;
   }
  _5TE_measure(raw);
  myFile.print("-");
  myFile.print(mos);
  myFile.print("-");
  myFile.print(cond);
  myFile.print("-");
  myFile.print(temp);


/*  
  Serial.print(TE_measure(raw,1));
  Serial.print(" ");
  Serial.print(TE_measure(raw,2));
  Serial.print(" ");
  Serial.print(TE_measure(raw,3));
  Serial.println("");
*/  
  return 0;
}


int k5TE::log(DateTime nowTime){
	char buf[50];
	  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d",
	           
	           now.year(), now.month(), now.date(),
	           now.hour(), now.minute());
	  if (!myLog.open(fname, O_RDWR | O_CREAT | O_AT_END)) {
	    return;
	  }
	  myLog.print(EEPROM.read(SN_ADD1),HEX);
	  myLog.print(EEPROM.read(SN_ADD2),HEX);
	  myLog.print(",");
	  myLog.print(buf);
	  myLog.print(",");

	  _log_cell(myLog);

	  myLog.println("");
	  myLog.close();
	  return 0;
  
}

