# 2019 Easy Bee Counter V.1

This version of the bee counter is easy to solder and assemble (all through-hole).  It's been tested and works* with sample code provided.

The current tested design is easy to program and approachable to beginner programmers.  The printed circuit board accepts multiple Arduino platforms made by Adafruit including their line of [Adafruit Feather](https://www.adafruit.com/category/777) type micro-controllers and [Adafruit ItsyBitsy](https://www.adafruit.com/category/1008) micro-controllers.   The Adafruit feathers include wifi and long range radio features (*esp8266, esp32, and LoRA). All the ItsyBitsy 3V models (M0, M4, and 32u4) should work fine.

*the esp8266 is missing A5 so you have to jumper to another pin if you use it

[![Foo](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/bees_flying.PNG)](https://youtu.be/SzXWWUh2k8w)


### [Data Analysis - *why count bees?](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/Data/README.md)
### [Instructions](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/README.md)
### [Arduino Code](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/arduino/README.md)
### Major Differences/Improvements
- All through-hole components for easy soldering
- Dual footprint, socketed, off-the-shelf micro-controllers => Feather and ItsyBitsy
- Program in Arduino, Lua, and microPython
- A total of 24 gates, 48 sensors, 6 shift registers
- ~14.75" long stretching the entire opening of a langstroth hive for easy placement
- using 2 PCBs to create a sandwich is an inexpensive quick solution. The PCBs must be ordered [black](https://github.com/hydronics2/2019-easy-bee-counter/tree/master/instructions/ordering_instructions) so the IR LED emitter is absorbed into the material.
- using 6 pin headers to create the turn-styles or gates
- N-Ch mosfet controlled IR LEDs such that LEDs can be controlled ON for short periods during while sensing (~75us). Allows for reduced power to less than 1ma (plus micro-controller).
![feather](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/gerber_feather_2.PNG)
![feather](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/finished.jpg)
![feather](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/finished2.jpg)
![feather](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/feather_finish.PNG)
![feather](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/itsy_bitsy_finish.PNG)
![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/pcb_notes_.PNG)

### General Operation
Honeybees are forced through 24 gates where optical sensors (48 sensors) determine whether the bee is present and determine the direction of the bee movement. Each optical sensors has an IR LED and an IR sensor. If no bee is present the IR light is absorbed into the black surface. If a bee is present the IR light reflects off the bee and triggers the sensor. ![https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/IR_photo_diode.PNG](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/IR_photo_diode.PNG)

### Micro-Controller Pinout
#### Feather ESP32 Pinout
![feather](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/feather_pinout3.PNG)
#### ItsyBitsy Pinout
![itsy](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/pics/itsy_pinout2.PNG)
### Shift-in registers
There are 6 shift-in registers. Here's a great description for how to connect and program [shift registers](http://www.gammon.com.au/forum/?id=11979).  The micro-controller's SPI pins read the shift registers. All six shift registers are read at the same time. The sensors are normally pulled low and show 3.3V or HIGH when a transistor is triggered and a bee is present.

### IR LEDs
The 48 LEDs are divided into two sets of 24 with each set controlled by an N-ch mosfet. The normal forward voltage of each IR LED is 1.2V and about 20ma as shown on the [data sheet](https://www.sparkfun.com/datasheets/Robotics/QR_QRE1113.GR.pdf). Two LEDs are connected in series with a 22ohm resistor. There are jumpers on the board that allow the LEDs to bypass the current limiting resistors. Do not solder the jumper until fully tested! Refer to [these instructions](https://github.com/hydronics2/2019-easy-bee-counter/tree/master/instructions)

### Power
The PCB design connects the USB power pin from the uController to the 3.3V regulator so that a usb cable connected to the micro-controller can power the entire project.


### Bill of Materials
#### uController
The code was tested with the feather esp32 Huzzah and itsyBitsy M0 but will work with all these boards.
- feather Huzzah from [mouser](https://www.mouser.com/ProductDetail/485-3591)
- feather esp8266 from [mouser](https://www.mouser.com/ProductDetail/485-2821)
  - the esp8266 is missing A5, so if this micro is used you have to jumper to another pin
- feather LoRa 900mhz from [mouser](https://www.mouser.com/ProductDetail/485-3178)
- ItsyBitsy M0 from [mouser](https://www.mouser.com/ProductDetail/485-3727)
- ItsyBitsy M4 from [mouser](https://www.mouser.com/ProductDetail/485-3800)
#### PCB
[JLCPCB](https://jlcpcb.com/quote#/) ~$16-25 with shipping. Order the PCBs Black. See [these instructions](https://github.com/hydronics2/2019-easy-bee-counter/tree/master/instructions/ordering_instructions) for ordering.
#### Parts and Pieces from [mouser](https://www.mouser.com/ProjectManager/ProjectDetail.aspx?AccessID=054286973a)
See alternative pricing below for cheaper options specifically for the reflectance sensors.
- [qre1113 Reflective Sensors](https://www.mouser.com/ProductDetail/512-QRE1113f) qty(48)
- [6 pin female headers](https://www.mouser.com/ProductDetail/437-8018700610001101) 7mm high, 0.1" spacing, qty(~36)
- [22ohm resistors](https://www.mouser.com/ProductDetail/Xicon/266-22-RC?qs=sGAEpiMZZMvrmc6UYKmaNXFefT4dxyTCwtpTxTI0yoo%3D), bussed, qty(4)
SIP Packaged, bussed
- [100k ohm resistors](https://www.mouser.com/ProductDetail/IRC-TT-Electronics/L091S104LF?qs=sGAEpiMZZMvrmc6UYKmaNdnTrsZX%2FuSiyGduauH5Qpc%3D) bussed, qty(6)
SIP-9, 8 resistors, 9 pins
- Shift registers, qty(6)
[74HC165](https://www.mouser.com/ProductDetail/595-SN74HC165N)
- [3.3V Regulator](https://www.mouser.com/ProductDetail/Microchip-Technology/MCP1826S-3302E-AB?qs=sGAEpiMZZMsGz1a6aV8DcJ7KfjtCj7Xd5CqQpyOghgk%3D), (input, ground, output - IGO, pinout), qty(1)
- [screw terminals](https://www.mouser.com/ProductDetail/490-TB006-508-02BE) Two pin, 0.1", qty(3)
- [0.1 uF Ceramic Capacitor](https://www.mouser.com/ProductDetail/594-K104K15X7RF53H5), through hole, qty(6)
- [1 uF Ceramic Capacitor](https://www.mouser.com/ProductDetail/594-K105Z20Y5VF5TL2), through hole, qty(1)
- [560uF, 6.3V Capacitor](https://www.mouser.com/ProductDetail/661-APSC6R3L561MH08S)
low esr, 3.5mm lead spacing, 8mm diameter
- N-Channel Mosfet [FQP30N06](https://www.mouser.com/ProductDetail/512-FQP30N06L), qty(2)

#### Alternative pricing from Chinese distributor LCSC
Someone pointed out some alternative pricing that can really bring the cost down.
- [ITR8307 Reflectance Sensors](https://lcsc.com/product-detail/Photo-Interrupter_Everlight-Elec-ITR8307_C63451.html) ~$0.13/each @ qty(48) (same as QRE1113)
- [6 pin female headers](https://lcsc.com/product-detail/Pin-Header-Female-Header_BOOMELE-Boom-Precision-Elec-C40877_C40877.html) 8.5mm high. ~$0.05/each @ qty(36+)
- [22 ohm SIP](https://lcsc.com/product-detail/Resistor-Networks-Arrays_FH-Guangdong-Fenghua-Advanced-Tech-A09-220JP_C9105.html) 8 resistor, 9 pin, it will fit. $0.44 for qty(4)
- [100k SIP Resistors](https://lcsc.com/product-detail/Resistor-Networks-Arrays_FH-Guangdong-Fenghua-Advanced-Tech-A09-104JP_C9108.html) 8 resistor, 9pin, it will fit. $0.44 for qty(6)
