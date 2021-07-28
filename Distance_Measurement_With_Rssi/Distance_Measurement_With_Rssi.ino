#include <WiFi.h> //ESP32 Core WiFi Library 
#include "SSD1306.h"
#include <stdio.h>
 
SSD1306 display(0x3c, 5, 4);
int VIBRACALL = 2;

void setup() {
  //  Serial.begin(115200);
  pinMode(VIBRACALL, OUTPUT);
  display.init();
  display.clear();
  
  while (WiFi.status() != WL_CONNECTED){
    WiFi.begin("ESP32_ACCESS_POINT");
    delay(3000);
  }
}

void loop() {
  display.clear();
  float rssi = 0;
  //  float a = -30.4;
  //  float n =1.81;
  char buf[10];
  
  for (int i=0; i < 20; i++){   //  Verificar 10 valores de rssi
    rssi += WiFi.RSSI();
    delay(20);
  }
  rssi = rssi/20;   //  Média de rssi

  //  float ratio = (a - rssi)/(10 * n);
  //  float d = pow(10,ratio);
  
  //  Serial.print("RSSI: ");
  //  Serial.println(buf);

  display.setFont(ArialMT_Plain_24);
  
  if (rssi > -65) { 
    display.drawString(0, 0, "PERIGO");
    digitalWrite(VIBRACALL, HIGH);   // turn the VIBRACALL on (HIGH is the voltage level)
  }
  else {
    display.drawString(0, 0, "SEGURO");
    digitalWrite(VIBRACALL, LOW);    // turn the VIBRACALL off by making the voltage LOW
  }
  

  //  gcvt(d, 4, buf);
  
  //  Serial.print("Distancia: ");
  //  Serial.print(buf);
  //  Serial.print(" m");

  //  display.setFont(ArialMT_Plain_16);
  //  display.drawString(0, 30, buf);

  gcvt(rssi, 4, buf);
  strcat(buf, " dBm");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 30, buf);

    //  Calibração
    //  Fórmula + Tecnologia + Ambiente
    
  //  Serial.println("----------------------------------------------------");
 
  display.display();
  delay(10);
}
