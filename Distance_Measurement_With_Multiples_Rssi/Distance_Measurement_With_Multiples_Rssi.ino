#include <WiFi.h> //ESP32 Core WiFi Library 
#include "SSD1306.h"

SSD1306 display(0x3c, 5, 4);
  
void setup() {
  Serial.begin(115200);
  display.init();
  display.clear();
}

void loop() {
  byte available_networks = WiFi.scanNetworks(); //escaneia as redes
  display.clear();

  for (int network = 0; network < available_networks; network++) {
    if(WiFi.SSID(network) == "ESP32_ACCESS_POINT") {
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 0, "PERIGO");
      
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 30, "Empilhadeira 01");
    }
    
    if(WiFi.SSID(network) == "Zhone_4D23") {
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 0, "PERIGO");
      
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 30, "Empilhadeira 02");
    }
  }

  display.display();
  
  Serial.println("----------------------------------------------------");
}
