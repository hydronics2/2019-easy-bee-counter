/*
 *  
 * Gate Map (Sensor Numbers)
 *   gate     0   ||  1  ||  2  ||  3  ||  4   ||   5  ||  6   ||  7   ||  8   ||  9   ||  10  ||  11  ||  12  ||  13  ||  14  ||  15  ||  16  ||  17  ||  18  ||  19  ||  20  ||  21  ||  22  ||  23
 *   inside   1   ||  3  ||  5  ||  7  ||  9   ||  11  ||  13  ||  15  ||  17  ||  19  ||  21  ||  23  ||  25  ||  27  ||  29  ||  31  ||  33  ||  35  ||  37  ||  39  ||  41  ||  43  ||  45  ||  47
 *   outside  2   ||  4  ||  6  ||  8  ||  10  ||  12  ||  14  ||  16  ||  18  ||  20  ||  22  ||  24  ||  26  ||  28  ||  30  ||  32  ||  34  ||  36  ||  38  ||  40  ||  42  ||  44  ||  46  ||  48
 * 
 * Gate Map (bit numbers)
 *   gate    ||  00  ||  01  ||  02  ||  03  ||  04  ||  05  ||  06  ||  07  ||  08  ||  09  ||  10  ||  11  ||  12  ||  13  ||  14  ||  15  ||  16  ||  17  ||  18  ||  19  ||  20  ||  21  ||  22  ||  23  ||
 *   inside  ||   5  ||   7  ||   2  ||   0  ||  13  ||  15  ||  10  ||   8  ||  21  ||  23  ||  18  ||  16  ||  29  ||  31  ||  26  ||  24  ||  37  ||  39  ||  34  ||  32  ||  45  ||  47  ||  42  ||  40  ||
 *   outside ||   4  ||   6  ||   3  ||   1  ||  12  ||  14  ||  11  ||   9  ||  20  ||  22  ||  19  ||  17  ||  28  ||  30  ||  27  ||  25  ||  36  ||  38  ||  35  ||  33  ||  44  ||  46  ||  43  ||  41  ||
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
 *  Rough Power Draw with cheap USB current sensor
 *  feather ESP32 by itself with tp/T  15us/2ms => 50ma
 *  feather ESP32 by itself with tp/T  15us/10ms => 40-50ma
 *  ESP32 & LEDs
 *  tp/T  15us/2ms  100ma
 *  tp/T  15us/4ms  75ma
 *  tp/T  15us/6ms  60-70ma had to add 3000uf cap to smooth out drawl
 *  tp/T  15us/8ms  50-60ma had to add 3000uf cap to smooth out drawl
 *  tp/T  15us/10ms  50ma had to add 3000uf cap to smooth out drawl 
 *  
 *  This sketch:
 *  It takes a honey bee around 250ms to traverse the sensor This code only looks for honeybees moving faster than 650ms.
 *  
 */
#define REV	1


// Map of sensor number onto input pin on shift register (sensor number % 8 = pin number, int(sensor number / 8) = shift register number)
#if REV >= 2
uint8_t gatemap[] = {
	0b00100000,	// Gate 0 (1I)
	0b00010000,	// Gate 1 (1O)
	0b10000000,	// Gate 2 (2I)
	0b01000000,	// Gate 3 (2O)
	0b00000100,	// Gate 4 (3I)
	0b00001000,	// Gate 5 (3O)
	0b00000001,	// Gate 6 (4I)
	0b00000010,	// Gate 7 (4O)
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

#define testLed  13 //onboard LED
#define LATCH    A5 // Shift Register Latch Control Pin

// Use compile-time macrod defined from build.board in boards.txt to determine which board type.
//Pins Feather ESP32
#if defined ARDUINO_FEATHER_ESP32
#define powerGates1 15
#define powerGates2 33
//Pins ItsyBitsy
#elif defined ARDUINO_ITSYBITSY_M0
#define powerGates1 10
#define powerGates2 11
#else
#warning Unknown board type, defaulting to ESP32 Feather Pinout
#define powerGates1 15
#define powerGates2 33
#endif

#define numberOfGates 24
#define startGate 0
#define endGate 24
#define debeebounce 30
#define outputDelay 15000
uint32_t lastOutput = 0;
uint32_t currentTime = 0;

//boolean 0 or 1 sensor readings, 1 bee is present
boolean inSensorReading[numberOfGates];
boolean outSensorReading[numberOfGates];

boolean lastInSensorReading[numberOfGates];
boolean lastOutSensorReading[numberOfGates];

boolean checkStateIn[numberOfGates];
boolean checkStateOut[numberOfGates];

int16_t inCount[numberOfGates];
int16_t outCount[numberOfGates];
  
uint32_t startInReadingTime[numberOfGates];
uint32_t startOutReadingTime[numberOfGates];

uint32_t inSensorTime[numberOfGates];
uint32_t outSensorTime[numberOfGates];
 
uint32_t lastInFinishedTime[numberOfGates];
uint32_t lastOutFinishedTime[numberOfGates];
  
uint32_t inReadingTimeHigh[numberOfGates];
uint32_t outReadingTimeHigh[numberOfGates];

uint32_t lastInTime[numberOfGates];
uint32_t lastOutTime[numberOfGates];

uint32_t lastInReadingTimeHigh[numberOfGates];
uint32_t lastOutReadingTimeHigh[numberOfGates];

int16_t totalTimeTravelGoingOut[numberOfGates];
int16_t totalTimeTravelGoingIn[numberOfGates];

int16_t firstTestInVariable[numberOfGates];


int16_t firstTestOutVariable[numberOfGates];


uint16_t inTotal;
uint16_t outTotal;


int n = 0;


uint8_t switchBank[numberOfGates / 4]; // 4 gates per chip, 8 sensors
uint8_t oldSwitchBank[numberOfGates / 4];

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
  result = switchBank[byte] & gatemap[(sensor % 8)];
  if (result) return(true);
  return(false);
}

bool get_o_sensor_value(uint8_t sensor)
{
  uint8_t byte;
  uint8_t result;
  uint8_t bit_position;

  byte = sensor / 8;
  result = oldSwitchBank[byte] & gatemap[(sensor % 8)];
  if (result) return(true);
  return(false);
}


void setup ()
{
  
  SPI.begin();
  SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE2));
  
  Serial.begin (115200);
  Serial.println ("Begin switch test.");
  pinMode (LATCH, OUTPUT);
  digitalWrite (LATCH, HIGH);

  pinMode (powerGates1, OUTPUT);
  digitalWrite(powerGates1, LOW);
  pinMode (powerGates2, OUTPUT);
  digitalWrite(powerGates2, LOW);

  pinMode(testLed, OUTPUT);

  memset(switchBank, 0, (numberOfGates / 4));
  memset(oldSwitchBank, 0, (numberOfGates / 4));
  
}  // end of setup

void loop ()
{
  uint8_t gate;
  currentTime = millis();  
  
  digitalWrite(powerGates1, HIGH);
  digitalWrite(powerGates2, HIGH);
  delayMicroseconds(75); //first 24 gates only need 15us while gates closer to the end need ~40us-75us
  
  digitalWrite (LATCH, LOW);    // pulse the parallel load latch
  delayMicroseconds(3);
  digitalWrite (LATCH, HIGH);

  delayMicroseconds(3);
  
  digitalWrite(powerGates1, LOW);
  digitalWrite(powerGates2, LOW);

  //Reading 24 bits at 1Mhz should take about 24 microseconds,
  //reading 24 bits at 3Mhz should take about 8us
  //reading 48 bits at 3Mhz should take abotu 16us
  (void) SPI.transfer((uint8_t *)switchBank, (uint32_t)(numberOfGates / 4));
 
  
  
  // Store received values from gate scan if changed
  if (memcmp(switchBank, oldSwitchBank, (numberOfGates / 4)))
  {
    for(gate=0; gate < numberOfGates; gate++)
    {
      inSensorReading[gate] = get_sensor_value(gate * 2);			// Even number sensors are inside
      outSensorReading[gate] = get_sensor_value(gate * 2 + 1);		// Odd number gates are outside
    }
    // Move current retrieved values to old values for comparison
    memcpy(oldSwitchBank, switchBank, (numberOfGates / 4));
  }

  for (int i = startGate; i < endGate; i++) 
  { 
    if(inSensorReading[i] == HIGH || outSensorReading[i] == HIGH) 
    {
      digitalWrite(testLed, HIGH);
      break;
    }
    digitalWrite(testLed, LOW);
  }

  
  for (int i = startGate; i < endGate; i++) 
  //for (int i = 8; i < 12; i++)
  { 
    if(inSensorReading[i] != lastInSensorReading[i])  //change of state on IN sensor
    { 
      checkStateIn[i] = 0;
      lastInSensorReading[i] = inSensorReading[i];
      inSensorTime[i] = currentTime;
      //Serial.print(i);
      //Serial.print(", ");
      //Serial.println(inSensorReading[i]);
    } 
    if(outSensorReading[i] != lastOutSensorReading[i])  //change of state on OUT sensor
    { 
      checkStateOut[i] = 0;
      lastOutSensorReading[i] = outSensorReading[i];
      outSensorTime[i] = currentTime;
      //Serial.print(i);
      //Serial.print(", ");
      //Serial.println(outSensorReading[i]);
    }       
    if(currentTime - inSensorTime[i] > debeebounce && checkStateIn[i] == 0)  //debounce IN sensor
    {
      checkStateIn[i] = 1; //passed debounce         
      //Serial.print(i);
      //Serial.print(", IN sensor - high_or_low: ");
      //Serial.println(inSensorReading[i]);
      if(inSensorReading[i] == HIGH) //a bee just entered the sensor
      {
        startInReadingTime[i] = currentTime;
        //Serial.print(i);
        //Serial.print(", I ,");
        //Serial.println(currentTime);
      }
      if(inSensorReading[i] == LOW)  //a bee just exits the sensor; that is, it was HIGH, now it is LOW (empty)
      {  
        lastInFinishedTime[i] = currentTime;            
        inReadingTimeHigh[i] = currentTime - startInReadingTime[i]; //this variable is how long the bee was present for
        Serial.print(i);
        Serial.print(", IT ,");
        Serial.print(inReadingTimeHigh[i]);
        Serial.print(", ");    
        if(outReadingTimeHigh[i] < 650 && inReadingTimeHigh[i] < 650){ //should be less than 650ms
          if(currentTime - lastOutFinishedTime[i] < 200){ //the sensors are pretty cose together so the time it takes to trigger on and then the other should be small.. ~200ms
            inTotal++;
            Serial.print(currentTime);
            Serial.print(",");
            Serial.println(1);
          }else{
            Serial.println(currentTime);
          }
        }else{
          Serial.println(currentTime);
        }
      }           
    }
    if(currentTime - outSensorTime[i] > debeebounce && checkStateOut[i] == 0)  //debounce OUT sensor
    {
      checkStateOut[i] = 1; //passed debounce         
      //Serial.print(i);
      //Serial.print(", IN sensor - high_or_low: ");
      //Serial.println(outSensorReading[i]);
      if(outSensorReading[i] == HIGH) //a bee just entered the sensor
      {
        startOutReadingTime[i] = currentTime;
        //Serial.print(i);
        //Serial.print(", O ,");
        //Serial.println(currentTime);
      }
      if(outSensorReading[i] == LOW)  //a bee just exits the sensor; that is, it was HIGH, now it is LOW (empty)
      {  
        lastOutFinishedTime[i] = currentTime;            
        outReadingTimeHigh[i] = currentTime - startOutReadingTime[i]; //this variable is how long the bee was present for
        Serial.print(i);
        Serial.print(", OT ,");
        Serial.print(outReadingTimeHigh[i]);
        Serial.print(", ");        
        if(outReadingTimeHigh[i] < 600 && inReadingTimeHigh[i] < 600){ //should be less than 600ms
          if(currentTime - lastInFinishedTime[i] < 200){ //the sensors are pretty cose together so this time should be small
            outTotal++;
            Serial.print(currentTime);
            Serial.print(",");
            Serial.println(1);
          }else{
            Serial.println(currentTime);
          }
        }else{
          Serial.println(currentTime);
        }
      }          
    }        
  }    

  delay (15);   // debounce

  if (currentTime - lastOutput > outputDelay) 
    {
    //Serial.println("sending data");
    sendData(); 
    lastOutput = currentTime; 
    inTotal = 0;
    outTotal = 0; 
  }
}
      

void sendData() {
  Serial.print("T, ");
  Serial.print(outTotal);
  Serial.print(", ");
  Serial.println(inTotal);
// over wifi or ethernet or serial
}
  
