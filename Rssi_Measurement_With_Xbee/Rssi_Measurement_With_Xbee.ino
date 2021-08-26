#include <SoftwareSerial.h>
#include <stdlib.h>

SoftwareSerial mySerial(2, 3);
String rssiMonitor;
int messagePackage = 0;
int retries = 0;
int noSignalReceived = 0;
int contadorRisco = 0;

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

      if(rssi <= 53 && rssi != 0) {
        if (rssi < 48) {
          digitalWrite(LED_BUILTIN, HIGH);   
          contadorRisco = 0;
        }
        else {
          if (contadorRisco < 5) {         
            digitalWrite(LED_BUILTIN, HIGH);
          }
          else {
            digitalWrite(LED_BUILTIN, LOW);

            if(contadorRisco == 9) {
                contadorRisco = 0;
            }
          }
        contadorRisco++;
        }
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
