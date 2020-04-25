/*
 *  
 *   gate     0   ||  1  ||  2  ||  3  ||  4   ||   5  ||  6   ||  7   ||  8   ||  9   ||  10  ||  11  ||  12  ||  13  ||  14  ||  15  ||  16  ||  17  ||  18  ||  19  ||  20  ||  21  ||  22  ||  23
 *   inside   1   ||  3  ||  5  ||  7  ||  9   ||  11  ||  13  ||  15  ||  17  ||  19  ||  21  ||  23  ||  25  ||  27  ||  29  ||  31  ||  33  ||  35  ||  37  ||  39  ||  41  ||  43  ||  45  ||  47
 *   outside  2   ||  4  ||  6  ||  8  ||  10  ||  12  ||  14  ||  16  ||  18  ||  20  ||  22  ||  24  ||  26  ||  28  ||  30  ||  32  ||  34  ||  36  ||  38  ||  40  ||  42  ||  44  ||  46  ||  48
 * 
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
 *  
 *  
 *  
 *  This sketch:
 *  It takes a honey bee around 250ms to traverse the sensor This code only looks for honeybees moving faster than 650ms.
 *  
 *  
 *  
 *  
 */

#include <SPI.h>

const int testLed = 13; //onboard LED
const int LATCH = A5; 

//Pins Feather ESP32
const byte powerGates1 = 15;
const byte powerGates2 = 33;

//Pins ItsyBitsy
//const byte powerGates1 = 10;
//const byte powerGates2 = 11;


const int numberOfGates = 24; // 24 gates, 48 sensors
const int startGate = 0;  //useful for testing
const int endGate = 24;   //useful for testing
const int debeebounce = 30;
const int outputDelay = 15000;  //prints bee counts every 15 seconds
unsigned long lastOutput = 0;
unsigned long currentTime = 0;


//boolean 0 or 1 sensor readings, 1 bee is present
boolean inSensorReading[numberOfGates];
boolean outSensorReading[numberOfGates];

boolean lastInSensorReading[numberOfGates];
boolean lastOutSensorReading[numberOfGates];

boolean checkStateIn[numberOfGates];
boolean checkStateOut[numberOfGates];

int inCount[numberOfGates];
int outCount[numberOfGates];
  
unsigned long startInReadingTime[numberOfGates];
unsigned long startOutReadingTime[numberOfGates];

unsigned long inSensorTime[numberOfGates];
unsigned long outSensorTime[numberOfGates];
 
unsigned long lastInFinishedTime[numberOfGates];
unsigned long lastOutFinishedTime[numberOfGates];
  
unsigned long inReadingTimeHigh[numberOfGates];
unsigned long outReadingTimeHigh[numberOfGates];

unsigned long lastInTime[numberOfGates];
unsigned long lastOutTime[numberOfGates];

unsigned long lastInReadingTimeHigh[numberOfGates];
unsigned long lastOutReadingTimeHigh[numberOfGates];

int totalTimeTravelGoingOut[numberOfGates];
int totalTimeTravelGoingIn[numberOfGates];

int firstTestInVariable[numberOfGates];


int firstTestOutVariable[numberOfGates];


int inTotal;
int outTotal;


int n = 0;



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
  
}  // end of setup

byte switchBank1;
byte oldSwitchBank1; 
byte switchBank2;
byte oldSwitchBank2; 
byte switchBank3;
byte oldSwitchBank3; 
byte switchBank4;
byte oldSwitchBank4; 
byte switchBank5;
byte oldSwitchBank5; 
byte switchBank6;
byte oldSwitchBank6; 
byte switchBank7;
byte oldSwitchBank7; 
byte switchBank8;
byte oldSwitchBank8; 

void loop ()
{
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
  switchBank1 = SPI.transfer (0); //8
  switchBank2 = SPI.transfer (0); //16
  switchBank3 = SPI.transfer (0); //24
  switchBank4 = SPI.transfer (0); //32
  switchBank5 = SPI.transfer (0); //40
  switchBank6 = SPI.transfer (0); //48  
  
 
  
  if(switchBank1 != oldSwitchBank1 || switchBank2 != oldSwitchBank2 || switchBank3 != oldSwitchBank3 || switchBank4 != oldSwitchBank4 || switchBank5 != oldSwitchBank5 || switchBank6 != oldSwitchBank6)
  {
    //convert bytes to gate values
    int gate = 0;
    for(int i = 0; i < 8; i++)
    {
      if((switchBank1 >> i) & 1)
          outSensorReading[gate] = HIGH;
      else outSensorReading[gate] = LOW;
      i++;
      if((switchBank1 >> i) & 1)
          inSensorReading[gate] = HIGH;
      else inSensorReading[gate] = LOW;       
      gate++;  
    }
    for(int i = 0; i < 8; i++)
    {
      if((switchBank2 >> i) & 1)
          outSensorReading[gate] = HIGH;
      else outSensorReading[gate] = LOW;
      i++;
      if((switchBank2 >> i) & 1)
          inSensorReading[gate] = HIGH;
      else inSensorReading[gate] = LOW;      
      gate++;  
    }
    for(int i = 0; i < 8; i++)
    {
      if((switchBank3 >> i) & 1)
          outSensorReading[gate] = HIGH;
      else outSensorReading[gate] = LOW;
      i++;
      if((switchBank3 >> i) & 1)
          inSensorReading[gate] = HIGH;
      else inSensorReading[gate] = LOW;       
      gate++;  
    }
    for(int i = 0; i < 8; i++)
    {
      if((switchBank4 >> i) & 1)
          outSensorReading[gate] = HIGH;
      else outSensorReading[gate] = LOW;
      i++;
      if((switchBank4 >> i) & 1)
          inSensorReading[gate] = HIGH;
      else inSensorReading[gate] = LOW;       
      gate++;  
    }
    for(int i = 0; i < 8; i++)
    {
      if((switchBank5 >> i) & 1)
          outSensorReading[gate] = HIGH;
      else outSensorReading[gate] = LOW;
      i++;
      if((switchBank5 >> i) & 1)
          inSensorReading[gate] = HIGH;
      else inSensorReading[gate] = LOW;       
      gate++;  
    }
    for(int i = 0; i < 8; i++)
    {
      if((switchBank6 >> i) & 1)
          outSensorReading[gate] = HIGH;
      else outSensorReading[gate] = LOW;
      i++;
      if((switchBank6 >> i) & 1)
          inSensorReading[gate] = HIGH;
      else inSensorReading[gate] = LOW;      
      gate++;  
    }  
    oldSwitchBank1 = switchBank1;
    oldSwitchBank2 = switchBank2;
    oldSwitchBank3 = switchBank3;
    oldSwitchBank4 = switchBank4;
    oldSwitchBank5 = switchBank5;
    oldSwitchBank6 = switchBank6;
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
  
