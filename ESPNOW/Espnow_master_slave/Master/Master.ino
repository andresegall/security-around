#include <ESP8266WiFi.h>
#include <espnow.h>
//**************************** config AP SSID  ********************************
void configDeviceAP() {
  String Prefix = "NOW";
  String Mac = WiFi.macAddress();
  String SSID = Prefix;
  String Password = "123456789";
  bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
  }
}
//*******************************************************************************
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println("ESPNow/Multi-Slave/Master Example");
  configDeviceAP();
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
}
void loop() {}
