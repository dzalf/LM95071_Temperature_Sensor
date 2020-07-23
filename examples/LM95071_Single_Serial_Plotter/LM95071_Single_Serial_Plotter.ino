
/*
      LM95071 SPI Temperature sensor

      Example: Print data on the serial port or Arduino's IDE Serial Plotter

      Author: github.com/dzalf
      Ver: 0.1
      Date: June 2020
*/

#include "LM95071.h"

#define SERIAL_PLOTTER true

// Variables and constants
unsigned long pollTime;
unsigned long previousLEDTime = 0;
const unsigned long pollDelay = 200;
int ledState = LOW;
long OnTime = 50;
long OffTime = 150;
float temperature;

// Pins definition
const int SSP = 10;
const int ledPin = 6;

// Instantiate a new LM95071
LM95071 SPI_Sensor(SSP, DEBUG_ON);

void setup() {

  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  SPI_Sensor.begin();

  pollTime = 0;
  previousLEDTime = 0;

}

void loop() {


  unsigned long nowTime = millis();

  // Sample temperatures at 5 Hz
  if (nowTime - pollTime >= pollDelay) {

    pollTime = nowTime;

    temperature =  SPI_Sensor.getTemperature();

    if (SERIAL_PLOTTER == false) Serial.print("Current temperature = ");

    Serial.print(temperature);

    if (SERIAL_PLOTTER == false) {

      Serial.print(char(176));
      Serial.println("C");

    } else {

      Serial.print("\n");

    }

  }

  flashLED(nowTime);

}

void flashLED(unsigned  long t ) {

  // From the great tutorial: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/using-millis-for-timing

  if ((ledState == HIGH) && (t - previousLEDTime >= OnTime))
  {
    ledState = LOW;  // Turn it off
    previousLEDTime = t;  // Remember the time
    digitalWrite(ledPin, ledState);  // Update the actual LED
  }
  else if ((ledState == LOW) && (t - previousLEDTime >= OffTime))
  {
    ledState = HIGH;  // turn it on
    previousLEDTime = t;   // Remember the time
    digitalWrite(ledPin, ledState);   // Update the actual LED
  }

}
