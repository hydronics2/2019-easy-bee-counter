from machine import Pin
import utime
# How many shift register chips are daisy-chained.
NUMBER_OF_SHIFT_CHIPS = 3

# Width of data (how many ext lines)
DATA_WIDTH = NUMBER_OF_SHIFT_CHIPS * 8

# Width of pulse to trigger the shift register to read and latch.
PULSE_WIDTH_USEC = 5

# Optional delay between shift register reads.
POLL_DELAY_MSEC = 1

pinValues = 0
oldPinValues = 0

def display_pin_values():
print("Pin states: ")
for i in range(24):
if(pinValues >> i & 1):
print(" Pin-" , i , ": HIGH")
else:
print(" Pin-" , i , ": LOW")
print("\r\n")

def read_shift_regs():
bitVal = 0
bytesVal = 0
ploadPin.value(0)
utime.sleep_us(PULSE_WIDTH_USEC)
ploadPin.value(1)

for i in range(DATA_WIDTH):

bitVal = dataPin.value()
# Set the corresponding bit in bytesVal.
bytesVal |= (bitVal << ((DATA_WIDTH-1) - i))
clockPin.value(1)
utime.sleep_us(PULSE_WIDTH_USEC)
clockPin.value(0)
return bytesVal



#Set up
ploadPin = Pin('P23', mode=Pin.OUT) #Blue
dataPin = Pin('P22', mode=Pin.IN) #Yellow
clockPin = Pin('P21', mode=Pin.OUT) #PARPEL

clockPin.value(0)
ploadPin.value(1)

clockPin.value(0)
ploadPin.value(1)



pinValues = read_shift_regs()
display_pin_values()
oldPinValues = pinValues

while True:
pinValues = read_shift_regs()
utime.sleep_ms(POLL_DELAY_MSEC)
pinValues = read_shift_regs()
utime.sleep_ms(POLL_DELAY_MSEC)
if(pinValues != oldPinValues):
pinValues = read_shift_regs()
if(pinValues != oldPinValues):
print("Pin value change detected*\r\n")
display_pin_values()
oldPinValues = pinValues
utime.sleep_ms(POLL_DELAY_MSEC)
