// Library: SPI Control of a Texas Instruments LM95071 SPI temperature Sensor
// Version: 0.1
// Developer: Daniel Melendrez
// email: dmelendrez(at)gmail(dot)com
// Category: Sensors
// Date: Oct 2018

#ifndef LM95071_h
#define LM95071_h

#define MASK_XOR 0x03;
#define COMPLEMENT_2_FACTOR 0x04
#define DONT_CARE_BYTE 0x55
#define RESOLUTION 0.03125
#define CONTINUOUS_CONV 0x5500
#define SHUTDOWN_MODE 0x11FF    // 0xXXFF  --> according to the datasheet
#define BYTES_TO_READ 2
#define DEBUG_ON true
#define DEBUG_OFF false

#include <Arduino.h>
#include <SPI.h>

class LM95071 {
  public: // reacheable to the main function

    //Constructors

    LM95071(uint8_t chipSelectPin, boolean debug = false);
    LM95071(uint8_t chipSelectPin, uint8_t dbgledPin, boolean debug = false);

    //Methods

    void begin(void);
    float getTemperature(void);
	int16_t readID(void);
    byte sleepMode(void);
    void conversionMode(void);
    


  private: //these are internal access functions and variables
    
    uint8_t _SelDev_Pin;
    uint8_t _debugLED_Pin;
    int _ledStatus = LOW;
    boolean _debug = false;
    uint16_t _tempHex;

    int16_t readTemp(int bytesToRead);
    float celsiusConversion(int16_t val);

};
#endif
