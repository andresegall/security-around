#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include "SSD1306.h"

const int CUTOFF = -45;
SSD1306 display(0x3c, 5, 4);

void setup() {
  BLEDevice::init("");
  display.init();
  display.clear();
}

void loop() {
  display.clear();
  
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(1);
  int best = CUTOFF;
  
  for (int i = 0; i < results.getCount(); i++) {
    BLEAdvertisedDevice device = results.getDevice(i);
    int rssi = device.getRSSI();
    if (rssi > best) {
      best = rssi;
    }
  }

  display.setFont(ArialMT_Plain_24);
  
  if (best > CUTOFF) {
    display.drawString(0, 0, "PERIGO");
  }
  
  else {
    display.drawString(0, 0, "SEGURO");
  }

  char buf[10];
  float displayRssi;
  gcvt(displayRssi, 4, buf);
  strcat(buf, " dBm");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 30, buf);
  
  display.display();
}
