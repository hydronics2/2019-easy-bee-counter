/*
 * WARNING: this code turns LEDs on for a long time (1 second). 
 * This is fine if the resistors are installed and the jumpers are NOT made 
 * 
 * 
 * 
 * 
*/

//Pins Feather ESP32
const byte powerGates1 = 15;
const byte powerGates2 = 33;

//Pins ItsyBitsy
//const byte powerGates1 = 10;
//const byte powerGates2 = 11;

void setup ()
{
  Serial.begin (115200);
  Serial.println ("Begin switch test.");

  pinMode (powerGates1, OUTPUT);
  digitalWrite(powerGates1, LOW);
  pinMode (powerGates2, OUTPUT);
  digitalWrite(powerGates2, LOW);
}

// 
void loop() {
  digitalWrite(powerGates1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(powerGates2, HIGH);
  delay(1000);                       // wait for a second
  digitalWrite(powerGates1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(powerGates2, LOW);
  delay(1000);                       // wait for a second
}
