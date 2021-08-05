/*
 XbeeRSSI.pde

 This is a sketch for RSSI-Measurements. The sketch reads the incoming RSSI Value and turns on a LED if the Signal is strong enough. 
 Please note that the used Value (40) depends on your project environement.

 ATTENTION!!!
 ---------------------------------------------
 YOU HAVE TO USE AN ARDUINO WITH AT LEAST TWO SERIAL PORTS!
 I am using an Arduino MEGA!
 Connect your Xbee RX to Arduino RX!
 Connect your Xbee TX to Arduino TX!
 And don't forget the power supply!
 RSSI Pin on Xbee -> 6
 ---------------------------------------------


 Author: Cédric Portmann (cedric.portmann@gmail.com.)
 Copyright (C) 2013 Cédric Portmann
*/

int digitalPin = 10;  // the RSSI pin 6 of Xbee is connected to this PWM Pin. (Digital Pin 10)
int rssiDur;  // Variable for RSSI
// int led = 13;  // LED connected to Pin 13

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(digitalPin, INPUT);
 
  // Serial.begin(9600);   // this is the connection for your Arduino to your PC/MAC
  Serial.begin(9600);   // this is the connection of your Xbee to your Arduino MEGA!!
}

void loop()
{
  if(Serial.available() >= 21) {    // This isn't important. You can do here whatever you want.
            
    if(Serial.read() == 0x7E) {  // Reads the start byte
      for(int i = 1; i < 19; i++) {
        byte discardByte = Serial.read();
        
        rssiDur = pulseIn(digitalPin, LOW, 200); // get's the RSSI Value
        Serial.println(rssiDur);  //for debbuging and first setup.
        
        if(rssiDur < 40 && rssiDur != 0){  //turns Led on if RSSI is less then 40
          digitalWrite(LED_BUILTIN, HIGH); 
        }
        
        if(rssiDur > 40 && rssiDur != 0){ //turns Led off if RSSI is bigger then 40
          digitalWrite(LED_BUILTIN, LOW); 
        }
      }
    }
  }
}
