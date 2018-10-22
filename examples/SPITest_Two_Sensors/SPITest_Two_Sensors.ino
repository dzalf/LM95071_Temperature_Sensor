#include "LM95071.h"

float temp1, temp2;
int SSP1 = 10;
int SSP2 = 9;
int LED = 14;

LM95071 SPI_Sensor_1(SSP1, DEBUG_OFF);
LM95071 SPI_Sensor_2(SSP2, DEBUG_OFF);

void setup() {

  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  SPI_Sensor_1.begin();
  SPI_Sensor_2.begin();
  
}


void loop() {

  delay(150);
  temp1 =  SPI_Sensor_1.getTemperature();
  temp2 =  SPI_Sensor_2.getTemperature();

  Serial.print("Temp 1 = ");
  Serial.print(temp1);
  Serial.print(" ");
  Serial.print(char(176));
  Serial.print("C");
  Serial.print("; ");

  
  Serial.print("Temp 2 = ");
  Serial.print(temp2);
  Serial.print(" ");
  Serial.print(char(176));
  Serial.print("C");
  Serial.println(";");
  
  digitalWrite(LED, HIGH);
  delay(50);

  digitalWrite(LED, LOW);
  delay(150);

}
