#include <WiFi.h> //ESP32 Core WiFi Library 
#include "SSD1306.h"

#define FORKLIFTS 2

SSD1306 display(0x3c, 5, 4);
char *forkLiftSsids[FORKLIFTS] = {"ESP32_ACCESS_POINT", "Segall"};
  
void setup() {
  display.init();
  display.clear();
}

void loop() {
  int forkLifts = 0;

  for (int network = 0; network < FORKLIFTS; network++) {
    WiFi.begin(forkLiftSsids[network]);
    delay(3000);

    if ((WiFi.status() == WL_CONNECTED) && (WiFi.RSSI() > -45)) {
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
