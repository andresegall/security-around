#include "SSD1306.h"
 
SSD1306 display(0x3c, 5, 4);
 
void setup() {
Serial.begin(115200);
display.init();
display.clear();
}
 
void loop() 
{ 
display.setFont(ArialMT_Plain_24);
display.drawString(0, 0, "Usinainfo");
 
display.setFont(ArialMT_Plain_16);
display.drawString(0, 30, "ESP32 OLED");
 
display.setFont(ArialMT_Plain_10);
display.drawString(0, 50, "www.www.usinainfo.com.br/blog/");
 
display.display();
delay(10);
}
