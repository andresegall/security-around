#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <Arduino.h>
#include "SSD1306.h"

SSD1306 display(0x3c, 5, 4);
int retries = 0;
const char *forkLiftNames = "RDL51822";

void setup() {
  BLEDevice::init("ESP32-BLE");
  display.init();
  display.clear();
}

void loop() {
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(1);

  int forklifts = 0;
  int rssi = -200;
  
  for (int i = 0; i < results.getCount(); i++) {
    BLEAdvertisedDevice device = results.getDevice(i);
    const char *deviceName = device.getName().c_str();
    int localRssi = device.getRSSI();;
    
    if (strstr(forkLiftNames, deviceName) != NULL) {
      retries = 0;
      forklifts++;

      if (localRssi > rssi) {
        rssi = localRssi; 
      }
    }
  }

  if (forklifts == 0) {
    retries++;

    if (retries > 5) {
      display.clear();
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 0, "NÃO CONECTADO");
    }
  }
  else {
    display.clear();
    display.setFont(ArialMT_Plain_16);
    
    if(rssi > - 40) {
      display.drawString(0, 0, "PERIGO");
    }
    else {
      display.drawString(0, 0, "SEGURO");
    }
    
    char dbm[5];
    gcvt(rssi, 4, dbm);
    strcat(dbm, " dBm");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 25, dbm);
  }

  display.display();
}
