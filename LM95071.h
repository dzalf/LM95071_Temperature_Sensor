// Library: SPI Control of a Texas Instruments LM95071 SPI temperature Sensor
// Version: 0.1
// Developer: Daniel Melendrez
// email: dmelendrez(at)gmail(dot)com
// Category: Sensors
// Date: Oct 2018

#ifndef LM95071_h
#define LM95071_h

#define MASK_XOR 0x03;
#define RESOLUTION 0.03125
#define CONTINUOUS_CONV 0x00
#define SHUTDOWN_MODE 0xFF
#define SHUT_DOWN 0xFF
#define BYTES_TO_READ 2
#define DEBUG_ON true
#define DEBUG_OFF false

#include <Arduino.h>
#include <SPI.h>

class LM95071 {
  public: // reacheable to the main function

    //Constructors

    LM95071(uint8_t chipSelectPin, boolean debug = false);

    //Methods

    void begin(void);
    float getTemperature(void);
	short readID(void);

  private: //these are internal access functions and variables
    
    uint8_t _SelDev_Pin;
    boolean _debug = false;
    short _tempHex;

    short readTemp(int bytesToRead);
    float celsiusConversion(short val);

};
#endif
