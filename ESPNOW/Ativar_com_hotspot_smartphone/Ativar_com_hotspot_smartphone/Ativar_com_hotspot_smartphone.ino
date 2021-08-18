
#if defined(ESP8266)
#include <ESP8266WiFi.h>  //ESP8266 Core WiFi Library  
#else
#include <WiFi.h>      //ESP32 Core WiFi Library   
#endif

//Name of the wifi network whom we are supposed to track
//nome da rede Wifi que o ESP irá buscar
const char* SSID = "MDKAUT_PESSOAL";


#define RELAY_ON   HIGH
#define RELAY_OFF  LOW    

// Relay pin number
//pino do RELAY
#define RELAY   2
//dB minimo para identificar a rede
#define MINdB  -100


//   PROCURA REDE
int32_t getRSSI(const char* target_ssid) {
  byte available_networks = WiFi.scanNetworks(); //escaneia as redes

  for (int network = 0; network < available_networks; network++) {
    if (WiFi.SSID(network).compareTo(target_ssid) == 0) { //compara se alguma das redes encontradas é a que desejamos  
      return WiFi.RSSI(network); //retorna o SSID da rede
    }
  }
  return 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT); //  Initialize the relay pin as an output.
  
}

void loop() {
  int32_t rssi = getRSSI(SSID); //busca o RSSI da rede desejada 

  // For debugging purpose only
  Serial.print("Signal strength: ");
  Serial.print(rssi);
  Serial.println("dBm");

  //se o RSSI for maior que o mínimo desejado e o RSSI é diferente de zero (ou seja, encontramos a rede desejada) 
  if (rssi > (MINdB) && rssi != 0) 
  {
    digitalWrite(RELAY, RELAY_OFF); //desliga o relé
    Serial.println("INSEGURO");
  }
  else 
  {
    digitalWrite(RELAY, RELAY_ON); //liga o relé
    Serial.println("SEGURO");
  }
}
