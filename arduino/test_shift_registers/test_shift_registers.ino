/*
 * For more help on reading shift registers: http://www.gammon.com.au/forum/?id=11979
 *  
 *   gate     1   ||  2  ||  3  ||  4  ||  5   ||   6  ||  7   ||  8   ||  9   ||  10  ||  11  ||  12  ||  13  ||  14  ||  15  ||  16  ||  17  ||  18  ||  19  ||  20  ||  21  ||  22  ||  23  ||  24
 *   inside   1   ||  3  ||  5  ||  7  ||  9   ||  11  ||  13  ||  15  ||  17  ||  19  ||  21  ||  23  ||  25  ||  27  ||  29  ||  31  ||  33  ||  35  ||  37  ||  39  ||  41  ||  43  ||  45  ||  47
 *   outside  2   ||  4  ||  6  ||  8  ||  10  ||  12  ||  14  ||  16  ||  18  ||  20  ||  22  ||  24  ||  26  ||  28  ||  30  ||  32  ||  34  ||  36  ||  38  ||  40  ||  42  ||  44  ||  46  ||  48
 * 
 *  HOW long can we drive the LEDs ON without current limiting resistors?
 *  LED timed pulse (tp) allowance vs period (T)
 *  with increasing forward current the IR LED cutsheet says max tp/T = 0.01
 *  so the max tp for 1 amp is 100us and 100us/0.01 = 10ms
 *  with an ON time of ~75us the max period or delay between ON times is 75us/0.01=7.5ms
 *  So the minimum OFF time between ON times is 7.5ms
 *  This is very conservative as the forward voltage of 3.3v/2 = 1.65v, and max current from the cutsheet is estimated ~170ma 
 *  this is well below the absolute max of 1 amp with which the tp/T ratio was developed for
 *  *  
 */


#include <SPI.h>

const int LATCH = 4; //A5

const byte powerGates1 = 15;
const byte powerGates2 = 33;

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

void loop ()
{
  digitalWrite(powerGates1, HIGH);
  digitalWrite(powerGates2, HIGH);
  delayMicroseconds(75); //first 24 gates only need 15us while gates closer to the end need ~40us-75us
  
  
  digitalWrite (LATCH, LOW);    // pulse the parallel load latch
  delayMicroseconds(3);
  digitalWrite (LATCH, HIGH);

  delayMicroseconds(3);
  
  digitalWrite(powerGates1, LOW);
  digitalWrite(powerGates2, LOW);

  switchBank1 = SPI.transfer (0); //8
  switchBank2 = SPI.transfer (0); //16
  switchBank3 = SPI.transfer (0); //24
  switchBank4 = SPI.transfer (0); //32
  switchBank5 = SPI.transfer (0); //40
  switchBank6 = SPI.transfer (0); //48  
  
  
  byte mask = 1;
  int sensor = 1;
  for (int i = 1; i <= 8; i++)
  {
    if ((switchBank1 & mask) != (oldSwitchBank1 & mask))
      {
      Serial.print ("Switch ");
      Serial.print (sensor);
      Serial.print (" ");
      Serial.println ((switchBank1 & mask) ? "ir triggered" : "none");
      }  // end of bit has changed
    mask <<= 1; 
    sensor++; 
  }  // end of for each bit
  mask = 1;
  sensor = 9;
  for (int i = 1; i <= 8; i++)
  {
    if ((switchBank2 & mask) != (oldSwitchBank2 & mask))
      {
      Serial.print ("Switch ");
      Serial.print (sensor);
      Serial.print (" ");
      Serial.println ((switchBank2 & mask) ? "ir triggered" : "none");
      
      }  // end of bit has changed
    mask <<= 1; 
    sensor++; 
  }  // end of for each bit
  mask = 1;
  sensor = 17;
  for (int i = 1; i <= 8; i++)
  {
    if ((switchBank3 & mask) != (oldSwitchBank3 & mask))
    {
      Serial.print ("Switch ");
      Serial.print (sensor);
      Serial.print (" ");
      Serial.println ((switchBank3 & mask) ? "ir triggered" : "none");
    }  // end of bit has changed
    mask <<= 1;
    sensor++;  
  }  // end of for each bit
  mask = 1;
  sensor = 25;
  for (int i = 1; i <= 8; i++)
  {
    if ((switchBank4 & mask) != (oldSwitchBank4 & mask))
    {
      Serial.print ("Switch ");
      Serial.print (sensor);
      Serial.print (" ");
      Serial.println ((switchBank4 & mask) ? "ir triggered" : "none");
    }  // end of bit has changed
    mask <<= 1; 
    sensor++; 
  }  // end of for each bit
  mask = 1;
  sensor = 33;
  for (int i = 1; i <= 8; i++)
  {
    if ((switchBank5 & mask) != (oldSwitchBank5 & mask))
    {
      Serial.print ("Switch ");
      Serial.print (sensor);
      Serial.print (" ");
      Serial.println ((switchBank5 & mask) ? "ir triggered" : "none");
    }  // end of bit has changed
    mask <<= 1; 
    sensor++; 
  }  // end of for each bit
  mask = 1;
  sensor = 41;
  for (int i = 1; i <= 8; i++)
  {
    if ((switchBank6 & mask) != (oldSwitchBank6 & mask))
    {
      Serial.print ("Switch ");
      Serial.print (sensor);
      Serial.print (" ");
      Serial.println ((switchBank6 & mask) ? "ir triggered" : "none");
    }  // end of bit has changed
    mask <<= 1;  
    sensor++;
  }  // end of for each bit

  oldSwitchBank1 = switchBank1;
  oldSwitchBank2 = switchBank2;
  oldSwitchBank3 = switchBank3;
  oldSwitchBank4 = switchBank4;
  oldSwitchBank5 = switchBank5;
  oldSwitchBank6 = switchBank6;

  delay (20);   // must be greater than 7.5ms (see notes at top of code)
}  // end of loop
