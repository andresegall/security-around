#include <WiFi.h> //ESP32 Core WiFi Library 
#include "SSD1306.h"

SSD1306 display(0x3c, 5, 4);
char *forkLiftSsids = "ESP32_ACCESS_POINT Zhone_4D23 Segall";
  
void setup() {
  display.init();
  display.clear();
}

void loop() {
  byte available_networks = WiFi.scanNetworks(); //escaneia as redes
  int forkLifts = 0;

  for (int network = 0; network < available_networks; network++) {
    char ssid[sizeof(WiFi.SSID(network))];

    for(int i=0; i<sizeof(WiFi.SSID(network)); i++) {
      ssid[i] = WiFi.SSID(network)[i];
    }
    
    if((strstr(forkLiftSsids, ssid) != NULL) && (WiFi.RSSI(network) > -45)) {
      display.clear();
      forkLifts++;

      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 0, "PERIGO");

      char number[99];
      itoa(forkLifts, number, 10);
      
      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 30, number);
      display.display();
    }
  }

  if(forkLifts == 0) {
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "SEGURO");
    display.display();
  }
}
