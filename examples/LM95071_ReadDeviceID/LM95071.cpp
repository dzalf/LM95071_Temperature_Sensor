#include "LM95071.h"


// Constructor

LM95071::LM95071(uint8_t pin, boolean debug) {

  _SelDev_Pin = pin;
  _debug = debug;

}

LM95071::LM95071(uint8_t pin,  uint8_t dbgledPin,  boolean debug) {

  _SelDev_Pin = pin;
  _debug = debug;
  _debugLED_Pin = dbgledPin;

  pinMode(_debugLED_Pin, OUTPUT);

}

void LM95071::begin(void) {

  SPI.begin();

  pinMode(_SelDev_Pin, OUTPUT);

  digitalWrite(_SelDev_Pin, HIGH);

  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

  delay(500);

}

float LM95071::getTemperature(void) {

  float final;

  _tempHex = readTemp(BYTES_TO_READ);

  final = celsiusConversion(_tempHex);

   if(_debug){
    Serial.print(F("Capture result [HEX] >> "));
    Serial.println(_tempHex, HEX);
  }

  return final;

}

int16_t LM95071::readTemp(int bytesToRead) {

  byte inByte = 0;

  int16_t result;

  int16_t dataToSend = (DONT_CARE_BYTE << 8) | CONTINUOUS_CONV;

  digitalWrite(_SelDev_Pin, LOW);

  //delay(1);

  _ledStatus = LOW;

  result = SPI.transfer16(CONTINUOUS_CONV);

  delay(150);
  //result = SPI.transfer16(dataToSend);

  /*
  
  bytesToRead--;

  if (_debug) {
    Serial.print(F("HIGH Temp byte = "));
    Serial.println(result, HEX);
    digitalWrite(_debugLED_Pin, _ledStatus);
  }

  result = result << 8;

  if (bytesToRead > 0) {

    //SPI.transfer(55);
    inByte = SPI.transfer(CONTINUOUS_CONV);

    result = result | inByte;

    if (_debug) {
      Serial.print(F("LOW Temp byte = "));
      Serial.println(inByte, HEX);
    }

    bytesToRead--;

  }

  */

   SPI.endTransaction();

   digitalWrite(_SelDev_Pin, HIGH);

   _ledStatus = HIGH;

   if (_debug) {
      digitalWrite(_debugLED_Pin, _ledStatus);
   }

  return result;

}

float LM95071::celsiusConversion(int16_t val) {

  float result = 0;

  int16_t dummy, shifted;

  dummy = val ^ MASK_XOR;
  shifted = dummy / COMPLEMENT_2_FACTOR;

  result = shifted * RESOLUTION;

  if (_debug) {

    Serial.print("Hex value = ");
    Serial.print(_tempHex, HEX);
    Serial.print(" ;");
    Serial.print("Xor value = ");
    Serial.print(dummy, HEX);
    Serial.print(" ;");
    Serial.print("Shifted = ");
    Serial.print(shifted);
    Serial.print(" ;");

  }

  return result;

}

byte LM95071::sleepMode(){

  uint16_t inShort = 0;
  
  digitalWrite(_SelDev_Pin, LOW);

 // delayMicroseconds(500);

  //SPI.transfer(DONT_CARE_BYTE);

  //SPI.transfer16(SHUTDOWN_MODE);

  //SPI.transfer16(SHUTDOWN_MODE);
  inShort = SPI.transfer16(SHUTDOWN_MODE);

 // delay(100);

  digitalWrite(_SelDev_Pin, HIGH);

  SPI.endTransaction();

  if (_debug) {
    Serial.print(" SHUTDOWN_MODE response byte = ");
    Serial.println(inShort, HEX);
  }

  return inShort;

}

void LM95071::conversionMode(){

  uint16_t inShort = 0;

  
  digitalWrite(_SelDev_Pin, LOW);

  //delayMicroseconds(50);
  
  inShort = SPI.transfer16(CONTINUOUS_CONV);

  //delayMicroseconds(50);

  digitalWrite(_SelDev_Pin, HIGH);

  SPI.endTransaction();

   if (_debug) {
    Serial.print(" CONTINUOUS_MODE response HEX = ");
    Serial.println(inShort, HEX);
  }

}

int16_t LM95071::readID() {

  /* From the datasheet:
    The following communication can be used to determine the Manufacturer's/Device ID and then immediately place
    the part into continuous conversion mode. With CS continuously low:

    a. Read 16 bits of temperature data
    b. Write 16 bits of data commanding shutdown
    c. Read 16 bits of Manufacture's/Device ID data
    d. Write 8 to 16 bits of data commanding Conversion Mode
    e. Take CS HIGH.

  */

  byte bytesToRead = BYTES_TO_READ;

  byte inByte = 0;

  int16_t dataToSend = (DONT_CARE_BYTE << 8) | SHUTDOWN_MODE;

  int16_t ID = 0x00;

  // a. Read a uint16_t of temp

  digitalWrite(_SelDev_Pin, LOW);

  //delayMicroseconds(50);

 //delayMicroseconds(100);

  // b. Write 16 bits --> SHUTDOWN

  //SPI.transfer(DONT_CARE_BYTE);
  //SPI.transfer(SHUTDOWN_MODE);

  ID = SPI.transfer16(SHUTDOWN_MODE);

  //delayMicroseconds(50);

  if (_debug) {

    Serial.println(F("___________________"));
    Serial.print(F("Shutdown command >> "));
    Serial.println(SHUTDOWN_MODE,HEX);
    Serial.print(F("Received uint16_t = "));
    Serial.println(ID, HEX);
  }

  //bytesToRead--;
  /*

  if (bytesToRead > 0) {

    ID = ID << 8;

    //SPI.transfer(DONT_CARE_BYTE);
    inByte = SPI.transfer(SHUTDOWN_MODE);

    if (_debug) {

      Serial.print(F("LOW byte = "));
      Serial.println(inByte, HEX);
      Serial.println(F("___________________"));
    }

    ID = ID | inByte;

    bytesToRead--;

    if (_debug) {

      Serial.print(F("Final ID = "));
      Serial.println(ID, HEX);
      Serial.println(F("___________________"));
    }

  }
  */

  // e. Take CS HIGH

  //SPI.transfer(CONTINUOUS_CONV);

  //SPI.endTransaction();

  SPI.endTransaction();

   digitalWrite(_SelDev_Pin, HIGH);

  return ID;

}