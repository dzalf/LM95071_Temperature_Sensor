# LM95071 Texas Instruments Temperature Sensor

Arduino*/Teensy** Library for reading temperatures from the SPI Temperature Sensor from TI

The Sensor comes in a SOT-23 package and requires three Pins from the uC board (Arduino/Teensy)

Datasheet: http://www.ti.com/lit/ds/symlink/lm95071.pdf

Description: The library uses the SPI library from Arduino (internally called) to comunicate with the sensor via two pins of the SPI port (CLK and data) of the uC. A third cable is necessary as a *Chip Select* pin (Active low) and therefore cascading devices is possible.

Usage: 

1. Declare a pin from the uC connected to the CS pin of the sensor --> SS_Pin
2. Instantiate as many devices as you have connected using **LM95071** device(SS_Pin). 
3. Initialize the library with the **begin()** method --> device.**begin()**;
4. Query the value using the method **getTemperature()** --> device.**getTemperature()**;  The result from the conversion is saved in a *float* variable.

Notes:

a. Debugging is possible via the serial port to observe the raw conversion of data. The second parameter of the object declaration defines if it is needed or not.
    If debugging is needed use: **DEBUG_ON** otherwise leave the second parameter blank or use **DEBUG_OFF**
    

If you find any issues with the implementation please let me know

Cheers!  :beer:

dzalf

* __Tested on Arduino Pro Micro and Leonardo.__ On these boards Pin 17 corresponds to the SS port from the SPI and it is connected to the Rx data from the serial port. Therefore, you must remove the resistor and connect this pin to pin 1 from the sensor. (I have no idea why they decided to wire the SPI like this :unamused:)

** __Tested on Teeensy 3.2.__ No wiring problems since all pins are available thanks to [Paul's](https://www.pjrc.com/teensy/) great design :sunglasses:
