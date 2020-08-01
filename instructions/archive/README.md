# 2019 Easy Bee Counter V.0 Build Instructions

I made a few mistakes on the first version (v0). The 74hc165 is not a true SPI device. It doesn't have a tri-state buffer on the MISO.

https://electronics.stackexchange.com/questions/121249/how-to-put-a-74hc165-on-an-spi-bus


The following fix, allows you to shift in all the data at once (all shift registers)... all shift registers are therefore always enabled. This fix wil work with all the stand alone feather micro-controllers... ESP32, ESP8266, SAMD21 M0 and M4... but doesn't work with the [LoRa module](https://cdn-learn.adafruit.com/assets/assets/000/031/658/original/feather_schem.png?1460518302) as it ALSO uses the SPI buss. In order to work with the LORa module you need to swap out the 74hc165 shift registers with true SPI based shift registers... like the 74HC589 referenced in the above [stack exchange](https://electronics.stackexchange.com/a/128220) answer.


To fix the old board... we want to read all 6 shift registers so just cut one of the MISO signal lines and add a jumper.

video cutting signal https://photos.app.goo.gl/VkyV412uJGBNS7sx8

video adding jumper https://photos.app.goo.gl/QXMhvH7FzpDfXWLs7

Top view showing cut jumper
![foo](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/archive/cut_miso.PNG)

Top view showing jumper(blue)
![foo](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/archive/miso_patch.PNG)
