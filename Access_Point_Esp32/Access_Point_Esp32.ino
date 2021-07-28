#include <WiFi.h> //ESP32 Core WiFi Library 
#include "SSD1306.h"

SSD1306 display(0x3c, 5, 4);

void setup() {
  WiFi.softAP("ESP32_ACCESS_POINT");    // Configurando o Access Point com o SSID
  display.init();
  display.clear();
}

void loop() {
  display.clear();

  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Access Point");
 
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 30, "Empilhadeira 01");

  display.display();
}
