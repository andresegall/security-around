#include <WiFi.h> //ESP32 Core WiFi Library 
#include "SSD1306.h"
#include <stdio.h>

SSD1306 display(0x3c, 5, 4);
int VIBRACALL = 2;
int intermittencyTime = 0;

void setup() {
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
  display.setFont(ArialMT_Plain_24);
  float rssi = 0;
  char buf[10];
  
  for (int i=0; i < 20; i++) {   //  Verificar 20 valores de rssi
    rssi += WiFi.RSSI();
    delay(10);
  }
  rssi = rssi/20;   //  Média de rssi

  if (rssi > -65) {
    display.drawString(0, 0, "PERIGO");
    digitalWrite(VIBRACALL, HIGH);
    intermittencyTime = 0;
  }

  else if (rssi > -90) {
    display.drawString(0, 0, "RISCO");

    if (intermittencyTime < 5) {
      digitalWrite(VIBRACALL, HIGH);
    }

    else {
      digitalWrite(VIBRACALL, LOW);
    }

    intermittencyTime++;

    if (intermittencyTime == 10) {
      intermittencyTime = 0;
    }
  }

  else {
    display.drawString(0, 0, "SEGURO");
    digitalWrite(VIBRACALL, LOW);
  }
}
