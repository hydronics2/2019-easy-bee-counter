/*
 * For more help on reading shift registers: http://www.gammon.com.au/forum/?id=11979
 *  
 * Gate Map (sensor numbers):
 *   gate     0   ||  1  ||  2  ||  3  ||  4   ||   5  ||  6   ||  7   ||  8   ||  9   ||  10  ||  11  ||  12  ||  13  ||  14  ||  15  ||  16  ||  17  ||  18  ||  19  ||  20  ||  21  ||  22  ||  23
 *   inside   1   ||  3  ||  5  ||  7  ||  9   ||  11  ||  13  ||  15  ||  17  ||  19  ||  21  ||  23  ||  25  ||  27  ||  29  ||  31  ||  33  ||  35  ||  37  ||  39  ||  41  ||  43  ||  45  ||  47
 *   outside  2   ||  4  ||  6  ||  8  ||  10  ||  12  ||  14  ||  16  ||  18  ||  20  ||  22  ||  24  ||  26  ||  28  ||  30  ||  32  ||  34  ||  36  ||  38  ||  40  ||  42  ||  44  ||  46  ||  48
 *
 * Gate Map (bit numbers):
 *   gate    ||  00  ||  01  ||  02  ||  03  ||  04  ||  05  ||  06  ||  07  ||  08  ||  09  ||  10  ||  11  ||  12  ||  13  ||  14  ||  15  ||  16  ||  17  ||  18  ||  19  ||  20  ||  21  ||  22  ||  23  ||
 *   inside  ||   5  ||   7  ||   2  ||   0  ||  13  ||  15  ||  10  ||   8  ||  21  ||  23  ||  18  ||  16  ||  29  ||  31  ||  26  ||  24  ||  37  ||  39  ||  34  ||  32  ||  45  ||  47  ||  42  ||  40  ||
 *   outside ||   4  ||   6  ||   3  ||   1  ||  12  ||  14  ||  11  ||   9  ||  20  ||  22  ||  19  ||  17  ||  28  ||  30  ||  27  ||  25  ||  36  ||  38  ||  35  ||  33  ||  44  ||  46  ||  43  ||  41  ||
 *
 * The bit numbers map is layed out such that bits 0-7 map to the bits with values 2^0 through 2^7 respectively in the first octet transferred.
 * Bits 8-15 map similarly onto the second octet and so on.
 * 
 *  HOW long can we drive the LEDs ON without current limiting resistors?
 *  LED timed pulse (tp) allowance vs period (T)
 *  with increasing forward current the IR LED cutsheet says max tp/T = 0.01
 *  so the max tp for 1 amp is 100us and 100us/0.01 = 10ms
 *  with an ON time of ~75us the max period or delay between ON times is 75us/0.01=7.5ms
 *  So the minimum OFF time between ON times is 7.5ms
 *  This is very conservative as the forward voltage of 3.3v/2 = 1.65v, and max current from the cutsheet is estimated ~170ma 
 *  this is well below the absolute max of 1 amp with which the tp/T ratio was developed for
 *  
 */

#define REV     1


// Map of sensor number onto input pin on shift register (sensor number % 8 = pin number, int(sensor number / 8) = shift register number)
#if REV >= 2
uint8_t gatemap[] = {
        0b00100000,     // Gate 0 (1I)
        0b00010000,     // Gate 1 (1O)
        0b10000000,     // Gate 2 (2I)
        0b01000000,     // Gate 3 (2O)
        0b00000100,     // Gate 4 (3I)
        0b00001000,     // Gate 5 (3O)
        0b00000001,     // Gate 6 (4I)
        0b00000010,     // Gate 7 (4O)
};
#else
uint8_t gatemap[] = {
        0b00000001,     // Gate 0 (1I)
        0b00000010,     // Gate 1 (1O)
        0b00000100,     // Gate 2 (2I)
        0b00001000,     // Gate 3 (2O)
        0b00010000,     // Gate 4 (3I)
        0b00100000,     // Gate 5 (3O)
        0b01000000,     // Gate 6 (4I)
        0b10000000,     // Gate 7 (4O)
};
#endif


#include <SPI.h>

#define LATCH A5

// Use compile-time macrod defined from build.board in boards.txt to determine which board type.
//Pins Feather ESP32
#if defined ARDUINO_FEATHER_ESP32
#define powerGates1 15
#define powerGates2 33
//Pins ItsyBitsy
#elif defined ARDUINO_ITSYBITSY_M0
#define powerGates1 = 10
#define powerGates2 = 11
#else
#warning Unknown board type, defaulting to ESP32 Feather Pinout
#define powerGates1 15
#define powerGates2 33
#endif

uint8_t sensors[6];
uint8_t o_sensors[6];

void sensor_to_name (uint8_t sensor, char *buf)
{
  // Take a sensor number and convert it to a gate name
  // Gate name is placed in buffer (must be at least 4 bytes)
  snprintf(buf, 4, "%0d%c", (sensor >> 1), (sensor % 2) ? 'O' : 'I');
}

bool get_sensor_value(uint8_t sensor)
{
  uint8_t byte;
  uint8_t result;
  uint8_t bit_position;

  byte = sensor / 8;
  result = sensors[byte] & gatemap[(sensor % 8)];
  if (result) return(true);
  return(false);
}

bool get_o_sensor_value(uint8_t sensor)
{
  uint8_t byte;
  uint8_t result;
  uint8_t bit_position;

  byte = sensor / 8;
  result = o_sensors[byte] & gatemap[(sensor % 8)];
  if (result) return(true);
  return(false);
}

void setup ()
{
  
  SPI.begin();
  SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE2)); //3Mhz
  //Reading 24 bits (all sensors) at 1Mhz should take about 24 microseconds,
  //reading 24 bits (all sensors) at 3Mhz should take about 8us
  
  Serial.begin (115200);
  Serial.println ("Begin switch test.");
  pinMode (LATCH, OUTPUT);
  digitalWrite (LATCH, HIGH);

  pinMode (powerGates1, OUTPUT);
  digitalWrite(powerGates1, LOW);
  pinMode (powerGates2, OUTPUT);
  digitalWrite(powerGates2, LOW);
  
  memset(sensors, 0, 6);
  memset(o_sensors, 0, 6);
}  // end of setup


void loop ()
{
  uint8_t result;
  uint8_t sensor;
  bool o_value;
  bool value;
  char name[4];
  char output[60];

  digitalWrite(powerGates1, HIGH);
  digitalWrite(powerGates2, HIGH);
  delayMicroseconds(75); //first 24 gates only need 15us while gates closer to the end need ~40us-75us
  
  
  digitalWrite (LATCH, LOW);    // pulse the parallel load latch
  delayMicroseconds(3);
  digitalWrite (LATCH, HIGH);

  delayMicroseconds(3);
  
  digitalWrite(powerGates1, LOW);
  digitalWrite(powerGates2, LOW);

  (void) SPI.transfer(sensors, 6); // Sends 6 octets currently in sensors out MOSI and replaces it with 6 octets read in from MISO  

  // Work through sensors in order and display any that have changed.
  for(sensor = 0; sensor < 48; sensor++)
  {
    value = get_sensor_value(sensor);
    o_value = get_o_sensor_value(sensor);
    sensor_to_name(sensor, name);
    if (value != o_value)
    {
      snprintf(output, 60, "Sensor: %s %s\n", name, value ? "Triggered" : "not triggered");
      Serial.print(output);
    }
  }
  memcpy(o_sensors, sensors, 6);
  delay (20);   // must be greater than 7.5ms (see notes at top of code)
}  // end of loop
