# Arduino

There are two test scripts here. One to blink LEDs and one to test shift registers.

### Warning
Soldering the 24 jumpers increases the throw range of the IR sensors by increasing the forward voltage and current in the LED. This is fine if we keep the LEDs ON time to less than 100us.

Two scripts above, both [test_shift_registers](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/arduino/test_shift_registers/test_shift_registers.ino) and [bee_counting](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/arduino/bee_counting/bee_counting.ino) satisfy this requirement by only turning the LEDs ON for 75us.  This is shown on line 68 (shift register) and line 158 (bee_counting).

### Calibrating the Bee Counter
I've captured some amazing data over the years. It's possible to calibrate the bee counter to achieve the required repeatability. Some of the obstacles to calibrate for include:
 - although bees don't add propolis to sensors they will spend several days filling voids with propolis upon initial installation
 - bearding in the summer evenings and general guard bees mulling about give false triggers
 - direct sun light at a low angle will false trigger sensors (this can be mitigated pretty easily)

One method is to measure the speed of the bees movement and only count known movements and throwing out all false triggers. This method misses a lot of bees but can give consistent values. It takes a bee about 180-350ms to traverse the sensor region.

The [bee_counting](https://github.com/hydronics2/2019-easy-bee-counter/blob/master/arduino/bee_counting/bee_counting.ino) code measures the speed of the bees through the sensor and counts bees moving faster than 650ms and demands the time between finishing one sensor and finishing the 2nd sensor is less than 150ms.
