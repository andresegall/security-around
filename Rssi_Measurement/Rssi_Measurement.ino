#include <WiFi.h> //ESP32 Core WiFi Library 
  
void setup() {
  Serial.begin(115200);
}

void loop() {
  byte available_networks = WiFi.scanNetworks(); //escaneia as redes

  for (int network = 0; network < available_networks; network++) {
    Serial.print(WiFi.SSID(network));
    Serial.print(" | ");
    Serial.print(WiFi.RSSI(network));
    Serial.println(" dBm");
  }
  
  Serial.println("----------------------------------------------------");
}
