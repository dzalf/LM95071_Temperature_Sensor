#include "LM95071.h"

float temperature;

const int SSP = 10;
const int LED = 14;

LM95071 SPI_Sensor(SSP, DEBUG_OFF); // Instantiate a new LM95071 

void setup() {

  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  SPI_Sensor.begin();
}

void loop() {

  delay(50);
  temperature =  SPI_Sensor.getTemperature();

  Serial.print("Current temperature = ");
  Serial.print(temperature);
  Serial.print(char(176));
  Serial.println("C");

  digitalWrite(LED, HIGH);
  delay(50);

  digitalWrite(LED, LOW);
  delay(150);             // Long-ish delay for visualization purposes...flashy response

}
