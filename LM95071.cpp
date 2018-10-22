#include "LM95071.h"




// Constructor

LM95071::LM95071(uint8_t pin, boolean debug) {

  _SelDev_Pin = pin;
  _debug = debug;

}

void LM95071::begin(void) {
  SPI.begin();
  pinMode(_SelDev_Pin, OUTPUT);
  digitalWrite(_SelDev_Pin, HIGH);
}

float LM95071::getTemperature(void) {

  float final;
  _tempHex = readTemp(BYTES_TO_READ);
  final = celsiusConversion(_tempHex);

  return final;

}
short LM95071::readTemp(int bytesToRead) {
  byte inByte = 0;
  short result;

  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE1));

  digitalWrite(_SelDev_Pin, LOW);
  result = SPI.transfer(CONTINUOUS_CONV);
  bytesToRead--;


  if (_debug) {
    Serial.print("1st byte = ");
    Serial.println(result, HEX);
  }
  if (bytesToRead > 0) {

    result = result << 8;

    inByte = SPI.transfer(CONTINUOUS_CONV);

    result = result | inByte;
    if (_debug) {
      Serial.print("2nd byte = ");
      Serial.println(inByte, HEX);
    }
    bytesToRead--;

  }
  SPI.endTransaction();

  digitalWrite(_SelDev_Pin, HIGH);

  return result;
}

float LM95071::celsiusConversion(short val) {

  float result = 0;
  short dummy, shifted;

  dummy = val ^ MASK_XOR;
  shifted = dummy / 0x04;

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
