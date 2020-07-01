/*Library: SPI Control of a Texas Instruments LM95071 SPI temperature Sensor
 Version: 1.1.0
 Developer: Daniel Melendrez
 email: dmelendrez(at)gmail(dot)com
 Category: Sensors
 Date: Oct 2018

 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
*/

#ifndef LM95071_h
#define LM95071_h

#define MASK_XOR 0x03;
#define RESOLUTION 0.03125
#define CONTINUOUS_CONV 0x00
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

  private: //these are internal access functions and variables
    
    uint8_t _SelDev_Pin;
    boolean _debug = false;
    short _tempHex;

    short readTemp(int bytesToRead);
    float celsiusConversion(short val);

};
#endif
