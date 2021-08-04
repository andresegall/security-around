#include <WiFi.h> //ESP32 Core WiFi Library
#include "SSD1306.h"
#include <stdio.h>

SSD1306 display(0x3c, 5, 4);
int VIBRACALL = 2;
char contadorRisco = 0;
char contadorAtencao = 0;

void setup() {
  pinMode(VIBRACALL, OUTPUT);
  display.init();
  display.clear();

  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin("ESP32_ACCESS_POINT");
    delay(3000);
  }
}

void loop() {
  display.clear();
  display.setFont(ArialMT_Plain_24);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(VIBRACALL, LOW);
    display.drawString(0, 0, "CONECTANDO");
    display.display();
    WiFi.begin("ESP32_ACCESS_POINT");
    delay(3000);
  }

  float rssi = 0;
  char buf[10];

  for (int i=0; i < 20; i++) { // Verificar 10 valores de rssi
    rssi += WiFi.RSSI();
    delay(10);
  }
  rssi = rssi/20; // Média de rssi

  if (rssi > -70) {
    display.drawString(0, 0, "PERIGO");
    digitalWrite(VIBRACALL, HIGH);

    contadorAtencao = 0;
    contadorRisco = 0;
  }
  else if (rssi > -85) {
    display.drawString(0, 0, "RISCO");

    if (contadorRisco < 5) {         
      digitalWrite(VIBRACALL, HIGH);
    }
    else {
      digitalWrite(VIBRACALL, LOW);

      if(contadorRisco == 9) {
        contadorRisco = 0;
      }
    }

    contadorAtencao = 0;
    contadorRisco++;
  }
  else if (rssi > -100) {
    display.drawString(0, 0, "ATENCAO");

    if(contadorAtencao < 10) {
      digitalWrite(VIBRACALL, HIGH);
    }
    else {
      digitalWrite(VIBRACALL, LOW);

      if(contadorAtencao == 20) {
        contadorAtencao = 0;
      }
    }
        
    contadorRisco = 0;
    contadorAtencao++;
  }
  else {
    display.drawString(0, 0, "SEGURO");
    digitalWrite(VIBRACALL, LOW);
  }

  gcvt(rssi, 4, buf);
  strcat(buf, " dBm");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 30, buf);
  display.display();
  delay(10);
}
