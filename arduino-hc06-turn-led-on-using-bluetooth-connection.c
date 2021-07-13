// Carrega a biblioteca SoftwareSerial
#include <SoftwareSerial.h>

SoftwareSerial hc06(2,3);
int led = 13;
char buf;

void setup(){
  //Initialize Serial Monitor
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  //Initialize Bluetooth Serial Port
  hc06.begin(9600);

  delay(1000);
}

void loop(){
  Serial.println("Conectado...");
  hc06.println("Conectado...");
  
  int watchDogCounter = 0;
  
  while(hc06.available() > 0){
    buf = hc06.read();
    
    // Caracter L para ligar o led
    Serial.println(buf);
    if (buf == 'L')
      digitalWrite(13, HIGH);

    // Caracter D para desligar o led
    if (buf == 'D')
      digitalWrite(13, LOW);

    // Se ficar mais de 5 segundos no loop, sai automaticamente
    delay(100);
    watchDogCounter++;
    if (watchDogCounter > 50)
      break;
  }

  delay(2000);
}