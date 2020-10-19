# BonIWear
Mobile platform for sensory feedback via bone conduction.

The Project gives the PCB, Embedded SW and the API to drive the device via Bluetooth/Wifi.
## Table of Content
- [The PCB](#the-pcb)
  * [Two Layer PCB](#two-layer-pcb)
    * [Components](#components)
    * [Modifications](#modifications)
    * [Connection of the PCB](#connection-of-the-pcb)
    * [Programming and Operation of the PCB](#programming-and-operation-of-the-pcb)
    * [Debugging of the PCB](#debugging-of-the-pcb)
    * [Files](#files)
  * [Four Layer PCB](#four-layer-pcb)
-[Schematic](#schematic)
  * [The MCU](#the-mcu)
    * [MCU Pin Connections](#mcu-pin-connections)
  * [Frequency Generator](#frequency-generator)
    * [Frequency Generator Pin Connections](#frequency-generator-pin-connections)
    * [Programming the Frequency Generator](#programming-the-frequency-generator)
  
   
## The PCB
### Two Layer PCB:
The two layer PCB is designed as a prototype to our system. The PCB is a two layer board with a poured common ground on the bottom plane for both analogue and digital circuitry. Power traces and signal traces are located mostly on the top plane. With two mounting holes at the side of the PCB it is intended to be contained in the designed box. The PCB is fabricated and assembled by PCBWay.
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
#### Programming and Operation of the PCB:
The prototype is programmed with Arduino IDE. To program the PCB properly, the following instructions must be followed:
1. Connect TP12 and TP18 to ground. This allows ESP32 to be working in bootloading mode and allows for 3.3V flashing voltage. Failing to do so will result in flash read error.
2. Set the uploading speed to 115200 or above, it will not work with 921600.
3. When uploading the code press and hold SW2, wait until `connecting....`shows up, press and release SW1. This put ESP into flashing mode. Failing to do so will result in `A fatal error occurred: Failed to connect to ESP32: Timed out waiting for packet header`.
4. When it is uploading the code SW2 can now be released.
5. After uploading, `Hard resetting via RTS pin` should be observed,press the SW1 again to reset and boot the program. 
6. Now TP12 and TP18 can be lifted from ground to allow the pins from the MCU to operate as normal I/O pins, but TP18 should be connected to ground when trying to reboot the MCU.
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
#### Files
All the PCB designs are done in KiCad. The PCB files of the two layer board can be found in the repository. The design is modified so that the aforementioned modifications does not need to be carried out for the two layer board PCB design if the desgin is to be printed in manufactures.
### Four Layer PCB
## Schematic
Both the original and updated version of the schematic can be found in the repository. The schematic is drawn in KiCad. On the first page, there is the frequency generator, amplifier and digital potentiometer. On the second page, there is the MCU and power section. 
### The MCU:
The MCU used in ths project is ESP32-WROOM-32D(4MB)([datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)). It mainly serves for communication between the GUI and the frequency generator. Apart from a few pins used for programming, most of the pins are used to communicate with the frequency generators, digital potentiometers and the amplifier.
The MCU communicates with frequency gnerators and digital potentiometers using SPI protocol. The ESP32 has two SPI channels available, and only one of them is utilized. Below are the connections from the MCU.
#### MCU Pin Connections
|Pin No.|Pin Name|Descriptions|
|----|----|----|
|1,15,38|GND|Connected to ground|
|2|DVDD|Power of ESP32, a well regulated 3.3V source is needed|
|3|EN|Reset pin of ESP32, it is connected to a switch, push to reboot the system|
|4|SENSOR_VP|Not used|
|5|SENSOR_VN|Not used|
|6,7,8|IO34 IO35 IO32|Not used|
|9,14,27|IO33 IO12 IO16|SYNC3, SYNC2 and SYNC1, slave select for digital potentiometer|
|10,16,28|IO25 IO13 IO17|ENABLE3, ENABLE2 and ENABLE1, used for turning on and off the amplifier|
|11,23,29|IO26 IO15 IO5|STANDBY3, STANDBY2 and STANDBY1, used for turning on and off the frequency generator|
|12,24,31|IO27 IO2 IO19|FSYNC3, FSYNC2 and FSYNC1, slave select for frequency generator|
|13,26,33|IO14 IO4 IO21|CTRL3, CTRL2 and CTRL1, update the output of the frequency generator|
|17,18,19,20,21,22|SDO SDI SHD SWP SCK SCS| Not used|
|25|IO0| Connected to a switch, hold low and press EN to enter bootloading|
|30|IO18|SPICLK used to synchronize all the SPI devices|
|32|NC|Do not connect|
|34,35|RXD0 TXD0| Serial port used for prgramming, connected to programming pins.|
|36|IO22|Not used.|
|37|IO23|SPIMOSI Used to send SPI data from the MCU|
### Frequency Generator
The frequency generator used in this project is AD5932([datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/AD5932.pdf)). This is a direct digital synthesis IC that uses SPI communication. It has 24 bits resolution frequency generation derived from the master clock (MCLK) fed in to it. In other words, the frequency it can output can be calculated by MCLK/2^24. We use a MCLK of 32.768kHz for our application. This means we have a frequency range from 0Hz to 32.768kHz with a frequency resolution of 0.00195Hz. It can produce sinusoidal, triangle and square waves at a fixed amplitude of 580 mV peak to peak. The IC also have auto frequency sweeping fucntion, which we are not intended to use in our project. To program the IC properly the MCU must write to AD5932 using SPI communication. 
#### Frequency Generator Pin Connections
|Pin No.|Pin Name|Descriptions|
|----|----|----|
|1|COMP|Decoupled to AVDD|
|2|AVDD|Analog supply (3.3V)|
|3|DVDD|Digital supply (3.3V)|
|4|CAP/2.5V|Decoupled to ground, decoupled to DVDD if DVDD is less than 2.5V|
|5|DGND|Digital Ground|
|6|MCLK|Input master clock from here, connected to SG-3030CM clock generator([datasheet](#https://www5.epsondevice.com/en/products/crystal_oscillator/sg3030cm.html))|
|7|SYNCOUT|Not connected, will output a signal after a frequency sweep(not tested)|
|8|MSBOUT|Not connected, square wave output can be yielded from this port|
|9|Interrupt|Not connected, used to interrupt a frequency sweep|
|10|CTRL|This pin needs to be toggled from low to high to output the frequency written to the frequency generator|
|11|SDATA|The MOSI pin of the device, receive data from SPI master|
|12|SCLK| The SPICLK pin of the device, receive clock from MCU to synchronize the bit transmision|
|13|FSYNC| The slave select pin of the device, pulled low to allow receiving of data|
|14|STANDY| Pull the pin high to disable the frequency generator|
|15|AGND|Analog ground|
|16|VOUT|The output pin for both triangle and sinusoidal wave, switch between the two in software|
#### Programming the Frequency Generator
To program the frequency generator AD5932, a 12 bit data must be written to the 4 bit register with mode 3 SPI communication(CPOL=1 CPHA=0). The following table shows the register used and the data transmitted to each register in the program where the first four bits represent the register written to and the rest are the data bits:
|Function|Data(Binary)|Data(Hexadecimal)|Description|
|--------|---|-----|---|
|Initialize:|	0	0	0	0 1 1 1 0	1 1	0	1	0	0	1	1|0x0ED3|	bit 11 set to one so that both	LSB and MSB are needed to change the outputfrequency. Bit 10 set to 1 to Enable DAC. Bit 9 set to 1	to select sinusoidal wave (0 for triangle wave).	Bit 8 set to 0 for N=no square output(1 for square output from MSBout)	Bit 5 set to 0 to enable automatic frequecny sweep(Don't matter). Bit 3 only matter if bit 2 is set to 1.	Bit 2 set to 0 to not have a pulse at end of sweep(not needed)|	
|No of increment|		0	0	0	1	0	0	0	0	0	0	0	0	0	0	1	0	|0x1002|The bit transmitted should be set to decimal equivalent of 2 for the minimum number of frequency increments(not needed in our case)|
|Period of increment|0	1	1	0	x	x	x	x	x	x	x	x	x	x	x	x|	0x63E8|	Don't care if no frequency sweeping is needed. It is initailized to 1000/MCLK=0.03s|
Frequency Increment LSB|0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0|0x2000|		Set to 0 if not needed|
Frequency Increment MSB|0	0	1	1	0	0	0	0	0	0	0	0	0	0	0	0	|0x3000|Set to 0 if not needed|																
Start Frequency LSB|1	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0|0xC000|	Set the frequency output. Divide the desired frequency by 0.00195 to yield the data bits.|
Start Frequency MSB	|1	1	1	0	0	0	0	0	0	0	0	0	0	0	0	0|0xD000|Set the frequency output. Divide the desired frequency by 0.00195 to yield the data bits.|












