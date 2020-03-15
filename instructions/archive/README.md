# 2019 Easy Bee Counter V.0 Build Instructions

I made a few mistakes on the first version (v0). The 74hc165 is not a true SPI device. It doesn't have a tri-state buffer on the MISO.

https://electronics.stackexchange.com/questions/121249/how-to-put-a-74hc165-on-an-spi-bus

To fix the old board... we want to read all 6 shift registers so just cut one of the MISO signal lines and add a jumper.

Add Jumper and cut leads
https://photos.app.goo.gl/VkyV412uJGBNS7sx8
https://photos.app.goo.gl/QXMhvH7FzpDfXWLs7

![foo](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/archive/cut_miso.PNG)
![foo](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/instructions/archive/miso_patch.PNG)
