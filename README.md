# BonIWear
Mobile platform for sensory feedback via bone conduction.

The Project gives the PCB, Embedded SW and the API to drive the device via Bluetooth/Wifi.
## Table of Content
- [The PCB](#the-pcb)
  * [Two layer PCB](#two-layer-pcb)
    * [Components](#components)
    * [Modifications](#modifications)
    * [Connection of the PCB](#connection-of-the-pcb)
    * [Programming and operation of the PCB](#programming-and-operation-of-the-pcb)
    * [Debugging of the PCB](#debugging-of-the-pcb)
   
## The PCB
### Two layer PCB:
#### Components:
- A power supply that can regulate 5V input into 3.3V and 5V. The 5V can be sourced from the programmer pins.
- ESP32 as the microcontorller.
- Three AD5932 ICs to generate frequencies.
- Three AD5970 digital potentiometers ICs for controlling the amplitude. 
- Three NCS2211 class AB amplifier ICs.
#### Modifications:
Being the first prototype of our project the PCB is heavily modified.
In order for the PCB to operate normally:
- The unconnected side of resistor C1 needs to be connected to ground.
- One of the unconnected pins of SW1 needs to be connected to ground.
- upper pads of C14 and C15 needs to be connected to provide power to function generators.
- R7, R11, R15, R19, R22 and R25 needs to be desoldered for the correct operation of SPI communications.
- 20K 0402 resistors need to be soldered at R20, R23 and R26 for the amplifier to work.
- The USB footprint J1 is left unused and is not intended to be used.
- Solder 2.56mm connecters to top pin of J1 and the square pin of J1, they are respectively the ground and +5 power supply for the PCB.
#### Connection of the PCB:
The PCB uses 2.56mm connectors for its programming pins and transducer signal output. 2.56mm female jumper headers should be used for proper connection to the system.
The battery port uses standard JST connenctors to fit with most lithium ion batteries.
#### Programming and operation of the PCB:
The prototype is programmed with Arduino IDE. To program the PCB properly, the following instructions must be followed:
1. Connect TP12 and TP18 to ground. This allows ESP32 to be working in bootloading mode and allows for 3.3V flashing voltage. Failing to do so will result in flash read error.
2. When uploading the code press and hold SW2, wait until `connecting....`shows up, press and release SW1. This put ESP into flashing mode. Failing to do so will result in `A fatal error occurred: Failed to connect to ESP32: Timed out waiting for packet header`.
3. When it is uploading the code SW2 can now be released.
4. After uploading, `Hard resetting via RTS pin` should be observed,press the SW1 again to reset and boot the program. 
5. Now TP12 and TP18 can be lifted from ground to allow the pins from the MCU to operate as normal I/O pins, but TP18 should be connected to ground when trying to reboot the MCU.
#### Debugging of the PCB:
If encountered any problem, test points near the MCU are available for ruling out errors and faulty circuits.
| Test Point No. |  Net Name | Description |
|----|----|----|
|TP1|CTRL3| The transition from low to high at this pin enable the output of bottom function generator after it being reprogrammed |
|TP2|STANDBY3| Toggle to high to disable the bottom function generator|
|TP3|CTRL2| The transition from low to high at this pin enable the output of middle function generator after it being reprogrammed |
|TP4|CTRL1| The transition from low to high at this pin enable the output of top function generator after it being reprogrammed|
|TP5|STANDBY1|Toggle to high to disable the top function generator|
|TP6|STANDBY2|Toggle to high to disable the middle function generator|
|TP7|SPI1CLK|This pin should provide the clock to all the SPI devices|
|TP8|No connection|Don't Bother|
|TP9|ENABLE1|Toggle to high to turn off the top amplifier(May not work)|
|TP10|ENABLE2|Toggle to high to turn off the middle amplifier(May not work)|
|TP11|SPI1MOSI|This pin should transmit data to all the SPI devices|
|TP12|FSYNC2| This is the slave select pin for the middle function generator, when toggled low it allows the middle function generator to receive data from the MCU|
|TP13|FSYNC3| This is the slave select pin for the bottom function generator, when toggled low it allows the bottom function generator to receive data from the MCU|
|TP14|ENABLE3| Toggle to high to turn off the bottom amplifier(May not work) |
|TP15|SYNC3|This is the slave select pin for the bottom digital potentiometer, when toggled low it allows the bottom digital potentiometer to receive data from the MCU|
|TP16|FSYNC1|This is the slave select pin for the top function generator, when toggled low it allows the top function generator to receive data from the MCU|
|TP17|SYNC1|This is the slave select pin for the top digital potentiometer, when toggled low it allows the top digital potentiometer to receive data from the MCU|
|TP18|SYNC2|This is the slave select pin for the middle digital potentiometer, when toggled low it allows the middle digital potentiometer to receive data from the MCU|







