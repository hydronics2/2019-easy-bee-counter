# 2019 Easy Bee Counter V.1 Build Instructions

This version of the bee counter is all through hole components. It's easy to solder and assemble. This is the 2nd version of the board (V1) completed March 2020. If you got the [Version 0](https://github.com/hydronics2/2019-easy-bee-counter/tree/b06d461f1881f2709d81f82d817dc76170a77fa7) board (Jan/Feb 2020) you just have to fix some of my previous mistakes including adding a jumper wire shown [here](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/archive)

1) Install IR sensors - [QRE1113](https://www.mouser.com/ProductDetail/512-QRE1113f) or [ITR8307](https://lcsc.com/product-detail/Photo-Interrupter_Everlight-Elec-ITR8307_C63451.html)

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/ir_sensors.PNG)

2) install shift registers qty(6), SIP 22R LED resistors and 100k pulldown resistors.
- Shift registers, qty(6) [74HC165](https://www.mouser.com/ProductDetail/595-CD74HC165E)

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/registers.PNG)
- [22ohm resistors](https://www.mouser.com/ProductDetail/Xicon/266-22-RC?qs=sGAEpiMZZMvrmc6UYKmaNXFefT4dxyTCwtpTxTI0yoo%3D), bussed, qty(4)
SIP Packaged, bussed
- [100k ohm resistors](https://www.mouser.com/ProductDetail/IRC-TT-Electronics/L091S104LF?qs=sGAEpiMZZMvrmc6UYKmaNdnTrsZX%2FuSiyGduauH5Qpc%3D) bussed, qty(6)
SIP-9, 8 resistors, 9 pins

3) install power mosfets qty(2),
- N-Channel Mosfet [FQP30N06](https://www.mouser.com/ProductDetail/512-FQP30N06L)

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/PowerMosfets.PNG)

4) install small capacitors

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/small_capacitors.PNG)

5) place/solder 3.3V power regulator

- [3.3V Regulator](https://www.mouser.com/ProductDetail/Microchip-Technology/MCP1826S-3302E-AB?qs=sGAEpiMZZMsGz1a6aV8DcJ7KfjtCj7Xd5CqQpyOghgk%3D), (input, ground, output - IGO, pinout), qty(1)

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/3vRegulator.PNG)

6) install large Capacitor

- [560uF, 6.3V Capacitor](https://www.mouser.com/ProductDetail/661-APSC6R3L561MH08S)

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/capacitor.PNG)

7) install green screw terminals, qty(3)

- [screw terminals](https://www.mouser.com/ProductDetail/490-TB006-508-02BE) Two pin, 0.1", qty(3)

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/headers.PNG)

8) install headers for microprocessor

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/uHeaders.PNG)

9) install qty(4) 10K Resistors
- i2c pullup resistors
- pulldown resistors for power mosfets

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/10kPullup.PNG)

## TEST sensors
Before you go any farther, test all your LEDs/sensors! It's much easier to test these now before going further.
Run the sample code [blink_IR_Leds](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/arduino/Blink_IR_Leds/Blink_IR_Leds.ino).

The IR LEDs are invisible to the human eye but many phones and cameras allow you to see the IR LEDs. See picture. (unfortunately most iphones have IR filters so try another phone until you see IR leds). This step is very important so make sure you can see all the LEDs.

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/ir_sensors_on.PNG)

LEDs look good? If no LEDs are blinking? Check to make sure you have 3.3V on the 3.3V pin header. If one or two LEDs are out, reflow your pins and/or replace the LEDs until you get 100% LEDs blinking together.

LEDs good, great, next test the shift registers with the sample code [test_shift_registers](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/arduino/test_shift_registers/test_shift_registers.ino). Use a white piece of paper to trigger the sensors. If some sensors are not working, check your pins, heat up and reflow solder on pins as needed.

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/serial_output.PNG)

10) Finish assembly once all sensors are tested. Install the headers that connect the top PCB to the bottom PCB.

![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/headers_bottom.PNG)
![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/finished.jpg)
![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/finished2.jpg)

11) Ok, once everything is tested out, you can short these jumpers.... BUT, now we can only turn the LEDs on for 100us. In Arduino that's delayMicroseconds(100).  Any longer and you risk burning out all 48 LEDs.  Making these jumpers increases the throw range of the LEDs.

Solder all 24 of the jumpers.
![pic](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/pics/jumpers.PNG)
