
/*
      LM95071 SPI Temperature sensor

      Example: Getting the device's ID during SHUTDOWN mode

      Author: github.com/dzalf
      Ver: 0.1
      Date: June 2020
*/

#include "LM95071.h"

#define SERIAL_PLOTTER false

// Variables and constants
unsigned long pollTime;
unsigned long IDTime;
unsigned long prevIDTime;
const unsigned long pollIDDelay = 3000;

unsigned long previousLEDTime = 0;
const unsigned long pollDelay = 500;

float temperature;
int16_t devID;

// Pins definition
const int SSP = 10;

// Instantiate a new LM95071
LM95071 SPI_Sensor(SSP, ledPin, DEBUG_ON);

void setup()
{

  Serial.begin(115200);

  while (!Serial)
  {
  };

  SPI_Sensor.begin();

  delay(100);

  SPI_Sensor.sleepMode();

  devID = SPI_Sensor.readID();

  delay(1000);

  SPI_Sensor.conversionMode();

  pollTime = 0;
  prevIDTime = 0;
}

void loop()
{

  unsigned long nowTime = millis();

  if (nowTime - IDTime >= pollIDDelay)
  {

    IDTime = nowTime;

    SPI_Sensor.sleepMode();

    devID = SPI_Sensor.readID();

    SPI_Sensor.conversionMode();

    Serial.print(F("Device ID >> "));
    Serial.println(devID, HEX);
  }

  // Sample temperatures at 5 Hz
  if (nowTime - pollTime >= pollDelay)
  {

    pollTime = nowTime;

    SPI_Sensor.conversionMode();

    temperature = SPI_Sensor.getTemperature();

    if (SERIAL_PLOTTER == false)
      Serial.print("Current temperature = ");

    Serial.print(temperature);

    if (SERIAL_PLOTTER == false)
    {

      Serial.print(char(176));
      Serial.println("C");

      Serial.print(F("Device ID >> "));
      Serial.println(devID, HEX);
    }
    else
    {

      Serial.print("\n");
    }
  }
}
