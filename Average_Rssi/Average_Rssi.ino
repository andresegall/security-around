#include <WiFi.h>   //ESP32 Core WiFi Library 

float media_max = -200;
float media_min = 0;
float media = 0;
float count = 1;
  
void setup() {
  Serial.begin(115200);
  
  while (WiFi.status() != WL_CONNECTED){    //Conecta ao AP
    WiFi.begin("ESP32_ACCESS_POINT");
    delay(3000);
  }
}

void loop() {
  int atual = 0;
  
  for (int i=0; i < 20; i++){   // Realiza 20 medições de rssi
    atual += WiFi.RSSI();
    delay(20);
  }

  if((atual/20)>media_max) {
    media_max = atual/20;   // Armazena o maior valor registrado
  }

  if((atual/20)<media_min) {
    media_min = atual/20;   // Armazena o menor valor registrado
  }

  media = (media+(atual/20));   // Soma o valor atual à média
  
  Serial.print("Max.: ");
  Serial.println(media_max);
  Serial.print("Min.: ");
  Serial.println(media_min);
  Serial.print("Atual: ");
  Serial.println(atual/20);
  Serial.print("Media: ");
  Serial.println(media/count);    // Imprime a média
  Serial.print("Medicoes: ");
  Serial.println(count);
  Serial.println("----------------------------------------------------");

  count = count + 1;
}
