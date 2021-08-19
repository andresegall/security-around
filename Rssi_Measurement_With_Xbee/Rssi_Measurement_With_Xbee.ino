#include <SoftwareSerial.h>
#include <stdlib.h>

SoftwareSerial mySerial(2, 3);
String rssiMonitor;
int messagePackage = 0;
int retries = 0;
int noSignalReceived = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Valor de RSSI:");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  delay(10);
  noSignalReceived++;
  
  if(mySerial.available()) { 
    noSignalReceived = 0;
     
    if(messagePackage == 6) {
      int rssi = getRssi();            

      if(rssi < 47 && rssi != 0) {
        turnOnSignal();
      }
      else {
        retryOrTurnOffSignal();
      }
    } 
    else {
      mySerial.read();
    }

    nextPackage();
  }

  if(noSignalReceived == 100) {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

int getRssi() {
  rssiMonitor = mySerial.read();
  Serial.println(rssiMonitor);
  
  char rssiChar[rssiMonitor.length()+1];  //Instanciando array de char
  strcpy(rssiChar, rssiMonitor.c_str());  //Convertendo a string pro array de char
  return atoi(rssiChar);                  //Convertendo o array de char em int
}

void turnOnSignal() {
  digitalWrite(LED_BUILTIN, HIGH);
  retries = 0;
}

void retryOrTurnOffSignal() {
  if(retries < 5) {
    retries++;
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void nextPackage() {
  messagePackage == 10 ? messagePackage = 0 : messagePackage++;
}
