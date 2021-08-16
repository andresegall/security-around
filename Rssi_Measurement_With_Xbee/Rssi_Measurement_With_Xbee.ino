#include <SoftwareSerial.h>
#include <stdlib.h>

SoftwareSerial mySerial(2, 3);
String rssiMonitor;
int count = 0;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("End-point");
  Serial.println("Valor de RSSI:");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (mySerial.available())
  { 
    if(count == 6)
    {
      delay(10);
      rssiMonitor = mySerial.read();
      Serial.println(rssiMonitor);

      char rssiChar[rssiMonitor.length()+1];//Instanciando array de char
      strcpy(rssiChar, rssiMonitor.c_str());//Convertendo a string pro array de char
      int rssi = atoi(rssiChar);            //Convertendo o array de char em int

      if(rssi < 37 && rssi != 0)
      {
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else
      {
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
    else
    {
      mySerial.read();
    }

    if(count == 10)
    {
      count = 0;
    }
    else
    {
      count++;
    }
  }
}
