# LM95071 Texas Instruments Temperature Sensor

Arduino/Teensy Library for reading temperatures from the SPI Temperature Sensor from TI

The Sensor comes in a SOT-23 package and requires three Pins from the uC board (Arduino/Teensy)

Datasheet: http://www.ti.com/lit/ds/symlink/lm95071.pdf

Description: The library uses the SPI library from Arduino (internally called) to comunicate with the sensor via two pins of the SPI port (CLK and data) of the uC. A third cable is necessary as a *Chip Select* pin (Active low) and therefore cascading devices is possible.

Usage: 

1. Declare a pin from the uC connected to the CS pin of the sensor --> SS_Pin
2. Instantiate as many devices as you have connected using # LM95071 # device(SS_Pin). 
3. Initialize the library with the *begin()* method --> device.begin();
4. The result from the conservion is saved in a *float* variable.

Notes:

a. Debugging is possible via the serial port to observe the raw conversion of data. The second parameter of the object declaration defines if it is needed or not.
    If debugging is needed use: # DEBUG_ON # otherwise leave the second parameter blank or use # DEBUG_OFF #
